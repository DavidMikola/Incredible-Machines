/**
 * @file Conveyor.cpp
 * @author djmik
 */

#include "pch.h"
#include "Conveyor.h"
#include "RotationSink.h"
#include "Machine.h"
#include "ContactListener.h"
#include <b2_world_callbacks.h>
#include <b2_contact.h>

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * constructor
 *
 * Apply images to physics polygon
 * create an attached rotation sink
 * @param imagesDir image directory
 */
Conveyor::Conveyor(const std::wstring& imagesDir): Component()
{
    mSink = std::make_shared<RotationSink>(this);
    mConveyor.BottomCenteredRectangle(ConveyorSize);
    mConveyor.SetImage(imagesDir+ConveyorImageName);
}

/**
 * Draw conveyor polygon image
 * @param graphics graphics context
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mConveyor.Draw(graphics);
}

/**
 * adds the speed to the touching object
 * @param contact contact event
 * @param oldManifold manifold
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    b2ContactListener::PreSolve(contact, oldManifold);
    contact->SetTangentSpeed(mSpeed);
}

/**
 * Updates the conveyoy speed and applies speed to touching objects
 * @param elapsed time since last update
 */
void Conveyor::Update(double elapsed)
{
    // TODO REDEFINE MSPEED
    double time = GetMachine()->GetCurrentTime();
    double rotation = mSink->GetRotation();
    mSpeed = (time > 0) ? -rotation/time : 0;

    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(mSpeed, 0));
        }

        contact = contact->next;
    }
}

/**
 * Sets position of the conveyor belt
 * @param x x position
 * @param y y position
 */
void Conveyor::SetPosition(int x, int y)
{
    Component::SetPosition(x, y);
    mConveyor.SetInitialPosition(x,y);
}

/**
 * Gets the shaft position of the conveyor belt
 * @return position point
 */
wxPoint2DDouble Conveyor::GetShaftPosition()
{
    return GetPosition() + ConveyorShaftOffset;
}

/**
 * Sets new machine this conveyor belongs to
 * @param machine parent machine
 */
void Conveyor::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
    mConveyor.InstallPhysics(machine->GetWorld());
    machine->GetContactListener()->Add(mConveyor.GetBody(), this);
}

