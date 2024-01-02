/**
 * @file Machine2Factory.h
 * @author djmik
 *
 * machien 2 factory header
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H

/**
 * Machine 2 factory class
 *
 * creates an instance of a pre-made machine factory 2
 */
class Machine2Factory
{
private:

public:
    static std::shared_ptr<Machine> Create(const std::wstring& resourcesDir);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
