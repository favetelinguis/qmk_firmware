Compile a firmware file with your new keymap by typing:
   make crkbd:favetelinguis
from the qmk_firmware directory

   make crkbd:favetelinguis:dfu-split-right
:dfu-split-right - This flashes the normal firmware, just like the default option (:dfu). 
However, this also flashes the "Right Side" EEPROM file for split keyboards. 
This is ideal for Elite C based split keyboards.
