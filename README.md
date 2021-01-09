
## Arduino EEPROM CString List Manager - EPList (For keep some Strings on External EEPROM and minimize use memory on Arduino Board).

Template class header file.

Written by Piotr Kupczyk (dajmosster@gmail.com) 
2020
v. 0.3

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

