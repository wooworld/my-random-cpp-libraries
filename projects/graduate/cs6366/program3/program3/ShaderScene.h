#ifndef SHADER_SCENE_H
#define SHADER_SCENE_H

#include "Scene.h"
#include "ShaderCamera.h"

class ShaderScene : public Scene {
private:
  GLvoid init();
  GLfloat COLOR_CHANGE;

public:
  ShaderScene();
  ShaderScene( GLuint numModels );
  ~ShaderScene();

  GLvoid loadDefaultShaders();
  GLint loadShader( char* loc, GLenum type );
  GLvoid printShaderInfoLog( GLuint shaderID );
  GLvoid printProgramInfoLog( GLuint programID );

  GLvoid drawCurrentModel();

  GLvoid centerOnCurrentModel();

  GLvoid handleKeys();

  GLvoid print();

  GLint m_vShader;             // The vertex shader ID
  GLint m_fShader;             // The fragment shader ID
  GLint m_shaderProgram;       // The shader program ID  
};

#endif