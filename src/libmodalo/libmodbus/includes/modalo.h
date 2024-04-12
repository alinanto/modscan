#ifndef MODALO
#define MODALO

#include <stdint.h>
#include <string>

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

  class MODALO_API Reg{
    public:
    std::string regName;
    uint16_t regAddress;
    REGTYPE regType;
    uint16_t regSize;
    uint16_t byteReversed;
    uint16_t bitReversed;
    uint16_t functionCode;
    uint16_t multiplier;
    uint16_t divisor;
    uint16_t movingAvgFilter;
    DATA32BIT data;        // for reading during a single modbus read request
    double value;       // to store value after successfull read

    Reg();
    bool read();
    void reverseByte();
    void reverseBit();

  };
}

#endif
