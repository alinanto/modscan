#include <iostream>

#include "modalo.h"

int main()
{
    std::cout<<"Hello World.\n";

    modalo::Reg registerOne;

    std::cout<<sizeof(registerOne);

    registerOne.read();



    return 0;
}