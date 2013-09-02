Braille-O-Matic
===============
The Braille-O-Matic is a device that allows the blind and visually impaired to read digital text by generating Braille characters at the pace at which Braille is read. The prototype was built using mbed microcontrollers- it sports Internet access, utilizes various self-built APIs, offers multiple speed options and provides a large RGB screen for education and verification purposes. The device presents a compelling value proposition for individuals hoping to keep up with the digital media at an affordable price point.

masterMain.cpp
--------------
This is the heart of the Braille-O-Matic device. This class speaks with slaveMain.cpp to handle the messaging, processing and executing of DC motor speeds, servo motor speeds and I/O. 

BrailleAlphabet.cpp
-------------------
This is the core implementation of the digital text to Braille conversion process. There is a 64 bit binary number - XXXXXX- that is 
used to distinguish between the various characters that may need to be deployed. For instance, 100000 corresponds to the letter 'A'

Corresponding code:
 if (character == 'A' || character =='a') return 100000;
 
There are unique binary numbers for each letter and number that may need to be displayed.

ledDisplay.cpp
--------------
This is the class that drives how we display characters on the led matrix (https://www.sparkfun.com/products/760). 
You can vary the duration of each display (ms), the wait (wt) and the frequency (freq). 

First, we populate an enum-like array of constants in matrix-form. The default setup would look like below:

volatile uint8_t blank[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    
Whereas the display for something like the letter A would look like the following. Note how varying RGB values create a background as well as foreground color scheme.

volatile uint8_t letter_a[] = {
        46, 46, 46, 46, 46, 46, 46, 46,
        46, 46, 46, 204, 204, 46, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 204, 204, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
        46, 46, 204, 46, 46, 204, 46, 46,
    };
    
    
The standard code to display an array is the following (A in this case):

switch(pattern) {
        case 5: {
            int i=0;
            do {
                cs = 0;
                wait_ms(ms); //wait for pre specified amount
                for(int k=0; k<65; k++) {
                    spi.write(letter_a[k+1]); //display all colors specified in the RGB array
                }
                wait_ms(ms); //wait some ms before moving on
                cs = 1;
                wait(wt);
                i++;
            } while(i<freq);
            break;
        }
    
    
Internet Setup
--------------
For Internet connectivity, we set up a unique MAC address. This is completed from lines 16-25 in masterMain.cpp. The wireless communication between the mbeds was handled from lines 96-146 in masterMain.cpp
