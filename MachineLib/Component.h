/**
 * @file Component.h
 * @author djmik
 *
 * Virtual Component class that all different component types borrow from
 * represents objects within machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

class b2World;
class Machine;

/**
 * Virtual component class
 */
class Component
{
protected:
    /// Protected constructor (virtual class)
    Component() {}
private:
    /// Position of component
    wxPoint2DDouble mPosition;

    /// Current time
    double mCurrentTime = 0;

    /// Machine this component belongs to
    Machine * mMachine = nullptr;

    /// image of body
    wxImage mImage;

public:
    /**
     * Pure virtual update function
     * intended to be overwritten by derived classes
     * update each type of component in their own necessary way
     * @param elapsed time since last update call
     */
    virtual void Update(double elapsed) = 0;

    /**
     * pure virtual draw function
     * Draws current component
     * @param graphics graphics context
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;

    /**
     * Sets the position of the component
     * @param x x position
     * @param y y position
     */
    virtual void SetPosition(int x, int y) { mPosition = wxPoint2DDouble(x, y); }

    /**
     * Gets the current position of the component
     * @return position of Component
     */
    wxPoint2DDouble GetPosition() { return mPosition; }

    /**
     * Sets the parent machine that owns this component
     * @param machine parent machine
     */
    virtual void SetMachine(Machine* machine) { mMachine = machine; }

    /**
     * Gets parent machine object
     * @return parent machine
     */
    Machine * GetMachine() { return mMachine; }

    /**
     * Resets the Component to its initial state
     * Intended to be overridden by derived components
     */
    virtual void Reset() {}

    /**
     * Set The rotation of current component
     * Intended to be overwritten by components that are capable of rotation
     * @param rotation new rotation
     */
    virtual void SetRotation(double rotation) {}

    /**
     * Gets rotation of component (0 by default)
     * intended to be overwritten by components capable of rotation
     * @return 0
     */
    virtual double GetRotation() { return 0; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
