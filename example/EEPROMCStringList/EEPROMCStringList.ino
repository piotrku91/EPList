#include <EPList.h>
#include <EPList.cpp>

void setup() {
  Serial.begin(9600);
  Wire.begin();

  //EPList<64> EC(0x50,32000,128); // Static allocation
  //EC.FillList(20,"PUSTY"); // Example of clear list and init first 20 items as PUSTY
  delay(1000);
 
}


void loop() {
  EPList<64> *EC = new EPList<64>(0x50,32000,128); // Dynamic allocation

  Serial.print("Items count: ");
  Serial.println(EC->size());

  // EC->pushItem("I'm inside the chip");
  // EC->pushItem("Thank you.");
  
// Example of read full list
   for (int i=0; i<EC->size(); i++)
 {
  Serial.print(i);
  Serial.print(" : ");
  Serial.println(EC->getItem(i)); // Access to item
delay(10);
  };
  
  delay(1000);

  delete EC; // Free memory
  while(1) {};
}
