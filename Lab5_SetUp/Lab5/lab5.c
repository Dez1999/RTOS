//Sysc 3310 Lab5
//Desmond Blake 101073534
//This application is used on a TI-msp432p401r.h and the analog booster pack. Using the analog stick, depending on where the stick is moved to a corresponding
//freqeuncy will appear. Also, the direction of the stick using Compass notations will be displayed on the LCD. 

#include <stdint.h>
#include "../inc/BSP.h"
#include "../inc/msp432p401r.h"

/**Declare Set_Buzzer Function
* This function sets the appropriate frequency and duty cycle of the Buzzer for each position
* Input: uint16)t duty & uint16_t PWMCycles
* Output: None
**/
void BSP_Set_Buzzer(uint16_t duty, uint16_t PWMCycles);

int main(void)
{

	
	//Character Arrays of pointers to the LCD to be printed
	char N[] = {' ',' ',' ','N',' ',' '};   //Added extra characters to replace default character array ("Centre")
	char W[] = {' ',' ',' ','W',' ',' '};
	char S[] = {' ',' ',' ','S',' ',' '};
	char E[] = {' ',' ',' ','E',' ',' '};
	char NE[] = {' ',' ',' ','N','E',' '};
	char NW[] = {' ',' ',' ','N','W',' '};
	char SE[] = {' ',' ',' ','S','E',' '};
	char SW[] = {' ',' ',' ','S','W',' '};
	char Centre[] = {'C','E','N','T','R','E'};
	char Compass[] = {'C','o','m','p','a','s','s'};
	char Mspname[] = {'T','I',' ','M','S','P','4','3','2','P','4','0','1','R','+','B','S','P'};
	char Desmond[] = {'D','E','S','M','O','N','D',' ','B','L','A','K','E'};
	
	//Disable Watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;			
	
	//Initialize Joystick
	BSP_Joystick_Init(); 
	//Initialize Buzzer PWM
	BSP_Buzzer_Init(0);
	
	//Initialize Joystick input positions
	uint16_t x_pos;		//x position on Joystick 
	uint16_t y_pos;		//y position on Joystick
	uint8_t select;		//select Button on Joystick
	static uint32_t frequency = 0; //Initialize Frequency variable
	

	//Initialize LCD Screen
	BSP_LCD_Init();
	//Message on LCD Screen (Constant)
	BSP_LCD_DrawString((uint16_t) 0, (uint16_t) 0, Mspname, (int16_t) 0xFFFF);
	BSP_LCD_DrawString((uint16_t) 0, (uint16_t) 1, Desmond, (int16_t) 0xFFFF);
	BSP_LCD_DrawString((uint16_t) 0, (uint16_t) 2, Compass, (int16_t) 0xFFFF);
	
	

	
	while(1) {
		//Read Analog position on joystick
		BSP_Joystick_Input(&x_pos, &y_pos, &select);
		
		/**Buzzer Set and Frequency Change depending on joystick position**/
		
		//Joystick Position 0: Duty Cycle of 0%
		if ((x_pos <= 682 && x_pos >= 341) && (y_pos <= 682 && y_pos >= 341)){
			//Set Frequency(880);		
			BSP_Set_Buzzer(0, (3000000/880));				//Set PWMCyles and Set Duty Cycle to 0%
			BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, Centre, (int16_t) 0x07E0);
		}
		
		//All other Joystick Positions: Duty Cycle of 50%
		else {
			//Joystick Postion 1: NW
			if ((x_pos < 341) && (y_pos > 682)){	
				frequency = 880; //Set Frequency to 880Hz
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, NW, (int16_t) 0x07E0);

			}
			//Joystick Position 2: N
			else if ((x_pos <= 682 && x_pos >= 341) && (y_pos > 682)){
				frequency = 988; //Set Frequency to 988Hz
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, N, (int16_t) 0x07E0);	
			}
			//Joystick Position 3: NE
			else if ((x_pos > 682) && (y_pos > 682)){
				frequency = 1109; //Set Frequency to 1109Hz	
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, NE, (int16_t) 0x07E0);	
			}
			//Joystick Position 4: W
			else if ((x_pos < 341) && (y_pos <= 682 && y_pos >= 341)){
				frequency = 1175; //Set Frequency to 1175Hz	
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, W, (int16_t) 0x07E0);	
			}
			//Joystick Position 5: E
			else if ((x_pos > 682) && (y_pos <= 682 && y_pos >= 341)){
				frequency = 1319; //Set Frequency to 1319Hz	
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, E, (int16_t) 0x07E0);	
			}
			//Joystick Position 6: SW
			else if ((x_pos < 341) && (y_pos < 341)){
				frequency = 1480; //Set Frequency to 1480Hz	
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, SW, (int16_t) 0x07E0);
			}
			//Joystick Position 7: S
			else if ((x_pos <= 682 && x_pos >= 341) && (y_pos < 341)){
				frequency = 1661; //Set Frequency to 1661Hz
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, S, (int16_t) 0x07E0);		
			}
			//Joystick Position 8: SE
			else if ((x_pos > 682 && y_pos < 341)){
				frequency = 1760; //Set Frequency to 1760Hz	
				BSP_LCD_DrawString((uint16_t) 7, (uint16_t) 6, SE, (int16_t) 0x07E0);	
			}
			
			//For current Position: Set PWMCyles with current frequency and Set Duty Cycle to 50%
			BSP_Set_Buzzer(512, (3000000/frequency)); 
		}
	}
		return 0; 
}

void BSP_Set_Buzzer(uint16_t duty, uint16_t PWMCycles){
	TA0CCR0 = PWMCycles - 1;         //Set Frequency of current position
	
  if(duty > 1023){
    return;                        // invalid input
  }
  TA0CCR4 = (duty*PWMCycles)>>10;  // defines when output signal is cleared
}
