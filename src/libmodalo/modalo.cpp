#include "modalo.h"

namespace modalo {

    // MemBlock Class function definitions
    MemBlock::MemBlock(){
        address = 0;
        size = 0;
        functionCode = 4;
        slaveID = 1;
        pData = NULL;
        pFirstReg = NULL;
    }

    // Destructor
    MemBlock::~MemBlock()
    {
        setSize(0); // to delete allocated memory
    }

    // Function to set Size of MemBlock element and allocate memory for changes
    bool MemBlock::setSize(uint16_t size)
    {
        if(size != this->size && pData != NULL) { // to delete allocated memory
            delete[] pData;
            pData = NULL;
            this->size = 0;
        }
        if (size !=0 && pData == NULL) { // to allocate memory
            pData = new uint16_t[size];
            if(pData == NULL) return false;; // add code here handle error here
            this->size = size;        
        }
        return this->size; //success
    }

    // function to read the given register in the given context
    bool MemBlock::read(modbus_t* ctx)
    {
        //char error[MODALO_ERROR_MAXLENGTH] = "";
        int mResult = 0;

        if(size == 0 || pData == NULL ) { // invalid REG
            //modaloSetLastError(EMODBUS_READ,"Invalid / NULL Register");
            return false;;
        }

        if(ctx == NULL) { // invalid modbus context
            //sprintf(error, "Reading register %s failed with CODE: %s",reg->regName,modbus_strerror(errno));
            //modaloSetLastError(EMODBUS_READ,error);
            return false;;
        }

        // set slave as current device configuration
        if(modbus_set_slave(ctx,slaveID) == -1)   { // set slave error
            //sprintf(error,"Unable to select slave: %s, ERROR CODE:%s",slaveID,modbus_strerror(errno));
            //modaloSetLastError(EMODBUS_INIT,error);
            return false;;
        }

        // function code 3: Read Holding Register
        if(functionCode==3) mResult = modbus_read_registers(ctx,address,size,pData);

        // function code 4: Read input register
        else if(functionCode==4) mResult = modbus_read_input_registers(ctx,address,size,pData);

        else return false;; // add code here for function Code error

        if(mResult != size)	{ // error reading register
            //sprintf(error, "SLAVE ID: %u => Reading register %s, failed with CODE: %s",slaveID,reg->regName,modbus_strerror(errno));
            modbus_flush(ctx);
            //modaloSetLastError(EMODBUS_READ,error);
            return false;;
        }
        /* shift following code to Reg Object
        if(byteReversed) { // reverse the bytes default : Big endian
            uint16_t temp;
            temp = reg->readReg.value.highWord;
            reg->readReg.value.highWord = reg->readReg.value.lowWord;
            reg->readReg.value.lowWord = temp;
        }
        if(reg->bitReversed) { // reverse the Bits
            reg->readReg.value.lowWord = reverseBits(reg->readReg.value.highWord);
            reg->readReg.value.highWord = reverseBits(reg->readReg.value.highWord);
        }

        if(reg->regType == F32) // F32
            reg->value = ((double)reg->readReg.valueF32 * (double)reg->multiplier) / (double)reg->divisor;
        else if(reg->regType == U32) // U32
            reg->value = ((double)reg->readReg.valueU32 * (double)reg->multiplier) / (double)reg->divisor;
        else if(reg->regType == U16)// U16
            reg->value = ((double)reg->readReg.valueU16 * (double)reg->multiplier) / (double)reg->divisor;
        else {
            sprintf(error, "SLAVE ID: %u => Reading register %s, failed -> Invalid Register Type: %d",slaveID,reg->regName,reg->regType);
            modaloSetLastError(EMODBUS_READ,error);
            return false;;
        }
        return 1; // read success
        */
       return true;
    }

    // Reg Class function definitions

    Reg::Reg(){
        address = 0; 
        size=0;
        name=""; 
        unit=""; 
        type=U16;
        byteReversed=false;
        bitReversed=false;
        multiplier=1;
        divisor=1;
        parent=NULL;
        pNextReg = NULL;
        pPrevReg = NULL;
    }

    // Function to reverse bits of num
    uint16_t Reg::reverseBits(uint16_t num)
    {
        int count = 15;
        uint16_t reverse_num = num;

        num >>= 1;
        while (num) {
            reverse_num <<= 1;
            reverse_num |= num & 1;
            num >>= 1;
            count--;
        }
        reverse_num <<= count;
        return reverse_num;
    }
}