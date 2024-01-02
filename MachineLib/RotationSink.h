/**
 * @file RotationSink.h
 * @author djmik
 *
 * Rotation sink header
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H

class Component;
class RotationSource;

/**
 * Rotation sink class
 * object capable of taking rotation from a given source
 * used by components to get power from other components
 */
class RotationSink
{
private:
    /// Component consuming rotation
    Component* mComponent = nullptr;

    /// attached rotation componet
    std::shared_ptr<RotationSource> mSource;
public:
    RotationSink(Component* component);
    void SetRotation(double rotation);
    double GetRotation();

    /**
     * set the source  this sink is drawing power from
     * @param source new source
     */
    void SetSource(std::shared_ptr<RotationSource> source) { mSource = source; }

    /**
     * Get the source this sink is drawing power from
     * @return current rotation sink
     */
    std::shared_ptr<RotationSource> GetSource() { return mSource; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
