#include "MRF24J40.h"
#include "AnalogOut.h"
#include <string>
#include "pinmap.h"
#include "BrailleAlphabet.h"

/********************************************************************/
/***************MASTER CODE*****BLUE MBED********LPC1768*************/
/********************************************************************/

//Load from API
BrailleAlphabet braille(p30);

// RF tranceiver to link with handheld.
MRF24J40 mrf(p11, p12, p13, p14, p21);

// Timer
Timer timer;

// Serial port for showing RX data.
Serial pc(USBTX, USBRX);

//DC Motor
PwmOut dcPWM(p25);
DigitalOut dcOUT(p23);

// Used for sending and receiving
char txbuffer[128];
char rxbuffer[128];
int rxLen;

//DC Motor Control: USEFUL FOR MASTER
Ticker speedChecker;

//Buttons for playing with speed
DigitalIn reduce(p15);
DigitalIn increase(p16);
DigitalIn stop(p17);
float dutyCycle = 0.9;
bool motorStopped = false;
DigitalOut myled(p26);

//Delay
int preSendDelay = 2700;
int postSendDelay = 800;

//Testing Dashboard (Baseline 0-1)
char testWord [] = "SAXOPHONE";
int sizeOfWord = strlen(testWord);
int whichCharacter = 0;

bool killSwitch = false; //Idle Test- Cease and Desist
bool wirelessTest = false; //Wireless Test- transmits sample messages from 1 Zigbee to another
bool upAndDownTest = false; //Power Test- raises all pins up and down
bool saxophoneTest = false; //Display the word 'saxophone'
bool motorTest = false;

//***************** BEGINNING OF WIRELESS SETUP [DONT EDIT] *****************//

/**
* Receive data from the MRF24J40.
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
* Send data to another MRF24J40.
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

/* check pin status--nice to have feature */
void isRaised()
{
}

/*loads the PDF */
void loadDoc()
{
}

void sendNumber(int n)
{
    sprintf(txbuffer,"%d",n);
    rf_send(txbuffer, strlen(txbuffer)+1);
    wait_ms(postSendDelay);
}

void dropAllPins()
{
    sendNumber(0);
}

void raiseAllPins()
{
    sendNumber(111111);
}

char getNextCharacter(char* testWord)
{
    int z = sizeOfWord;
    char returnChar = 'X';
    if(whichCharacter<z) {
        returnChar = testWord [whichCharacter];
    } else {
        whichCharacter=0;
        returnChar = testWord [whichCharacter];
    }
    whichCharacter=whichCharacter+1;
    return returnChar;
}

void speedLogic()
{
    if(reduce==1) {
        while(reduce==1 && !motorStopped) {
            myled=1;
        }
        float temp = dutyCycle;
        dutyCycle = temp + 0.1; //motors slow down
        sendDelay = sendDelay + 0.3; //solenoids slow down
        if(sendDelay>3.0){
            sendDelay = 3.0;
        }
        if(dutyCycle==1) {
            motorStopped=true;
        }
    }

    else if(increase==1) {
        while(increase==1) {
            myled=1;
        }
        motorStopped=false;
        float temp = dutyCycle;
        if(temp==1){//in the case that you're reviving it
            sendDelay=3.0;
        }
        dutyCycle = temp - 0.1; //motor speeds up
        sendDelay = sendDelay - 0.3; //solenoids speed up
        if(sendDelay<0.0){
            sendDelay=0.0;
        }
        //myled=1;
    }

    else if(stop==1) {
        while(stop==1 && !motorStopped) {
            myled=1;
        }
        motorStopped=true;
        dutyCycle = 1;
    }
}

void handleNumberCase(char character){
                int poundSign = braille.matchCharacter('#');
                sendNumber(poundSign);
                dropAllPins();
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
    
    speedChecker.attach(&speedLogic,0.005);
    dcOUT =1;

    while(1) {
        dcPWM.write(dutyCycle);
        myled=0;
        
        while(killSwitch==true) {
            dcOUT = 0;
            sendNumber(111111);
        }

        while(upAndDownTest==true) {
            raiseAllPins();
            dropAllPins();
        }//end up and down test
        
        
        if(!motorStopped) {
            char character = getNextCharacter(testWord);
            int pinBinary = braille.matchCharacter(character);

            if(braille.isNumber(character)) {
                handleNumberCase(character);
            }
       
            wait_ms(preSendDelay);
            myled=1;
            sendNumber(pinBinary);
            myled=0;
            
            //***** ACKNOWLEDGE CODE ******//
             int recLength = rf_receive(rxbuffer,128);
             while(recLength<=0) {
                 recLength = rf_receive(rxbuffer,128);
              }           
            //***** END ACKNOWLEDGE CODE ******//         
        }//end if motor stopped code
        dropAllPins();
    }//end while loop
}//end kill switch logic