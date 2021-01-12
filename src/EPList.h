#ifndef EPList_H
#define EPList_H

/*
Arduino EEPROM CString List Manager  - EPList (For keep some Strings on Arduino EEPROM / External EEPROM and minimize use memory on Arduino Board).

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.9

Github: https://github.com/piotrku91/

Depedencies:
SparkFun_External_EEPROM.h // Click here to get the library: http://librarymanager/All#SparkFun_External_EEPROM (for External EEPROM's)

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

template <typename T, unsigned int InitStringSize>
class EPList
{
private:
  const unsigned int m_StringSize; // Size of actual size of Item defined by template.
  const unsigned int m_MemorySize; // Size of EEPROM in bytes
  unsigned int m_SpaceSize;  // Max amount of items available.
  unsigned int ItemsCounter; // Keeps size of list on the begin of EEPROM (Address 0x0);
  short int Delay;           // Default delay after access of EEPROM to solve stability.


  char m_Value[InitStringSize]; // Last touched item on list
  T Memory;                     // SparkFun_External_EEPROM or Arduino builtin EEPROM object

public: // Constructors
                                        //////////////// External EEPROM Constructor /////////////////
  EPList(uint8_t EEPROMAddress, unsigned int MemorySize) : m_StringSize{InitStringSize}, m_MemorySize{MemorySize}, ItemsCounter{0}, Delay{10}
  {
    Memory.begin(EEPROMAddress);
    Memory.setMemorySize(m_MemorySize);
    Memory.setPageSize(m_StringSize);
    Memory.enablePollForWriteComplete();
    Memory.setPageWriteTime(3);

    ItemsCounter = size(); // Load Items counter
    CountSpace();
  };

                                       //////////////// Arduino builtin EEPROM Constructor /////////////////
  EPList(unsigned int MemorySize) : m_StringSize{InitStringSize}, m_MemorySize{MemorySize}, ItemsCounter(0), Delay{10}
  {
    ItemsCounter = size();
    CountSpace();
  };

private: // Private functions
  bool MemReady();
  void SaveCounter(); // Save size of list

public:
  bool setCounterManually(const unsigned int &New){ItemsCounter = New; SaveCounter(); };                                // Set counter manually                                                                                    // Public Functions
  const char *getItem(const unsigned int &Index);                                                                       // Return item in index
  bool setItem(const unsigned int &Index, const char *NewString);                                                       // Set item in index by NewString
  bool pushItem(const char *NewString);                                                                                 // Add new item on the end
  const unsigned int size();                                                                                            // Return actual size of list
  const unsigned int CountSpace() { return m_SpaceSize = floor((m_MemorySize - sizeof(ItemsCounter)) / m_StringSize); } // Count available space for that size of items
  bool isFreeSpace() { return (ItemsCounter < m_SpaceSize); };                                                          // Checks if is some space to store the data
  bool removeItem();                                                                                                    // Removes last item from the list

  bool ClearList(bool areyousure = false);               // !!!!! Erasing full list !!!!!!
  void FillList(int ItemsToFill, const char *NewString); // !!!!! Erasing full list and fill by NewString !!!!!!

  const T *RawAccess(); // Access to EEPROM object from outside of class.

  // Operators overload
  const char *operator[](const unsigned &Index);

};


#endif
