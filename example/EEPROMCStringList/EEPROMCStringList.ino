#include <EPList.h>
#include <EPList.cpp> // Include cpp file as well for link template functions.

enum ExampleTextsID {Text1=0,Text2=1}; // Use enum for name indexes of items on the list.

void setup()
{
  Serial.begin(9600); // Init Serial Interface
  Wire.begin(); // Init i2c interface. It's very important to work with EPList.

  pinMode(LED_BUILTIN,OUTPUT); // Set default LED as OUTPUT for help.

  //EPList<64> EC(0x50,32000,128); // Example of Static allocation

}

void loop()
{
  EPList<64> *EC = new EPList<64>(0x50, 32000, 128); // Example of Dynamic allocation

  // EC->ClearList(true); // Example of erase the list.
   //EC->FillList(EC->CountSpace(),"DEFAULT"); // Example of clear list and init full available space by DEFAULT.
  // digitalWrite(LED_BUILTIN,HIGH); // Set as high after clearing EEPROM memory.
   

  Serial.print("Items count: ");
  Serial.println(EC->size());

  Serial.print("Available space: ");
  Serial.println(EC->CountSpace());
  //delay(5000);

   Example of add some items.
   EC->pushItem("I'm inside the chip. ");
   EC->pushItem("Save your space. Thank you.");

   //EC->setItem(0,"b1231456789012314567890123145678911231456789112314567891000000"); // Example of 63 bytes String + 1 byte for null char.


  // Example of read full list
  for (int i = 0; i < EC->size(); i++)
  {
    Serial.print(i);
    Serial.print(" : ");
    Serial.println((*EC)[i]); // Access to item by overloaded operator [] (same as EC->getItem(i);). For assign use only EC->setItem(i,"example");
  };

  delay(1000);

  Serial.println("Hello!");
  Serial.println("I'm text on Arduino board");
  Serial.println((*EC)[ExampleTextsID::Text1]); // Usage of list example.
  Serial.println((*EC)[ExampleTextsID::Text2]); // Usage of list example.

  delete EC; // Free memory
  while (1)
  {
  }; // Freeze program.
}