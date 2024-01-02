/**
 * @file Pulley.h
 * @author djmik
 *
 * Pulley component header
 */

#include "Component.h"
#include "Polygon.h"

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include "RotationSource.h"
#include "RotationSink.h"

/**
 * pulley component class
 *
 * Pulley object capable of transferring speed and rotation between components
 */
class Pulley : public Component
{
private:
    /// The pulley
    cse335::Polygon mPulley;

    /// We are rotation source
    std::shared_ptr<RotationSource> mSource;

    /// We are a rotation sink
    std::shared_ptr<RotationSink> mSink;

    /// Radius of pulley wheel
    double mRadius;

    /// Pulley currently connected to via belt
    std::shared_ptr<Pulley> mOtherPulley;
public:
    Pulley(double radius);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetImage(const std::wstring& imageName);
    void Update(double elapsed) override;

    /**
     * Get attached rotation source
     * @return current rotation source
     */
    std::shared_ptr<RotationSource> GetSource() { return mSource; }

    /**
     * Get attached rotation sink
     * @return current rotation sink
     */
    std::shared_ptr<RotationSink> GetSink() { return mSink; }

    /**
     * Get the radius of the pulley
     * @return radius
     */
    double GetRadius() { return mRadius; }

    /**
     * Get the other pulley this pulley is currently attached to (next in line if in chain of pulleys)
     * @param other
     */
    void SetOtherPulley(std::shared_ptr<Pulley>& other) { mOtherPulley = other; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
