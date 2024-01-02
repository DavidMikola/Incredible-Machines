/**
 * @file Hamster.h
 * @author djmik
 *
 * Hamster component header file
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H

#include <b2_world_callbacks.h>
#include "Component.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"
#include "RotationSource.h"

/**
 * Hamster component class
 *
 * hamster runs at a set speed
 * if it is not running at start, will start running when a body comes in contact with it
 * outputs a set speed to connected pulleys
 */
class Hamster : public Component, public b2ContactListener
{
private:
    /// Speed at which hamster is running
    double mSpeed = 1;

    /// Whether or not the Hamster will be actually running (true if running)
    bool mIsRunning = false;

    /// Array containing different polygons for each hamster image
    cse335::Polygon mHamsters[4];

    /// Polygon for the hamster wheel
    cse335::Polygon mWheel;

    /// Physics Polygon for hamster cage.  Handles collisions to start hamster if not already moving
    cse335::PhysicsPolygon mCage;

    /// We are a rotation source
    std::shared_ptr<RotationSource> mSource;

public:

    /// Constructor
    Hamster(const std::wstring& imagesDir);

    void SetInitiallyRunning(bool running);

    void SetPosition(int x, int y) override;

    void SetSpeed(double speed);

    void BeginContact(b2Contact* contact) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetRotation(double rotation);

    void Update(double elapsed) override;

    void SetMachine(Machine * machine) override;

    void Reset() override;

    /**
     * Get the rotation source attached to this hamster
     * @return current rotation source
     */
    std::shared_ptr<RotationSource> GetSource() { return mSource; }

    wxPoint2DDouble GetShaftPosition();


};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
