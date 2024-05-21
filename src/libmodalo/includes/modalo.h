#ifndef MODALO
#define MODALO

#include <stdint.h>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <fmt/core.h>
#include <modbus.h>


/* Pending Works

///////////////////////////////////////////////////////for MODBUS SCANNER

Config ->
  Device information variables (baud, slave ID, Parity, databits & stop bits)
  Method to parse config file
  Pointer to a Mlog object to be used for current configuration
  Pointer to a dump file to be used for current dump operation
  Variables for config and targetscan file Names


ScanTarget -> 
  Loads a ScanTarget File from the memory that specifies which register spaces to scan first
  Parsed the Scan Target File and for each Target space defined, starts scanning for valid responses
  For read MemBlock, adds the read data to a dump object
  After finishing the target space moves to the next target until complete

MemBlock ->
  Private Method to check for valid parameters (Fcode, size, DATA pointer, Modbus ctx, RegType) before scanning
  Method to dump information regarding the values that are read to a dump file/object
  Method to get information regarding the values that are read from a dump file/object
  Method to return DATA32 object of the given Mem Address if it belong to its address space

/////////////////////////   for MODBUS LOGGER /////////////////////////////

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
    L_REG,
    L_MEMBLOCK,
    L_CONFIG,
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
    unsigned int modbus_read_interval; // milliseconds
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
    ~MemBlock(); // destructor
    bool read(); // read memory from modbus device
    bool setSize(uint16_t size);   // set size of MemBlock element
    bool scan(std::vector<uint16_t> *pAddrList); // scan the address space and updates the address pairs in list

    private: 

    static Config *config;
    uint16_t size; // private because should not be changed in userspace due to 
                   // pData reallocation issues.
    uint16_t * pData;
    struct tm *localTimeS; // for holding read time
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

    static Config *config; // pointer to Parent MemBlock
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
