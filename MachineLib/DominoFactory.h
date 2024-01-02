/**
 * @file DominoFactory.h
 * @author djmik
 *
 * Creates a dynamic domino body
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_DOMINOFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_DOMINOFACTORY_H

class Body;

/**
 * Class that creates a domino body component with a specified color
 */
class DominoFactory
{
private:

public:
    static std::shared_ptr<Body> Create(const std::wstring& resourcesDir, int color);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_DOMINOFACTORY_H
