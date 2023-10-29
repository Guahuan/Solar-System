#include <GL/glut.h>
#include <iostream>

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

  glutInitWindowSize(1024, 768);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Tutorial 01");

  glutDisplayFunc(display);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
  glutMainLoop();
  return 0;
}