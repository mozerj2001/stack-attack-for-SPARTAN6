/*
 * testfunctions.c
 *
 *  Created on: Nov 30, 2021
 *      Author: student
 */
#include "xparameters.h"
#include "structures.h"
#include "framework.h"
#include "testfunctions.h"

void testFall(){

	int cntr = 0;
	int i;
	int k = 0;

	// random numbers for deployment test
	int posGen1 = 0;
	int genCounter = 0;
	struct coords deploymentTestLoc;

	setupObjects();

	while(1)
	{


		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0x03;
		}

		// Deploy 4 test boxes.
		if(genCounter == 0){
			deploymentTestLoc.x = 0;
			deploymentTestLoc.y = 0;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 30;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 60;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 90;
			deployBox(deploymentTestLoc);
		}

		updateStates();
		updatePositions();

		/*for(i = 0; i < deployedBoxes; i++){
			boxesArray[i].position.y += 4;
		}*/

		for(i = 0; i < deployedBoxes; i++){
			objectToFB(boxesArray[i].position);
		}

		delay(30);

		genCounter++;
	}
}


void testStacking(){
	int cntr = 0;
	int i;
	int k = 0;

	// random numbers for deployment test
	//int posGen1 = 0;
	int genCounter = 0;
	struct coords deploymentTestLoc;

	setupObjects();

	while(1)
	{
		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0x03;
		}

		// Deploy 4 test boxes.
		if(genCounter == 0){
			deploymentTestLoc.x = 0;
			deploymentTestLoc.y = 0;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 30;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 60;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 90;
			deployBox(deploymentTestLoc);
		}

		if(genCounter == 20){
			deploymentTestLoc.x = 0;
			deploymentTestLoc.y = 0;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 30;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 60;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 90;
			deployBox(deploymentTestLoc);
		}

		if(genCounter == 40){
			deploymentTestLoc.x = 0;
			deploymentTestLoc.y = 0;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 30;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 60;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 90;
			deployBox(deploymentTestLoc);
		}

		if(genCounter == 60){
			deploymentTestLoc.x = 0;
			deploymentTestLoc.y = 0;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 30;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 60;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 90;
			deployBox(deploymentTestLoc);
		}

		updateStates();
		updatePositions();

		/*for(i = 0; i < deployedBoxes; i++){
			boxesArray[i].position.y += 4;
		}*/

		for(i = 0; i < deployedBoxes; i++){
			objectToFB(boxesArray[i].position);
		}

		delay(30);

		genCounter++;
	}
}
