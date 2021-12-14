/*
 * movement.h
 *
 *  Created on: Dec 8, 2021
 *      Author: József Mózer
 *
 *  This header file contains the declarations of every function
 *  that controls the movement of the player character in some way.
 *  List:		- jumpC
 *
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

/*
 * This function makes the character jump, by giving it a v0 vertical
 * speed.
 * INPUT: none
 * OUTPUT: none
 * */
void jumpC();

/*
 * This function reads the navi switch values and modifies the model/framework
 * accordingly. It should be called every cycle. Always have a delay function after
 * to account for oscillations.
 * INPUT: none
 * OUTPUT: none
 * */
void readNavi();

#endif /* MOVEMENT_H_ */
