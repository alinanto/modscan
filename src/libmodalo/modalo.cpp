#include "modalo.h"

namespace modalo {

    // MemBlock Class function definitions
    MemBlock::MemBlock(){
        this->address = 0;
        this->size = 1;
        this->functionCode = 4;
        this->slaveID = 1;
    }
    MemBlock::MemBlock(uint16_t addr, uint16_t sz, uint16_t fCode, uint16_t sID){
        this->address = addr;
        this->size = sz;
        this->functionCode = fCode;
        this->slaveID = slaveID;
    }

    bool MemBlock::read(){
        return false;
    }

    // Reg Class function definitions

    Reg::Reg(){
        this->address = 0; 
        this->size=0;
        this->name=""; 
        this->unit=""; 
        this->type=U16;
        this->byteReversed=false;
        this->bitReversed=false;
        this->multiplier=1;
        this->divisor=1;
        this->parent=NULL;
        this->pNextReg = NULL;
    }

    Reg::Reg(uint16_t address, 
        uint16_t size, 
        std::string name, 
        std::string unit, 
        REGTYPE type,
        bool byteReversed,
        bool bitReversed,
        uint16_t multiplier,
        uint16_t divisor,
        MemBlock *parent) {
        
        this->address = address; 
        this->size = size; 
        this->name = name; 
        this->unit = unit; 
        this->type = type;
        this->byteReversed = byteReversed;
        this->bitReversed = bitReversed;
        this->multiplier = multiplier;
        this->divisor = divisor;
        this->parent = parent;
        this->pNextReg = pNextReg;

    }
}