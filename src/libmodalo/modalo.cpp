#include "modalo.h"

namespace modalo {
    
    // MemBlock Class function definitions

    MemBlock::MemBlock(Config * config) {
        this->config = config;
        address = 0;
        size = 0;
        functionCode = 4;
        slaveID = 1;
        pData = NULL;
        pFirstReg = NULL;
    }

    MemBlock::~MemBlock()   {
        setSize(0); // to delete allocated memory
    }

    bool MemBlock::setSize(uint16_t size)    {
        if(size != this->size && pData != NULL) { // to delete allocated memory
            delete[] pData;
            pData = NULL;
            this->size = 0;
        }
        if (size !=0 && pData == NULL) { // to allocate memory
            pData = new uint16_t[size];
            if(pData == NULL) {
                config->mlog->setLastLog(L_MEM_ALLOC,"Unable to allocate memory of new MemBlock Object");
                return false;
            }
            this->size = size;        
        }
        return true; //success
    }

    bool MemBlock::read()    {
        int mResult = 0;

        if(size == 0 || pData == NULL ) { // Unintiallised MemBlock
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid MemBlock Object in MemBlock::read()");
            return false;
        }

        if(config->ctx == NULL) { // invalid modbus context
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid modbus context in MemBlock::read()");
            return false;
        }

        // set slave as current device configuration
        if(modbus_set_slave(config->ctx,slaveID) == -1)   { // set slave error
            config->mlog->setLastLog(L_MODBUS,"Unable to set slave in MemBlock::read()");
            return false;
        }

        // function code 3: Read Holding Register
        if(functionCode==3) mResult = modbus_read_registers(config->ctx,address,size,pData);

        // function code 4: Read input register
        else if(functionCode==4) mResult = modbus_read_input_registers(config->ctx,address,size,pData);

        else {
            config->mlog->setLastLog(L_MEMBLOCK,"Invalid Function Code in MemBlock::read()");
            return false; 
        }
        if(mResult != size)	{ // error reading register
            modbus_flush(config->ctx);
            config->mlog->setLastLog(L_MODBUS_READ,"Unable to read from Reg in MemBlock::read()");
            config->mlog->setLastLog(L_MODBUS_READ,modbus_strerror(errno));
            return false;
        }
        time_t seconds=time(NULL); // get the current time
        localTimeS = localtime(&seconds); // set the time struct
        return true;
    }

    // Reg Class function definitions

    Reg::Reg(Config *config) {
        this->config = config;
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
        pNextReg = NULL;        
    }

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
            default : { config->mlog->setLastLog(L_REG,"Invalid Register Type in Reg::setValue()");
                return false;
            }
        }
        this->data32 = data32; // only if valid type 
        return true;
    }

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

    // Mlog class definitions

    Mlog::Mlog(std::string logFname) {
        logString = "";
        module_t = L_MODALO;

        // to open errorLogFile
        if(!logFname.empty())
        {
            logFile.open(logFname,std::ofstream::out|std::ofstream::app);
            if(logFile.is_open()) // confirmed no error
                setLastLog(L_FILE_IO,"File " + logFname + " opened for Logs.");
            else setLastLog(L_FILE_IO,"Failed to open file " + logFname + " for Logs.");
        }
    }

    Mlog::~Mlog() {
        setLastLog(L_MODALO,"Program Terminated.");
        if(logFile.is_open()) {
            logFile<<std::endl;
            logFile.close();
        }
    }

    void Mlog::setLastLog(MODULE_TYPE module_t, std::string logString) {
        this->module_t = module_t;
        this->logString = logString;
        
        time_t seconds=time(NULL); // get the current time
        localTimeS = localtime(&seconds); // set the time struct

        if(logFile.is_open()) logFile<<getLastLog(); // output to logFile
    }

    std::string Mlog::getLastLog() {
        // log format        YYYY-MM-DD HH:MM:SS : MODULE_TYPE : "LogString"
        return fmt::format("{:04}-{:02}-{:02} {:02}:{:02}:{:02} : {:^16} : \"{}\"\n",                        
            localTimeS->tm_year+1900,
            localTimeS->tm_mon+1,     // month, range 0 to 11
            localTimeS->tm_mday,      // day of the month, range 1 to 31
            localTimeS->tm_hour,      // hours, range 0 to 23
            localTimeS->tm_min,       // minutes, range 0 to 59
            localTimeS->tm_sec,       // update the ISO 8601 time strings
            getModuleString(),        // to get the module string of Last Log (not exceed 16 char)
            logString                 // to get the logString of Last Log
        );
    }

    std::string Mlog::getModuleString() {
        switch(module_t) {
            case L_MODALO: return "MODALO";
            case L_MODBUS: return "LIB-MODBUS";
            case L_REG: return "REGISTER";
            case L_MEMBLOCK: return "MEM_BLOCK";
            case L_CONFIG: return "CONFIG";
            case L_FILE_IO: return "FILE-IO";
            case L_MEM_ALLOC: return "MEM-ALLOC";
            case L_MODBUS_READ: return "MODBUS-READ";
            case L_MODBUS_SLAVE: return "SET-SLAVE";
            case L_PARSE_MAP: return "PARSE-MAP";
            case L_PARSE_CONFIG: return "PARSE-CONFIG";
            default : return "UNKNOWN MODULE";
        }
    }    

    // Modalo Class definitions

    Config::Config(std::string logFname) {
        mlog = new Mlog(logFname);
        modbus_read_interval = 1000; // milliseconds
        ctx = NULL;
    }

    Config::~Config() {
        delete mlog;
    }
}