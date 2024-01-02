/**
 * @file Curtain.h
 * @author djmik
 *
 * curtain component header file
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H
#define CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H

#include "Component.h"
#include "Polygon.h"
#include "PhysicsPolygon.h"

/**
 * Curtain component
 *
 * After a delay, curtain will "unroll" to reveal an image
 * this is accomplished by slowly moving the image into a cropped polygon
 */
class Curtain : public Component
{
private:
    /// Curtain Rod Polygon
    cse335::Polygon mRod;

    /// Left Curtain Polygon
    cse335::Polygon mLeft;

    /// Right Curtain Polygon
    cse335::Polygon mRight;

    /// Scale of curtain (% of width/ how open/closed they are)
    double mStep = 1.0;

public:
    Curtain(const std::wstring &imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void Reset() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CURTAIN_H
