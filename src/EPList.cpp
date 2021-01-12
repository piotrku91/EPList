#include "EPList.h"

/*
Arduino EEPROM CString List Manager  - EPList (For keep some Strings on External EEPROM and minimize use memory on Arduino Board).

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.8

Github: https://github.com/piotrku91/

Depedencies:
SparkFun_External_EEPROM.h // Click here to get the library: http://librarymanager/All#SparkFun_External_EEPROM

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <unsigned int InitStringSize>
const unsigned int EPList<InitStringSize>::size()
{
  delay(Delay);
  return Memory.get(0, ItemsCounter);
  
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
void EPList<InitStringSize>::SaveCounter()
{
  delay(Delay);
  Memory.put(0, ItemsCounter);
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
const char *EPList<InitStringSize>::getItem(const unsigned int &Index)
{
  if (!MemReady())
    return "NR!"; // NOT READY
  if (Index < ItemsCounter)
  {
    Memory.get(sizeof(ItemsCounter) + (Index * m_StringSize), m_Value);
    delay(Delay);
    return m_Value;
  };

  strcpy(m_Value, "NA"); // NOT AVAILABLE (index out of range)
  return m_Value;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
bool EPList<InitStringSize>::setItem(const unsigned int &Index, const char *NewCaption)
{
  if (MemReady())
  {
    int tmpCnt = strlen(NewCaption);
    if ((Index < ItemsCounter) && (tmpCnt <= m_StringSize))
    {

      for (int i = 0; (i <= tmpCnt); i++) // Send to memory in parts of bytes.
      {
        Memory.write(sizeof(ItemsCounter) + (Index * m_StringSize) + i, NewCaption[i]);
        delay(Delay);
      };

      delay(Delay);
      return true; // Changed
    };

    return false; // Not Changed (index out of range)
  };
  return false; // Not Changed (memory not ready)
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
bool EPList<InitStringSize>::pushItem(const char *NewCaption)
{

  if ((MemReady()) && (isFreeSpace()))
  {

    int tmpCnt = strlen(NewCaption);
    if (tmpCnt >= m_StringSize)
      return false;

    ItemsCounter++;
    SaveCounter();

    for (int i = 0; (i <= tmpCnt); i++) // Send to memory in parts of bytes.
    {
      Memory.write(sizeof(ItemsCounter) + ((ItemsCounter - 1) * m_StringSize) + i, NewCaption[i]);
      //  Memory.put(sizeof(ItemsCounter) + ((ItemsCounter - 1) * m_StringSize), m_Value);
      delay(Delay);
    };

    delay(Delay);

    return true; // Changed
  };

  return false; // Not Changed (memory not ready)
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <unsigned int InitStringSize>
bool EPList<InitStringSize>::removeItem()
{
  if ((MemReady()) && (ItemsCounter > 0))
  {

    for (int i = 0; (i <= m_StringSize); i++) // Send to memory in parts of bytes.
    {
      Memory.write(sizeof(ItemsCounter) + ((ItemsCounter - 1) * m_StringSize) + i, '\0');
      delay(Delay);
    };

    ItemsCounter--;
    SaveCounter();

    delay(Delay);
    return true; // Changed
  };
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
bool EPList<InitStringSize>::ClearList(bool areyousure)
{
  if ((MemReady()) && (areyousure))
  {
    Memory.erase();
    ItemsCounter = 0;
    Memory.put(0, ItemsCounter);

    return true; //  Changed
  };
  return false; // Not Changed (memory not ready)
};

template <unsigned int InitStringSize>
const ExternalEEPROM *EPList<InitStringSize>::RawAccess()
{
  return &Memory;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
const char *EPList<InitStringSize>::operator[](const unsigned int &Index)
{
  return getItem(Index);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
void EPList<InitStringSize>::FillList(int ItemsToFill, const char *NewString)
{
  ClearList(true); // Erase list

  for (int i = 0; i <= ItemsToFill; i++) // Fill list by new string
  {
    pushItem(NewString);
    delay(Delay);
  };
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <unsigned int InitStringSize>
bool EPList<InitStringSize>::MemReady() { return Memory.isConnected(); };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////