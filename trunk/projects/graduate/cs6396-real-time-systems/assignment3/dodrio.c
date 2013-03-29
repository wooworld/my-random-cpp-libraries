#include "dodrio.h"

#include <pob-eye.h>
#include "joystick.h"
#include "pattern.h"
#include "bitmap.h"

UInt8 numFormsThisFrame = 0;
UInt8 formsThisFrameIdx = 0;
Form  formsListThisFrame[MAX_OF_FORM];

// Struct of three pointers on the RGB components
UInt8 * cameraFrame;
 
//This buffers will stock the pixels to display
UInt8 LCD_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS];
GraphicBuffer screenBuffer;

void initCameraAndLCD();

void initRobit()
{
  //Initialize POB-EYE (lib), POB-LCD (lib), POB-PROTO(file Functions.c) and Servomotors
  InitPobeye2();
  InitI2C(I2C_100_KHZ);
  InitCameraPobeye2();
  InitLCD();      
  SwitchOnAllServo();  
  initCameraAndLCD();
}

// I don't know how many degrees left this rotates
void rotateLeft() 
{
  MoveBot(LEFT); 
}

// I don't know how many degrees right this rotates
void rotateRight()
{
  MoveBot(RIGHT);
}

// I don't know how far forward this moves the robot
void moveForward()
{
  MoveBot(FORWARD);
}

// I don'tk now how far backward this moves the robot
void moveBackward()
{
  MoveBot(BACK);
}

// Each of the above rotate/move functions stays ON until stopMovement() is called
void stopMovement()
{
  MoveBot(STOP);
}

void initCameraAndLCD()
{
  // Get the pointer of the red,green and blue video buffer
  cameraFrame = GetRGBFrame();
  
  // Initialize the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
  // And clear the buffer, draw it, to make the screen clean
  InitGraphicBuffer(&screenBuffer, LCD_WIDTH, LCD_HEIGHT, ONE_BIT, LCD_Buffer);
  ClearGraphicBuffer(&screenBuffer);
}

void captureImage()
{
  // grab the RGB components from the camera
  GrabRGBFrame();        
}

void decipherImage() 
{
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
