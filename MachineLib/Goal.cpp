/**
 * @file Goal.cpp
 * @author djmik
 */

#include "pch.h"
#include <b2_contact.h>
#include "Goal.h"
#include "Machine.h"
#include "ContactListener.h"
#include <sstream>
#include <iomanip>

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);


/// Image to draw for the goal
const std::wstring &goalImage = L"/goal.png";

/**
 * constructor
 *
 * Sets the image for the goal
 * sets shaps for all goal polygons
 * @param imagesDir
 */
Goal::Goal(const std::wstring &imagesDir) : Component()
{
    mGoalImage.SetImage(imagesDir+goalImage);
    mGoalImage.BottomCenteredRectangle(GoalSize);

    mGoal.BottomCenteredRectangle(TargetSize);
    mPost.BottomCenteredRectangle(PostSize);

}

/**
 * draws goal component and scoreboard
 * @param graphics graphics context
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPoint2DDouble position = GetPosition();
    mGoalImage.DrawPolygon(graphics,position.m_x, position.m_y,0);

    double x = ScoreboardRectangle.m_x + position.m_x;
    double y = ScoreboardRectangle.m_y + position.m_y;

    wxPen pen = wxPen();
    pen.SetColour(*wxBLACK);
    pen.SetWidth(ScoreboarderLineWidth);
    wxBrush brush = wxBrush();
    brush.SetColour(ScoreboardBackgroundColor);

    graphics->SetPen(pen);
    graphics->SetBrush(brush);
    graphics->DrawRectangle(x, y, ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);

    wxFont coordFont(wxSize(0, ScoreboardFontSize),
                     wxFONTFAMILY_SWISS,
                     wxFONTSTYLE_NORMAL,
                     wxFONTWEIGHT_NORMAL);

    graphics->SetFont(coordFont, *wxWHITE);

    std::stringstream str;
    str << std::setfill('0') << std::setw(2) << mScore;

    x += ScoreboardTextLocation.m_x-ScoreboardRectangle.m_x;
    y += ScoreboardTextLocation.m_y-ScoreboardRectangle.m_y+3;
    graphics->PushState();
    graphics->Translate(x,y);
    graphics->Scale(1, -1);
    graphics->DrawText(str.str(),0,0);
    graphics->PopState();

}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact* contact)
{
    mScore += 2;
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    contact->SetEnabled(false);
}

/**
 * Update goal object (doesnt really do anything)
 * @param elapsed time since last update call
 */
void Goal::Update(double elapsed)
{

}

/**
 * Sets position of goal
 * @param x x position
 * @param y y position
 */
void Goal::SetPosition(int x, int y)
{
    Component::SetPosition(x, y);
    mGoal.SetInitialPosition(x+GoalPosition.m_x,y+GoalPosition.m_y);
    mPost.SetInitialPosition(x+PostPosition.m_x,y+PostPosition.m_y);

}

/**
 * Sets the parent machine of this component
 * adds physics to necessary polygons
 * @param machine new parent machine
 */
void Goal::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);

    mGoal.InstallPhysics(machine->GetWorld());
    mPost.InstallPhysics(machine->GetWorld());
    machine->GetContactListener()->Add(mGoal.GetBody(), this);
}

/**
 * Resets the goal to its base state
 * resets points to 0
 */
void Goal::Reset()
{
    Component::Reset();
    mScore = 0;
}


