
#include <GL/glut.h>
#include<bits/stdc++.h>
#define pi atan(1)*4
using namespace std;
int xdeg=0;
int ydeg=0;
int zdeg=0;

int zoom=-30;


double sx=.3;
double sy=.3;
double sz=.3;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void circle(){
    vector< pair < double,double > >point;
    double r=3;
    for(int i=0;i<360;i++){
        double x = r * cos( i * pi / 180 );
        double y = r * sin( i * pi / 180 );
        point.push_back(make_pair(x,y));
    }
     glBegin(GL_POLYGON);
            int sz=point.size()-1;
            for(int i=0;i<=sz;i++){
                glVertex3f(point[i].first,point[i].second,0);
            }
    glEnd();
    glBegin(GL_POLYGON);
            for(int i=sz;i>=0;i--){
                glVertex3f(point[i].first,point[i].second,0);
            }
    glEnd();
}

void halfcircle(){
    vector< pair < double,double > >point;
    double r=3.15;
    for(int i=0;i<=180;i++){
        double x = r * cos( i * pi / 180 );
        double y = r * sin( i * pi / 180 );
        point.push_back(make_pair(x,y));
    }
    glBegin(GL_POLYGON);
            int sz=point.size()-1;
            for(int i=0;i<=sz;i++){
                glVertex3f(point[i].first,point[i].second,5);
            }
    glEnd();
    glBegin(GL_POLYGON);
            sz=point.size()-1;
            for(int i=sz;i>=0;i--){
                glVertex3f(point[i].first,point[i].second,-5);
            }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point[i].first,point[i].second,-5);

        }
        glVertex3f(point[0].first,point[0].second,5);
        glVertex3f(point[0].first,point[0].second,-5);
    glEnd();

}

void cylinder(double r1=3,double r2=3){
    vector< pair < double,double > >point,point2;
    double r=r1;
    for(int i=0;i<360;i++){
        double x = r * cos( i * pi / 180 );
        double y = r * sin( i * pi / 180 );

        point.push_back(make_pair(x,y));
        x = r2 * cos( i * pi / 180 );
        y = r2 * sin( i * pi / 180 );
        point2.push_back(make_pair(x,y));
    }
    glBegin(GL_POLYGON);
            int sz=point.size()-1;
            for(int i=0;i<=sz;i++){
                glVertex3f(point[i].first,point[i].second,5);
            }
    glEnd();
    glBegin(GL_POLYGON);
            sz=point.size()-1;
            for(int i=sz;i>=0;i--){
                glVertex3f(point2[i].first,point2[i].second,-5);
            }
    glEnd();
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point2[i].first,point2[i].second,-5);

        }
        glVertex3f(point[0].first,point[0].second,5);
        glVertex3f(point2[0].first,point2[0].second,-5);
    glEnd();
}

void cube()
{
    glBegin(GL_QUADS);

    glVertex3f(-2,2,2);
    glVertex3f(-2,-2,2);
    glVertex3f(2,-2,2);
    glVertex3f(2,2,2);

    //glColor3d(1,0,1);
    glVertex3f(-2,2,-2);
    glVertex3f(-2,-2,-2);
    glVertex3f(-2,-2,2);
    glVertex3f(-2,2,2);

    //glColor3d(1,0,0);
    glVertex3f(-2,-2,-2);
    glVertex3f(-2,2,-2);
    glVertex3f(2,2,-2);
    glVertex3f(2,-2,-2);

    //glColor3d(0,1,1);
    glVertex3f(2,2,2);
    glVertex3f(2,-2,2);
    glVertex3f(2,-2,-2);
    glVertex3f(2,2,-2);

    //glColor3d(0,0,0);
    glVertex3f(-2,2,2);
    glVertex3f(2,2,2);
    glVertex3f(2,2,-2);
    glVertex3f(-2,2,-2);

    //glColor3d(1,1,0);
    glVertex3f(-2,-2,2);
    glVertex3f(-2,-2,-2);
    glVertex3f(2,-2,-2);
    glVertex3f(2,-2,2);

    glEnd();
}


void base(){

    glPushMatrix(); //top base
        glColor3d(1,0,0);
        glTranslated(0,21,0);
        glScalef(1,.2,3);
        cube();
    glPopMatrix();

    glColor3d(0,1,0);
    glPushMatrix();
        glRotated(15,0,0,1);
        glRotated(-15,1,0,0);
        glPushMatrix();  //right front
            glTranslated(5,0,5);
            glScalef(.3,10,.3);
            cube();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glRotated(-15,0,0,1);
        glRotated(-15,1,0,0);
        glPushMatrix();  //left front
            glTranslated(-5,0,5);
            glScalef(.3,10,.3);
            cube();
        glPopMatrix();
    glPopMatrix();



    glPushMatrix();
        glRotated(15,0,0,1);
        glRotated(15,1,0,0);
        glPushMatrix();  //right back
            glTranslated(5,0,-5);
            glScalef(.3,10,.3);
            cube();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glRotated(-15,0,0,1);
        glRotated(15,1,0,0);
        glPushMatrix();  //left back
            glTranslated(-5,0,-5);
            glScalef(.3,10,.3);
            cube();
        glPopMatrix();
    glPopMatrix();
}

void fanbase(){
        glPushMatrix();
            glColor3d(0,0,.5);
            glTranslated(0,23,-5);
            glScalef(.3,.3,5);
            cylinder();
        glPopMatrix();

        glPushMatrix();
            glColor3d(0,.5,0);
            glTranslated(0,23,0);
            glRotated(90,1,0,0);
            glScalef(1,1,.4);
            cylinder();
        glPopMatrix();
}

void fan(){
        glPushMatrix();
            glColor3d(1,0,0);
            glTranslated(0,23.5,10);
            glScalef(7,1.5,.5);
            cube();
        glPopMatrix();

        glPushMatrix();
            glColor3d(0,.4,0);
            glTranslated(14,23.5,10);
            glRotated(-90,0,0,1);
            glScalef(1,1,.2);
            halfcircle();
        glPopMatrix();

        glPushMatrix();
            glColor3d(0,.4,0);
            glTranslated(-14,23.5,10);
            glRotated(90,0,0,1);
            glScalef(1,1,.2);
            halfcircle();
        glPopMatrix();
}


void dana(){
    glPushMatrix();
        glTranslated(15,0,0);
            fan();
    glPopMatrix();

    glPushMatrix();
        glTranslated(13,-2,0);
        glRotated(60,0,0,1);
        fan();
    glPopMatrix();

    glPushMatrix();
        glTranslated(13,48,0);
        glRotated(120,0,0,1);
        fan();
    glPopMatrix();
}

void lez(){
    glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(4,0,0);
        glVertex3f(6,4,0);
        glVertex3f(2,4,0);

        glVertex3f(0,0,0);
        glVertex3f(2,4,0);
        glVertex3f(6,4,0);
        glVertex3f(4,0,0);
    glEnd();
}

void stair(){
        glPushMatrix(); //last stair
            glTranslated(0,-13,9);
            glRotated(90,0,0,1);
            glScalef(.3,4.2,.3);
            cube();
        glPopMatrix();

        glPushMatrix(); //mid stair
            glTranslated(0,-5,7);
            glRotated(90,0,0,1);
            glScalef(.3,3.2,.3);

            cube();
        glPopMatrix();
        glPushMatrix(); //top stair
            glTranslated(0,2,5);
            glRotated(90,0,0,1);
            glScalef(.3,2.2,.3);

            cube();
        glPopMatrix();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glPushMatrix();
        glTranslated(0,-5,zoom);
        glRotated(xdeg,1,0,0);
        glRotated(ydeg,0,1,0);
        glRotated(zdeg,0,0,1);
        glScalef(sx,sy,sz);

        base();
        fanbase();
        glPushMatrix();
            glTranslated(0,5,1);
            glScalef(.75,.75,.75);
            dana();
        glPopMatrix();

        glPushMatrix(); //shamner circle
            glColor3d(.8,0,.7);
            glTranslated(0,23.5,10);
            glScalef(1.5,1.5,1);
            circle();
        glPopMatrix();

        glPushMatrix(); //picher circle
            glColor3d(.8,0,.7);
            glTranslated(0,23.5,7);
            glScalef(2.5,2.5,1);
            circle();
        glPopMatrix();

        stair(); //shamner stair
        glPushMatrix();// daner stair
            glRotated(90,0,1,0);
            stair();
        glPopMatrix();
        glPushMatrix();//bamer stair;
            glRotated(-90,0,1,0);
            stair();
        glPopMatrix();
        glPushMatrix();// back stair
            glRotated(-180,0,1,0);
            stair();
        glPopMatrix();


        glPushMatrix(); //uporer lez
            glTranslated(0,22,-15);
            glRotated(90,0,1,0);
            glScalef(3,3,3);
            lez();
        glPopMatrix();

        glPushMatrix(); //nicher lez
            glTranslated(0,22,-15);
            glRotated(90,0,1,0);
            glRotated(180,1,0,0);
            glScalef(3,3,3);
            lez();
        glPopMatrix();

        glPushMatrix(); //shamner matha
            glColor3d(1,0,0);
            glTranslated(0,23,20);
            glRotated(180,0,1,0);
            glScalef(1,1,.75);
            cylinder(3,.1);
        glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'x':
            xdeg+=3;
            break;
        case 'y':
            ydeg+=3;
            break;
        case 'z':
            zdeg+=3;
            break;
        case 'X':
            xdeg-=3;
            break;
        case 'Y':
            ydeg-=3;
            break;
        case 'Z':
            zdeg-=3;
            break;


        case '+':
            zoom++;
            break;
        case '-':
            zoom--;
            break;



        case 'a':
            sx+=.2;
            break;
        case 'b':
            sy+=.2;
            break;
        case 'c':
            sz+=.2;
            break;
        case 'A':
            sx-=.2;
            break;
        case 'B':
            sy-=.2;
            break;
        case 'C':
            sz-=.2;
            break;

    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutMainLoop();

    return EXIT_SUCCESS;
}
