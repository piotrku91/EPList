
## Arduino EEPROM CString List Manager - EPList (For keep some Strings on External EEPROM and minimize use memory on Arduino Board).


Template class.

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.7

Github: https://github.com/piotrku91/EPList

### Depedencies:

SparkFun_External_EEPROM.h // Click here to get the library: http://librarymanager/All#SparkFun_External_EEPROM

### Tips:

- For proper work execute Wire.begin() function in setup() function (main sketch).

- When you finish your list is better to set Write Protect on your chip.

### Example of create objects:

EPList<64> EC(0x50); // Static allocation (i2c chip Address)

EPList<64> *EC = new EPList<64>(0x50); // Dynamic allocation (Address, Size of EEPROM chip, Page Size)


EPList<64> EC(0x50,32000,128); // Static allocation with more settings (i2c chip Address, Size of EEPROM chip, Page Size)

EPList<64> *EC = new EPList<64>(0x50,32000,128); // Dynamic allocation (Address, Size of EEPROM chip, Page Size)

### Example of use:

#### Example of add some items.

EC->pushItem("I'm inside the chip. ");
EC->pushItem("Save your space. Thank you.");


#### Get some Strings from list on External EEPROM in easy way 

 Serial.println(EC[0]);

 #### Change some Strings from list on External EEPROM in easy way 

 EC.setItem(0,"Good Job.")

