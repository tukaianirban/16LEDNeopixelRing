This project uses an Arduino Nano as the microcontroller to display ring patterns on a 16-led Neopixel LED ring.
The data pin (3.3V) D6 on the Arduino is connected through a 200ohm resistor to 1A on a 74AHCT125N. 
A power-down transformer is used to convert 12V supply lines to 5V/3A output for use in the circuitry.
A 1000uF/16V capacitor is connected across the 5V supply power line to protect the complete circuitry from power(draw) surges.
 
The 74AHCT125N level shifter is used to bump up the data pin output(3.3V) from the Arduino to 5V. 
Vcc pin is connected to 5V input power line. /OE1 and GND pins are connected to GND.
1A pin is connected to the datapin on the Arduino. 1Y provides the level-shifted 5V data signals to use on the Nanopixels.

