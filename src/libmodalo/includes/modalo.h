#ifndef MODALO
#define MODALO

#include <stdint.h>
#include <string>
#include "modbus.h"

/* Pending Works

1) REG SIZE to be made private as changing it in userspace can cause memory reallocation issues
2) ERROR API to be ported to CPP
3) 

*/

#ifdef _WIN32
  /* You should define MODALO_EXPORT *only* when building the DLL. */
  #ifdef MODALO_EXPORT
    #define MODALO_API __declspec(dllexport) // only import if MODALO_EXPORT is defined
  #else
    #define MODALO_API __declspec(dllimport) // by default import
  #endif
#else /* _WIN32 not defined. */
  /* Define with no value on non-Windows OSes. */
  #define MODALO_EXPORT
#endif

namespace modalo {
  // enum definition for denoting various register type
  typedef enum REGTYPE {
    U16 = 1,
    U32 = 2,
    F32 = 12
  }REGTYPE;

  // union definition for holding various register type
  typedef union DATA32BIT {
    struct {
      uint16_t lowWord;
      uint16_t highWord;
    } value;
    uint16_t valueU16; // Unsinged 16-bit integer
    uint32_t valueU32; // Unsigned 32-bit integer
    float valueF32; //IEEE 32-bit float
  }DATA32BIT;

  // class declarations
  class MODALO_API Reg; // class used to represent a register
  class MODALO_API MemBlock; // parent class used purely for reading contigous memory 
  
  class MODALO_API MemBlock{

    public:
    uint16_t address;
    uint16_t functionCode;
    uint16_t slaveID;

    MemBlock(); // constructor
    ~MemBlock(); // desctructor
    bool read(modbus_t* ctx); // read memory from modbus device
    bool setSize(uint16_t size);   // set size of MemBlock element

    private: 
    uint16_t size; // private because should not be changed in userspace due to 
                   // pData reallocation issues.
    uint16_t * pData;
    Reg * pFirstReg;
  };

  class MODALO_API Reg{

    public: 
    uint16_t address;
    uint16_t size;
    std::string name;
    std::string unit;
    REGTYPE type;
    bool byteReversed;
    bool bitReversed;
    uint16_t multiplier;
    uint16_t divisor;
    DATA32BIT data;     // for getting value from parent
    double value;       // to store value after successfull read
    
    Reg();
    void getValueFromParent();
    
    private:

    MemBlock *parent; // pointer to Parent MemBlock
    Reg *pNextReg;   // pointer to Next Register in Parent MemBlock
    Reg *pPrevReg;   // pointer to Next Register in Parent MemBlock

    uint16_t reverseBits(uint16_t num);
    void reverseBit();
  };

}
#endif
