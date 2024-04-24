#ifndef MODALO
#define MODALO

#include <stdint.h>
#include <string>
#include <fstream>
#include <time.h>
#include <fmt/core.h>
#include <modbus.h>


/* Pending Works

///////////////////////////////////////////////////////for MODBUS SCANNER

0) Create a MemDump Class to hold information regarding the values that are read.
1) MemBlock Method to return DATA32 object of the given Mem Address if it belong to its address space
3) MemBlock Method to use a Reg objects to dump all combination (U16,U32,F32 * (BYTE REVERSED and BYTE NORMAL)) to MemDump Class

///////////////////////////////////////////////////////for MODBUS LOGGER

4) MemBlock Destructor to delete all Reg Objects by traversing the Reg Linked-list
5) MemBlock Method to add a new Reg to its Chain of Reg Linked List
2) MemBlock Method to traverse the registers and update register values

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

  // enum definition for denoting byte and bit order
  typedef enum ENDIANNESS {
    M_BIG_ENDIAN = 0,
    M_LITTLE_ENDIAN = 1
  }ENDIANNESS;

  // enum definition for denoting Modalo erros
  typedef enum MODULE_TYPE {
    L_MODALO,
    L_MODBUS,
    L_MEM_ALLOC,
    L_FILE_IO,
    L_MODBUS_READ,
    L_MODBUS_SLAVE,
    L_PARSE_MAP,
    L_PARSE_CONFIG,
  }MODULE_TYPE;

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
  class MODALO_API Config; // classs used to represent the config file
  class MODALO_API Reg; // class used to represent a register
  class MODALO_API MemBlock; // parent class used purely for reading contigous memory 
  class MODALO_API Mlog; // class to handle Modalo logs
  
  class MODALO_API Config{

    public:
    Mlog *mlog;
    modbus_t* ctx;
    Config(std::string logFname);
    ~Config();

    private: 
    std::string logFname;

  };

  class MODALO_API MemBlock{

    public:
    uint16_t address;
    uint16_t functionCode;
    uint16_t slaveID;

    MemBlock(Config *config); // constructor
    ~MemBlock(); // desctructor
    bool read(); // read memory from modbus device
    bool setSize(uint16_t size);   // set size of MemBlock element

    private: 
    Config *config;
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
    ENDIANNESS byteOrder;
    ENDIANNESS bitOrder;
    uint16_t multiplier;
    uint16_t divisor;
    DATA32BIT data32;     // for getting value from parent
    double value;       // to store value after successfull read
    
    Reg(Config *config);  // constructor
    bool setValue(DATA32BIT data32); // to be used only by parent MemBlock Object
    
    private:

    Config *config; // pointer to Parent MemBlock
    Reg *pNextReg;   // pointer to Next Register in Parent MemBlock
    uint16_t reverseBits(uint16_t num);
  };

  class MODALO_API Mlog{

    public:

    Mlog(std::string logFname); // constructor
    ~Mlog(); // destructor
    void setLastLog(MODULE_TYPE module_t, std::string logString);
    std::string getLastLog();

    private:
    std::ofstream logFile;
    MODULE_TYPE module_t;
    std::string logString;
    struct tm *localTimeS; // for holding error time
    std::string getModuleString();

  }; // Object created to handle modalo errors

}
#endif
