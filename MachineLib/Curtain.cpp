/**
 * @file Curtain.cpp
 * @author djmik
 */

#include "pch.h"
#include "Curtain.h"

/// Height of our curtains in pixels converted to cm
const double CurtainHeight = 550/1.5;

/// Total width of the curtains in pixels
const double CurtainWidth = 600;

/// Number of seconds to open the curtains. not used from sample code
const double CurtainOpenTime = 2.0;

/// Minimum scaling factor for when the curtains are open
const double CurtainMinScale = 0.15;

/// Curtain rod image Name
const std::wstring RodImage = L"/curtain-rod.png";

/// Left curtain image name
const std::wstring LeftImage = L"/curtain1.png";

/// Right curtain image name
const std::wstring RightImage = L"/curtain2.png";

/**
 * Constructor
 * Establishes polygon images and shapes
 * @param imagesDir
 */
Curtain::Curtain(const std::wstring &imagesDir)
{
    mRod.SetImage(imagesDir + RodImage);
    mLeft.SetImage(imagesDir + LeftImage);
    mRight.SetImage(imagesDir + RightImage);
    mRod.BottomCenteredRectangle(CurtainWidth, CurtainHeight);
    mLeft.Rectangle(0,0,CurtainWidth/2, CurtainHeight);
    mRight.Rectangle(0,0,CurtainWidth/2,CurtainHeight);
}

/**
 * Draws curtains component
 * Also transfroms the graphics to shrink the curtains to the sides
 * @param graphics
 */
void Curtain::Draw(std::shared_ptr<wxGraphicsContext>  graphics)
{
    double width = CurtainWidth/2;
    wxPoint2DDouble p = GetPosition();
    // draw curtain rod
    mRod.DrawPolygon(graphics, p.m_x, p.m_y, 0);
    // draw left
    graphics->PushState();
    graphics->Scale(mStep, 1.0);
    graphics->Translate(width * (mStep - 1) / mStep, 0.0);
    mLeft.DrawPolygon(graphics, p.m_x - 300, p.m_y, 0);
    graphics->PopState();
    // draw right
    graphics->PushState();
    graphics->Scale(mStep, 1.0);
    graphics->Translate(width * (1 - mStep) / mStep, 0.0);
    mRight.DrawPolygon(graphics, p.m_x, p.m_y, 0);
    graphics->PopState();
}

/**
 * Updates the component
 * Shrinks the curtains to the sides over time
 * @param elapsed time elapsed since last call of update
 */
void Curtain::Update(double elapsed) {
    if (mStep > CurtainMinScale)
    {
        mStep -= 0.01;
    }
}
/**
 * Resets the component back to its original state
 * curtains will be closed again
 */
void Curtain::Reset()
{
    Component::Reset();

    // Resets scale of curtains back to 1.0
    mStep = 1;
}

