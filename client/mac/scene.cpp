//
//  scene.cpp
//  client
//
//  Created by jesson on 2021/8/28.
//

#include "scene.hpp"
#include <gl/GL.h>
#include <gl/GLU.h>


void InitScene() {
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawScene(){
    glClearColor(0.5f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

