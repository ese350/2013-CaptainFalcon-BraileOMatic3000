#include "BrailleAlphabet.h"
#include "mbed.h"


BrailleAlphabet::BrailleAlphabet(PinName pin) : _pin(pin)
{
    _pin = 0;
}

bool BrailleAlphabet::isNumber(char c)
{
    if(c == '0' || c == '1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9') {
        return true;
    }
    return false;
}

int BrailleAlphabet::matchCharacter(char character)
{

    if (character == 'A' || character =='a') {
        //pc.printf("%s\r\n","detect_a");
        return 100000;
    }
    if (character == 'B' || character=='b') {
        // pc.printf("%s\r\n","detect_b");
        return 101000;
    }
    if (character == 'C'||character=='c') {
        //pc.printf("%s\r\n","detect_c");
        return 110000;
    }
    if (character == 'D'||character=='d') {
        //pc.printf("%s\r\n","detect_d");
        return 110100;
    }
    if (character == 'E'||character=='e') {
        // pc.printf("%s\r\n","detect_e");
        return 100100;
    }
    if (character == 'F'||character=='f') {
        // pc.printf("%s\r\n","detect_f");
        return 111000;
    }
    if (character == 'G'||character=='g') {
        // pc.printf("%s\r\n","detect_g");
        return 111100;
    }
    if (character == 'H'||character=='h') {
        // pc.printf("%s\r\n","detect_h");
        return 101100;
    }
    if (character == 'I' || character=='i') {
        //pc.printf("%s\r\n","detect_i");
        return 11000;
    }
    if (character == 'J'||character=='j') {
        //pc.printf("%s\r\n","detect_j");
        return 11100;
    }
    if (character == 'K'||character=='k') {
        // pc.printf("%s\r\n","detect_k");
        return 100010;
    }
    if (character == 'L'||character=='l') {
        // pc.printf("%s\r\n","detect_l");
        return 101010;
    }
    if (character == 'M'||character=='m') {
        // pc.printf("%s\r\n","detect_m");
        return 110010;
    }
    if (character == 'N'||character=='n') {
        // pc.printf("%s\r\n","detect_n");
        return 110110;
    }
    if (character == 'O'||character=='o') {
        // pc.printf("%s\r\n","detect_o");
        return 100110;
    }
    if (character == 'P'||character=='p') {
        // pc.printf("%s\r\n","detect_p");
        return 111010;
    }
    if (character == 'Q'||character=='q') {
        //  pc.printf("%s\r\n","detect_q");
        return 111110;
    }
    if (character == 'R'||character=='r') {
        // pc.printf("%s\r\n","detect_r");
        return 101110;
    }
    if (character == 'S'||character=='s') {
        //  pc.printf("%s\r\n","detect_s");
        return 11010;
    }
    if (character == 'T'||character=='t') {
        //  pc.printf("%s\r\n","detect_t");
        return 11110;
    }
    if (character == 'U'||character=='u') {
        //  pc.printf("%s\r\n","detect_u");
        return 100011;
    }
    if (character == 'V'||character=='v') {
        // pc.printf("%s\r\n","detect_v");
        return 101011;
    }
    if (character == 'W'||character=='w') {
        //pc.printf("%s\r\n","detect_w");
        return 11101;
    }
    if (character == 'X'||character=='x') {
        //pc.printf("%s\r\n","detect_x");
        return 110011;
    }
    if (character == 'Y'||character=='y') {
        // pc.printf("%s\r\n","detect_y");
        return 110111;
    }
    if (character == 'Z'||character=='z') {
        // pc.printf("%s\r\n","detect_z");
        return 100111;
    }
    if (character == '1') {
        //  pc.printf("%s\r\n","detect_1");
        return 100000;
    }
    if (character == '2') {
        //  pc.printf("%s\r\n","detect_2");
        return 101000;
    }
    if (character == '3') {
        //  pc.printf("%s\r\n","detect_3");
        return 110000;
    }
    if (character == '4') {
        // pc.printf("%s\r\n","detect_4");
        return 110100;
    }
    if (character == '5') {
        //  pc.printf("%s\r\n","detect_5");
        return 100100;
    }
    if (character == '6') {
        // pc.printf("%s\r\n","detect_6");
        return 111000;
    }
    if (character == '7') {
        //  pc.printf("%s\r\n","detect_7");
        return 111100;
    }
    if (character == '8') {
        //  pc.printf("%s\r\n","detect_8");
        return 101100;
    }
    if (character == '9') {
        //  pc.printf("%s\r\n","detect_9");
        return 11000;
    }
    if (character == '0') {
        //  pc.printf("%s\r\n","detect_0");
        return 11100;
    }
    if (character == '#') {
        // pc.printf("%s\r\n","detect_#");
        return 10111;
    }
    if (character == '?') {
        //pc.printf("%s\r\n","detect_?");
        return 110101;
    }
    if (character == '*') {
        //  pc.printf("%s\r\n","detect_*");
        return 100001;
    }
    if (character == '&') {
        //   pc.printf("%s\r\n","detect_&");
        return 111011;
    }
    if (character == '=') {
        //  pc.printf("%s\r\n","detect_=");
        return 111111;
    }
    if (character == '(') {
        //  pc.printf("%s\r\n","detect_(");
        return 101111;
    }
    if (character == '!') {
        //  pc.printf("%s\r\n","detect_!");
        return 11011;
    }
    if (character == ')') {
        //  pc.printf("%s\r\n","detect_)");
        return 11111;
    }
    if (character == '<') {
        //  pc.printf("%s\r\n","detect_<");
        return 101001;
    }
    if (character == '%') {
        //  pc.printf("%s\r\n","detect_%");
        return 110001;
    }
    if (character == ':') {
        //   pc.printf("%s\r\n","detect_:");
        return 100101;
    }
    if (character == '$') {
        //    pc.printf("%s\r\n","detect_$");
        return 111001;
    }
    if (character == ']') {
        //   pc.printf("%s\r\n","detect_]");
        return 111101;
    }
    //missing / test
    if (character == '[') {
        //   pc.printf("%s\r\n","detect_[");
        return 11001;
    }
    if (character == '/') {
        //   pc.printf("%s\r\n","detect_/");
        return 10010;
    }
    if (character == '+') {
        //  pc.printf("%s\r\n","detect_+");
        return 10011;
    }
    if (character == '#') {
        //  pc.printf("%s\r\n","detect_#");
        return 10111;
    }
    if (character == '>') {
        //  pc.printf("%s\r\n","detect_>");
        return 10110;
    }
    //Apostrophe test required...
    if (character == '-') {
        //  pc.printf("%s\r\n","detect_-");
        return 11;
    }
    if (character == '@') {
        //   pc.printf("%s\r\n","detect_@");
        return 10000;
    }
    if (character == '^') {
        //  pc.printf("%s\r\n","detect_^");
        return 10100;
    }
    //Quote test required...
    if (character == '_') {
        //  pc.printf("%s\r\n","detect_underscore");
        return 10101;
    }
    if (character == '.') {
        //   pc.printf("%s\r\n","detect_.");
        return 10001;
    }
    if (character == ';') {
        //  pc.printf("%s\r\n","detect_;");
        return 101;
    }
    if (character == ',') {
        //  pc.printf("%s\r\n","detect_,");
        return 1;
    }
    return 000000; //blank
}
