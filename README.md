The design and simulation for this project is accomplished the use of Tinkercad; circuit fabrication is finished the use of Arduino; and real-time records monitoring is done via communique with the ThingSpeak cloud.

Component Required in the Tinkercad Version of Fire and Gas Detection:
"U1"	        1              	" Arduino Uno R3"
"GAS1"    	  1             	" Gas Sensor"
"R1,R2,R3,R4"	4	              " 220 Ω Resistor"
"PIEZO1,2"	  2             	" Piezo"
"U2"	        1             	" IR sensor"
"D1"	        1             	" Green LED"
"D2"	        1             	" Yellow LED"
"D3"	        1	              " Red LED"


•	Microcontroller (Arduino Uno): Processes sensor signals and triggers alerts.
•	Gas Sensor (MQ6): Detects combustible gases and smoke.
•	Infrared Sensor: Identifies heat and fire by detecting infrared radiation.
•	Buzzer: Activates audible alerts when a fire is detected.

The proposed IoT fire detection system operates by continuously monitoring the environment for changes in gas concentration and infrared radiation. When the gas sensor detects a significant rise in combustible gases or the infrared sensor identifies elevated infrared radiation indicative of a fire, they send signals to the microcontroller.

