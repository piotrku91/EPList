#include "EPList.h"


/*
Arduino EEPROM CString List Manager  - EPList (For keep some Strings on External EEPROM and minimize use memory on Arduino Board).
Template class header file.

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.3

Github: https://github.com/piotrku91/

Depedencies:
SparkFun_External_EEPROM.h // Click here to get the library: http://librarymanager/All#SparkFun_External_EEPROM

*/



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <int InitStringSize>
const int EPList<InitStringSize>::size()
{
  return Memory.get(0, ItemsCounter);
  delay(10);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
void EPList<InitStringSize>::SaveCounter()
{
  delay(10);
  Memory.put(0, ItemsCounter);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
const char *EPList<InitStringSize>::getItem(const uint8_t &Index)
{
  if (!MemReady())
    return "NR!"; // NOT READY
  if (Index < ItemsCounter)
  {
    m_ActualIndex = Index;

    Memory.get(sizeof(ItemsCounter) + (m_ActualIndex * m_StringSize), m_Value);
    return m_Value;
  };

  strcpy(m_Value, "NA"); // NOT AVAILABLE (index out of range)
  return m_Value;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
bool EPList<InitStringSize>::setItem(const uint8_t &Index, const char *NewCaption)
{
  if (MemReady())
  {

    if (Index < ItemsCounter)
    {
      strcpy(m_Value, NewCaption);
      m_ActualIndex = Index;
      Memory.put(sizeof(ItemsCounter) + (m_ActualIndex * m_StringSize), m_Value);

      return true; // Changed
    };

    return false; // Not Changed (index out of range)
  };
  return false; // Not Changed (memory not ready)
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
bool EPList<InitStringSize>::pushItem(const char *NewCaption)
{
  if (MemReady())
  {

    strcpy(m_Value, NewCaption);

    ItemsCounter++;
    SaveCounter();
    m_ActualIndex = ItemsCounter - 1;

    Memory.put(sizeof(ItemsCounter) + (m_ActualIndex * m_StringSize), m_Value);

    return true; // Changed
  };

  return false; // Not Changed (memory not ready)
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <int InitStringSize>
bool EPList<InitStringSize>::ClearList(bool areyousure)
{
  if ((MemReady()) && (areyousure))
  {

    Memory.erase();
    ItemsCounter = 0;
    Memory.put(0, ItemsCounter);

    return true;  //  Changed 
  };
  return false;  // Not Changed (memory not ready)
};

template <int InitStringSize>
const ExternalEEPROM *EPList<InitStringSize>::RawAccess()
{
  return &Memory;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
const char * EPList<InitStringSize>::operator[](const uint8_t &Index)
{
  return getItem(Index);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
void EPList<InitStringSize>::FillList(int ItemsToFill, const char *NewString)
{
  ClearList(true); // Erase list

  for (int i = 0; i <= ItemsToFill; i++) // Fill list by new string
  {
    pushItem(NewString);
    delay(10);
  };
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <int InitStringSize>
bool EPList<InitStringSize>::MemReady() { return Memory.isConnected(); };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////