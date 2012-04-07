#include "Scene.h"

using namespace std;

GLboolean Scene::checkSupport() {
  GLenum glewInitCheck = glewInit();

  if ( !(glewInitCheck == GLEW_OK) ) {
    printf( "[FAIL] %s\n", glewGetErrorString(glewInitCheck) );
    return false;
  }

  if ( !glewIsSupported("GL_VERSION_2_0") ) {
		printf( "[FAIL] OpenGL 2.0 not supported.\n" );
		return false;
  }

  printf( "[OK] GLEW Version: %s\n", glewGetString(GLEW_VERSION) );
  printf( "[OK] OpenGL Version: 2.0\n" );
  return true;
}
