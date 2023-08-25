#include "wled.h"
#include <HardwareSerial.h>
#include <stdio.h>

HardwareSerial SerialPort(0);
long _lastRead = millis() - 2001;
long _lastRead2 = millis() - 2001;
long _lastRead3 = millis() - 2001;
Segment &front;
Segment &back;
Segment &bar;

uint8_t fade_time = 50;

/*
 * This v1 usermod file allows you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
 * If you just need 8 bytes, use 2551-2559 (you do not need to increase EEPSIZE)
 *
 * Consider the v2 usermod API if you need a more advanced feature set!
 */

//Use userVar0 and userVar1 (API calls &U0=,&U1=, uint16_t)

//gets called once at boot. Do all initialization that doesn't depend on network here
void userSetup()
{
    //_lastRead = millis();
    front = strip.getSegment(0);
    //back = strip.getSegment(1);
    //bar = strip.getSegment(2);
    //SerialPort.begin(15200, SerialConfig::SERIAL_8N1);
}

//gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{

}

//loop. You can use "if (WLED_CONNECTED)" to check for successful connection
void userLoop() {
    if (_lastRead > millis() - 5000) {

        if (front.colors[1] != 0xFFFFFF) {
            front.colors[1] = 0xFFFFFF;
        } else {
            front.colors[1] = 0xFF0000;
        }

        colorUpdated(CALL_MODE_DIRECT_CHANGE);
        _lastRead = millis();
    }

    if (_lastRead2 > millis() - 17000) {
        front.colors[1] = 0xFFFFFF;
        front.colors[2] = 0xFFFFFF;
        colorUpdated(CALL_MODE_DIRECT_CHANGE);
        _lastRead2 = millis();
    }

    if (_lastRead3 > millis() - 27000) {
        adc_triggered();
        _lastRead3 = millis();
    }

}

void forward() {
    front.colors[1] = 0xFFFFFF;
    //back.colors[1] =  0xFF0000;
}

void reverse() {
    front.colors[1] = 0xFF0000;
    //back.colors[1] =  0xFFFFFF;
}

void adc_triggered() {
    front.intensity = 255;
    colorUpdated(CALL_MODE_DIRECT_CHANGE);
    front.fade_out(fade_time);
    colorUpdated(CALL_MODE_DIRECT_CHANGE);
}

void updateBatteryBar() {

}

void readUART() {
    int incomingByte = 0;

    if (SerialPort.available()) {
        incomingByte = SerialPort.read();
        //sprintf("Received: %s", incomingByte);
    }
}
