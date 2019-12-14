Compile a firmware file with your new keymap by typing:
   make crkbd:favetelinguis
from the qmk_firmware directory

   make crkbd:favetelinguis:dfu-split-left
:dfu-split-left - This flashes the normal firmware, just like the default option (:dfu). 
However, this also flashes the "Left Side" EEPROM file for split keyboards. 
This is ideal for Elite C based split keyboards.

This config is set RIGHT side as master in config.h
