#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#include <GL/glut.h>
#include <GL/GL.H>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace std;
float v[27982][3];
int f[25130][3];
int rotX, rotY;
int trX, trY, trZ;
int scX = 1, scY = 1 , scZ = 1;
//bool* keyStates = new bool[256];

GLfloat amblight[] = { 1.0, 0.0, 0.0, 0.0 };
GLfloat diflight[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat speclight[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat position[] = { 1.0, 0.0, 1.0 };
GLfloat difposition[] = { 1.0, 0.0, 1.0, 0.0 };

GLfloat shinines[] = { 120.0 };
GLfloat ambmatherial[] = { 1.0, 0.0, 0.0, 0.0 };
GLfloat difmatherial[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat specmatherial[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat angle = 0.0;
double alphaY = 0.0;
double alphaX = 0.0;

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, amblight);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambmatherial);

	glLightfv(GL_LIGHT0, GL_POSITION, difposition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diflight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difmatherial);

	//glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, speclight);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specmatherial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shinines);

}
void idle() {
	glutPostRedisplay();
}

//normal calculation
class Coord
{
public:
	float x;
	float y;
	float z;
} fCoord, sCoord, tCoord;


Coord norm(Coord a, Coord b, Coord c)
{
	Coord normal;
	
	normal.x = (b.y - a.y)*(c.z - b.z) - (b.z - a.z)*(c.y - b.y);
	normal.y = (b.z - a.z)*(c.x - b.x) - (b.x - a.x)*(c.z - b.z);
	normal.z = (b.x - a.x)*(c.y - b.y) - (b.y - a.y)*(c.x - b.x);

	double l = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	normal.x /= l;
	normal.y /= l;
	normal.z /= l;
	return normal;
}

void drawAnyObject(){

	glPushMatrix();
	for (int i = 0; i<25130; i++){
		glBegin(GL_TRIANGLES);
		fCoord.x = v[f[i][0]][0];
		fCoord.y = v[f[i][0]][1];
		fCoord.z = v[f[i][0]][2];
		sCoord.x = v[f[i][1]][0];
		sCoord.y = v[f[i][1]][1];
		sCoord.z = v[f[i][1]][2];
		tCoord.x = v[f[i][2]][0];
		tCoord.y = v[f[i][2]][1];
		tCoord.z = v[f[i][2]][2];

		glVertex3f(fCoord.x, fCoord.y, fCoord.z);
		glVertex3f(sCoord.x, sCoord.y, sCoord.z);
		glVertex3f(tCoord.x, tCoord.y, tCoord.z);
		Coord normal = norm(fCoord, sCoord, tCoord);
		glNormal3f(normal.x, normal.y, normal.z);
		glEnd();
	}
	glPopMatrix();
}
/*
void keyOperations() {
	if (keyStates['w'] && keyStates['a']){ trZ += 20; trX -= 20; }
	glutPostRedisplay();
}*/

void display(){

	//keyOperations();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(0.0f, 0.5f, 0.3f);
	glRectf(-0.75f, 0.75f, 0.75f, -0.75f);
	glLoadIdentity();
	//gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 10.0);

	glTranslatef(0, 0, -1500); //helikopter boyuk oldugundan onu uzaqlasdiririq
	glRotatef(180.0, 0, 1, 0); //helikopteri arxasi bize teref ceviririk
	glRotatef(alphaY, 0, 1, 0);//rotation
	glRotatef(alphaX, 1, 0, 0);//rotation
	glScalef(scX, scY, scZ); //scaling
	glTranslatef(trX, trY, trZ); //3d transformation
	glRotatef(rotX, 0, 1, 0); //rotation
	glRotatef(rotY, 1, 0, 0); //rotation

	drawAnyObject();

	glutSwapBuffers();
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 8000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyPressed(unsigned char key, int x, int y) { // transformation, scaling, rotation
	if (key == 'a'){ alphaY += 1; }
	else if (key == 'd'){ alphaY -= 1; }
	else if (key == 'w'){ trZ += 20; }
	else if (key == 's'){ trZ -= 20; }
	else if (key == 'o'){ alphaX += 1; }
	else if (key == 'l'){ alphaX -= 1; }
	else if (key == '['){ scX += 1.0; scY += 1.0; scZ += 1.0; }
	else if (key == ']'){ scX -= 1.0; scY -= 1.0; scZ -= 1.0; }
	glutPostRedisplay();
}
/*
void keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) { 
	keyStates[key] = false;
}*/

void motion(int x, int y){ // rotating
	rotX = x;
	rotY = y;
	glutPostRedisplay();
}

int main(){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1200, 640);
	glutCreateWindow("Helicopter");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	int k = 0, m = 0;
	char ch;
	float aa, bb, cc;

	//Fayldan oxuma kodu - template
	ifstream in("havoc.obj", ios::in);

	string line;
	while (getline(in, line))
	{
		//check v for vertices
		if (line.substr(0, 2) == "v ")
		{
			istringstream vert(line.substr(2));

			vert >> aa;
			vert >> bb;
			vert >> cc;
			v[k][0] = (float)aa;
			v[k][1] = (float)bb;
			v[k][2] = (float)cc;

			k++;
		}

		else if (line.substr(0, 2) == "f ")
		{
			int a, b, c, d; //to store mesh index
			int A, B, C, D; //to store texture index
			int a1, b1, c1;

			const char* chh = line.c_str();
			sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &A, &a1, &b, &B, &b1, &c, &C, &c1); //here it read the line start with f and store the corresponding values in the variables

			f[m][0] = a - 1;
			f[m][1] = b - 1;
			f[m][2] = c - 1;
			m++;
		}
	}

	printf("Use 'w'/'s' keys to move forward/downward\n");
	printf("Use 'a'/'d' keys to move to the left/right\n");
	printf("Use 'o'/'l' keys to move up/down\n");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	//glutKeyboardUpFunc(keyUp);
	glutMotionFunc(motion);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}
