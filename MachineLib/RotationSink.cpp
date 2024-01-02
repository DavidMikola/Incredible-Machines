/**
 * @file RotationSink.cpp
 * @author djmik
 */

#include "pch.h"
#include "RotationSink.h"
#include "Component.h"
#include "RotationSource.h"

/**
 * Constructor
 *
 * Sets the component this sink is attached to
 * @param component component this sink will be attached to
 */
RotationSink::RotationSink(Component* component) : mComponent(component)
{

}

/**
 * Set the rotation of the attached component
 * @param rotation rotation to set
 */
void RotationSink::SetRotation(double rotation)
{
    if (nullptr != mComponent)
    {
        mComponent->SetRotation(rotation);
    }
}

/**
 * Get the rotation from the attached source
 * @return rotation source's rotation.  0 if not attached
 */
double RotationSink::GetRotation()
{
    if (mSource) {
        return mSource->GetRotation() * mSource->GetRatio();
    } else {
        return 0;
    }
}


