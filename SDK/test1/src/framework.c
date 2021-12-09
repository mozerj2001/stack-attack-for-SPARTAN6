/*
 * framework.c
 *
 *  Created on: Nov 24, 2021
 *      Author: József Mózer
 *
 *  This .c source file contains the implementations of all functions
 *  declared in the framework header. These functions together are the "game engine".
 */

#include "xparameters.h"
#include "structures.h"
#include "framework.h"
#include "movement.h"

///////////////////////////////////////////////////////////////////////////////////

struct object boxesArray[BOXES_COUNT];

struct character playerC;

int* FB_POINTER  = XPAR_AXI_APB_BRIDGE_0_BASEADDR + 131072;

unsigned int characterPixels[8][8] = { 	0, 0, 0, 0x23, 0x23, 0x23, 0, 0,
										0x23, 0, 0, 0x0B, 0x0B, 0, 0, 0x23,
										0x23, 0x23, 0, 0x0B, 0x0B, 0, 0x23, 0x23,
										0, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0,
										0, 0, 0, 0x23, 0x23, 0, 0, 0,
										0, 0, 0x3F, 0x3F, 0x3F, 0x3F, 0, 0,
										0, 0x3F, 0x3F, 0, 0, 0x3F, 0x3F, 0,
										0x3F, 0x3F, 0x3F, 0, 0, 0x3F, 0x3F, 0x3F};

unsigned int deployedBoxes = 0;

unsigned int groundLevelY = 90;

unsigned int verticalAcceleration = 2;

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
	playerC.jumpStart = 0;
	for(m = 0; m < 10; m++){
		for(n = 0; n < 10; n++){
			playerC.pixels[m][n] = characterPixels[m][n];
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////
void objectToFB(struct coords coordinates){
	unsigned long int m = 0;
	unsigned long int n = 0;
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
void characterToFB(unsigned int rgbMap[8][8], struct coords coordinates){
	unsigned int m = 0;
	unsigned int n = 0;
	int* rowPtr = FB_POINTER + coordinates.y * 160;


	for(n = 0; n < 8; n++){
		for(m = 0; m < 8; m++){
			*(rowPtr + coordinates.x + m) = rgbMap[n][m];
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
	int deltaX;
	int deltaY;

	for(; i < deployedBoxes; i++){

		if(boxesArray[i].position.y == groundLevelY){
			boxesArray[i].isFalling = 0;
		}
		else{
			for(k = 0; k < deployedBoxes; k++){
				if(i != k && ((boxesArray[i].position.x / 8) == (boxesArray[k].position.x / 8)) && (boxesArray[k].position.y - boxesArray[i].position.y) <= 8){
					boxesArray[i].isFalling = 0;
				}
			}
		}

		if(boxesArray[i].isHorizontallyBlocked == 0){
			for(k = 0; k < deployedBoxes; k++){
				deltaX = playerC.position.x - boxesArray[i].position.x;
				deltaY = playerC.position.y - boxesArray[i].position.y;

				if(boxesArray[i].position.y == boxesArray[k].position.y && ((boxesArray[i].position.x - boxesArray[k].position.x) <= 8 && (boxesArray[i].position.x - boxesArray[k].position.x) >= -8)){
					boxesArray[i].isHorizontallyBlocked = 1;
				}

				if((deltaY >= 0) && (deltaY <= 8)){
					if(((deltaX < 0) && (deltaX >= -8) && (playerC.hspeed > 0)) || ((deltaX > 0) && (deltaX <= 8) && (playerC.hspeed < 0))){
						playerC.hspeed = 0;
					}
				}
			}
		}
	}

	playerC.isFalling = isCFalling();
	playerC.jumpStart = 0;

	if(playerC.isFalling == 1){
		playerC.vspeed += verticalAcceleration;
	}
	else{
		playerC.vspeed = 0;
	}
}
///////////////////////////////////////////////////////////////////////////////////
void updatePositions(){
	unsigned int i = 0;

	for(; i < deployedBoxes; i++){
		if(boxesArray[i].isFalling == 1){
			boxesArray[i].position.y += 1;
		}
		else{
			boxesArray[i].position.x += boxesArray[i].hspeed;
		}
	}

	if(((playerC.position.x + playerC.hspeed) >= 0) && ((playerC.position.x + playerC.hspeed) <= 152)){
		playerC.position.x += playerC.hspeed;
	}
	if((playerC.position.y + playerC.vspeed) <= groundLevelY && ((playerC.position.y + playerC.vspeed) > 0)){
		playerC.position.y += playerC.vspeed;
	}
	else if((playerC.position.y + playerC.vspeed) > groundLevelY){
		playerC.position.y = groundLevelY;
	}
}
///////////////////////////////////////////////////////////////////////////////////
unsigned int isCFalling(){
	unsigned int i;
	int deltaX;
	int deltaY;

	if(playerC.jumpStart == 1){
		playerC.isFalling = 1;
		return 1;
	}
	else if(playerC.position.y >= groundLevelY){ return 0; }

	for(i = 0; i < deployedBoxes; i++){
		deltaX = playerC.position.x - boxesArray[i].position.x;
		deltaY = playerC.position.y - boxesArray[i].position.y;

		if((deltaX < 8) && (deltaY <= 8)){
			return 0;
		}
	}

	return 1;
}








