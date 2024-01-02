/**
 * @file RotationSource.h
 * @author djmik
 *
 * rotation source file
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

class Component;
class RotationSink;

/**
 * Rotation source class
 *
 * object used to provide power to other components
 * attached componet will generate rotation power to pass
 */
class RotationSource
{
private:
    /// Current rotation angle in radians
    double mRotation = 0;

    /// Component providing rotation
    Component* mComponent = nullptr;

    /// Attached Rotation Sink
    std::shared_ptr<RotationSink> mSink;

    /// ratio between source and sink
    double mRatio = 1;

public:
    RotationSource(Component* component);

    void SetRotation(double rotation);

    /**
     * Get the rotation value from this source
     * @return current source's rotation value
     */
    double GetRotation() { return mRotation; }

    void Connect(std::shared_ptr<RotationSource> source, std::shared_ptr<RotationSink> sink, double ratio = 1);

    /**
     * Get the attached rotation sink currently drawing power
     * @return current rotation sink
     */
    std::shared_ptr<RotationSink> GetSink() { return mSink; }

    void SetSink(std::shared_ptr<RotationSink> sink);

    /**
     * Get a specific ratio set for this rotation source
     * @return specific set ratio
     */
    double GetRatio() { return mRatio; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
