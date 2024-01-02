/**
 * @file Goal.h
 * @author djmik
 *
 * goal component header file
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H

#include "Component.h"
#include <b2_world_callbacks.h>
#include "Polygon.h"
#include "PhysicsPolygon.h"

/**
 * Goal component class
 *
 * goal component capable of keeping a score
 * when a body passes through the "hoop" of the goal, 2 points are added to the score
 */
class Goal : public Component, public b2ContactListener
{
private:
    /// current score
    int mScore = 0;

    /// Goal image polygon
    cse335::Polygon mGoalImage;

    /// physics polygon handling collisions of goal post
    cse335::PhysicsPolygon mPost;

    /// physics polygon handling collisions and goals of goal head/net
    cse335::PhysicsPolygon mGoal;

public:

    Goal(const std::wstring& imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void BeginContact(b2Contact* contact) override;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    void Update(double elapsed) override;

    void SetPosition(int x, int y) override;

    void SetMachine(Machine * machine) override;

    void Reset() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
