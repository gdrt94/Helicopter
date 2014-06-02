Helicopter
==========
First of all I have downloaded a helicopter .obj file from http://tf3dm.com/3d-models/helicopter. Then I have loaded this .obj file using reading from file templates. Then obj file was drawn. The file is quite big enough, so you should wait several seconds until it opens. The idea of loading a helicopter object was best for 3D transformations. I gave the object transformation, scaling and rotation effects. It can be tested using keyboard and mouse. Also I gave lighting effects to my helicopter. 

In main() function there is a standard code for positioning a window, naming it and other stuff. 

Then using obj file reading template I am reading objects vertices and faces to 2 different arrays. 

After reading I am writing to console additional information for an end user how to use my program.

init() method is called for initializing lighting parameters.

Then glutDisplayFunc(display) is called. display() function is responsible for rotating, scaling and translation effects. From display() function drawAnyObject() function is called, which was responsible for drawing triangles using 2 above mentioned arrays. Also the normal values were calculated here using Coord norm, which is declared right above drawAnyObject() function in the code. Here a simplified formula for normal calculation was used and normal with 3 attributes is returned. Then glNormal3f(normal.x, normal.y, normal.z) is called, which sets the current normal vector. drawAnyObject() function ends, and then display() function ends too with calling glutSwapBuffers() function.

There is a standard glutReshapeFunc(reshape) in my main() function. Here is the gluPerspective(60.0, (GLdouble)w / (GLdouble)h, 1.0, 8000.0) function, where the most visible far point is assigned to 8000.0, because my object is very big.

glutKeyboardFunc(keyPressed) in my main() function does the core actions in my project. There are 8 different keys you can press and move my object in 3D-scene. After keyPressed event occurs, glutPostRedisplay() method is called, which calls display() function again. Here glRotatef(alphaY, 0, 1, 0) glRotatef(alphaX, 1, 0, 0) are rotating my object around Y and X – axis respectively, dependent on which key in keyboard is pressed and therefore which value (alphaY or alphaX) is changed. glScalef(scX, scY, scZ) is used here for scaling also dependent on which key in keyboard is pressed. And finally the glTranslatef(trX, trY, trZ) is responsible for moving forward and backward, also dependent on which key in keyboard is pressed. 

glutMotionFunc(motion) in my main() function is responsible for mouse interuptions. Mouse positions are assigned to my global variables rotX and rotY. Then glutPostRedisplay() is called. In display() dunction 2 methods interacts with this parameters glRotatef(rotX, 0, 1, 0)	glRotatef(rotY, 1, 0, 0).

There is also glutIdleFunc(idle)  in my main() function which sets the global idle callback as documentation of opengl.org states. 
