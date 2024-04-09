#include <iostream>

#include "modalo.h"

int main()
{
    std::cout<<"Hello World.\n";

    modalo::MemBlock Memory;
    std::cout<<sizeof(Memory)<<std::endl;
    Memory.read();

    modalo::Reg regist;
    std::cout<<sizeof(regist)<<std::endl;
    
    return 0;
}