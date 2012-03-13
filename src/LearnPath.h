/*
  LearnPath.h - Roboter Moving Library
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

#ifndef LEARN_PATH_H
#define LEARN_PATH_H

#include <Move.h>

/**
 *  Defines methods for learning paths for autonomous movements.
 */
class LearnPath : public Move {

public:

    LearnPath();

		/** Find a path to point given in polar coordinates around barriers. */
		void LearnOrthogonalPath(unsigned long distance, uint8_t degree);

		/** Moves in concentric circles until told otherwise. */
		void searchCircles();
		
		/** Make a map of all barriers. */
		void map();
};

#endif