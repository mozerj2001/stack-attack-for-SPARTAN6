#include "xparameters.h"
#include "structures.h"
#include "framework.h"


volatile int* LED_PTR = XPAR_AXI_GPIO_LED_BASEADDR;
volatile int* DIG0_PTR = XPAR_AXI_APB_BRIDGE_0_BASEADDR + 0x0;
volatile int* DIG1_PTR = XPAR_AXI_APB_BRIDGE_0_BASEADDR + 0x4000;



int main()
{
	int cntr = 0;
	int i;
	int k = 0;

	// random numbers for deployment test
	int posGen1 = 0;
	int genCounter = 0;
	struct coords deploymentTestLoc;

	*(LED_PTR+1) = 0x0;

	setupObjects();


	while(1)
	{
		*LED_PTR = cntr;
		*DIG0_PTR = cntr & 0xF;
		*DIG1_PTR = (cntr >> 4) & 0xF;		// counter shifted by 4, then masked
		cntr++;


		for(k = 0; k < 19200; k++){
			*(FB_POINTER+k) = 0x00;
		}
		// Deploy 4 test boxes.
		if(genCounter == 0){
			/*deploymentTestLoc.x = 0;
			deploymentTestLoc.y = 0;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 30;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 60;
			deployBox(deploymentTestLoc);
			deploymentTestLoc.x = 90;
			deployBox(deploymentTestLoc);*/

			boxesArray[0].position.x = 10;
			boxesArray[0].position.y = 10;
			/*boxesArray[1].position.x = 30;
			boxesArray[1].position.y = 0;
			boxesArray[2].position.x = 60;
			boxesArray[2].position.y = 0;
			boxesArray[3].position.x = 90;
			boxesArray[3].position.y = 0;*/
		}

		//updateStates();
		//updatePositions();

		objectToFB(boxesArray[0].position);
		/*objectToFB(boxesArray[1].position);
		objectToFB(boxesArray[2].position);
		objectToFB(boxesArray[3].position);*/

		/*
		for(i = 0; i < deployedBoxes; i++){
			objectToFB(boxesArray[i].position);
		}*/

		delay(100);

		genCounter++;
	}
}


























