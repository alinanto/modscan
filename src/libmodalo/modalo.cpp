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
       return true;
    }

    // Reg Class function definitions

    Reg::Reg(){
        address = 0; 
        size=0;
        name=""; 
        unit=""; 
        type=U16;
        byteOrder=M_BIG_ENDIAN;
        bitOrder=M_BIG_ENDIAN;
        multiplier=1;
        divisor=1;
        data32.valueU32 = 0;
        parent=NULL;
        pNextReg = NULL;
        pPrevReg = NULL;
        
    }

    // Function to accept data from parent MemBlock    
    bool Reg::setValue(DATA32BIT data32) {
        if(byteOrder == M_BIG_ENDIAN) { // reverse the bytes for Big Endian Register Byte Order
            uint16_t temp;
            temp = data32.value.highWord;
            data32.value.highWord = data32.value.lowWord;
            data32.value.lowWord = temp;
        }
        if(bitOrder == M_LITTLE_ENDIAN) { // reverse the Bits for Little Endian Register Byte Order
            data32.value.lowWord = reverseBits(data32.value.highWord);
            data32.value.highWord = reverseBits(data32.value.highWord);
        }

        switch(type) {
            case F32: { // F32
                value = ((double)data32.valueF32 * (double)multiplier) / (double)divisor;
                break;
            }
            case U32: { // U32
                value = ((double)data32.valueU32 * (double)multiplier) / (double)divisor;
                break;
            }
            case U16: { // U16
                value = ((double)data32.valueU16 * (double)multiplier) / (double)divisor;
                break;
            }
            default : { // add code here : handle error
                return false;
            }
        }
        this->data32 = data32; // only if valid type 
        return true;
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

    // Merror class definitions

    Merror::Merror() {
        errorString = "";
        error_t = ENO_ERROR;
    }
}