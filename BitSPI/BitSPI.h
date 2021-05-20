/*
 * 2021, Afinogeev Ruslan
 */


#pragma once
#include <Arduino.h>


class BitSPI{

    private:
        byte _miso;
        byte _mosi;
        byte _sck;
		
		void sendBit(byte value, byte bit);
		int quant;

    public:
        BitSPI(byte mosi, byte miso, byte sck, int speed = 9600);
		void begin();
		void end();
        byte* transfer(byte* data, byte sizeBit = 8, byte startBit = 0);
		void setSpeed(int speed);
};
