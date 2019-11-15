Names: Jack Opgenorth and Justin Macenzie
ID #: 1580266
CMPUT 274 FA19

Assignment 2: Encrypted Arduino Communication (part 1)

Included files:
    encrypted_communication_part1.cpp
    README
    Makefile

Compenents:
 	2 Arduino Mega board
 	Breadboard
	male to male wires
	2 resistors


Running instructions:
	1. Connect and wire the arduinos
	2. Compile with "make"
 	3. Upload with "make upload"
 	4. Open Serial moniters

Wiring instructions:
	server pin (13)<---->resistor<----> 5V
	client pin (13)<----> resistor<---->ground
    	server pin (TX3 14)<---->client pin(RX3 15)
	server pin (RX3 15)<---->client pin(TX3 14)
	server ground<---->client ground
   

Notes and Assumptions:
	None
