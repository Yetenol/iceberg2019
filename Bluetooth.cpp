#include "Bluetooth.h"

/*

Format einer Nachricht: "[<message><checkbyte>]"
message = Nachricht
checkbyte = Summe aller char-Werte von message % 255 + 1

*/

bool Bluetooth::extractMessage(String input, String * output){
    *output = "";
    int i = 0;
    byte checksum = 0;

    //check for minimum length
    if(input.length() < 5){
        return false;
    }

    //check if '[' is followed by '<'
    i++
    if(input[i] != '<'){
        return false;
    }

    //read the message
    while( input[i] != '>' ){
        if(i+1 >= input.length()){
            return false;
        }
        (*output) += input[i];
        i++;
    }

    //check if there are enough chars left
    if(i+3 >= input.length()){
        return false;
    }

    //check if '[' is followed by '<'
    i++
    if(input[i] != '<'){
        return false;
    }

    //read checksum
    i++
    checksum = (byte) input[i];

    //check if checksum is followed by '>'
    i++
    if(input[i] != '>'){
        return false;
    }

    //check if checksum is correct
    int tempChecksum = 0;
    for(int i = 0; i<(*output).length(); i++){
        tempChecksum += (byte) output[i];
    }
    tempChecksum %= 255;
    tempChecksum += 1;
    if(tempChecksum != checksum){
        return false;
    }

    //zeigt an, dass Konvertierung erfolgreich war
    return true;
}

void send(String input){
    int checksum = 0;
    for(int i = 0; i<input.length(); i++){
        checksum += input[i];
    }
    checksum %= 255;
    checksum += 1;

    BOTTOM_SERIAL.print("[<");
    BOTTOM_SERIAL.print(input);
    BOTTOM_SERIAL.print("><");
    BOTTOM_SERIAL.write((byte)checksum);
    BOTTOM_SERIAL.print(">]");
}

bool Bluetooth::update(String input, String * output){
    bool newMessageAvailable = false;

    while(BLUETOOTH_SERIAL.available()){        //prüfe auf neue Bytes
        char tempBuffer;                        
        tempBufer = BLUETOOTH_SERIAL.read()     //liest neue Nachricht aus und speichert sie

        if(tempBuffer == '['){
            capture = true;
            buffer = "";
        }
        else if(tempBuffer == ']'){
            capture = false;
            if(extractMessage(buffer, &lastMessage)){
                newMessageAvailable = true;
            }
        }
        else if(capture){
            buffer += tempBuffer;
        }
    }

    return newMessageAvailable;

}

String Bluetooth::getMessage(){
    return lastMessage;
}