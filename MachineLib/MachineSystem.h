/**
 * @file MachineSystem.h
 * @author djmik
 *
 * machien system header
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H

#include "IMachineSystem.h"

class Machine;

/**
 * Machine system class
 *
 * inherits from interface
 * system capable of holding a machine and drawing it
 */
class MachineSystem : public IMachineSystem
{
private:
    /// location of machine
    wxPoint mLocation = wxPoint(0,0);

    /// current frame of machine
    int mFrame = 0;

    /// Current machine number
    int mNumber = 0;

    /// Duration of machine animation
    int mDuration = 0;

    /// Frame rate of machine in frames/second
    double mFrameRate = 30;

    /// Current flag set
    int mFlag;

    /// resource directory
    std::wstring mResourcesDir;

    /// currently loaded machine
    std::shared_ptr<Machine> mMachine;

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

public:

    MachineSystem(const std::wstring& resourcesDir);

    /**
     * Set location of the machine system
     * @param pos new location
     */
    void SetLocation(wxPoint pos) override { mLocation = pos; }

    /**
     * Get locaation of machine
     * @return current location
     */
    wxPoint GetLocation() override {return mLocation; }

    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetMachineFrame(int frame) override;

    void SetMachineNumber(int machine) override;

    /**
     * Get the number of the currently loaded machien
     * @return
     */
    int GetMachineNumber() override { return mNumber; }

    /**
     * Set the frame rate if it is atleast 1.0
     * @param rate new frame rate
     */
    void SetFrameRate(double rate) override { mFrameRate = (rate > 1.0) ? rate : 1.0; }

    /**
     * Get the current machine time
     * @return
     */
    double GetMachineTime() override { return mFrame/mFrameRate; }

    /**
     * Sets flags of the machine, if any (flags not implemented)
     * @param flag value of flag to set
     */
    void SetFlag(int flag) override { mFlag = flag; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
