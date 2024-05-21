#include <iostream>
#include <modalo.h>
using namespace modalo;

class MemScan {

    public:
    static uint16_t functionCode;
    static uint16_t slaveID;
    static Config *config;
    uint16_t startAddr;
    uint16_t endAddr;

    void scan();



}



    bool MemBlock::scan(std::vector<uint16_t> *pAddrList) { // scan the address space and shrinks to fit the valid registers
        
        if(pAddrList == NULL) {
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid AddrSize Vector Pointer given in MemBlock::scan()");
            return false;
        }

        if(size == 0 || pData == NULL ) { // Unintiallised MemBlock
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid MemBlock Object in MemBlock::scan()");
            return false;
        }

        if(config->ctx == NULL) { // invalid modbus context
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid modbus context in MemBlock::scan()");
            return false;
        }

        // set slave as current device configuration
        if(modbus_set_slave(config->ctx,slaveID) == -1)   { // set slave error
            config->mlog->setLastLog(L_MODBUS,"Unable to set slave in MemBlock::scan()");
            return false;
        }

        if(functionCode != 3 && functionCode != 4)  {
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid Function Code in MemBlock::scan()");
            return false; 
        }

        // we can start the scanning process        
        return recursiveScan(address, address+size-1);
    }

    bool MemBlock::recursiveScan(uint16_t startAddr, uint16_t endAddr) {
        if(startAddr == endAddr) {
            pAddrList.append
        }

    }

    inline bool MemBlock::scanLocation(uint16_t scanAddr, uint16_t scanSize=1) {
        uint16_t *pScanData = new uint16_t[scanSize]; // temp memory for scanning
        int mResult = 0;

        // function code 3: Read Holding Register
        if(functionCode==3) mResult = modbus_read_registers(config->ctx,scanAddr,scanSize,pScanData);

        // function code 4: Read input register
        else if(functionCode==4) mResult = modbus_read_input_registers(config->ctx,scanAddr,scanSize,pScanData);
        
        delete[] pScanData; // free memory
        if(mResult != scanSize)	{ // error reading register
            modbus_flush(config->ctx);
            return false;
        }
        return true;        
    }





int main()
{
    Config config("logFile.log");
    return 0;
}