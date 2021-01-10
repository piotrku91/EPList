#include <EPList.h>
#include <EPList.cpp> // Include cpp file as well for link template functions.

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  //EPList<64> EC(0x50,32000,128); // Static allocation
  //EC.FillList(20,"PUSTY"); // Example of clear list and init first 20 items as PUSTY
//  delay(1000);
}

void loop()
{
  EPList<64> *EC = new EPList<64>(0x50, 32000, 128); // Dynamic allocation

  Serial.print("Items count: ");
  Serial.println(EC->size());

  Serial.print("Available space: ");
  Serial.println(EC->CountSpace());
  //delay(5000);

   //Example of add some items.
   EC->pushItem("I'm inside the chip");
   EC->pushItem("Thank you.");

  //
  //EC->FillList(EC->CountSpace(),"PUSTY"); // Example of clear list and init full available space by PUSTY.

  // Example of read full list
  for (int i = 0; i < EC->size(); i++)
  {
    Serial.print(i);
    Serial.print(" : ");
    Serial.println((*EC)[i]); // Access to item by overloaded operator [] (same as EC->getItem(i);). For assign use only EC->setItem(i,"example");
    delay(10);
  };

  delay(1000);

  delete EC; // Free memory
  while (1)
  {
  }; // Freeze program.
}