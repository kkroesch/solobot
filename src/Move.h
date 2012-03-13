/*
  Move.h - Roboter Moving Library
  2012 Copyright (c) Karsten Kroesch. All right reserved.

  Original Author: Karsten Kroesch <karsten@kroesch.de>

	NOTE: --
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MOVE_H
#define MOVE_H

#include <inttypes.h>
#include <Arduino.h>

//Initialization Commands or Responses
//#define UART_READY		0xA3
//#define SLCD_INIT_ACK		0xA5
//#define SLCD_INIT_DONE		0xAA
//#define SLCD_INVALIDCOMMAND	0x46


/**
 *  Defines methods for autonomous movement of the robot.
 */
class Move {

public:

    Move();

		/** Check if one or more sensors are below safety distance. */
		uint8_t checkDistance();
    
		/** Set speed of motors in percent (0 .. 100). */
		void setSpeed(uint8_t speed);

		/** Read accumulated distance from sensors. */
		unsigned long getDistance();

		/** Set distance to zero for next path segment. */
		void resetDistance();

		/** Just move forward infinitely until told otherwise. */
		void march();

		/** Turn to specific degree in range (0 .. 360). 
		  * Implement this according to available sensors.
		  */
		void turn(uint8_t degree);
		
		/** Turn left 90° from current heading. Convenience method. */
		void turnLeft();

		/** Turn right 90° from current heading. Convenience method. */
		void turnRight();

		/** Gets current heading in range (0 .. 360).
		  * Implement this according to available sensors.
		  */
		uint8_t getDegree();

		/** Halt the motors. */
		void stop();
};

#endif