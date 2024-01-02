/**
 * @file Banner.cpp
 * @author djmik
 */

#include "pch.h"
#include "Banner.h"

/// Scale to draw relative to the image sizes
const double BannerScale = 0.42;

/// Height of the banner in pixels
double const BannerHeight = 150 * BannerScale;

/// Width fo the banner in pixels
const double BannerWidth = 1024 * BannerScale;

/// Height of the banner roll image in pixels
const double BannerRollHeight = 300 * BannerScale;

/// Width of the banner roll image in pixels
double const BannerRollWidth = 16 * BannerScale;

/// How fast ot unfurl the banner in pixels per second
double const BannerSpeed = 41.65;

/// Minimum number of pixels to start with as unfurled
const double BannerMinimum = 15;

/// Name of banner image
const std::wstring BannerName = L"/banner.png";

/// name of banner roll image
const std::wstring RollName = L"/banner-roll.png";

/**
 * Constructor
 * Establishes banner images and shapes
 * @param imagesDir directory for images
 */
Banner::Banner(const std::wstring &imagesDir)
{
    mBanner.SetImage(imagesDir + BannerName);
    mScroll.SetImage(imagesDir + RollName);
    mBanner.Rectangle(-BannerWidth,0,BannerWidth,BannerHeight);
    mScroll.Rectangle(0,-(BannerRollHeight-BannerHeight)/2,BannerRollWidth, BannerRollHeight);
}

/**
 * Draws banner component
 * @param graphics graphics context
 */
void Banner::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPoint2DDouble p = GetPosition();
    double clip_width = BannerWidth * (1 - mStep);
    graphics->PushState();
    graphics->Clip(p.m_x - clip_width, 0, clip_width, 700 );
    graphics->Translate(BannerWidth - clip_width, 0.0);
    mBanner.DrawPolygon(graphics, p.m_x, p.m_y, 0);
    graphics->PopState();
    mScroll.DrawPolygon(graphics, p.m_x, p.m_y, 0);
}

/**
 * update banner member variables determining how much of the banner image is shown
 * @param elapsed elapsed time since last update call
 */
void Banner::Update(double elapsed)
{
    mTimer -= elapsed;
    if (mTimer <= 0) {
        if (mStep > 0)
        {
            mStep -= 0.01;
        }
    }
}

/**
 * Reset banner to its base state
 */
void Banner::Reset()
{
    Component::Reset();
    mStep = 1;
    mTimer = mCountdown;
}

/**
 * Set the countdown before the banner starts unrolling
 * @param time time at which banner will start unrolling
 */
void Banner::SetCountdown(double time)
{
    mCountdown = time;
    mTimer = time;
}
