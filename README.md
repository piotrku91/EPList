
## Arduino EEPROM CString List Manager  - EPList (For keep some Strings on Arduino EEPROM / External EEPROM and minimize use memory on Arduino Board).

Template class for EEPROM / External EEPROM.

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.9

Github: https://github.com/piotrku91/EPList

### Depedencies:

SparkFun_External_EEPROM.h // Click here to get the library: http://librarymanager/All#SparkFun_External_EEPROM (for External EEPROM's)

### Tips:

- For proper work execute Wire.begin() function in setup() function (main sketch). (External EEPROM)

- When you finish your list is better to set Write Protect on your chip. (External EEPROM)

### Example of create objects:

EPList<EEPROMClass,64> EC(4096); // Static allocation (Size of EEPROM)

EPList<EEPROMClass,64> *EC = new EPList<64>(4096); // Dynamic allocation (Size of EEPROM chip)


EPList<ExternalEEPROM,64> EC(0x50,32000); // Static allocation ExternalEEPROM (i2c chip Address, Size of EEPROM chip)

EPList<ExternalEEPROM,64> *EC = new EPList<64>(0x50,32000); // Dynamic allocation ExternalEEPROM  (Address, Size of EEPROM chip)

First argument of template is type of used EEPROM (EEPROMClass / ExternalEEPROM) and second is size of one item on the list.

### Example of use:

#### Example of add some items.

EC->pushItem("I'm inside the chip. ");
EC->pushItem("Save your space. Thank you.");


#### Get some Strings from list on EEPROM in easy way 

 Serial.println(EC[0]);
 Serial.println((*EC)[0]);

 #### Change some Strings from list on EEPROM in easy way 

 EC.setItem(0,"Good Job.")

