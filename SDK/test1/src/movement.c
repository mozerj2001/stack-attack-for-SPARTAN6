/*
 * movement.c
 *
 *  Created on: Dec 8, 2021
 *      Author: József Mózer
 *
 *  This .c source file contains the implementations of all functions
 *  declared in the movement header. These functions together provide full
 *  control over the player character, with regard to the framework system.
 */

#include "xparameters.h"
#include "structures.h"
#include "framework.h"
#include "testfunctions.h"


///////////////////////////////////////////////////////////////////////////////////
void jumpC(){
	playerC.vspeed = 6;
}
///////////////////////////////////////////////////////////////////////////////////
