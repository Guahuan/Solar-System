#pragma once
#include <GL/glut.h>

class Ball {
public:
  Ball(float x, float y, float z, float size, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->size = size;
    this->r = r;
    this->g = g;
    this->b = b;
  };

  virtual void draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidSphere(size, 30, 30);
    glPopMatrix();
  };

public:
  float x, y, z;
  float size;
  float r, g, b;
};