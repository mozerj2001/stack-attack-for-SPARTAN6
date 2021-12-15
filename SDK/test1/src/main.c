#include "xparameters.h"
#include "structures.h"
#include "framework.h"
#include "testfunctions.h"
#include "movement.h"

int main(void)
{
		int cntr = 0;
		int i;
		int k = 0;
		int genCounter = 0;
		struct coords deploymentTestLoc;



		setupObjects();
		playerC.position.x = 0;
		playerC.position.y = 50;


		while(1){
			//if(cntr % 30 == 0){ playerC.hspeed -= 2*playerC.hspeed; }
			if(cntr == 0){
				deploymentTestLoc.x = 20;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				/*deploymentTestLoc.x = 28;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 36;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 44;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 52;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 60;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 60;
				deploymentTestLoc.y = 10;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 68;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 68;
				deploymentTestLoc.y = 10;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 68;
				deploymentTestLoc.y = 0;
				deployBox(deploymentTestLoc);*/
				/*deploymentTestLoc.x = 76;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 76;
				deploymentTestLoc.y = 10;
				deployBox(deploymentTestLoc);*/
				/*deploymentTestLoc.x = 84;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 84;
				deploymentTestLoc.y = 10;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 84;
				deploymentTestLoc.y = 0;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 92;
				deploymentTestLoc.y = 40;
				deployBox(deploymentTestLoc);*/
				/*deploymentTestLoc.x = 92;
				deploymentTestLoc.y = 10;
				deployBox(deploymentTestLoc);
				deploymentTestLoc.x = 92;
				deploymentTestLoc.y = 0;
				deployBox(deploymentTestLoc);*/

			}
			/*if(cntr > 100){ playerC.hspeed = 4; }
			if(cntr == 100){ jumpC(); }
			if(cntr == 150){ jumpC(); }
			if(cntr == 200){ jumpC(); }*/

			readNavi();
			updateStates();
			updatePositions();
			while((*BLANK_POINTER) == 0){}
			for(k = 0; k < 17280; k++){
				*(FB_POINTER+k) = 0x00;
			}
			for(; k < 19200; k++){
				*(FB_POINTER+k) = 0x0c;
			}
			characterToFB(characterPixels, playerC.position);
			for(i = 0; i < deployedBoxes; i++){
				objectToFB(boxesArray[i].position);
			}
			delay(5);

			cntr++;
		}
}


























