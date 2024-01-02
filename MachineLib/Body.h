/**
 * @file Body.h
 * @author djmik
 *
 * header file of body component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

#include "Component.h"
#include "PhysicsPolygon.h"

class RotationSink;

/**
 * Body machine component
 *
 * Body represents a generic object capable of being either
 * -static: Does not move or rotate
 * -Dynamic: Can move and rotate
 * -kinematic: does not move but can rotate in place
 */
class Body: public Component
{
private:
    /// Physics polygon enabling body to have correct physics
    cse335::PhysicsPolygon mBody;

    /// Initial position of body.  Important for rotations
    wxPoint2DDouble mInitialPosition;

    /// We are a rotation sink
    std::shared_ptr<RotationSink> mSink;
public:
    /// constructor
    Body();

    void Update(double elapsed) override;

    /// Draws current body
    void Draw(std::shared_ptr<wxGraphicsContext>  graphics) override;

    /// adds a point to attached Polygon
    void AddPoint(int x, int y);

    /// Set body image
    void SetImage(const std::wstring &imageDir);

    /**
     * Sets the color of the body polygon
     * @param color new color
     */
    void SetColor(wxColour color) { mBody.SetColor(color); }

    /// Set initial position of body
    void SetInitialPosition(int x, int y);

    /// Set position position of body
    void SetPosition(int x, int y) override;

    /**
     * Sets body to be a dynamic body, capable of obeying physics
     */
    void SetDynamic() { mBody.SetDynamic(); }

    /**
     * Sets body to be a kinematic body, capable of rotation in place
     */
    void SetKinematic() { mBody.SetKinematic(); }

    void SetMachine(Machine * machine) override;

    void Reset() override;

    void Rectangle(double x, double y, double width, double height);

    void Circle(double radius);

    /**
     * Gets the corresponding rotation sink attatched to this body
     * @return rotation sink
     */
    std::shared_ptr<RotationSink> GetSink() { return mSink; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
