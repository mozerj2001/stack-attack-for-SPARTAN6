/*
 * framework.c
 *
 *  Created on: Nov 24, 2021
 *      Author: J�zsef M�zer
 *
 *  This .c source file contains the implementations of all functions
 *  declared in the framework header. These functions together are the "game engine".
 */

#include "structures.h"
#include "framework.h"

///////////////////////////////////////////////////////////////////////////////////

struct object boxesArray[BOXES_COUNT];

struct character playerC;

int* FB_POINTER  = XPAR_AXI_APB_BRIDGE_0_BASEADDR + 65536;

unsigned int characterPixels[16][15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0x2A, 0x2A, 0x2A, 0x2A, 0x0B, 0x3F, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0x0B, 0x2A, 0x0B, 0x0B, 0x0B, 0x39, 0x0B, 0x0B, 0, 0, 0, 0,
										 0, 0, 0, 0, 0x0B, 0x2A, 0x2A, 0x0B, 0x0B, 0x0B, 0x0B, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0, 0x0B, 0x0B, 0x0B, 0x0B, 0, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0, 0, 0, 0, 0,
										 0, 0, 0, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0, 0, 0, 0, 0,
										 0, 0, 0, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0x23, 0x23, 0x23, 0x23, 0, 0, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0, 0x05, 0x05, 0x05, 0, 0, 0, 0, 0, 0, 0, 0,
										 0, 0, 0, 0, 0, 0x05, 0x05, 0x05, 0x05, 0, 0, 0, 0, 0, 0, 0};



///////////////////////////////////////////////////////////////////////////////////
void setupObjects(){
	unsigned int i = 0;
	unsigned int n = 0;
	unsigned int m = 0;

	for(; i < BOXES_COUNT; i++){
		boxesArray[i].position.x = 0;
		boxesArray[i].position.x = 0;
		boxesArray[i].isFalling = 1;
		boxesArray[i].isDeployed = 0;
	}
	playerC.position.x = 71;
	playerC.position.y = 30;
	playerC.vspeed = 0;
	playerC.hspeed = 0;
	playerC.isFalling = 0;
	for(m = 0; m < 10; m++){
		for(n = 0; n < 10; n++){
			playerC.pixels[m][n] = characterPixels[m][n];
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
void objectToFB(struct coords coordinates){
	unsigned int m = 0;
	unsigned int n = 0;
	int* rowPtr = FB_POINTER + coordinates.y * 160;

	for(n = 0; n < 15; n++){
		for(m = 0; m < 16; m++){
			*(rowPtr + coordinates.x + m) = 0x3F;
		}
		rowPtr += 160;
	}
}
///////////////////////////////////////////////////////////////////////////////////
void characterToFB(unsigned int** rgbMap, struct coords coordinates){
	unsigned int m = 0;
	unsigned int n = 0;
	int* rowPtr = FB_POINTER + coordinates.y * 160;


	for(n = 0; n < 15; n++){
		for(m = 0; m < 16; m++){
			*(rowPtr + coordinates.x + m) = rgbMap[m][n];
		}
		rowPtr += 160;
	}
}
