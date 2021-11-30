/*
 * framework.c
 *
 *  Created on: Nov 24, 2021
 *      Author: József Mózer
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

unsigned int deployedBoxes = 0;



///////////////////////////////////////////////////////////////////////////////////
void delay(unsigned int x){
	unsigned int i = 0;
	for(; i < 10000 * x; i++);
}
///////////////////////////////////////////////////////////////////////////////////
void setupObjects(){
	unsigned int i = 0;
	unsigned int n = 0;
	unsigned int m = 0;

	for(; i < BOXES_COUNT; i++){
		boxesArray[i].position.x = 0;
		boxesArray[i].position.y = 0;
		boxesArray[i].hspeed = 0;
		boxesArray[i].isFalling = 1;
		boxesArray[i].isHorizontallyBlocked = 0;
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

	for(n = 0; n < 8; n++){
		for(m = 0; m < 8; m++){
			if(m == 0 || m == 7 || n == 0 || n == 7){
				*(rowPtr + coordinates.x + m) = 0x30;
			}
			else{
				*(rowPtr + coordinates.x + m) = 0x3F;
			}
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
///////////////////////////////////////////////////////////////////////////////////
void deployBox(struct coords depPosition){
	boxesArray[deployedBoxes].position.x = depPosition.x;
	boxesArray[deployedBoxes].position.y = depPosition.y;
	boxesArray[deployedBoxes].hspeed = 0;
	boxesArray[deployedBoxes].isFalling = 1;
	boxesArray[deployedBoxes].isHorizontallyBlocked = 0;

	deployedBoxes++;
}
///////////////////////////////////////////////////////////////////////////////////
void updateStates(){
	unsigned int i = 0;
	unsigned int k;

	for(; i < deployedBoxes; i++){

		if(boxesArray[i].position.y == 112){ boxesArray[i].isFalling = 0; }
		else{
			for(k = 0; k < deployedBoxes; k++){
				if(((boxesArray[i].position.x / 8) == (boxesArray[k].position.x / 8)) && (boxesArray[k].position.y - boxesArray[i].position.y) <= 8){
					boxesArray[i].isFalling = 0;
				}
			}
		}

		if(boxesArray[i].isHorizontallyBlocked == 0){
			for(k = 0; k < deployedBoxes; k++){
				if(boxesArray[i].position.y == boxesArray[k].position.y && ((boxesArray[i].position.x - boxesArray[k].position.x) <= 8 && (boxesArray[i].position.x - boxesArray[k].position.x) >= -8)){
					boxesArray[i].isHorizontallyBlocked = 1;
				}
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
void updatePositions(){
	unsigned int i = 0;

	for(; i < deployedBoxes; i++){
		if(boxesArray[i].isFalling){
			boxesArray[i].position.y--;
		}
		else{
			boxesArray[i].position.x += boxesArray[i].hspeed;
		}
	}
}









