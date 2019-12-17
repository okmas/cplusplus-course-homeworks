#ifndef COMMAND_H
#define COMMAND_H

#include "virtualMachine.h"

class Command
{
    VirtualMachine *m_vm;
    *m_fn;
    int m_param;
public:
    Command(VirtualMachine *vm, (void)(*VirtualMachine::fn)(int), int param) : m_vm(vm), m_fn(fn), m_param(param);
    Command(VirtualMachine *vm, (void)(*VirtualMachine::fn)(int)) : m_vm(vm), m_fn(fn), m_param(0);

    operator() ()
    {
    m_fn(m_param);

    }
};

#endif // COMMAND_H
