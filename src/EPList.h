#ifndef EPList_H
#define EPList_H

/*
Arduino EEPROM CString List Manager - EPList (For keep some Strings on External EEPROM and minimize use memory on Arduino Board).
Template class header file.

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.5

Github: https://github.com/piotrku91/

Depedencies:
SparkFun_External_EEPROM.h // Click here to get the library: http://librarymanager/All#SparkFun_External_EEPROM

Tip:
For proper work execute Wire.begin() function in setup() function (main sketch).

Example of create objects:
EPList<64> EC(0x50); // Static allocation (i2c chip Address)
EPList<64> *EC = new EPList<64>(0x50); // Dynamic allocation (Address, Size of EEPROM chip, Page Size)

EPList<64> EC(0x50,32000,128); // Static allocation with more settings (i2c chip Address, Size of EEPROM chip, Page Size)
EPList<64> *EC = new EPList<64>(0x50,32000,128); // Dynamic allocation (Address, Size of EEPROM chip, Page Size)

*/

#include <Wire.h>
#include <EEPROM.h>
#include "SparkFun_External_EEPROM.h"

/*

Parameter of template (<int InitStringSize>) defines size of one Item (bytes) on the list.
Counter is before list and takes 4 bytes of memory (int).

Scheme for 64 byte item (Hex):
Address 0 -> 00 00 00 00 (Counter) - unsigned int - 4 bytes
Address 4 + (0*64) -> 00 00 00 00 00 00 00 00 00 00 00 00 ... (Item 0) - char array - 64 bytes 
Address 4 + (1*64) -> 00 00 00 00 00 00 00 00 00 00 00 00 ... (Item 1) - char array - 64 bytes
Address 4 + (2*64) -> 00 00 00 00 00 00 00 00 00 00 00 00 ... (Item 2) - char array - 64 bytes
...

*/

template <unsigned int InitStringSize>
class EPList
{
private:
  const unsigned int m_StringSize; // Size of actual size of Item defined by template.
  unsigned int m_SpaceSize;        // Max amount of items available.
  unsigned int ItemsCounter;       // Keeps size of list on the begin of EEPROM (Address 0x0);
  short int Delay;       // Default delay after access of EEPROM to solve stability.

  char m_Value[InitStringSize]; // Last touched item on list

  ExternalEEPROM Memory; // SparkFun_External_EEPROM object

public: // Constructors
  EPList(uint8_t EEPROMAddress, int MemorySize, uint8_t PageSize) : m_StringSize{InitStringSize}, ItemsCounter{0}, Delay{10}
  {
    Memory.begin(EEPROMAddress);
    Memory.setMemorySize(MemorySize);
    Memory.setPageSize(PageSize);
    Memory.enablePollForWriteComplete();
    Memory.setPageWriteTime(3);

    ItemsCounter = size(); // Load Items counter
    CountSpace();
  };
  EPList(uint8_t EEPROMAddress = 0x50) : m_StringSize{InitStringSize}, ItemsCounter(0)
  {
    ItemsCounter = size();
    CountSpace();
  };

private: // Private functions
  bool MemReady();
  void SaveCounter(); // Save size of list

public:                                                                                                                           // Public Functions
  const char *getItem(const unsigned int &Index);                                                                                 // Return item in index
  bool setItem(const unsigned int &Index, const char* NewString);                                                                 // Set item in index by NewString
  bool pushItem(const char *NewString);                                                                                           // Add new item on the end
  const unsigned int size();                                                                                                      // Return actual size of list
  const unsigned int CountSpace() { return m_SpaceSize = floor((Memory.getMemorySize() - sizeof(ItemsCounter)) / m_StringSize); } // Count available space for that size of items
  bool isFreeSpace() { return (ItemsCounter < m_SpaceSize); };                                                                    // Checks if is some space to store the data

  bool ClearList(bool areyousure = false);               // !!!!! Erasing full list !!!!!!
  void FillList(int ItemsToFill, const char *NewString); // !!!!! Erasing full list and fill by NewString !!!!!!

  const ExternalEEPROM *RawAccess(); // Access to SparkFun_External_EEPROM object from outside of class.

  // Operators overload
  const char *operator[](const unsigned &Index);
};

#endif
