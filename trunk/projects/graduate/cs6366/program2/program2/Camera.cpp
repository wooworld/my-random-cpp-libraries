#include "Camera.h"

using namespace std;

extern GLuint windowWidth;
extern GLuint windowHeight;
extern GLuint subwindowWidth;
extern GLuint subwindowHeight;
extern GLubyte borderSize;

Camera::Camera() { 
  init();
}

GLvoid Camera::init() {
  FOVY = 60.0;
  FOVX = 60.0;
  ASPECT_RATIO = 1.0;  
  NEAR_CLIPPING_PLANE = 1.0;
  FAR_CLIPPING_PLANE = 10e4;
  DEFAULT_TRANSLATE_STEP = 0.0;
  DEFAULT_ROTATE_ANGLE = 0.0;

  memset( m_translateDelta, 0, 3*sizeof(GLfloat) );
  memset( m_rotateDelta,    0, 3*sizeof(GLfloat) );
  memset( m_projMatr,       0, 16*sizeof(GLfloat) );
  memset( m_modelViewMatr,  0, 16*sizeof(GLfloat) );
  memset( m_tempMatr,       0, 16*sizeof(GLfloat) );

  m_invertYLook = false;
  m_invertXLook = false;
  m_fovY = FOVY;
  m_fovX = FOVX;
  m_aspect = ASPECT_RATIO;
  m_zNear = NEAR_CLIPPING_PLANE;
  m_zFar = FAR_CLIPPING_PLANE;
  m_clipDelta = 0.05f;
}
  
Camera::~Camera() { }

GLvoid Camera::translate( GLfloat x, GLfloat y, GLfloat z ) {
  translate( m_modelViewMatr, x, y, z );
}

GLvoid Camera::translate( const vec3f& v ) {
  translate( m_modelViewMatr, v[0], v[1], v[2] );
}

GLvoid Camera::translate( GLubyte axis, GLint dir ) {
  if ( axis == 'u' || axis == 'U' || axis == 'x' || axis == 'X' ) {
    translate( m_modelViewMatr, dir * m_translateDelta[0], 0.0, 0.0 );
  }

  else if ( axis == 'v' || axis == 'V' || axis == 'y' || axis == 'Y' ) {
    translate( m_modelViewMatr, 0.0, dir * m_translateDelta[1], 0.0 );
  }

  else if ( axis == 'n' || axis == 'N' || axis == 'z' || axis == 'Z' ) {
    translate( m_modelViewMatr, 0.0, 0.0, dir * m_translateDelta[2] );
  }

  print();
}

GLvoid Camera::translate( mat4f& m, GLfloat x, GLfloat y, GLfloat z ) {
  // Transpose of a translation matrix, because column major format
  mat4f T_t = { 1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                x, y, z, 1 };
  // (T * M) * v -> v * (M * T) because column major format
  multMatrix( m, T_t, m );

  print();
}


GLvoid Camera::rotate( GLubyte axis, GLfloat theta ) {
  /*if ( axis == 'u' || axis == 'U' || axis == 'x' || axis == 'X' ) {
    m_userRotation[0] = 1.0;
    m_userRotation[1] = 0.0;
    m_userRotation[2] = 0.0;
    if ( m_invertYLook == GL_TRUE ) { theta *= -1.0; }
  }

  if ( axis == 'v' || axis == 'V' || axis == 'y' || axis == 'Y' ) {
    m_userRotation[0] = 0.0;
    m_userRotation[1] = 1.0;
    m_userRotation[2] = 0.0;
    if ( m_invertXLook == GL_TRUE ) { theta *= -1.0; }
    rotateV( theta );
  }
  
  else if ( axis == 'n' || axis == 'N' || axis == 'z' || axis == 'Z' ) {
    m_userRotation[0] = 0.0;
    m_userRotation[1] = 0.0;
    m_userRotation[2] = 1.0;
  }

  glMatrixMode( GL_MODELVIEW );
  glGetDoublev( GL_MODELVIEW_MATRIX, m_modelViewMatr );
  glLoadIdentity();
  glRotated( theta, m_userRotation[0], m_userRotation[1], m_userRotation[2] );
  glMultMatrixd( m_modelViewMatr );
  glGetDoublev( GL_MODELVIEW_MATRIX, m_modelViewMatr );*/
}

GLvoid Camera::rotate( const vec3f& v, GLfloat theta ) {
  /*m_userRotation[0] = (GLfloat) *(v[0]);
  m_userRotation[1] = (GLfloat) *(v[1]);
  m_userRotation[2] = (GLfloat) *(v[2]);

  glMatrixMode( GL_MODELVIEW );
  glGetDoublev( GL_MODELVIEW_MATRIX, m_modelViewMatr );
  glLoadIdentity();
  glRotated( theta, m_userRotation[0], m_userRotation[1], m_userRotation[2] );
  glMultMatrixd( m_modelViewMatr );
  glGetDoublev( GL_MODELVIEW_MATRIX, m_modelViewMatr );*/
}

GLvoid Camera::rotate( GLubyte axis, GLint dir ) {
  if ( axis == 'u' || axis == 'U' || axis == 'x' || axis == 'X' ) {
    rotateU( m_modelViewMatr, dir * m_rotateDelta[0] );
  }

  else if ( axis == 'v' || axis == 'V' || axis == 'y' || axis == 'Y' ) {
    rotateV( m_modelViewMatr, dir * m_rotateDelta[1] );
  }
  
  else if ( axis == 'n' || axis == 'N' || axis == 'z' || axis == 'Z' ) {
    rotateN( m_modelViewMatr, dir * m_rotateDelta[2] );
  }

  print();
}

GLvoid Camera::rotateU( mat4f& m, GLfloat theta ) {
  theta *= conv::DegToRad;
  // Transpose of a rotation matrix because column major format
  mat4f R_t = { 1, 0,           0,          0,
                0, cos(theta),  sin(theta), 0,
                0, -sin(theta), cos(theta), 0,
                0,  0,          0,          1 };

  // (R * M) * v -> v * (M * R) because column major format
  multMatrix( m, m, R_t );
}

GLvoid Camera::rotateV( mat4f& m, GLfloat theta ) {

  theta *= conv::DegToRad;
  // Transpose of a rotation matrix because column major format
  mat4f R_t = { cos(theta), 0, -sin(theta), 0,
                0,          1, 0,           0,
                sin(theta), 0, cos(theta),  0,
                0,          0, 0,           1 };

  // (R * M) * v -> v * (M * R) because column major format
  multMatrix( m, m, R_t );
}

GLvoid Camera::rotateN( mat4f& m, GLfloat theta ) {
  theta *= conv::DegToRad;

  // Transpose of a rotation matrix because column major format
  mat4f R_t = { cos(theta),  sin(theta), 0, 0,
                -sin(theta), cos(theta), 0, 0,
                0,           0,          1, 0,
                0,           0,          0, 1 };

  // (R * M) * v -> v * (M * R) because column major format
  multMatrix( m, m, R_t );
}

GLvoid Camera::moveClippingPlane( GLubyte plane, GLint dir ) {
  if ( plane == 'f' ) {
    cout << "updating a clipping plane from " << m_zFar << " to " << m_zFar * (1.0f + ((GLfloat)dir * m_clipDelta)) << endl;
    m_zFar *= (1.0f + ((GLfloat)dir * m_clipDelta));
    if ( m_zFar < m_zNear ) { m_zFar = m_zNear; }
  }
  if ( plane == 'n' ) {
    cout << "updating a clipping plane from " << m_zNear << " to " << m_zNear * (1.0f + ((GLfloat)dir * m_clipDelta)) << endl;
    m_zNear *= (1.0f + ((GLfloat)dir * m_clipDelta));
    if ( m_zNear > m_zFar ) { m_zNear = m_zFar; }
  }

  updatePerspective( m_aspect ); 
}

GLvoid Camera::calcTranslateDelta( const Model& m ) {
  // Move 5% of model width/etc for each translation
  m_translateDelta[0] = (m.m_box[3] - m.m_box[0]) * .05f;
  m_translateDelta[1] = (m.m_box[4] - m.m_box[1]) * .05f;
  m_translateDelta[2] = (m.m_box[5] - m.m_box[2]) * .05f;
}

GLvoid Camera::calcRotateDelta( const Model& m ) {
  // 50 rotations to complete a circle
  m_rotateDelta[0] = 360.0f / 50.0f;
  m_rotateDelta[1] = 360.0f / 50.0f;
  m_rotateDelta[2] = 360.0f / 50.0f;
}

/* http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/ */
GLvoid Camera::updatePerspective( GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar ) {
  /* DOES NOT WORK */
  m_aspect = aspect;
  GLfloat ymax = zNear * tan(fovy * conv::DegToRad);
  GLfloat xmax = ymax * m_aspect;
  setFrustum( -xmax, xmax, -ymax, ymax, zNear, zFar );
  transpose( m_projMatr );

  /* WORKS */
  /*glMatrixMode( GL_PROJECTION );
  glLoadIdentity();  
  gluPerspective( fovy, aspect, zNear, zFar );*/
}

GLvoid Camera::updatePerspective( GLfloat aspect) {
  updatePerspective( m_fovY, aspect, m_zNear, m_zFar );
}

GLvoid Camera::setFrustum( GLfloat l, GLfloat r, GLfloat b, 
                           GLfloat t, GLfloat n, GLfloat f ) {
  m_projMatr[0] = 2*n/(r-l); m_projMatr[1] = 0;        m_projMatr[2] = (r+l)/(r-l);   m_projMatr[3] = 0;
  m_projMatr[4] = 0;         m_projMatr[5] = 2*n/(t-b); m_projMatr[6] = (t+b)/(t-b);   m_projMatr[7] = 0;
  m_projMatr[8] = 0;         m_projMatr[9] = 0;         m_projMatr[10] = -(f+n)/(f-n); m_projMatr[11] = -2*f*n/(f-n);
  m_projMatr[12] = 0;         m_projMatr[13] = 0;        m_projMatr[14] = -1;           m_projMatr[15] = 0;  
 //m_projMatr[0] = 2*n/(r-l); /*m_projMatr[4] = 0;*/         m_projMatr[8] = (r+l)/(r-l);   /*m_projMatr[12] = 0;*/
 ///*m_projMatr[1] = 0;*/         m_projMatr[5] = 2*n/(t-b); m_projMatr[9] = (t+b)/(t-b);   /*m_projMatr[13] = 0;*/
 ///*m_projMatr[2] = 0;*/         /*m_projMatr[6] = 0;*/         m_projMatr[10] = -(f+n)/(f-n); m_projMatr[14] = -2*f*n/(f-n);
 ///*m_projMatr[3] = 0;*/         /*m_projMatr[7] = 0;*/         m_projMatr[11] = -1;           /*m_projMatr[15] = 0;*/  
  /*float temp, temp2, temp3, temp4;
  temp = 2.0f * n;
  temp2 = r - l;
  temp3 = t - b;
  temp4 = f - n;
  m_projMatr[0] = temp / temp2;  m_projMatr[1] = 0;             m_projMatr[2] = 0;                  m_projMatr[3] = 0;
  m_projMatr[4] = 0;             m_projMatr[5] = temp / temp3;  m_projMatr[6] = 0;                  m_projMatr[7] = 0;
  m_projMatr[8] = (r+l) / temp2; m_projMatr[9] = (t+b) / temp3; m_projMatr[10] = (-f-n) / temp4;    m_projMatr[11] = -1;
  m_projMatr[12] = 0;            m_projMatr[13] = 0;            m_projMatr[14] = (-temp*f) / temp4; m_projMatr[15] = 0;*/
  /*m_projMatr[0] = temp / temp2;  m_projMatr[4] = 0;             m_projMatr[8] = 0;                  m_projMatr[12] = 0;
  m_projMatr[1] = 0;             m_projMatr[5] = temp / temp3;  m_projMatr[9] = 0;                  m_projMatr[13] = 0;
  m_projMatr[2] = (r+l) / temp2; m_projMatr[6] = (t+b) / temp3; m_projMatr[10] = (-f-n) / temp4;    m_projMatr[14] = -1;
  m_projMatr[3] = 0;            m_projMatr[7] = 0;            m_projMatr[11] = (-temp*f) / temp4; m_projMatr[15] = 0;*/
}

GLvoid Camera::centerOn( const Model& m ) {
  // Update model view matrix to be equivalent to lookAt
  GLfloat modelHeight = (m.m_box[4] - m.m_box[1]);
  GLfloat modelWidth = (m.m_box[3] - m.m_box[0]);
  GLfloat ez;
  if ( modelWidth <= modelHeight ) {
    ez = m.m_center[2] + modelHeight/(GLfloat)tan((FOVY/2.0)*conv::DegToRad);
  }
  else {
    ez = m.m_center[2] + modelWidth/(GLfloat)tan((FOVY/2.0)*conv::DegToRad);
  } 

  cout << "lookAt = " << endl;
  cout << m.m_center[0] << " " << m.m_center[1] << " " << ez << endl;
  cout << m.m_center[0] << " " << m.m_center[1] << " " << m.m_center[2] << endl;
  cout << 0 << " " << 1 << " " << 0 << endl;

  identity( m_modelViewMatr );
  lookAt( m.m_center[0], m.m_center[1], ez,
          m.m_center[0], m.m_center[1], m.m_center[2],
          0,             1,             0 );

  // Update clipping planes to fit model
  m_zNear = NEAR_CLIPPING_PLANE;

  // dist(camera's z, midpoint of model's far side) + 10.0
  /*GLfloat modelDepth = (m.m_box[5] - m.m_box[2]);
  m_zFar = fun::dist( (GLfloat)m.m_center[0], (GLfloat)m.m_center[1], (GLfloat)ez, 
                      (GLfloat)m.m_center[0], (GLfloat)m.m_center[1], (GLfloat)(m.m_center[2] + (modelDepth / 2.0)) )
    + 10.0f;*/

  m_zFar = ez 
    + fun::dist(m.m_center[0], m.m_center[1], ez, 
                m.m_center[0], m.m_center[1], m.m_box[5] - m.m_box[2] )
    + 10.0;

  // Update perspective matrix
  updatePerspective( (GLfloat)windowWidth / (GLfloat)windowHeight );

  // Update deltas for proper translation/rotation control
  calcTranslateDelta( m );
  calcRotateDelta( m );
}

/* http://www.opengl.org/wiki/GluLookAt_code */
GLvoid Camera::lookAt( GLfloat ex, GLfloat ey, GLfloat ez,
                       GLfloat cx, GLfloat cy, GLfloat cz,
                       GLfloat ux, GLfloat uy, GLfloat uz ) {
  vec3f forward = {cx-ex, cy-ey, cz-ez};
  vec3f side = {0, 0, 0};
  vec3f up = {ux, uy, uz};
  normalize( forward );
  normalize( up );

  // side = forward x up
  cross( side, forward, up ); 
  normalize( side );

  // up = side x forward
  cross( up, side, forward );
  up[1] = -up[1];

  mat4f temp = { side[0], up[0], -forward[0], 0,
                 side[1], up[1], -forward[1], 0,
                 side[2], up[2], -forward[2], 0,
                 0,       0,     0,           1 };

  // m_modelViewMatr = temp translated by -ex, -ey, -ez.
  multMatrix( temp, m_modelViewMatr, temp );
  translate( temp, -ex, -ey, -ez );
  memcpy( &m_modelViewMatr, &temp, 16*sizeof(GLfloat) );
}

GLvoid Camera::normalize( vec3f& v ) {
  GLfloat length = sqrt( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] );
  if ( length != 0 ) {
    v[0] /= length;
    v[1] /= length;
    v[2] /= length;
  }
  else {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
  }
}

GLvoid Camera::identity( mat4f& m ) {
  memset( m, 0, 16*sizeof(GLfloat) );
  m[0] = 1;
  m[5] = 1;
  m[10] = 1;
  m[15] = 1;
}

GLvoid Camera::transpose( mat4f& m ) {
  mat4f temp;
  temp[0] = m[0];  temp[4] = m[1];  temp[8] = m[2];   temp[12] = m[3];
  temp[1] = m[4];  temp[5] = m[5];  temp[9] = m[6];   temp[13] = m[7];
  temp[2] = m[8];  temp[6] = m[9];  temp[10] = m[10]; temp[14] = m[11];
  temp[3] = m[12]; temp[7] = m[13]; temp[11] = m[14]; temp[15] = m[15];
  memcpy( m, &temp, 16*sizeof(GLfloat) );
}

GLvoid Camera::multMatrix( mat4f& res, const mat4f& lhs, const mat4f& rhs ) {
  mat4f temp;
  /*temp[0]  = lhs[0] * rhs[0] + lhs[1] * rhs[4] + lhs[2] * rhs[8] + lhs[3] * rhs[12];
  temp[1]  = lhs[0] * rhs[1] + lhs[1] * rhs[5] + lhs[2] * rhs[9] + lhs[3] * rhs[13];
  temp[2]  = lhs[0] * rhs[2] + lhs[1] * rhs[6] + lhs[2] * rhs[10] + lhs[3] * rhs[14];
  temp[3]  = lhs[0] * rhs[3] + lhs[1] * rhs[7] + lhs[2] * rhs[11] + lhs[3] * rhs[15];
  temp[4]  = lhs[4] * rhs[0] + lhs[5] * rhs[4] + lhs[6] * rhs[8] + lhs[7] * rhs[12];
  temp[5]  = lhs[4] * rhs[1] + lhs[5] * rhs[5] + lhs[6] * rhs[9] + lhs[7] * rhs[13];
  temp[6]  = lhs[4] * rhs[2] + lhs[5] * rhs[6] + lhs[6] * rhs[10] + lhs[7] * rhs[14];
  temp[7]  = lhs[4] * rhs[3] + lhs[5] * rhs[7] + lhs[6] * rhs[11] + lhs[7] * rhs[15];
  temp[8]  = lhs[8] * rhs[0] + lhs[9] * rhs[4] + lhs[10] * rhs[8] + lhs[11] * rhs[12];
  temp[9]  = lhs[8] * rhs[1] + lhs[9] * rhs[5] + lhs[10] * rhs[9] + lhs[11] * rhs[13];
  temp[10] = lhs[8] * rhs[2] + lhs[9] * rhs[6] + lhs[10] * rhs[10] + lhs[11] * rhs[14];
  temp[11] = lhs[8] * rhs[3] + lhs[9] * rhs[7] + lhs[10] * rhs[11] + lhs[11] * rhs[15];
  temp[12] = lhs[12] * rhs[0] + lhs[13] * rhs[4] + lhs[14] * rhs[8] + lhs[15] * rhs[12];
  temp[13] = lhs[12] * rhs[1] + lhs[13] * rhs[5] + lhs[14] * rhs[9] + lhs[15] * rhs[13];
  temp[14] = lhs[12] * rhs[2] + lhs[13] * rhs[6] + lhs[14] * rhs[10] + lhs[15] * rhs[14];
  temp[15] = lhs[12] * rhs[3] + lhs[13] * rhs[7] + lhs[14] * rhs[11] + lhs[15] * rhs[15];*/
  temp[0] = lhs[0]*rhs[0] + lhs[1]*rhs[4] + lhs[2]*rhs[8] + lhs[3]*rhs[12];
  temp[1] = lhs[0]*rhs[1] + lhs[1]*rhs[5] + lhs[2]*rhs[9] + lhs[3]*rhs[13];
  temp[2] = lhs[0]*rhs[2] + lhs[1]*rhs[6] + lhs[2]*rhs[10] + lhs[3]*rhs[14];
  temp[3] = lhs[0]*rhs[3] + lhs[1]*rhs[7] + lhs[2]*rhs[11] + lhs[3]*rhs[15];
  temp[4] = lhs[4]*rhs[0] + lhs[5]*rhs[4] + lhs[6]*rhs[8] + lhs[7]*rhs[12];
  temp[5] = lhs[4]*rhs[1] + lhs[5]*rhs[5] + lhs[6]*rhs[9] + lhs[7]*rhs[13];
  temp[6] = lhs[4]*rhs[2] + lhs[5]*rhs[6] + lhs[6]*rhs[10] + lhs[7]*rhs[14];
  temp[7] = lhs[4]*rhs[3] + lhs[5]*rhs[7] + lhs[6]*rhs[11] + lhs[7]*rhs[15];
  temp[8] = lhs[8]*rhs[0] + lhs[9]*rhs[4] + lhs[10]*rhs[8] + lhs[11]*rhs[12];
  temp[9] = lhs[8]*rhs[1] + lhs[9]*rhs[5] + lhs[10]*rhs[9] + lhs[11]*rhs[13];
  temp[10] = lhs[8]*rhs[2] + lhs[9]*rhs[6] + lhs[10]*rhs[10] + lhs[11]*rhs[14];
  temp[11] = lhs[8]*rhs[3] + lhs[9]*rhs[7] + lhs[10]*rhs[11] + lhs[11]*rhs[15];
  temp[12] = lhs[12]*rhs[0] + lhs[13]*rhs[4] + lhs[14]*rhs[8] + lhs[15]*rhs[12];
  temp[13] = lhs[12]*rhs[1] + lhs[13]*rhs[5] + lhs[14]*rhs[9] + lhs[15]*rhs[13];
  temp[14] = lhs[12]*rhs[2] + lhs[13]*rhs[6] + lhs[14]*rhs[10] + lhs[15]*rhs[14];
  temp[15] = lhs[12]*rhs[3] + lhs[13]*rhs[7] + lhs[14]*rhs[11] + lhs[15]*rhs[15];
  //transpose(temp);
  memcpy( res, &temp, 16*sizeof(GLfloat) );
}

GLvoid Camera::cross( vec3f& res, const vec3f& lhs, const vec3f& rhs ) {
  vec3f temp;
  temp[0] = lhs[1] * rhs[2] - rhs[1] * lhs[2];
  temp[1] = lhs[0] * rhs[2] - rhs[0] * lhs[2];
  temp[2] = lhs[0] * rhs[1] - rhs[0] * lhs[1];
  memcpy( res, &temp, 3*sizeof(GLfloat) );
}

GLvoid Camera::print() {
  cout << "fovy = " << m_fovY << endl;
  cout << "aspect = " << m_aspect << endl;
  cout << "near, far = " << m_zNear << " " << m_zFar << endl;
  cout << "modelview = " << endl;
  cout << "  [" << m_modelViewMatr[0] << " " << m_modelViewMatr[4] << " " << m_modelViewMatr[8] << " " << m_modelViewMatr[12] << "]" << endl;
  cout << "  [" << m_modelViewMatr[1] << " " << m_modelViewMatr[5] << " " << m_modelViewMatr[9] << " " << m_modelViewMatr[13] << "]" << endl;
  cout << "  [" << m_modelViewMatr[2] << " " << m_modelViewMatr[6] << " " << m_modelViewMatr[10] << " " << m_modelViewMatr[14] << "]" << endl;
  cout << "  [" << m_modelViewMatr[3] << " " << m_modelViewMatr[7] << " " << m_modelViewMatr[11] << " " << m_modelViewMatr[15] << "]" << endl;

  cout << "projection = " << endl;
  cout << "  [" << m_projMatr[0] << " " << m_projMatr[4] << " " << m_projMatr[8] << " " << m_projMatr[12] << "]" << endl;
  cout << "  [" << m_projMatr[1] << " " << m_projMatr[5] << " " << m_projMatr[9] << " " << m_projMatr[13] << "]" << endl;
  cout << "  [" << m_projMatr[2] << " " << m_projMatr[6] << " " << m_projMatr[10] << " " << m_projMatr[14] << "]" << endl;
  cout << "  [" << m_projMatr[3] << " " << m_projMatr[7] << " " << m_projMatr[11] << " " << m_projMatr[15] << "]" << endl;

  /*cout << "  [" << m_modelViewMatr[0] << " " << m_modelViewMatr[1] << " " << m_modelViewMatr[2] << " " << m_modelViewMatr[3] << "]" << endl;
  cout << "  [" << m_modelViewMatr[4] << " " << m_modelViewMatr[5] << " " << m_modelViewMatr[6] << " " << m_modelViewMatr[7] << "]" << endl;
  cout << "  [" << m_modelViewMatr[8] << " " << m_modelViewMatr[9] << " " << m_modelViewMatr[10] << " " << m_modelViewMatr[11] << "]" << endl;
  cout << "  [" << m_modelViewMatr[12] << " " << m_modelViewMatr[13] << " " << m_modelViewMatr[14] << " " << m_modelViewMatr[15] << "]" << endl;

  cout << "projection = " << endl;
  cout << "  [" << m_projMatr[0] << " " << m_projMatr[1] << " " << m_projMatr[2] << " " << m_projMatr[3] << "]" << endl;
  cout << "  [" << m_projMatr[4] << " " << m_projMatr[5] << " " << m_projMatr[6] << " " << m_projMatr[7] << "]" << endl;
  cout << "  [" << m_projMatr[8] << " " << m_projMatr[9] << " " << m_projMatr[10] << " " << m_projMatr[11] << "]" << endl;
  cout << "  [" << m_projMatr[12] << " " << m_projMatr[13] << " " << m_projMatr[14] << " " << m_projMatr[15] << "]" << endl;  
  */
}
