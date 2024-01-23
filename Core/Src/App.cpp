/*
 * App.cpp
 *
 *  Created on: Dec 20, 2023
 *      Author: Jabber
 *
 *      Core application file for Dual Feline Feeder Project *
 */
//=============================================================
// 						Includes
//=============================================================
#include <App.h>

//=============================================================
// 						Typedefs
//=============================================================

//Wave Player
extern ApplicationTypeDef Appli_state;
extern AUDIO_PLAYBACK_StateTypeDef AudioState;

// LCD Structs
LiquidCrystal_LCD lcd0;

//=============================================================
//						Defines
//=============================================================
// LCD defines
 #define ADDRESS 0x4E // Write to LCD
 #define COLS 16
 #define ROWS 2


// Serial UART
//#define UartHandle &huart2

//=============================================================
// 						Macros
//=============================================================

//=============================================================
//					Global Variables
//=============================================================



// WavePlayer
int IsFinished = 0;

//=============================================================
//					Function Prototypes
//=============================================================


//=============================================================
// 					Call Back Functions
//=============================================================


// Button Input (Was used for waveplayer)
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0)
	{
		AudioState = AUDIO_STATE_NEXT;
//		if (AudioState == AUDIO_STATE_PLAY)
//		{
//			AudioState = AUDIO_STATE_PAUSE;
//		}
//
//		if (AudioState == AUDIO_STATE_WAIT)
//		{
//			AudioState = AUDIO_STATE_RESUME;
//		}
	}
}

// Encoder Interrupt
uint32_t encoderCount = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	encoderCount = __HAL_TIM_GET_COUNTER(htim);
}

//=============================================================
// 						APP MAIN
//=============================================================
void app_main(){
	// ---------------------SETUP -------------------------------

	// ***Encoder***
	     HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
	     char strCnt [16];

	  // ***LCD*** 20x4
	     LiquidCrystal_I2C(&lcd0, &hi2c2, ADDRESS, COLS, ROWS); // Update to appropriate I2C
	     init(&lcd0);
	     clear(&lcd0);
	     home(&lcd0);
	     char str1[] = "Starting Up!";
	     printToLCD(&lcd0, str1,strlen(str1));
	     HAL_Delay(1000);
	     clear(&lcd0);
	     home(&lcd0);
	     // Print the current count to LCD
	     char msg[] = "Count:";
         printToLCD(&lcd0, msg, strlen(msg));
// ---------------------MAIN LOOP -------------------------------
	while (1)
	{
		// Get the encoder count.
		setCursor(&lcd0, 6, 0);
		sprintf(strCnt, "%05ld", encoderCount);
		printToLCD(&lcd0, strCnt, strlen(strCnt));



		// Mount the USB for Audio
	    if (Appli_state == APPLICATION_READY)
	        {
	        	Mount_USB();
	        	AUDIO_PLAYER_Start(0);

	        	while (!IsFinished)
	        	{
	        		AUDIO_PLAYER_Process(FALSE); // TRUE = loop

	        		if (AudioState == AUDIO_STATE_STOP)
	        		{
	        			IsFinished = 1;
	        		}
	        	}
	        }
	    MX_USB_HOST_Process();
	}
}

