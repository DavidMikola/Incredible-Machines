/**
 * @file RotationSource.cpp
 * @author djmik
 */

#include "pch.h"
#include "RotationSource.h"
#include "RotationSink.h"
#include "Component.h"

/**
 * Constructor
 *
 * attaches this source to a component
 * @param component component this source will pass power from
 */
RotationSource::RotationSource(Component* component) : mComponent(component)
{

}

/**
 * Sets the rotation of the source
 * @param rotation
 */
void RotationSource::SetRotation(double rotation)
{
    mRotation = rotation;
}

/**
 * Connects a rotation source to a rotation sink
 * @param source source providing power
 * @param sink sink taking power
 * @param ratio ratio between the two objects.  Needed for pulleys.  1 if one or neither of the components are pulleys
 */
void RotationSource::Connect(std::shared_ptr<RotationSource> source, std::shared_ptr<RotationSink> sink, double ratio)
{
    source->SetSink(sink);
    sink->SetSource(source);
    mRatio = ratio;
}

/**
 * Set the sink this object is attached to
 * @param sink new rotation sink
 */
void RotationSource::SetSink(std::shared_ptr<RotationSink> sink)
{
    mSink = sink;
}
