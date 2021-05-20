/*
 * 2021, Afinogeev Ruslan
 */


#include <BitSPI.h>

BitSPI::BitSPI(byte mosi, byte miso, byte sck, int speed = 9600) {
    _mosi = mosi;
    _miso = miso;
    _sck = sck;
	setSpeed(speed);
} 

void BitSPI::begin() {
    pinMode(_mosi, OUTPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, OUTPUT);
	digitalWrite(_sck, LOW);
}

void BitSPI::end() {
    pinMode(_mosi, INPUT);
    pinMode(_miso, INPUT);
    pinMode(_sck, INPUT);
}

byte* BitSPI::transfer(byte* data, byte sizeBit = 8, byte startBit = 0) {
    byte* out = 0;
	
	Serial.println(*data, DEC);
	Serial.println(sizeBit, DEC);
	byte quantityByte = (sizeBit-1+startBit)/8+1u;
	Serial.println(quantityByte, DEC);
	byte stopBit = quantityByte>1?(sizeBit-1+startBit)%8:(sizeBit-1+startBit);
	Serial.println(stopBit, DEC);
	byte countBit = 0;
	

    for(byte ibyte = 0; ibyte < quantityByte; ibyte++)
    {
		byte curByte = *(data + ibyte);
		byte shift = ibyte?0:startBit;
		byte stop = ((ibyte+1)==quantityByte)?stopBit:7;
		
		Serial.println(shift, DEC);
		Serial.println(stop, DEC);
		Serial.println(curByte, DEC);
		
		for(byte ibit = shift; ibit<=stop; ibit++)
			sendBit(curByte, ibit);
		digitalWrite(_mosi, LOW);
    }
	
	Serial.println();
	Serial.println(1111111, DEC);
    return out;
}

void BitSPI::sendBit(byte value, byte bit) {
	
	Serial.print(bitRead(value, 7-bit), BIN);
	digitalWrite(_mosi, bitRead(value, 7-bit));
	delayMicroseconds(quant);
	digitalWrite(_sck, HIGH);
	delayMicroseconds(2*quant);
	digitalWrite(_sck, LOW);
	delayMicroseconds(quant);
}

void BitSPI::setSpeed(int speed) {
	quant = 500;//int((1./float(speed))*1000000./4.);
}
