/**
 * @file MachineSystem.cpp
 * @author djmik
 */

#include "pch.h"
#include "Machine.h"
#include "MachineSystem.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

/**
 * Constructor
 *
 * sets the resource directory for the machine system
 * sets the machine number to its default of 1
 * @param resourcesDir
 */
MachineSystem::MachineSystem(const std::wstring &resourcesDir) : mResourcesDir(resourcesDir)
{
    SetMachineNumber(1);
}


/**
 * Draws the machine
 * @param graphics  graphics context
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    if (mMachine) {
        mMachine->Draw(graphics);
    }
    graphics->PopState();
}

/**
 * Sets the machine number
 * @param machine new machine number
 */
void MachineSystem::SetMachineNumber(int machine)
{
    mMachine.reset();
    switch(machine) {
        case (1):
            Machine1Factory machine1Factory;
            mMachine = machine1Factory.Create(mResourcesDir);
            mMachine->SetSystem(this);
            break;
        case (2):
            Machine2Factory machine2Factory;
            mMachine = machine2Factory.Create(mResourcesDir);
            mMachine->SetSystem(this);
            break;
        default:
            break;
    }
    mNumber = machine;
}

/**
 * Sets the frame the machine is currently drawing
 * @param frame new current frame
 */
void MachineSystem::SetMachineFrame(int frame)
{
    if (mMachine) {
        if(frame < mFrame)
        {
            mFrame = 0;
            mMachine->Reset();
        }

        for( ; mFrame < frame;  mFrame++)
        {
            mMachine->SetCurrentTime(GetMachineTime());

            mMachine->Update(1.0 / mFrameRate);
        }
    } else {
        mFrame = frame;
    }

    // May need more than these, but you'll figure that out...


}

