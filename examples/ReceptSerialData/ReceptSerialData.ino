#include <DataProcess.h>


bool getMesage(char *msg,int size);
int pin_led = 13;
char msg[151];

void setup(){
    //Serial.begin(115200);// for ESP32 and ESP12
    Serial.begin(9600);// for Arduino
    pinMode(pin_led,OUTPUT);
}
void loop(){
    if(getMesage(str,150)){
        int estado;
        char value[26];
        if(loadCommand(msg,"setLed","d",&estado)){// msg must be "setLed:1 "
            digitalWrite(pin_led,estado);
        } else if(loadCommand(msg,"print","s[25]",value)){//msg must be "print:[[anything]]"
            Serial.println(value);
        }else{
            Serial.print("Command not find:");
            Serial.print(msg);
        }
    }
}

bool getMesage(char *msg,int size){
    if(Serial.available()){
        int i = 0;
        while(i<size && Serial.available()){
            msg[i++] = Serial.read();
        }
        msg[i]=0;
        return true;
    }
    return false;
}
