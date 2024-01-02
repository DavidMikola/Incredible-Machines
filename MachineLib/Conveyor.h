/**
 * @file Conveyor.h
 * @author djmik
 *
 * header file for conveyor class
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

#include <b2_world_callbacks.h>
#include "Component.h"
#include "PhysicsPolygon.h"

class RotationSink;

/**
 * Conveyor component class
 *
 * Component capable moving bodies
 * bodies on top of the conveyor will have speed applied to them based on their component sink
 */
class Conveyor : public Component, public b2ContactListener
{
private:
    /// Indicates if we are moving or not
    bool mIsMoving = false;

    /// The conveyor belt
    cse335::PhysicsPolygon mConveyor;

    /// We are a rotation sink
    std::shared_ptr<RotationSink> mSink;

    /// Speed of conveyor belt
    double mSpeed = 5;
public:
    Conveyor(const std::wstring& imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    void Update(double elapsed) override;

    void SetPosition(int x, int y) override;

    void SetMachine(Machine * machine) override;

    /**
     * Get the rotation sink attached to this object
     * @return attached component sink
     */
    std::shared_ptr<RotationSink> GetSink() { return mSink; }

    wxPoint2DDouble GetShaftPosition();


};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
