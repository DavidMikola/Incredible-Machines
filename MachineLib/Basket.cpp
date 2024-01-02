/**
 * @file Basket.cpp
 * @author djmik
 */

#include "pch.h"
#include "Basket.h"
#include "Machine.h"
#include "ContactListener.h"
#include <b2_world_callbacks.h>
#include <b2_contact.h>

/// The size of the basket in centimeters
const double BasketSize = 40;

/// Delay between when the ball hits the basket
/// and when it is shot out
const double BasketDelay = 1.0;

/// Basket Image Name
const std::wstring BasketName = L"/basket.png";

/**
 * constructor
 *
 * Establishes image file for basket
 * creates physics polygons to create basket shape/hold objects
 * @param imagesDir directory for basket image
 */
Basket::Basket(const std::wstring &imagesDir)
{
    mBasketImage.SetImage(imagesDir+BasketName);
    mBasketImage.BottomCenteredRectangle(BasketSize, BasketSize);
    mLauncher.BottomCenteredRectangle(BasketSize, BasketSize/5);
    mLeftWall.BottomCenteredRectangle(BasketSize/10, (4*BasketSize/5));
    mRightWall.BottomCenteredRectangle(BasketSize/10, (4*BasketSize/5));

    mTimer = BasketDelay;
}

/**
 * Draws basket
 * @param graphics graphics context
 */
void Basket::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPoint2DDouble pos = GetPosition();
    mBasketImage.DrawPolygon(graphics, pos.m_x, pos.m_y, 0);

    //mLauncher.Draw(graphics);
    //mRightWall.Draw(graphics);
    //mLeftWall.Draw(graphics);
}

/**
 * Updates timer on basket
 * if timer is 0, item will be launched
 * @param elapsed time since last update call
 */
void Basket::Update(double elapsed)
{
    if(mIsCounting) {
        mTimer-=elapsed;
        if (mTimer <= 0) {
            auto contact = mLauncher.GetBody()->GetContactList();
            while(contact != nullptr)
            {
                if(contact->contact->IsTouching())
                {
                    contact->other->SetLinearVelocity(mDirection);
                }

                contact = contact->next;
            }
            Reset();
        }
    }
}

/**
 * Sets the machine this component belongs to. Installs physics into polygons
 * @param machine new parent machine
 */
void Basket::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
    mLeftWall.InstallPhysics(machine->GetWorld());
    mRightWall.InstallPhysics(machine->GetWorld());
    mLauncher.InstallPhysics(machine->GetWorld());
    machine->GetContactListener()->Add(mLauncher.GetBody(), this);
}

/**
 * Set Position of basket and all corresponding images/polygons
 * @param x new x position
 * @param y new y position
 */
void Basket::SetPosition(int x, int y)
{
    Component::SetPosition(x, y);
    mLauncher.SetInitialPosition(x,y);
    mLeftWall.SetInitialPosition(x-(9*BasketSize/20), y+(BasketSize/5));
    mRightWall.SetInitialPosition(x+(9*BasketSize/20), y+(BasketSize/5));

}

/**
 * Resets basket back to its initial, non-counting state
 */
void Basket::Reset()
{
    Component::Reset();
    mIsCounting = false;
    mTimer = BasketDelay;
}

/**
 * Start counting when an object comes into contact with the basket
 * @param contact contact event
 */
void Basket::BeginContact(b2Contact *contact)
{
    b2ContactListener::BeginContact(contact);
    mIsCounting = true;
}
