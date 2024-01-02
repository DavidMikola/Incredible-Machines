/**
 * @file Machine.cpp
 * @author djmik
 */

#include "pch.h"
#include "Component.h"
#include "Machine.h"
#include "b2_world.h"
#include "ContactListener.h"

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * constructor
 *
 * everything needed to do in constructor is also in reset, so just calls reset
 */
Machine::Machine() {
    Reset();
}

/**
 * Adds a component to the machine
 * sets a component's machine field
 * @param component component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}

/**
 * Draws a machine and all attached components
 * @param graphics graphics context
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!mComponents.empty()){
        for (const auto component: mComponents) {
            component->Draw(graphics);
        }
    } else {

    }

}

/**
 * Update the machine and all attached components
 * @param elapsed time since last update call
 */
void Machine::Update(double elapsed)
{
    // Call Update on all of our components so they can advance in time

    for(auto component: mComponents) {
        component->Update(elapsed);
    }

    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Reset machine to its initial state
 * Sets gravity
 * Creates new contact listener and sets it
 * Resets each component
 * reset time to 0
 */
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    for(auto component: mComponents) {
        component->Reset();
        component->SetMachine(this);
    }

    mCurrentTime = 0;
}

