// this example is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple
/* this code is a mixture of code by Lukas Grasse and chase from chase'sWKshop youtube channel.
* Written by Ahmad Nejrabi for Robojax Video
* Date: Dec 09, 2017, in Ajax, Ontario, Canada
* Permission granted to share this code given that this
* note is kept with the code.
* Disclaimer: this code is "AS IS" and for educational purpose only.
*
/*Thanks to Robojax for the help with the code. Check out his videos on
*youtube and website Robojax.com*/
/*You can add as many displays by following the directions in the comments
 *edited by Chase Weatherford Youtube Channel Chase'sWKshop*/
/*Download source code if want here, http://robojax.com/learn/arduino/?vid=r ... 675-thermo */

// Using Mega2560 Arduino board
// 2 Max6675 Thermocouples
// 2 TM1637 Digital Displays

#include "max6675.h" //Max6675 thermocouple library include.
#include <Arduino.h>
#include <ModbusRtu.h>
#include <TM1637Display.h> //TM1637 display library include.

// data array for modbus network sharing
uint16_t au16data[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1};

/**
 * Modbus object declaration
 * u8id : node id = 0 for master, = 1..247 for slave
 * u8serno : serial port (use 0 for Serial)
 * u8txenpin : 0 for RS-232 and USB-FTDI
 * or any pin number > 1 for RS-485
 */
Modbus slave(1, 0, 0); // this is slave @1 and RS-232 or USB-FTDI

// Thermocouple 1
int thermoDO = 2; // First code you get from Max6675 library
int thermoCS = 3;
int thermoCLK = 4;

// Thermocouple 2
int thermoDO2 = 5; // Add a 2 to each int from first Thermocouple. Ex(ThermoDO to ThermoDO2).
int thermoCS2 = 6; // Change pins to the ones you use for your board. Can be any digital pins.
int thermoCLK2 = 7;

// Display 1 connection pins
// (Digital Pins)
int CLK = 8; // CLK and DIO pins numbers for Digital Display.
int DIO = 9;

// Display 2 connection pins
// (Digital Pins)
#define CLK2 10 // Copied contents of Display one and Changed CLK to CLK2 and
#define DIO2 11 // DIO to DIO2.

// The amount of time (in milliseconds) between tests
#define TEST_DELAY 2000

// display 1 setting TM1637Display from display to display1(CLK, DIO)
TM1637Display display1(CLK, DIO);

// display 2 copied contents of above code and changed display1 to display2, CLK to CLK2 and DIO to DIO2
TM1637Display display2(CLK2, DIO2);

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO); // Thermocouple 1
// int vccPin = 5; //Defining ThermoCLK, CS and DO to thermocouple
// int gndPin = 6; //also set vcc and gnd to pins 3 and 2 can change to other digital pins.

MAX6675 thermocouple2(thermoCLK2, thermoCS2, thermoDO2); // Thermocouple 2
// int vccPin2 = 11; //Copied above lines and added a 2 to thermocouple2 (thermoCLK2, thermoCS2, thermoDO2);
// int gndPin2 = 12; //also added a 2 to each vccPin2 and gndPin2 and set them to 51, 53. can change to other digital pins.

int led = 13;

// Display 1 uses vcc and gnd from 5v and gnd pin on board so we dont set a vccPin or a gndPin but you can if you want to.
//  TM1637Display (CLK, DIO);
//  int vccPin(name) = (pinhere)
//  int gndPin(name) = (pinhere)

// TM1637Display2 (CLK2, DIO2); //Display 2
//  int vccPin3 = 33; //Setting display2 CLK2, DIO2, vccPin3 and gndPin3.
//  int gndPin3 = 35;

void setup()
{
    slave.begin(19200); // 19200 baud, 8-bits, none, 1-bit stop
    // use Arduino pins

    // use Arduino pins
    // pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH); //setting pinModes for vcc and gnd to Thermocouple 1
    // pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

    // pinMode(vccPin2, OUTPUT); digitalWrite(vccPin2, HIGH); //setting pinModes for vcc and gnd to Thermocouple 2
    // pinMode(gndPin2, OUTPUT); digitalWrite(gndPin2, LOW); //Notice 2's after vccPin2 and gndPin2

    // pinMode(vccPin3, OUTPUT); digitalWrite(vccPin3, HIGH); //setting pinModes for vcc and gnd to display 2
    // pinMode(gndPin3, OUTPUT); digitalWrite(gndPin3, LOW); //Notice 3's after vccPin3 and gndPin3

    // pinMode(vccPin4, OUTPUT); digitalWrite(vccPin(name), HIGH); //if you use vccPin and gndPin for display 1 you can to set your pinModes here
    // pinMode(gndPin(name), OUTPUT); digitalWrite(gndPin(name), LOW); //

    Serial.println("MAX6675 test");
    // wait for MAX chip to stabilize
    delay(100);
}

void loop()
{
    display1.setBrightness(0x0f); // Display 1 void loop setup. Copied from TM1637 Library except for
    uint8_t data[] = {0x0, 0x0, 0x0, 0x0};
    display1.setSegments(data);
    delay(1);
    int temp = (int)thermocouple.readCelcius(); // this line and //got these two lines from Robojax youtube video.
    display1.showNumberDec(temp, true, 4, 0);      // this line
    // if you want to use Celsius, substitute .readFahrenheit with .readCelcius
    // Changed display to display1 //and unblock
    // Serial.print("C = ");
    // Serial.println(thermocouple.readCelsius());
    // below

    display2.setBrightness(0x0f);           // Display 2 void loop setup. Copied from above and changed
    uint8_t data2[] = {0x0, 0x0, 0x0, 0x0}; // changed data to data2
    display2.setSegments(data);             // display1 to display2
    delay(1);
    int temp2 = (int)thermocouple2.readCelcius(); // changed temp to temp2
    display2.showNumberDec(temp2, true, 4, 0);       // changed temp to temp2

    // Thermocouple 1 Reading to serial print. Celsius blocked to read fahrenheit.

    // Serial.print("C = ");
    // Serial.println(thermocouple.readCelsius());
    // Serial.print("F = ");
    //  Serial.println(thermocouple.readFahrenheit()); //Thermocouple 1 Reading

    // Thermocouple 2 Reading to serial print. Celsius blocked to read fahrenheit.

    // Serial.print("C = ");
    // Serial.println(thermocouple2.readCelsius());
    //  Serial.print("F = ");
    // Serial.println(thermocouple2.readFahrenheit()); //Thermocouple 2 Reading
    // Notice thermocouple.readFahrenheit changed to thermocouple2.readFahranheit

    au16data[2] = (uint16_t)(thermocouple.readCelsius() * 100);

    au16data[3] = (uint16_t)(thermocouple2.readCelsius() * 100);

    slave.poll(au16data, 16);

    for (int i = 1; i <= 99; i++)
    {
        if (i <= au16data[4])
            digitalWrite(led, HIGH);
        else
            digitalWrite(led, LOW);

        delay(5);
    }
}