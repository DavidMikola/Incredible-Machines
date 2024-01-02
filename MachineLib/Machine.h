/**
 * @file Machine.h
 * @author djmik
 *
 * Machine header file
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

class Component;
class b2World;
class ContactListener;
class MachineSystem;

/**
 * machine class
 *
 * Machine capable of holding components
 */
class Machine
{
private:
    /// current machine time
    double mCurrentTime = 0;

    /// components that are part of this machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// physics world object
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

    /// System this machine belongs too
    MachineSystem * mSystem;


public:
    Machine();

    void AddComponent(std::shared_ptr<Component> component);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set current machine time
     * @param time new time
     */
    void SetCurrentTime(double time) { mCurrentTime = time; }

    /**
     * Get current machine time
     * @return current time
     */
    double GetCurrentTime() { return mCurrentTime; }

    /**
     * Gets the physics world to add components
     * @return current physics world
     */
    std::shared_ptr<b2World> GetWorld() { return mWorld; }

    void Update(double elapsed);

    void Reset();

    /**
     * Get attatched contact listener for required contact event
     * @return current contact listener
     */
    std::shared_ptr<ContactListener> GetContactListener() { return mContactListener; }

    /**
     * Sets the current machine to a new system
     * @param system new machine system
     */
    void SetSystem(MachineSystem * system) { mSystem = system; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
