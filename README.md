AS3935-Arduino-Library
======================

AS3935 Franklin Lightning Sensor™ IC by AMS Arduino library

Link to manufacturer site:

&nbsp;&nbsp;&nbsp;&nbsp;http://www.ams.com/eng/Products/RF-Products/Lightning-Sensor/AS3935

Link to my blog:

&nbsp;&nbsp;&nbsp;&nbsp;http://www.rrkb.lv/musings

To use is chip/board, you will definitely need to read it's datasheet, so
I am not going to dwell into details of tuning and using this small gem.

Tested with Arduino 1.0.1 on Arduino Mega 2560 and mpide-0023-20120903-newlib on
chipKIT Max32.

Connections between breakout by TAUTIC LLC and chipKIT Max32 or Arduino Mega 2560
for example code to work:

	breakout pin    arduino pin

	VDD             3.3V - Max32, 5V - Mega 2560
	GND             GND
	MOSI            51
	MISO            50
	SCLK            52
	IRQ             2
	SI              GND
	CS              53

NB! on Mega 2560 you have to comment out attachInterrupt(1,AS3935Irq,RISING); line and
uncomment attachInterrupt(0,AS3935Irq,RISING); line

Short function reference:
	AS3935(byte (*SPItransfer)(byte),int csPin,int irq);
&nbsp;&nbsp;&nbsp;&nbsp;object constructor, first parameter is pointer to a function that
&nbsp;&nbsp;&nbsp;&nbsp;does SPI transfer, second parameter is pin that has to be used as
&nbsp;&nbsp;&nbsp;&nbsp;chip select and third parameter is interrupt pin
	
	void registerWrite(byte reg, byte mask, byte data)
&nbsp;&nbsp;&nbsp;&nbsp;write to specified register specified data using specified bitmask,
&nbsp;&nbsp;&nbsp;&nbsp;the rest of the register remains intact

	byte registerRead(byte reg, byte mask)
&nbsp;&nbsp;&nbsp;&nbsp;read specified register using specified bitmask and return value aligned
&nbsp;&nbsp;&nbsp;&nbsp;to lsb, i.e. if value to be read is in a middle of register, function
&nbsp;&nbsp;&nbsp;&nbsp;reads register and then aligns lsb of value to lsb of byte

	void reset()
&nbsp;&nbsp;&nbsp;&nbsp;reset all the registers on chip to default values

	bool calibrate()
&nbsp;&nbsp;&nbsp;&nbsp;perform calibration routine, calibrate receiving antenna tank and then
&nbsp;&nbsp;&nbsp;&nbsp;instruct the chip to calibrate both RCOs present on chip

	void powerDown()
&nbsp;&nbsp;&nbsp;&nbsp;put chip into power down mode

	void powerUp()
&nbsp;&nbsp;&nbsp;&nbsp;bring chip out of power down mode and perform RCO calibration

	int interruptSource()
&nbsp;&nbsp;&nbsp;&nbsp;return interrupt source, bitmask, 0b0001 - noise, 0b0100 - disturber,
&nbsp;&nbsp;&nbsp;&nbsp;0b1000 - lightning

	void disableDisturbers()
&nbsp;&nbsp;&nbsp;&nbsp;disable indication of disturbers

	void enableDisturbers()
&nbsp;&nbsp;&nbsp;&nbsp;enable indication of distrubers

	int getMinimumLightnings()
&nbsp;&nbsp;&nbsp;&nbsp;return number of lightnings that need to be detected in 17 minute period
&nbsp;&nbsp;&nbsp;&nbsp;before interrupt is issued

	int setMinimumLightnings(int minlightning)
&nbsp;&nbsp;&nbsp;&nbsp;set number of lightnings that need to be detected in 17 minute period
&nbsp;&nbsp;&nbsp;&nbsp;before interrupt is issued

	int lightningDistanceKm()
&nbsp;&nbsp;&nbsp;&nbsp;return distance to lightning in kilometers, 1 means storm is overhead,
&nbsp;&nbsp;&nbsp;&nbsp;63 means it is too far to reliably calculate distance

	void setIndoors()
&nbsp;&nbsp;&nbsp;&nbsp;load gain preset to operate indoors

	void setOutdoors()
&nbsp;&nbsp;&nbsp;&nbsp;load gain preset to operate outdoors

	int getNoiseFloor()
&nbsp;&nbsp;&nbsp;&nbsp;return noise floor setting - refer to datasheet for meaning and range

	int setNoiseFloor(int noisefloor)
&nbsp;&nbsp;&nbsp;&nbsp;set noise floor setting

	int getSpikeRejection()
&nbsp;&nbsp;&nbsp;&nbsp;return spike rejection value - refer to datasheet for meaning and range

	int setSpikeRejection(int srej)
&nbsp;&nbsp;&nbsp;&nbsp;set spike rejection value

	int getWatchdogThreshold()
&nbsp;&nbsp;&nbsp;&nbsp;return watchdog threshold value - refer to datasheet for meaning and range

	int setWatchdogThreshold(int wdth)
&nbsp;&nbsp;&nbsp;&nbsp;set watchdog threshold value

	void clearStats()
&nbsp;&nbsp;&nbsp;&nbsp;clear internal accumulated lightning statistics
