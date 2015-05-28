char dummyvar; // dummy declaration for STUPID IDE!!!!
/*----------------------------------------------------------------------------
 * vi:ts=4
 *
 * i2cLCDguesser - guess i2c constructor for pcf8574 lcd backpack
 *
 * Created by Bill Perry 2013-04-16
 * Copyright 2013 - Under creative commons license 3.0:
 * Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)
 * license page: http://creativecommons.org/licenses/by-nc-sa/3.0/
 * 
 *  This sketch attempts to locate a pcf8574 based hd44780 backpack
 *  and then tries to figure out the pin configuration for it by guessing....
 *
 *  NOTE/WARNING: Guessing is not really a good thing since 
 *  depending on the hardware design and wiring,
 *  it could actually damage the hardware. Use with caution!!!
 *  and do not leave things with an incorrect guess for too long.
 *  i.e. advance to the next guess as soon as possible.
 * 
 *  It requires using fm's LiquidCrystal library replacement:
 *  https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home
 *
 *  For each guess it will re-initialize the display and
 *  write the constructor to the serial port.
 *  It will then attempt to blink the backlight 3 times.
 *  Finally it will attempt to write the constructor used to the LCD.
 *  When the correct configuration is guessed,
 *  the LCD will display the constructor
 *  and the backlight will be on.
 *
 * Since the guesser uses a limited number of known permutations,
 * it is possible that it will not be able to guess the needed
 * wiring.
 * 
 *  To use:
 *  1. install fm's library (it replaces the stock LiquidCrystal library)
 *  2. hookup the i2c backpack and only the i2c backpack to the Arduino
 *    (make sure to use the needed pullup resistors - 
 *      i2c needs them to work correctly)
 *  3. compile and upload the sketch
 *  4. go to the serial monitor in the IDE and set the baud rate to 9600 baud
 *  5. press the reset button on the arduino to start clean
 *  6. Press the <ENTER> key or [Send] button to advance to next guess
 *     NOTE: Make sure to select a newline as the line ending and
 *           if using the <ENTER> key you must first click on the text box
 *           to give it focus.
 *
 * Also note:
 * With respect to the the jumper on certain baords:
 * On the boards Ive seen so far, it controls the backlight control.
 * Depending on the board, it can
 * - force the backlight on
 * - force the backlight off
 * - allow backlight control by PCF8574
 *
 * So you may have to experiment with the jumper in/out to be able
 * to see anything on the display if you have a display that uses
 * light pixels on a dark background.
 *
 * Known Issue:
 * On chipkit platforms, with MPIDE mpide-0023-linux32-201311118-test
 * and earlier you must modify the twi.c file in
 * {installdir}/pic32/libraries/wire/utility/twic.
 * in the function twi_init()
 * Somthing in the clock stretching initalization causes the i2c module
 * to enter an infinite clock stretch and hang. A work around is to
 * change this:
 *----------------------------------------------------------------------
 *	ptwi->ixCon.reg = (1 << _I2CCON_ON) | (1 << _I2CCON_STREN);
 *----------------------------------------------------------------------
 * to this:
 *----------------------------------------------------------------------
 *	ptwi->ixCon.reg = 0; // disable then renable i2c module
 *	ptwi->ixCon.reg = (1 << _I2CCON_ON) | (1 << _I2CCON_STREN);
 *----------------------------------------------------------------------
 *  Created April 2013
 *  Author: Bill Perry
 * 
 * History
 * 2014-01-09 bperrybap - changed i2c bus scan to avoid reserved space
 * 2013.11.26 bperrybap - added a version number
 * 2013.11.24 bperrybap - added multiple device detection (not allowed)
 * 2013.08.01 bperrybap - added chip type detection
 * 2013.04.16 bperrybap - Original creation
 *
 * @author Bill Perry - bperrybap@opensource.billsworld.billandterrie.com
 *----------------------------------------------------------------------------*/

#define VERSION 141 // major.minor.point 120 is 1.2.0
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Try to detect if fm's library is being used
// and bomb out with an error if missing known defines
// or if using defines that fm's library is known not to use
#if !defined(BACKLIGHT_OFF) || !defined(BACKLIGHT_ON) || !defined(FOUR_BITS) || defined(En) || defined(Rw) || defined(Rs)
#error i2dLCDguesser requires using fmalpartida LiquidCrystal replacement library
#endif

#define LCD_COLS 16
#define LCD_ROWS 2

// hide STUPID ugly 1.x Wire API change nonsense
#if ARDUINO < 100
#define write(_data) send(_data)
#define read() receive()
#endif

#define 	IICchip_UNKNOWN 0
#define 	IICchip_PCF8574 1
#define 	IICchip_MCP23008 2

#define DEFPROMPT ((const char *) 0)


const char *i2cWarning = \
"----------------------------------------------------------------\n"\
"NOTE/WARNING: Guessing the i2c constructor is not really a\n"\
"good thing since it could damage the hardware. Use with caution!\n"\
"Do not leave things with an incorrect guess for too long.\n"\
"i.e. advance to the next guess as soon as possible\n"\
"when the guess in incorrect.\n"\
"If the guess is correct, the constructor will show up\n"\
"on the LCD.\n"\
"----------------------------------------------------------------\n"\
;

int locatedevice(void);
int guessconfig(uint8_t address);
int IdentifyIOexp(uint8_t address);
const char *iicType2Name(int type);

void setup()
{
	Wire.begin();
 
#if ARDUINO >= 100
	while(!Serial); // wait for native USB devices to enumerate/attach
#endif

	Serial.begin(9600);
	Serial.print("i2cLCDguesser v");
	Serial.print(VERSION/100);
	Serial.print('.');
	Serial.print((VERSION%100)/10);
	Serial.print('.');
	Serial.println((VERSION%100)%10);

	Serial.println(" - Guess constructor for i2c LCD backpack");
	Serial.println(i2cWarning);
	waitinput(DEFPROMPT);
}
 
void loop()
{
int address;
int chiptype;

	address = locatedevice(); // go look for a i2c device
	if(address >= 0)
	{
		chiptype = IdentifyIOexp((uint8_t)address);

		Serial.print("Device found: ");
		Serial.println(iicType2Name(chiptype));
		
		/*
		 * Check for PCF8574 chip
		 */
		if(chiptype != IICchip_PCF8574)
		{
			Serial.println("Only supports PCF8574");
		}
		else
		{
			waitinput("<Press <ENTER> or click [Send] to start guessing>");
			/*
 			 * Got i2c address, and PCF8574 so now go start trying configurations
			 */

			if( guessconfig((uint8_t) address))
				while(1); // user found config so halt
		}
	}
	delay(3000); // wait before looking again
}

/*
 * Returns address of first i2c device found, negative value if none found
 */

int locatedevice(void)
{
uint8_t error, address;
int rval = -1;
int devcount = 0;
 
	Serial.println("Scanning i2c bus for devices..");
 
	/*
 	 * Note: 
	 * 	Addresses below 8 are reserved for special use
	 * 	Addresses above 0x77 are reserved for special use
	 */
	for(address = 8; address <= 0x77; address++ )
	{
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if (error == 0)
		{
			devcount++;
			Serial.print("i2c device found at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address,HEX);
			rval = address;
		}
		else if (error==4)
		{
			Serial.print("Unknown error at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address,HEX);
		}   
	}
	if (rval < 0)
		Serial.println("No I2C device found");

	if (devcount > 1)
	{
		Serial.println("Warning: More than 1 device found");
		rval = -1; // for now we don't allow multiple devices on the bus
	}

	return(rval);
}

/*
 * Identify I2C device type.
 * Currently PCF8574 or MCP23008
 */

int IdentifyIOexp(uint8_t address)
{
uint8_t data;
int chiptype;

	/*
	 * Identify PCF8574 vs MCP23008
	 * It appears that on a PCF8574 that 1 bits turn on pullups and make the pin an input.
	 * and 0 bits set the output pin to 0.
	 * And a read always reads the port pins.
	 *
	 * Strategy:
	 *	- Try to Write 0xff to MCP23008 IODIR register (location 0)
	 *  - Point MCP23008 to IODIR register (location 0)
	 *	- Read 1 byte
	 *
	 * On a MCP23008 the read will return 0xff because it will read the IODIR we just wrote
	 * On a PCF8574 we should read a 0 since we last wrote zeros to all the PORT bits
	 */

	/*
	 * First try to write 0xff to MCP23008 IODIR
	 * On a PCF8574 this will end up writing 0 and then ff to output port
	 */
	Wire.beginTransmission(address);
	Wire.write((uint8_t) 0);	// try to point to MCP23008 IODR
	Wire.write((uint8_t) 0xff);	// try to write to MCP23008 IODR
	Wire.endTransmission();

	/*
	 * Now try to point MCP23008 to IODIR for read
	 * On a PCF8574 this will end up writing a 0 to the output port
	 */

	Wire.beginTransmission(address);
	Wire.write((uint8_t) 0);	// try to point to MCP23008 IODR
	Wire.endTransmission();

	/*
	 * Now read a byte
	 * On a MCP23008 we should read the 0xff we wrote to IODIR
	 * On a PCF8574 we should read 0 since the output port was set to 0
	 */
	Wire.requestFrom((int)address, 1);
	data = Wire.read();

	if(data == 0xff)
	{
		chiptype = IICchip_MCP23008;
	}
	else if (data == 0x00)
	{
		chiptype = IICchip_PCF8574;
	}
	else
	{
		chiptype = IICchip_UNKNOWN;
	}
	return(chiptype);
}
const char *iicType2Name(int type)
{
const char *name;
	switch(type)
	{
		case IICchip_PCF8574:
			name = "PCF8574";
			break;
		case IICchip_MCP23008:
			name = "MCP23008";
			break;
		default:
			name = "UNKNOWN";
			break;
	}
	return(name);
}

/*
 * Bit positions on i2c expander output port for LCD pins 
 */
typedef struct
{
	uint8_t en;
	uint8_t rw;
	uint8_t rs;
	uint8_t d4;
	uint8_t d5;
	uint8_t d6;
	uint8_t d7;
	uint8_t bl;
	__typeof__(POSITIVE) pol; // use typeof() for backward compability since polarity type name changed
} IICexpdata;



IICexpdata i2cparam[] = {
// EN, RW, RS, D4, D5, D6, D7, BL, POL
  { 2,  1,  0,  4,  5,  6,  7,  3, POSITIVE }, // YwRobot/DFRobot/SainSmart
  { 2,  1,  0,  4,  5,  6,  7,  3, NEGATIVE }, // Robot Arduino LCM1602/2004
  { 4,  5,  6,  0,  1,  2,  3,  7, NEGATIVE }, // MJKDZ board
  { 6,  5,  4,  0,  1,  2,  3,  7, NEGATIVE }, // I2CIO board modded for backlight (pnp transistor)
  { 6,  5,  4,  0,  1,  2,  3,  7, POSITIVE }, // I2CIO board modded for backlight (npn transistor)
  { 4,  5,  6,  0,  1,  2,  3,  7, POSITIVE }, // (extra combination of MJKDZ just in case...)
  {0xff} // end of guess table
};


int guessconfig(uint8_t address)
{
uint8_t guess = 0;
char buf[64];

	while(i2cparam[guess].en != 0xff)
	{

		Serial.print("Trying: ");

		sprintf(buf, "lcd(0x%02x, %d, %d, %d, %d, %d, %d, %d, %d, %s)",
			 address,
			 i2cparam[guess].en,
			 i2cparam[guess].rw,
			 i2cparam[guess].rs,
			 i2cparam[guess].d4,
			 i2cparam[guess].d5,
			 i2cparam[guess].d6,
			 i2cparam[guess].d7,
			 i2cparam[guess].bl, i2cparam[guess].pol == POSITIVE ? "POSITIVE" : "NEGATIVE");
		Serial.println(buf);
			
		/*
		 * initialize constructor with guess
		 */
		LiquidCrystal_I2C lcd = LiquidCrystal_I2C(
					 address,
					 i2cparam[guess].en,
					 i2cparam[guess].rw,
					 i2cparam[guess].rs,
					 i2cparam[guess].d4,
					 i2cparam[guess].d5,
					 i2cparam[guess].d6,
					 i2cparam[guess].d7,
					 i2cparam[guess].bl,
					 i2cparam[guess].pol);

		lcd.begin(LCD_ROWS, LCD_COLS);

		/*
		 * Quick 3 blinks of backlight
		 */
		for(int i = 0; i< 3; i++)
		{
			lcd.backlight();
			delay(250);
			lcd.noBacklight();
			delay(250);
		}
		lcd.backlight();

		lcd.clear();
		sprintf(buf, "0x%02x,%d,%d,%d,%d,",
			 address,
			 i2cparam[guess].en,
			 i2cparam[guess].rw,
			 i2cparam[guess].rs,
			 i2cparam[guess].d4);
		lcd.print(buf);

		sprintf(buf, "%d,%d,%d,%d,%s",
			 i2cparam[guess].d5,
			 i2cparam[guess].d6,
			 i2cparam[guess].d7,
			 i2cparam[guess].bl, i2cparam[guess].pol == POSITIVE ? "POSITIVE" : "NEGATIVE");
		lcd.setCursor(0, 1);
		lcd.print(buf);

		waitinput(DEFPROMPT);
		lcd.clear();
		guess++;
	}
	return(0);
}
#undef read // ugly but removes Wire libary function mapping done above
void waitinput(const char *prompt)
{
	if(prompt)
		Serial.print(prompt);
	else
		Serial.print("<Press <ENTER> or click [Send] to Continue>");

	while(Serial.available())
		Serial.read(); // swallow all input

	while(!Serial.available()){} // wait on serial input

	Serial.println();
}
