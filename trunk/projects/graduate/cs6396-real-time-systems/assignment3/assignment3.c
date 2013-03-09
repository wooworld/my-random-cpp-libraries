#include <pob-eye.h>
#include "bitmap.h" 
#include "pattern.h"
#include "joystick.h"

// external functions declarations (for PrintTextOnPobLCD)
//extern void InitAsciiBuffer();
//extern void PrintTextOnPobLCD(int row, int col, char *string, UInt8 *Screen_Buffer);
//extern void HLightText(int row, int col, int size, UInt8 *Screen_Buffer);

int  main(void) {
  // Stores value of joystick axes
  int joystickUpDownAxis = 0;
  int joystickLeftRightAxis = 0;
  
  // The number of forms identified in a frame, an index to loop over them,
  // and an array to hold them
  UInt8 numFormsThisFrame = 0;
  UInt8 formsThisFrameIdx = 0;
  Form  formsListThisFrame[MAX_OF_FORM];

  // Struct of three pointers on the RGB components
  UInt8 * cameraFrame;
  
  //This buffers will stock the pixels to display, 
  UInt8 LCD_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS];
  GraphicBuffer screenBuffer;
  
  //Initialize POB-EYE (lib), POB-LCD (lib), POB-PROTO(file Functions.c) and Servomotors
  InitPobeye2();
  InitI2C(I2C_100_KHZ);
  InitCameraPobeye2();
  InitLCD();      
  SetupJoystick();
  SwitchOnAllServo();

  // Get the pointer of the red,green and blue video buffer
  cameraFrame = GetRGBFrame();
  
  // Initialize the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
  // And clear the buffer, draw it, to make the screen clean
  InitGraphicBuffer(&screenBuffer, LCD_WIDTH, LCD_HEIGHT, ONE_BIT, LCD_Buffer);
  ClearGraphicBuffer(&screenBuffer);

  while (1) {    
    // Get the values of Joystick
    joystickUpDownAxis = GetPortAnalog(UP_DOWN_AXIS);
    joystickLeftRightAxis = GetPortAnalog(RIGHT_LEFT_AXIS);
    
    // Gives the joystick a deadzone of 200x100 around central axis before movement occurs
    // And if joystick is not pushed in any direction, stop movement. 
    // Forward and backward movement take precedence.
    if (joystickUpDownAxis > 200) {
      MoveBot(FORWARD);
    } else if (joystickUpDownAxis < 100) {
      MoveBot(BACK);
    } else if (joystickLeftRightAxis > 200) {
      MoveBot(RIGHT);
    } else if (joystickLeftRightAxis < 100) {
      MoveBot(LEFT); 
    } else {
      MoveBot(STOP);
    }
    
    // grab the RGB components from the camera
    GrabRGBFrame();        
    
    // Convert RGB camera frame to binary
    BinaryRGBFrame(cameraFrame); 
    
    // Try to identify the forms and make a list of it.
    // CAN IDENTIFY MULTIPLE FORMS IN THE SAME IMAGE.
    // pattern defined in pattern.h
    numFormsThisFrame = IdentifyForm(cameraFrame, formsListThisFrame, pattern);  

    // No forms identified this frame
    if (numFormsThisFrame == 0) {
      DrawBitmap(0, 0, IDB_NOFORMS, bitmap, &screenBuffer);
      DrawLCD(&screenBuffer);
      continue;
    }
    
    // Parse the list of the form and print result on the Pob-Terminal and the LCD Screen
    // Draw bitmap and store into screenBuffer, then output screenBuffer
    // to the LCD screen. Note: This displays BIGA when a Trefle is observed?
    for (formsThisFrameIdx = 0; formsThisFrameIdx < numFormsThisFrame; formsThisFrameIdx++) {
	 // Switch on the Pattern ID observed this frame
      switch (formsListThisFrame[formsThisFrameIdx].id) {
        case IDP_0_CROSS:
          DrawBitmap(0, 0, IDB_CROSS, bitmap, &screenBuffer);
          DrawLCD(&screenBuffer);
          break;          
        case IDP_1_BIGA:
          DrawBitmap(0, 0, IDB_BIGA, bitmap, &screenBuffer);
          DrawLCD(&screenBuffer);
          break;
        case IDP_2_KING:
          DrawBitmap(0, 0, IDB_KING, bitmap, &screenBuffer);
          DrawLCD(&screenBuffer);
          break;
        case IDP_3_TOWER:
          DrawBitmap(0, 0, IDB_TOWER, bitmap, &screenBuffer);
          DrawLCD(&screenBuffer);
          break;        
        case IDP_4_TREFLE:
          DrawBitmap(0, 0, IDB_BIGA, bitmap, &screenBuffer);
          DrawLCD(&screenBuffer);
          break;        
        case IDP_5_TRIANGLE:
          DrawBitmap(0, 0, IDB_TRIANGLE, bitmap, &screenBuffer);
          DrawLCD(&screenBuffer);
          break;
        default:
          break;
      }        
    }   
  }
  
  return 0;  
}
