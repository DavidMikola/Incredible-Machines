/**
 * @file Banner.h
 * @author djmik
 *
 *header file for banner component
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BANNER_H
#define CANADIANEXPERIENCE_MACHINELIB_BANNER_H

#include "Component.h"
#include "Polygon.h"

/**
 * Banner component Class
 *
 * Banner unfolds when the machine begins to run, expanding the image file contained inside until it is fully visible
 */
class Banner : public Component
{
private:
    /// Banner image polygon
    cse335::Polygon mBanner;

    /// Banner Scroll image polygon
    cse335::Polygon mScroll;

    /// Scale of dimensions of banner width
    double mStep = 1.0;

    /// Max time until banner unfolds
    double mCountdown = 1;

    /// Timer keeping track of how long until banner unfolds
    double mTimer = 1;

public:
    Banner(const std::wstring& imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void Reset() override;

    void SetCountdown(double time);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BANNER_H
