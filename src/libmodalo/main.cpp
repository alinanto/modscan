#include <iostream>
#include <modalo.h>
#include <windows.h>

int main()
{
    std::cout<<"Hello World.\n";
    modalo::Mlog mlog("modaloLog.txt");
    
    mlog.setLastLog(modalo::L_MODALO,"This is a sample error");
    mlog.setLastLog(modalo::L_MODBUS,"This is a sample error");
    mlog.setLastLog(modalo::L_MODBUS_READ,"This is a sample error");
    Sleep(1540);
    mlog.setLastLog(modalo::L_MODBUS_SLAVE,"This is a sample error"); Sleep(1540);
    mlog.setLastLog(modalo::L_PARSE_MAP,"This is a sample error");Sleep(1540);
    mlog.setLastLog(modalo::L_PARSE_CONFIG,"This is a sample error");
    return 0;
}