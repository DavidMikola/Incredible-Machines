/**
 * @file Machine1Factory.h
 * @author djmik
 *
 * machine 1 factory header
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE1FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE1FACTORY_H

class Machine;

/**
 * Machine 1 factory calss
 */
class Machine1Factory
{
private:

public:
    static std::shared_ptr<Machine> Create(const std::wstring& resourcesDir);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE1FACTORY_H
