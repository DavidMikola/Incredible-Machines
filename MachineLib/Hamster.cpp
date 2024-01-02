/**
 * @file Hamster.cpp
 * @author djmik
 */

#include "pch.h"
#include <b2_contact.h>
#include "Hamster.h"
#include "Machine.h"
#include "ContactListener.h"


/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};


/**
 * Constructor
 * Establishes Polygons and any other intial settings/variables not defined in header
 * @param imagesDir
 */
Hamster::Hamster(const std::wstring &imagesDir): Component()
{
    //hamster images same size as wheel.  Use same position
    for (int i = 0; i < 4; i++) {
        mHamsters[i].CenteredSquare(HamsterWheelSize);
        mHamsters[i].SetImage(imagesDir + HamsterImages[i]);
    }
    mWheel.SetImage(imagesDir + HamsterWheelImage);
    mCage.SetImage(imagesDir+HamsterCageImage);
    mWheel.Circle(HamsterWheelSize/2);
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mSource = std::make_shared<RotationSource>(this);
}

/**
 * Sets hamster to be initially running or not
 * @param running true if running at start
 */
void Hamster::SetInitiallyRunning(bool running)
{
    mIsRunning = running;
}

/**
 * Sets speed of hamster when running
 * @param speed new speed of hamster
 */
void Hamster::SetSpeed(double speed)
{
    mSpeed = speed;
}

/**
 *  tells hamster to start running when a body comes in contact
 * @param contact contact event
 */
void Hamster::BeginContact(b2Contact *contact)
{
    // Turn hamster rotation on
    mIsRunning = true;
}

/**
 * draws the hamster
 * @param graphics sets specific hamster graphic
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    double rotation = mSource->GetRotation();
    int hamsterIndex;
    if (mSpeed == 0.0)
    {
        hamsterIndex = 0;
    }
    else
    {
        double angle = fabs(fmod(HamsterSpeed * rotation, 1));
        if (angle < 0.25)
        {
            hamsterIndex = 1;
        }
        else if ((angle > 0.5) && (angle < 0.75))
        {
            hamsterIndex = 3;
        }
        else
        {
            hamsterIndex = 2;
        }
    }

    mCage.Draw(graphics);

    graphics->PushState();
    graphics->Translate(GetPosition().m_x + WheelCenter.m_x, GetPosition().m_y + WheelCenter.m_y);

    mWheel.DrawPolygon(graphics, 0, 0, rotation);

    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }

    // Draw the running image
    if (mIsRunning) {
        mHamsters[hamsterIndex].DrawPolygon(graphics, 0, 0, 0);
    } else {
        mHamsters[0].DrawPolygon(graphics, 0, 0, 0);
    }

    graphics->PopState();
}

/**
 * Sets the rotation of the attatched rotation source object
 * @param rotation rotation of source
 */
void Hamster::SetRotation(double rotation)
{
    mSource->SetRotation(rotation);
}

/**
 * Updates the hamster's rotation if it is running
 * @param elapsed time since last update call
 */
void Hamster::Update(double elapsed)
{
    // Update the rotation of our source
    double rotation = mSource->GetRotation();
    rotation += -mSpeed * elapsed;
    if (mIsRunning) {
        mSource->SetRotation(rotation);
    }


}

/**
 * Sets the position of the hamster
 * @param x x position
 * @param y y position
 */
void Hamster::SetPosition(int x, int y)
{
    Component::SetPosition(x, y);
    mCage.SetInitialPosition(x,y);

}

/**
 * Gets the shaft position of the hamster
 * @return position of hamster's pully axel
 */
wxPoint2DDouble Hamster::GetShaftPosition()
{
    return GetPosition() + HamsterShaftOffset;

}

/**
 * Sets the parent machine that owns this hamster
 * adds physics to necessary polygon
 * @param machine new parent machine
 */
void Hamster::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
    mCage.InstallPhysics(machine->GetWorld());
    machine->GetContactListener()->Add(mCage.GetBody(), this);
}

/**
 * Resets the hamster to its initial state
 * sets the rotation to 0
 */
void Hamster::Reset()
{
    mSource->SetRotation(0);
}