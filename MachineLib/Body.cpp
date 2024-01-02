/**
 * @file Body.cpp
 * @author djmik
 */

#include "pch.h"
#include "Body.h"
#include "PhysicsPolygon.h"
#include "Machine.h"
#include "RotationSink.h"

/**
 * Body Constructor
 *
 * Creates attached rotation sink pointer
 */
Body::Body() : Component()
{
    mSink = std::make_shared<RotationSink>(this);
}

/**
 * Updates Body object
 * If the body is a kinematic body, update its rotational velocity
 * @param elapsed time since last update call
 */
void Body::Update(double elapsed)
{
    auto body = mBody.GetBody();
    if((body != nullptr) && (body->GetType() == b2_kinematicBody))
    {
        double time = GetMachine()->GetCurrentTime();
        double rotation = mSink->GetRotation();
        double speed = (time > 0) ? -rotation/time : 0;
        mBody.SetAngularVelocity(-speed);
    }
}

/**
 * Draws current body object
 * @param graphics graphics context
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mBody.Draw(graphics);
}

/**
 * Adds a point to attatched body polygon
 * @param x x location of point
 * @param y y location of point
 */
void Body::AddPoint(int x, int y)
{
    mBody.AddPoint(x,y);
}

/**
 * Set image of body
 * @param imageDir image directory
 */
void Body::SetImage(const std::wstring &imageDir)
{
    mBody.SetImage(imageDir);
}

/**
 * Set initial position of body for rotation purposes
 * @param x x initial position
 * @param y y initial position
 */
void Body::SetInitialPosition(int x, int y)
{
    mInitialPosition = wxPoint2DDouble(x,y);
    mBody.SetInitialPosition(x,y);
}

/**
 * Set position of body component
 * @param x x position
 * @param y y position
 */
void Body::SetPosition(int x, int y)
{
    Component::SetPosition(x, y);
    SetInitialPosition(x,y);
}

/**
 * Set machine that owns this body
 * @param machine parent machine
 */
void Body::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
    mBody.InstallPhysics(machine->GetWorld());
}

/**
 * Reset body back to its initial state
 */
void Body::Reset()
{
    Component::Reset();
    SetPosition(mInitialPosition.m_x, mInitialPosition.m_y);
}

/**
 * Set body shape to be a rectangle
 * @param x x position
 * @param y y position
 * @param width rectangle width
 * @param height rectangle height
 */
void Body::Rectangle(double x, double y, double width, double height)
{
    mBody.Rectangle(x,y,width,height);
}

/**
 * Sets body shape to be a cirle
 * @param radius radius of circle
 */
void Body::Circle(double radius)
{
    mBody.Circle(radius);
}





