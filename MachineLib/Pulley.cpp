/**
 * @file Pulley.cpp
 * @author djmik
 */

#include "pch.h"
#include "Pulley.h"
#include "RotationSource.h"
#include "RotationSink.h"

/**
 * Constructor
 *
 * Creates the pulley shape
 * creates attached rotation sink and source objects
 * @param radius radius of pulley
 */
Pulley::Pulley(double radius) : Component(), mRadius(radius)
{
    mPulley.Circle(radius);
    mSource = std::make_shared<RotationSource>(this);
    mSink = std::make_shared<RotationSink>(this);
}

/**
 * draws the pulley
 * rotates it by a given amount
 * draws connection to mOtherPulley
 * @param graphics graphics context
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPulley.DrawPolygon(graphics, GetPosition().m_x, GetPosition().m_y, mSource->GetRotation());

    if (mOtherPulley)
    {
        bool flip = false;
        double r1 = mRadius;
        double r2 = mOtherPulley->GetRadius();
        auto p1 = GetPosition();
        auto p2 = mOtherPulley->GetPosition();
        // tan(θ) = (y2-y1)/(x2-x1)
        double theta = atan2((p2.m_y - p1.m_y), (p2.m_x - p1.m_x));
        // sin(ϕ) = (r2-r1)/|p2-p1|
        double phi = asin((r2 - r1) /
            sqrt(pow((p2.m_x - p1.m_x),2) +
                pow((p2.m_y - p1.m_y), 2)));
        double beta;
        if (signbit(GetRotation()) == signbit(mOtherPulley->GetRotation()))
        {
            // Same side connection
            if ((p1.m_y >= p2.m_y) && (theta >= 0) && !flip)
            {
                // β=θ+ϕ+π/2
                beta = theta + phi + (M_PI / 2.0);
            }
            else
            {
                // β=θ-ϕ+3π/2
                beta = theta - phi + (3.0 * M_PI / 2.0);
            }
            // p1 + ( r1cos(β), r1sin(β) )
            p1.m_x += r1 * cos(beta);
            p1.m_y += r1 * sin(beta);
            // p2 + ( r2cos(β), r2sin(β) )
            p2.m_x += r2 * cos(beta);
            p2.m_y += r2 * sin(beta);
        }
        else
        {
            // Opposite side connection
            if ((p1.m_y <= p2.m_y) && (theta >= 0) && !flip)
            {
                // β=θ-ϕ+π/2
                beta = theta + phi + (M_PI / 2.0);
            }
            else
            {
                // β=θ+ϕ+3π/2
                beta = theta + phi + (3.0 * M_PI / 2.0);
            }
            // p1 + ( r1cos(β), r1sin(β) )
            p1.m_x += r1 * cos(beta);
            p1.m_y += r1 * sin(beta);
            // p2 - ( r2cos(β), r2sin(β) )
            p2.m_x -= r2 * cos(beta);
            p2.m_y -= r2 * sin(beta);
        }
        graphics->SetPen(*wxBLACK_PEN);
        graphics->StrokeLine(p1.m_x, p1.m_y, p2.m_x, p2.m_y);
    }
}

/**
 * Set the image of the pulley
 * @param imageName pulley image name
 */
void Pulley::SetImage(const std::wstring &imageName)
{
    mPulley.SetImage(imageName);
}

/**
 * Update the pulleys rotation
 * @param elapsed time since last update call
 */
void Pulley::Update(double elapsed)
{
    // propagate through the rotation
    double rotation = mSink->GetRotation();
    mSource->SetRotation(rotation);
}
