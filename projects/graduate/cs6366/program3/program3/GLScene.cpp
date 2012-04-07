#include "GLScene.h"

using namespace std;

GLScene::GLScene() {
  m_numModels = 0; 
  init();
}

GLScene::GLScene( GLuint numModels ) {
  m_numModels = numModels; 
  init();
}

GLvoid GLScene::init() {
  COLOR_CHANGE = 0.05f;

  m_windowWidth = WINDOW_WIDTH;
  m_windowHeight = WINDOW_HEIGHT;
  m_windowID = -1;
 
  m_cam      = new GLCamera();
  
  m_keyboard = new Keyboard();

  m_models   = new Model[m_numModels];
  m_modChoice= 0;
  
  m_color    = new Colorizer();
  
  m_ccw = GL_TRUE;
  m_backfaceCulling = GL_TRUE;
}

GLScene::~GLScene() {
  delete m_cam;
  delete m_keyboard;
  delete [] m_models;
  delete m_color;
}

GLvoid GLScene::print() {
  cout << "GLScene: " << endl;
  cout << "  Window = " << m_windowWidth << "x" << m_windowHeight << endl;
  cout << "  Model choice = " << m_modChoice << endl;
  cout << "  Render mode = " << (GLint)m_rMode << endl;
  cout << "  CCW drawing = " << (GLint)m_ccw << endl;
  cout << "  Backface culling = " << (GLint)m_backfaceCulling << endl;

  m_cam->print();
  m_color->print();
}

GLvoid GLScene::drawCurrentModel() {
  glColor4fv( m_color->m_color );

  glFrontFace( m_ccw ? GL_CCW : GL_CW );    

  if ( m_backfaceCulling == GL_TRUE ) { glEnable( GL_CULL_FACE ); }
  else { glDisable( GL_CULL_FACE ); }

  if ( m_rMode == R_POINT ) {
    glPolygonMode( GL_FRONT_AND_BACK, GL_POINTS );
    glBegin( GL_POINTS );
  }
  
  else if ( m_rMode == R_WIREFRAME ) { 
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glBegin( GL_TRIANGLES );
  }

  else if ( m_rMode == R_SOLID ) { 
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glBegin( GL_TRIANGLES );
  }

  for ( GLuint i = 0; i < m_models[m_modChoice].m_tris.size(); i++ ) {
    for ( GLuint j = 0; j < 3; j++ ) {
      // TODO use arraylist/displaylist somewhere 
      glVertex3fv( m_models[m_modChoice].m_tris[i].m_verts[j] );
    }
  }

  glEnd();
}

GLvoid GLScene::centerOnCurrentModel() {
  m_cam->centerOn( m_models[m_modChoice], m_windowWidth, m_windowHeight );
}

GLvoid GLScene::handleKeys() {
  if ( m_keyboard->isPressed(27) ) { exit(0); }

  // Reset view
  if ( m_keyboard->isPressed('r') || m_keyboard->isPressed('R') ) { centerOnCurrentModel(); }
  // Translation along specific axes by 5% of model size
  if ( m_keyboard->isPressed('a') || m_keyboard->isPressed('A') ) { m_cam->translate( 'u', 1 ); }
  if ( m_keyboard->isPressed('d') || m_keyboard->isPressed('D') ) { m_cam->translate( 'u', -1 ); }
  if ( m_keyboard->isPressed('w') || m_keyboard->isPressed('W') ) { m_cam->translate( 'n', 1 ); }
  if ( m_keyboard->isPressed('s') || m_keyboard->isPressed('S') ) { m_cam->translate( 'n', -1 ); }
  if ( m_keyboard->isPressed('q') || m_keyboard->isPressed('Q') ) { m_cam->translate( 'v', 1 ); }
  if ( m_keyboard->isPressed('e') || m_keyboard->isPressed('E') ) { m_cam->translate( 'v', -1 ); }
  if ( m_keyboard->isPressed('z') || m_keyboard->isPressed('Z') ) { m_cam->translate(5.0, 5.0, 5.0); }
  // Rotation about specific axes by 10 degrees
  if ( m_keyboard->isPressed('l') || m_keyboard->isPressed('L') ) { m_cam->rotate('v', 1 ); }
  if ( m_keyboard->isPressed('\'') )                   { m_cam->rotate('v', -1 ); }
  if ( m_keyboard->isPressed('p') || m_keyboard->isPressed('P') ) { m_cam->rotate('u', 1 );  }
  if ( m_keyboard->isPressed(';') )                    { m_cam->rotate('u', -1 ); }
  if ( m_keyboard->isPressed('o') || m_keyboard->isPressed('O') ) { m_cam->rotate('n', 1 ); }
  if ( m_keyboard->isPressed('[') )                    { m_cam->rotate('n', -1 ); }
  // Change drawing colors
  if ( m_keyboard->isPressed('1') )                    { m_color->changeColor( 'r', 1 ); }
  if ( m_keyboard->isPressed('2') )                    { m_color->changeColor( 'g', 1 ); }
  if ( m_keyboard->isPressed('3') )                    { m_color->changeColor( 'b', 1 ); }
  if ( m_keyboard->isPressed('4') )                    { m_color->changeColor( 'a', 1 ); }
  if ( m_keyboard->isPressed('5') )                    { m_color->changeColor( 'r', -1 ); }
  if ( m_keyboard->isPressed('6') )                    { m_color->changeColor( 'g', -1 ); }
  if ( m_keyboard->isPressed('7') )                    { m_color->changeColor( 'b', -1 ); }
  if ( m_keyboard->isPressed('8') )                    { m_color->changeColor( 'a', -1 ); }
  if ( m_keyboard->isPressed('9') )                    { m_cam->moveClippingPlane( 'f', 1 ); }
  if ( m_keyboard->isPressed('0') )                    { m_cam->moveClippingPlane( 'n', 1 ); }
  if ( m_keyboard->isPressed('-') )                    { m_cam->moveClippingPlane( 'f', -1 ); }
  if ( m_keyboard->isPressed('=') )                    { m_cam->moveClippingPlane( 'n', -1 ); }
  if ( m_keyboard->isPressed(' ') ) {
    m_modChoice = (m_modChoice + 1) % m_numModels;
    centerOnCurrentModel();
  }
}
