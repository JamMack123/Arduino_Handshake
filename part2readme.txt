Names: Jack Opgenorth and Justin Macenzie
ID # (Jack Opgenorth): 1580266 
CMPUT 274 FA19

Assignment 2: Encrypted Arduino Communication (part 2)



Included files:
    encrypted_communication_part2.cpp
    README
    Makefile

Components:
 	2 Arduino Megaboards
 	Breadboard
	male to male wires
	2 resistors
	USB Cables


Running instructions:
	1. Connect and wire the arduinos
	2. Compile with "make" on each arduino
 	3. Upload with "make upload" on each arduino
 	4. Open each Serial monitor and begin inputting once
	   handshaking is finished.

Wiring instructions:
	server pin (13)<---->resistor<---->5V
	client pin (13)<----> resistor<---->ground
    	server pin(TX3 14)<---->client pin(RX3 15)
	server pin(RX3 15)<---->client pin(TX3 14)
	server ground<---->client ground
   

Notes and Assumptions:
	The Mulmod and Powmod functions from our part 1 submission would
	not work for some keys we generated, despite working for our
	part 1 solution. Because of this we are using the mulmod and powmod functions 
	in the part 1 solution posted on eclass

	We are also using the upper_sqrt and isPrime function from the primality morning
	problem, and the gcd_euclid_fast function from eclass, 

	Note that when a device is ready to chat, it is locked in that state until it is
	reset
	
	Code for part 2 starts at around line 108








