AS3935-Arduino-Library
======================

AS3935 Franklin Lightning Sensor™ IC by AMS Arduino library
<pre>
Link to manufacturer site:
	http://www.ams.com/eng/Products/RF-Products/Lightning-Sensor/AS3935
Link to TAUTIC ELECTRONICS LLC Lightning Sensor Board on tindie.com:
	https://tindie.com/TAUTIC/as3935-lightning-sensor-board/
Link to my blog:
	http://www.rrkb.lv/musings

To use is chip/board, you will definitely need to read it's datasheet, so
I am not going to dwell into details of tuning and using this small gem.

Tested with Arduino 1.0.1 on Arduino Mega 2560 and mpide-0023-20120903-newlib on
chipKIT Max32 (earlier mplab releases have crippled c/c++ library support and
will not work).

Short function reference:

void registerWrite(byte reg, byte mask, byte data)
	write to specified register specified data using specified bitmask,
	the rest of the register remains intact
byte registerRead(byte reg, byte mask)
	read specified register using specified bitmask and return value aligned
	to lsb, i.e. if value to be read is in a middle of register, function
	reads register and then aligns lsb of value to lsb of byte
void reset()
	reset all the registers on chip to default values
bool calibrate()
	perform calibration routine, calibrate receiving antenna tank and then
	instruct the chip to calibrate both RCOs present on chip
void powerDown()
	put chip into power down mode
void powerUp()
	bring chip out of power down mode and perform RCO calibration
int interruptSource()
	return interrupt source, bitmask, 0b0001 - noise, 0b0100 - disturber,
	0b1000 - lightning
void disableDisturbers()
	disable indication of disturbers
void enableDisturbers()
	enable indication of distrubers
int getMinimumLightnings()
	return number of lightnings that need to be detected in 17 minute period
	before interrupt is issued
int setMinimumLightnings(int minlightning)
	set number of lightnings that need to be detected in 17 minute period
	before interrupt is issued
int lightningDistanceKm()
	return distance to lightning in kilometers, 1 means storm is overhead,
	63 means it is too far to reliably calculate distance
void setIndoors()
	load gain preset to operate indoors
void setOutdoors()
	load gain preset to operate outdoors
int getNoiseFloor()
	return noise floor setting - refer to datasheet for meaning and range
int setNoiseFloor(int noisefloor)
	set noise floor setting
int getSpikeRejection()
	return spike rejection value - refer to datasheet for meaning and range
int setSpikeRejection(int srej)
	set spike rejection value
int getWatchdogThreshold()
	return watchdog threshold value - refer to datasheet for meaning and range
int setWatchdogThreshold(int wdth)
	set watchdog threshold value
void clearStats()
	clear internal accumulated lightning statistics
</pre>
