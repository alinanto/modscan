#include <iostream>
#include <modalo.h>
#include <windows.h>

int main()
{
    std::cout<<"Hello World.\n";
    
    modalo::Config config("logFile.log");
    config.mlog->setLastLog(modalo::L_MODALO,"Sample Error Log");

    return 0;
}