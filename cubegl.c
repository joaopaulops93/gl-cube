#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <unistd.h>     // Header File For sleeping.
#include <stdio.h>
#include <time.h>

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;

/* Grid squares that will be gridColors */
int gridColors[16];
int cubeColors[6];
int finish;

/* Cube initial psition */
int cubePos;

struct rot_state {
    float angle;
    int direction;
} app_state;

void drawRectangle(float r, float g, float b, float l, float h) {

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(-l/2, h/2, 0.0f);
	glVertex3f( l/2, h/2, 0.0f);
	glVertex3f( l/2,-h/2, 0.0f);
	glVertex3f(-l/2,-h/2, 0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(r, g, b);
	glVertex3f(-l/2, h/2, 0.0f);
	glVertex3f( l/2, h/2, 0.0f);
	glVertex3f( l/2,-h/2, 0.0f);
	glVertex3f(-l/2,-h/2, 0.0f);
	glEnd();
}

void drawGrid() {
	int i, j;
	glPushMatrix();
	for (i=0; i<4; i++) {
		glPushMatrix();
		for (j=0; j<4; j++) {
			if (gridColors[i*4+j] == 0) {
				drawRectangle(0.0f,0.0f, 0.0f, 1.0f, 1.0f);
			} else {
				drawRectangle(0.0f,0.0f, 1.0f, 1.0f, 1.0f);
			}
			glTranslatef(1.0f,0.0f,0.0f);
		}
		glPopMatrix();
		glTranslatef(0.0f,-1.0f,0.0f);
	}
	glPopMatrix();
}

void drawCube() {
	switch (app_state.direction) {
	case 0:
		glTranslatef(cubePos%4, -cubePos/4+0.5f, 0.0f);
		glRotatef(-app_state.angle,1.0f,0.0f,0.0f);
		glTranslatef(0.0f, -0.5f, 0.5f);
		break;
	case 1:
		glTranslatef(cubePos%4, -cubePos/4-0.5f, 0.0f);
		glRotatef(app_state.angle,1.0f,0.0f,0.0f);
		glTranslatef(0.0f, 0.5f, 0.5f);
		break;
	case 2:
		glTranslatef(cubePos%4-0.5f, -cubePos/4, 0.0f);
		glRotatef(-app_state.angle,0.0f,1.0f,0.0f);
		glTranslatef(0.5f, 0.0f, 0.5f);
		break;
	case 3:
		glTranslatef(cubePos%4+0.5f, -cubePos/4, 0.0f);
		glRotatef(app_state.angle,0.0f,1.0f,0.0f);
		glTranslatef(-0.5f, 0.0f, 0.5f);
		break;
	default:
		glTranslatef(cubePos%4, -cubePos/4, 0.5f);
		break;
	}
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	if (cubeColors[2] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(0.0f,0.0f,-1.0f);
	if (cubeColors[0] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,0.0f,1.0f,0.0f);
	glTranslatef(0.0f,0.0f,0.5f);
	if (cubeColors[5] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(0.0f,0.0f,-1.0f);
	if (cubeColors[4] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(0.0f,0.0f,0.5f);
	if (cubeColors[1] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glTranslatef(0.0f,0.0f,-1.0f);
	if (cubeColors[3] == 0) {
		drawRectangle(0.3f, 0.3f, 0.3f, 1.0f, 1.0f);
	} else {
		drawRectangle(0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	}
	glPopMatrix();
}

void action(void)
{
    // Animate the rotation
    float increment = 1.0f;
    int i, last;
    switch (app_state.direction)
    {
    case 0:
        if (app_state.angle <= 89.0f) {
            app_state.angle += increment;
        } else {
            app_state.angle = 0.0f;
            cubePos -= 4;
            app_state.direction = -1;
            last = cubeColors[3];
            for (i=3; i>0; i--) {
               cubeColors[i] = cubeColors[i-1];
            }
            if (finish==0) {
                cubeColors[0] = gridColors[cubePos];
                gridColors[cubePos] = last;
            } else {
                cubeColors[0] = last;
            }
        }
        break;
    case 1:
        if (app_state.angle <= 89.0f) {
            app_state.angle += increment;
        } else {
            app_state.angle = 0.0f;
            cubePos += 4;
            app_state.direction = -1;
            last = cubeColors[0];
            if (finish==0) {
                cubeColors[0] = gridColors[cubePos];
                gridColors[cubePos] = cubeColors[1];
            } else {
                cubeColors[0] = cubeColors[1];
            }
            for (i=1; i<3; i++) {
               cubeColors[i] = cubeColors[i+1];
            }
            cubeColors[3] = last;
        }
        break;
    case 2:
        if (app_state.angle <= 89.0f) {
            app_state.angle += increment;
        } else {
            app_state.angle = 0.0f;
            cubePos -= 1;
            app_state.direction = -1;
            last = cubeColors[0];
            if (finish==0) {
                cubeColors[0] = gridColors[cubePos];
                gridColors[cubePos] = cubeColors[4];
            } else {
                cubeColors[0] = cubeColors[4];
            }
            cubeColors[4] = cubeColors[2];
            cubeColors[2] = cubeColors[5];
            cubeColors[5] = last;
        }
        break;
    case 3:
        if (app_state.angle <= 89.0f) {
            app_state.angle += increment;
        } else {
            app_state.angle = 0.0f;
            cubePos += 1;
            app_state.direction = -1;
            last = cubeColors[0];
            if (finish==0) {
                cubeColors[0] = gridColors[cubePos];
                gridColors[cubePos] = cubeColors[5];
            } else {
                cubeColors[0] = cubeColors[5];
            }
            cubeColors[5] = cubeColors[2];
            cubeColors[2] = cubeColors[4];
            cubeColors[4] = last;
            app_state.direction = -1;
        }
        break;
    default:
        break;
    }
    last = 1;
    for (i=0; i<6;i++) {
        last = last && cubeColors[i];
    }
    finish = last;
    glutPostRedisplay();
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  app_state.direction = -1;
  app_state.angle = 0.0f;
  app_state.angle = 0.0f;
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glTranslatef(-1.5f,1.5f,-6.0f);
  drawGrid();
  drawCube();
  glPopMatrix();
  glutSwapBuffers();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
	usleep(100);
	switch (key)
	{
	case 27:
		glutDestroyWindow(window); 
		exit(0);
		break;
	case 'w':
		if (cubePos > 3) {
			app_state.direction = 0;
		}
		break;
	case 's':
		if (cubePos < 12) {
			app_state.direction = 1;
		}
		break;
	case 'a':
		if (cubePos%4 != 0) {
			app_state.direction = 2;
		}
		break;
	case 'd':
		if (cubePos%4 != 3) {
			app_state.direction = 3;
		}
		break;
	}
	glutPostRedisplay();

}

int main(int argc, char **argv) {

  srand(time(NULL));
  int i, n;
  for (i=0; i<16; i++) {
    gridColors[i] = 0;
  }
  for (i=0; i<6; i++) {
    cubeColors[i] = 0;
  }
  finish = 0;
  i = 0;
  while (i!=7) {
    n = rand() % 16;
    if (gridColors[n] == 0) {
      if (i == 6) {
        cubePos = n;
      } else {
        gridColors[n] = 1;
      }
      i++;
    }
  }
  
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);  

  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

  /* get a 640 x 480 window */
  glutInitWindowSize(640, 480);  

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);  

  /* Open a window */  
  window = glutCreateWindow("TintCube");  

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);  

  /* Go fullscreen.  This is as soon as possible. */
/*  glutFullScreen();*/

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&action);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(640, 480);
  
  /* Start Event Processing Engine */  
  glutMainLoop();  

  return 1;
}
