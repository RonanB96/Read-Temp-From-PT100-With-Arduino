/* This code calculates the temperature using a PT100, 
 * circuit diagram can be found here:https://circuits.io/circuits/2962051-reading-temperature-from-pt100#schematic
 * The circuit has a temperature range of -51.85 to 129.87 degrees C
 * or -61.33 to 265.73 degree fahrenheit.  
 * 
 * As the temperature equation fro the PT100 requires you to know the 
 * resistance of it, you'll need to convert the voltage to a resistance 
 * and this can be done by using y=mx+c formula(Rx=m*V+Roff) Rx is the pt100
 * resistance, m is the slope(ohms/volt), v is the voltage read into the analog pin
 * and Roff is the offset resistance(should be close to the real value you use when calculated.
 *  
 * To calculate the slope, you need to have the PT100 at steady state(settle at one temp) 
 * and measure its resistance then measure the voltage at analog pin, do this for again at a different 
 * temp.
 * Now we can find m: m=(R2-R1)/(V2-V1) eg from simulator (150-80)/(4.97-0.036)
 * m = 14.187 ohms/volt
 * to find c just fill one of the values into the Rx=m*V+c
 * c = 150-14.187*4.97 = 79.489ohms
 * 
 * Written by Roboro
 * Github: https://github.com/RonanB96/Read-Temp-From-PT100-With-Arduino
 * Blog: https://roboroblog.wordpress.com
  */

// You'll need to download this timer library from here
// http://www.doctormonk.com/search?q=timer 
#include "Timer.h"

// Define Variables
float V;
float temp;
float Rx;

// Variables to convert voltage to resistance
float C = 79.489;
float slope = 14.187;

// Variables to convert resistance to temp
float R0 = 100.0;
float alpha = 0.00385;

int Vin = A0; // Vin is Analog  Pin A0

Timer t; // Define Timer object

void setup() {
  Serial.begin(9600); // Set Baudrate at 9600
  pinMode(Vin,INPUT); // Make Vin Input
  t.every(100,takeReading); // Take Reading Every 100ms
}

void loop() {
  t.update(); // Update Timer
}

void takeReading(){
  // Bits to Voltage
  V = (analogRead(Vin)/1023.0)*5.0; // (bits/2^n-1)*Vmax 
  // Voltage to resistance
  Rx = V*slope+C; //y=mx+c
  // Resistance to Temperature
  temp= (Rx/R0-1.0)/alpha; // from Rx = R0(1+alpha*X)
  Serial.println(V);
}

