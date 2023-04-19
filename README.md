# Sequent-ESP32_PI-Library
Arduino library for Sequent Microsystems [ESP32-Pi: a really low cost Replacement Solution for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/esp32-pi-low-cost-replacement-for-raspberry-pi?variant=44337131487484)

## Install
### Library manager
Go to **Tools**>>**Manage Libraries..** menu and search for *SM_ESP32Pi* and click install 
### Manual install
To download click <>Code > [Download ZIP](https://github.com/SequentMicrosystems/Sequent-ESP32-PI-Library/archive/refs/heads/main.zip) button, rename the uncompressed folder to "SM_ESP32Pi" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see Sequent LCD Adaptor HAT inside. 
 The library will be compiled with sketches that use it. Open an arduino sketch, go to File > Examples > Sequent LCD Adaptor HAT > and chose your example to run.

## Usage
Now you can try one of his examples, open a sketchbook and go to File>Example>SM_ESP32Pi and select one of the example. The GPIO's , SDCard, Ethernet port both syncronous and asynchronous can be tested.
To run the examples you need to select the board "DOIT ESP32 DEVKIT V1". 