#ifdef _CLIKTS

#include <stdlib.h>
#include "CLKTSDefines.h"
#include "CLVentilationControl.h"
#include "VS\KTS\CLIKTS\CLIKTS.h"

using Climalombarda::KTS::CLIKTS;


unsigned long millis()
{
	long	millis	= System::DateTime::Now.Ticks / System::TimeSpan::TicksPerMillisecond;
	return millis;
}

void delay( unsigned long millisencond )
{
	System::Threading::Thread::Sleep( millisencond );
}

void delayMicroseconds( unsigned int us )
{
	// TODO: vedere di effettuare il ritardo corretto in microseconds
	System::Threading::Thread::Sleep( 1 );
}

long random(long)
{
	return 0L;
}

long random( long range1, long range2 )
{
	// TODO: Da rivedere
	return (range1 + rand());
}

void randomSeed( unsigned int seed )
{
	srand( seed );   // should only be called once
}

double sin( double )
{
	return 0.0;
}

double cos( double )
{
	return 0.0;
}

double pow( double x, double y )
{
	return 0.0;
}

void pinMode( uint8_t pin, uint8_t mode )
{
}

void digitalWrite(uint8_t pin, uint8_t val)
{
}

int digitalRead(uint8_t pin)
{
	return 0;
}

int analogRead(uint8_t)
{
	return 0;
}

void analogWrite(uint8_t, int)
{
}

void KTSRun()
{
	setup();
	VentilationControl_Write( CLVentilationControl_FSC );

	while (true)
	{
		loop();
	}
}


void Serial::begin( int baudRate )
{
	if (CLIKTS::SerialPort == nullptr)
		return;

	CLIKTS::SerialPort->Close();
	CLIKTS::SerialPort->BaudRate	= baudRate;
	CLIKTS::SerialPort->Open();
}

int Serial::available()
{
	if (CLIKTS::SerialPort != nullptr
		&& CLIKTS::SerialPort->IsOpen)
		return CLIKTS::SerialPort->BytesToRead;

	return 0;
}

int Serial::read()
{
	if (CLIKTS::SerialPort != nullptr
		&& CLIKTS::SerialPort->IsOpen)
	{
		if (CLIKTS::SerialPort->BytesToRead > 0)
			return CLIKTS::SerialPort->ReadByte();
	}

	return -1;
}

int Serial::write( byte* buff, int len )
{
	if (CLIKTS::SerialPort != nullptr
		&& CLIKTS::SerialPort->IsOpen)
	{
		array<Byte>^	byteArray = gcnew array<Byte>( len );

		System::Runtime::InteropServices::Marshal::Copy( (IntPtr) buff, byteArray, 0, len );

		CLIKTS::SerialPort->DiscardOutBuffer();
		CLIKTS::SerialPort->Write( byteArray, 0, len );

		return len;
	}

	return 0;
}


#endif

