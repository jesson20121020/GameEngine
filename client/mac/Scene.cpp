//
//  scene.cpp
//  client
//
//  Created by jesson on 2021/8/28.
//

#include "Scene.h"
#include <OpenGL/OpenGL.h>
#include <OpenGL//gl.h>
#include <OpenGl/glu.h>


void Init(float width, float height) {
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0f, width / height, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Renderer(){
    glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

