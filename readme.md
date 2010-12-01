RGBspokePOV - A Full Color Persistence of Vision Toy
====================================================
This project is build onto of Jan Paul Posma's work for his *PimpMyBike* personal project which also has an [inactive repo on github](http://github.com/abritinthebay/PimpMyBike).

This repo is intended, with his blessing, to turn his personal project into a well documented and hopefully improved codebase and hardware platform. 

## Project Goals ##

These can be read in the roadmap file included with these source files.

### Jan Paul's Original Notes ###

> 1. Bear in mind that I created this when I was 17. While the board is of pretty high quality (they still work!), and the firmware works quite good too, the Java code is horrible. A friend of mine created a project similar to the LadyAda thing [ed - spokePOV, single color], and he wrote this program, and I tried to convert it for RGB and that shows. For example, there is still a button for a COM-port connection, although this one works fully with USB!

> 2. From what I can figure out right now, you have to split the hex file at 0x300 and create two files: firma.hex and firmb.hex. Then the Java program will assemble the final hex from these files and the image code that belongs in between.

> 3. The bootloader is pretty standard stuff, so you can probably also use an updated version, e.g. from usbpicprog.org. The important thing is the line in Bootloader/main.c where it enters the program once the magnet switch is toggled.

> 4. Biertje.hex is the (Heineken) star, and haha.hex is (I think) the Dutch flag at one side of the wheel, and a nuclear sign at the other side. :-)

> 5. I think that I've also got some components laying around here. Most interesting would be the components for the switching power supply, as this part of the board was designed to fit my components exactly. A bit of advice: spend enough money on good RGB LEDs! I got some cheap-ass components and now the blue channel is ruined on these LEDs. Blue tends to go down first, as it's most sensitive to heat. So take good care when buying these parts.

## Licence ##

*RGBspokePOV, A Full Color Persistence of Vision Toy*
Original Project Copyright (C) 2007 Jan Paul Posma
This Project Copyright (C) 2010 Project Contributors.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not see http://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
