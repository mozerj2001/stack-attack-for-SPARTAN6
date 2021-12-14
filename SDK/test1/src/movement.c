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
	if(playerC.isFalling == 0){
		playerC.vspeed = -10;
		playerC.jumpStart = 1;
	}
}
///////////////////////////////////////////////////////////////////////////////////
void readNavi(){
	unsigned int naviValue = (*NAVI_POINTER);

	switch(naviValue){
		case 1:
			jumpC();
			break;
		case 4:
			playerC.hspeed = -4;
			break;
		case 8:
			playerC.hspeed = 4;
			break;
		case 5:
			playerC.hspeed = -4;
			jumpC();
			break;
		case 9:
			playerC.hspeed = 4;
			jumpC();
			break;
		default:
			playerC.hspeed = 0;
	}
}
