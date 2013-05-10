#include "mbed.h"
#include "MRF24J40.h"
#include <string>
#include "pinmap.h"

/********************************************************************/
/************** SLAVE CODE *****YELLOW MBED***********LPC 11U24******/
/********************************************************************/

// RF tranceiver to link with handheld.
MRF24J40 mrf(p11, p12, p13, p14, p21);

// Timer
Timer timer;

// Serial port for showing RX data.
Serial pc(USBTX, USBRX);

// Used for sending and receiving
char txbuffer[128];
char rxbuffer[128];
int rxLen;

//Solenoid Dashboard
DigitalOut dot1(p5);
DigitalOut dot2(p36);
DigitalOut dot3(p6);
DigitalOut dot4(p35);
DigitalOut dot5(p7);
DigitalOut dot6(p34);

//Speed Control Dashboard
int dropLevel = 0;
int raiseLevel = 1;

//DELAYS
float stickDelay = 1700;
float stickSlow = 1700;
float stickMed = 1300;
float stickHigh = 1000;

DigitalOut myled0(p25);
DigitalOut myled1(p26);
DigitalOut myled2(p27);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);


bool wirelessTest = false;
bool stopSolenoids = false;

//***************** BEGINNING OF WIRELESS SETUP [DONT EDIT] *****************//

/**
* Receive data from the MRF24J41.
*
* @param data A pointer to a char array to hold the data
* @param maxLength The max amount of data to read.
*/
int rf_receive(char *data, uint8_t maxLength)
{
    uint8_t len = mrf.Receive((uint8_t *)data, maxLength);
    uint8_t header[8]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};

    if(len > 10) {
        //Remove the header and footer of the message
        for(uint8_t i = 0; i < len-2; i++) {
            if(i<8) {
                //Make sure our header is valid first
                if(data[i] != header[i])
                    return 0;
            } else {
                data[i-8] = data[i];
            }
        }

        //pc.printf("Received: %s length:%d\r\n", data, ((int)len)-10);
    }
    return ((int)len)-10;
}

/**
* Send data to another MRF24J41.
*
* @param data The string to send
* @param maxLength The length of the data to send.
*                  If you are sending a null-terminated string you can pass strlen(data)+1
*/
void rf_send(char *data, uint8_t len)
{
    //We need to prepend the message with a valid ZigBee header
    uint8_t header[8]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};
    uint8_t *send_buf = (uint8_t *) malloc( sizeof(uint8_t) * (len+8) );

    for(uint8_t i = 0; i < len+8; i++) {
        //prepend the 8-byte header
        send_buf[i] = (i<8) ? header[i] : data[i-8];
    }
    //pc.printf("Sent: %s\r\n", send_buf+8);

    mrf.Send(send_buf, len+8);
    free(send_buf);
}


//***************** END OF WIRELESS SETUP *****************//


/*Drop pins*/
void dropPin(int pin)
{
    if(pin == 1) {
        dot1=dropLevel;
    } else if(pin == 2) {
        dot2 = dropLevel;
    } else if(pin == 3) {
        dot3=dropLevel;
    } else if(pin == 4) {
        dot4=dropLevel;
    } else if(pin == 5) {
        dot5=dropLevel;
    } else if(pin == 6) {
        dot6=dropLevel;
    } else {
        return;
    }
}

/*Raise pins*/
/* For pin-out information, refer to below */
/* http://mbed.org/handbook/mbed-NXP-LPC1768 */

void raisePin(int pin)
{
    if(pin == 1) {
        dot1=raiseLevel;
    } else if(pin == 2) {
        dot2=raiseLevel;
    } else if(pin == 3) {
        dot3=raiseLevel;
    } else if(pin == 4) {
        dot4=raiseLevel;
    } else if(pin == 5) {
        dot5=raiseLevel;
    } else if(pin == 6) {
        dot6=raiseLevel;
    } else {
        return;
    }
}

/* check pin status--nice to have feature */
void isRaised()
{
}

void loadDoc()
{
}

void acknowledge(int n)
{
    sprintf(txbuffer,"%d",n);
    rf_send(txbuffer, strlen(txbuffer)+1);
}

void pinLogic(int pinBinary)
{
    if(pinBinary-100000 >= 0) {
        raisePin(1);
        pinBinary = pinBinary-100000;
    } else {
        dropPin(1);
    }

    if(pinBinary-10000 >= 0) {
        raisePin(2);
        pinBinary = pinBinary-10000;
    } else {
        dropPin(2);
    }

    if(pinBinary-1000 >= 0) {
        raisePin(3);
        pinBinary = pinBinary-1000;
    } else {
        dropPin(3);
    }

    if(pinBinary-100 >= 0) {
        raisePin(4);
        pinBinary = pinBinary-100;
    } else {
        dropPin(4);
    }

    if(pinBinary-10 >= 0) {
        raisePin(5);
        pinBinary = pinBinary-10;
    } else {
        dropPin(5);
    }

    if(pinBinary-1 >= 0) {
        raisePin(6);
        pinBinary = pinBinary-1;
    } else {
        dropPin(6);
    }
    wait_ms(stickDelay);
}

void dropAllPins()
{
    /* drop all pins in the initial state */
    for(int i=1; i<=6; i++) {
        dropPin(i);
    }
}

void raiseAllPins()
{
    /* drop all pins in the initial state */
    for(int i=1; i<=6; i++) {
        raisePin(i);
    }
}

void delayHandler(int timePassed)
{
    if(timePassed>=1800) {
        stickDelay = stickSlow; //set the pins to stay up at a slow rate
    } else{
     stickDelay = stickHigh;
    }
}



/********************************************************************/
/************** MAIN MAIN  MAIN  MAIN  MAIN  MAIN  MAIN *************/
/********************************************************************/

void main(void)
{
    //***************** BEGINNING OF WIRELESS SETUP [DONT EDIT] *****************//
    uint8_t channel = 6;
    //Set the Channel. 0 is default, 15 is max
    mrf.SetChannel(channel);
    //Start the timer
    timer.start();
    //***************** END OF WIRELESS SETUP **********************************//

    raiseAllPins();
    dropAllPins();

    while(1) {
        int recLength = 0;
        recLength = rf_receive(rxbuffer,128);
        timer.reset();
        while(recLength<=0) {
            recLength = rf_receive(rxbuffer,128);
            led1=!led1;
        }
        led2=1;
        int timePassed = timer.read(); //the speed at which the master is sending
        delayHandler(timePassed);
        int temp = atoi(rxbuffer);
        pinLogic(temp);
        acknowledge(1); //tell Master you're ready for the next signal
        led3=1;
        dropAllPins();
        led3=0;
    }
}//end MAIN LOOP
