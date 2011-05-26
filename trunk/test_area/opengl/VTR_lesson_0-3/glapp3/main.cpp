/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/* File for "Color" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */

#include <iostream>
#include <stdlib.h> // needed for exit

#ifdef __APPLE__
  #include <OpenGL/OpenGL.h>
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

// As to not prepend everything with std::
using namespace std;

// COLORS { Red, Green, Blue }
float _C_SKYBLUE[]  = {0.7f, 0.9f, 1.0f};
float _C_RED[]      = {1.0f, 0.0f, 0.0f};
float _C_GREEN[]    = {0.0f, 1.0f, 0.0f};
float _C_BLUE[]     = {0.0f, 0.0f, 1.0f};
float _C_DEEPPINK[] = {1.0f, 0.078f, 0.576f};
float _C_WHITE[]    = {1.0f, 1.0f, 1.0f};
float _C_BLACK[]    = {0.0f, 0.0f, 0.0f};

#define _OPAQUE      1.0f
#define _TRANSPARENT 0.0f
#define _TRANSLUCENT 0.6f

// Update speed to force 60 "frames" per second
#define _FPS 60.0f
#define _MS_PER_FRAME  1000.0f / _FPS

#define _SCREEN_WIDTH    1280
#define _SCREEN_HEIGHT   720
#define _FIELD_OF_VIEW_Y 45.0f

// The closest the view will render, anything closer will just take up the whole screen
#define _Z_NEAR          1.0f

// The farthest the view will render, anything farther away will just be a dot
#define _Z_FAR           200.0f

// Rotate view by this angle
float _PENTAGON_ROT = 30.0f;
float _TRIANGLE_ROT = 30.0f;
float _TRAPEZOID_ROT = 30.0f;
float _CAMERA_ANGLE = 10.0f;

/**
 * @desc Called when a keyboard key is pressed
 */
void handleKeypress( unsigned char key, int x, int y ) 
{
	switch ( key ) 
  {
    // Escape key   
		case 27:
			exit(0);
	}
}

/**
 * @desc Initialize the 3D rendering settings
 */
void initRendering() 
{
  // Draw OBJ1, Draw OBJ2. If OBJ2 is drawn behind OBJ1, this 
  // allows OBJ2 to actually show up behind OBJ1
	glEnable(GL_DEPTH_TEST);

  // Enable colors for the window
	glEnable( GL_COLOR_MATERIAL ); 

  // Set the background color to a color
	glClearColor( _C_BLACK[0], _C_BLACK[1], _C_BLACK[2], _OPAQUE );
}

/**
 * @desc On window resize
 */
void handleResize( int w, int h ) 
{
  // OGL digital world values to pixel values
	glViewport( 0, 0, w, h );

  // Switch setting to camera perspective, used only with resize
	glMatrixMode( GL_PROJECTION );
	
  // Reset the reference frame
  glLoadIdentity();

  // Update the camera perspective for the new window size
                                     // aspect ratio
	gluPerspective( _FIELD_OF_VIEW_Y, (double)w / (double)h, _Z_NEAR, _Z_FAR );
}



/**
 * @desc Draw the scene in the buffer to be shown later
 * @note This is where the action is!
 */
void drawScene() 
{
  // Clear the scene from the last draw
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
  // Normal drawing mode
	glMatrixMode( GL_MODELVIEW );

  // Resets the reference frame to the origin and w/ x in X+, y in Y+ and z in Z-
	glLoadIdentity();

  // Rotate the reference frame -cameraAngle degrees about the axis defined
  // by the vector <0, 1, 0> relative to (0,0,0)
  // This "looks left" by _CAMERA_ANGLE degrees.
	//glRotatef( -_CAMERA_ANGLE, 0.0f, 1.0f, 0.0f );
  glRotatef( -_CAMERA_ANGLE, 0.1f, -0.1f, 1.0f );

  // Push reference frame 5 units into the screen
	glTranslatef( 0.0f, 0.0f, -5.0f );
	
  // Draw the world frame origin for visual reference
  glBegin( GL_LINES );

    glColor3f( _C_RED[0], _C_RED[1], _C_RED[2] );

    // Draw the X+ axis    
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 100.0f, 0.0f, 0.0f );

    // Draw Y+ axis
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0, 100.0f, 0.0f );

    // Draw Z+ axis
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 100.0f, 0.0f, 0.0f );

    glColor3f( _C_BLUE[0], _C_BLUE[1], _C_BLUE[2] );

    // Draw the X- axis
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( -100.0f, 0.0f, 0.0f );

    // Draw the Y- axis
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, -100.0f, 0.0f );

    // Draw the Z- axis
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 0.0f, -100.0f );
  glEnd();

  // Save the transformation state on the stack of 5 units into the screen
	glPushMatrix();
    // Translate to center of trapezoid
	  glTranslatef( 0.0f, -1.0f, 0.0f );

    // Rotate the trapezoid about <0,0,1>
	  glRotatef( _TRAPEZOID_ROT, 0.0f, 0.0f, 1.0f );
	  glBegin( GL_QUADS );
  	
	    // Draw a trapezoid with 4 different colors, one at each vertex
	    glColor3f(0.5f, 0.0f, 0.8f);
	    glVertex3f(-0.7f, -0.5f, 0.0f);
	    glColor3f(0.0f, 0.9f, 0.0f);
	    glVertex3f(0.7f, -0.5f, 0.0f);
	    glColor3f(1.0f, 0.0f, 0.0f);
	    glVertex3f(0.4f, 0.5f, 0.0f);
	    glColor3f(0.0f, 0.65f, 0.65f);
	    glVertex3f(-0.4f, 0.5f, 0.0f);
  	
    // End drawing quadrilaterals
	  glEnd();
	glPopMatrix();

	glPushMatrix();
    // Translate to center of pentagon
	  glTranslatef( 1.0f, 1.0f, 0.0f );

    // Rotate pentagon about <0,1,0> 
	  glRotatef( _PENTAGON_ROT, 0.0f, 1.0f, 0.0f );

    // Scale it to 70% of its size
	  glScalef( 0.7f, 0.7f, 0.7f );

	  glBegin( GL_TRIANGLES );

      // Draw a deep pink colored pentagon
	    glColor3f( _C_DEEPPINK[0], _C_DEEPPINK[1], _C_DEEPPINK[2] );
    	
	    // Draw a pentagon using 3 triangles
	    glVertex3f(-0.5f, -0.5f, 0.0f);
	    glVertex3f(0.5f, -0.5f, 0.0f);
	    glVertex3f(-0.5f, 0.0f, 0.0f);
    	
	    glVertex3f(-0.5f, 0.0f, 0.0f);
	    glVertex3f(0.5f, -0.5f, 0.0f);
	    glVertex3f(0.5f, 0.0f, 0.0f);
    	
	    glVertex3f(-0.5f, 0.0f, 0.0f);
	    glVertex3f(0.5f, 0.0f, 0.0f);
	    glVertex3f(0.0f, 0.5f, 0.0f);
  	
	  glEnd();	
	glPopMatrix();

  /* NOTE: Cannot call transformation functions inside of a glBegin()-glEnd() block! */

	glPushMatrix();
    // Translate to center of triangle
	  glTranslatef(-1.0f, 1.0f, 0.0f);

    // Rotate traiangle about <1,2,3>
	  glRotatef( _TRIANGLE_ROT, 1.0f, 2.0f, 3.0f );  	
	  glBegin( GL_TRIANGLES );
  	
	    // Draw a triangle with 3 different colors, one at each vertex
	    glColor3f(1.0f, 0.7f, 0.0f);
	    glVertex3f(0.5f, -0.5f, 0.0f);
	    glColor3f(1.0f, 1.0f, 1.0f);
	    glVertex3f(0.0f, 0.5f, 0.0f);
	    glColor3f(0.0f, 0.0f, 1.0f);
	    glVertex3f(-0.5f, -0.5f, 0.0f);
  	
	  glEnd();	
	glPopMatrix();
	
  // Swap the drawn scene in the buffer to the screen buffer
	glutSwapBuffers();
}

/**
 * @desc Update the angle of rotations for each shape
 * @note This is where the action is!
 */
void update_rotations( int value ) 
{
  // One full rotation of objects every two seconds
  _TRAPEZOID_ROT += 360.0f / _FPS / 2.0f;
  _PENTAGON_ROT += 360.0f / _FPS / 2.0f;
  _TRIANGLE_ROT += 360.0f / _FPS / 2.0f;

  // Rotate the camera once every six seconds
  _CAMERA_ANGLE += 360.0f / _FPS / 6.0f;

  // Reset the angle to be closer to 0
	if ( _TRAPEZOID_ROT > 360.0f ) 
  {
		_TRAPEZOID_ROT -= 360.0f;
	}

  // Reset the angle to be closer to 0
	if ( _PENTAGON_ROT > 360.0f ) 
  {
		_PENTAGON_ROT -= 360.0f;
	}

  // Reset the angle to be closer to 0
	if ( _TRIANGLE_ROT > 360.0f ) 
  {
		_TRIANGLE_ROT -= 360.0f;
	}

  // Reset the angle to be closer to 0
	if ( _CAMERA_ANGLE > 360.0f ) 
  {
		_CAMERA_ANGLE -= 360.0f;
	}
	
  // Scene has changed, redisplay it
	glutPostRedisplay();

  // Call update_rotations again in _MS_PER_FRAME, pass 0 as value
	glutTimerFunc( _MS_PER_FRAME, update_rotations, 0);
}

int main( int argc, char** argv ) 
{
	// Initialize GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( _SCREEN_WIDTH, _SCREEN_HEIGHT );
	
	// Create the window then begin set parameters for the scene
	glutCreateWindow( "Testing [Color - videotutorialsrock.com]" );
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
  // Call update _MS_PER_FRAME ms after program starts
	glutTimerFunc( _MS_PER_FRAME, update_rotations, 0); //Add a timer

	
  // Redraw window when necessary, handle keypresses, etc. 
  // DOES NOT RETURN
	glutMainLoop();

  // Here to make the compiler from throwing error
	return 0;
}









