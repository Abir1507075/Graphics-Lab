
#include <GL/glut.h>

#include <stdlib.h>
#include<bits/stdc++.h>
#define pi atan(1)*4
static int xdeg = 0;
static int ydeg = 0;
static int zdeg = 0;
static int zoom = -30;
using namespace std;

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

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'x':
            xdeg+=4;
            break;

        case 'y':
            ydeg+=4;
            break;
        case 'z':
            zdeg+=4;
            break;
        case 'X':
            xdeg-=4;
            break;

        case 'Y':
            ydeg-=4;
            break;
        case 'Z':
            zdeg-=4;
            break;
        case '+':
            zoom++;
            break;
        case '-':
            zoom--;
            break;


    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}
vector<pair<double,double>> circle(double r){
    vector<pair<double,double>>point;

    for(int i=0;i<=360;i++){
        double x = r * cos(i* pi / 180);
        double y = r * sin(i * pi /180);
        point.push_back(make_pair(x,y));
    }
    return point;
}
static wheel(int n);
static void car(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    wheel(4);
    glutSwapBuffers();
}

static wheel(int n){
    vector< pair<double,double> > point;
    double r = 3;
    for(int i=0;i<=360;i++){
        double x = r * cos(i* pi /180 ) ;
        double y = r * sin(i* pi /180) ;
        point.push_back(make_pair(x+n,y));
    }
    sort(point.begin(),point.end());
    glPushMatrix();
       glColor3d(1,0.5,0);
        glTranslated(0,-5,zoom);
        glRotated(xdeg,1,0,0);
        glRotated(ydeg,0,1,0);
        glRotated(zdeg,0,0,1);

    vector< pair<double,double> >half1,half2;
    for(int i=0;i<point.size();i++){
        point[i].first  = r * cos( i* pi /180 ) - n;
        point[i].second = r * sin( i* pi /180 ) ;
        if(point[i].second >= 0.0 ){
            if(point[i].first <= -3.00)half1.push_back(point[i]);
            else half2.push_back(point[i]);
        }
    }

    sort(half1.begin(),half1.end());
    sort(half2.begin(),half2.end());

    vector< pair<double,double> >body1,body2,body3,body4;
    body1.push_back(make_pair(-10,5));
    body1.push_back(make_pair(-10,0));
    body1.push_back(make_pair(-10,0));
    for(int i=0;i<half1.size();i++){
        body1.push_back(half1[i]);
    }
    body1.push_back(make_pair(-3,5));

    body2.push_back(make_pair(0,5));
    body2.push_back(make_pair(-3,5));
    body2.push_back(make_pair(-4,3));
    for(int i=0;i<half2.size();i++){
        body2.push_back(half2[i]);
    }
    body2.push_back(make_pair(0,0));

    glBegin(GL_TRIANGLE_FAN); //first concave
        for(int i=0;i<body1.size();i++){
            glVertex3f(body1[i].first,body1[i].second,4);
        }
    glEnd();
    glBegin(GL_TRIANGLE_FAN); //second concave
        for(int i=0;i<body2.size();i++){
            glVertex3f(body2[i].first,body2[i].second,4);
        }
    glEnd();
    body3.push_back(make_pair(0,5));
    body3.push_back(make_pair(0,0));


    for(int i=0;i<half1.size();i++){
        half1[i].first += 2*n;
        body3.push_back(half1[i]);
    }
    body3.push_back(make_pair(5,5));

    glBegin(GL_TRIANGLE_FAN); //third concave
        for(int i=0;i<body3.size();i++){
            glVertex3f(body3[i].first,body3[i].second,4);
        }
    glEnd();

    body4.push_back(make_pair(10,5));
    body4.push_back(make_pair(5,5));
    body4.push_back(make_pair(3,5));

    for(int i=0;i<half2.size();i++){
        half2[i].first+=2*n;
        body4.push_back(half2[i]);
    }
    body4.push_back(make_pair(10,0));

    glBegin(GL_TRIANGLE_FAN); //fourth concave
        for(int i=0;i<body4.size();i++){
            glVertex3f(body4[i].first,body4[i].second,4);
        }
    glEnd();
    body1.clear(),body2.clear(),body3.clear(),body4.clear();

///////back section/////

    body1.push_back(make_pair(-10,5));
    body1.push_back(make_pair(-3,5));
    body1.push_back(make_pair(-3,3));

    reverse(half1.begin(),half1.end());

    for(int i=0;i<half1.size();i++){
        half1[i].first-=2*n;
        body1.push_back(half1[i]);
    }
    body1.push_back(make_pair(-10,0));

    body2.push_back(make_pair(0,5));
    body2.push_back(make_pair(0,0));
    reverse(half2.begin(),half2.end());

    for(int i=0;i<half2.size();i++){
        half2[i].first-=2*n;
        body2.push_back(half2[i]);
    }
    body2.push_back(make_pair(-3,3));
    body2.push_back(make_pair(-3,5));

    glBegin(GL_TRIANGLE_FAN); //first concave 2
        for(int i=0;i<body1.size();i++){
            glVertex3f(body1[i].first,body1[i].second,-4);
        }
    glEnd();
    glBegin(GL_TRIANGLE_FAN); //second concave 2
        for(int i=0;i<body2.size();i++){
            glVertex3f(body2[i].first,body2[i].second,-4);
        }
    glEnd();
    body3.push_back(make_pair(0,5));
    body3.push_back(make_pair(5,5));
    body3.push_back(make_pair(5,3));

    for(int i=0;i<half1.size();i++){
        half1[i].first += 2*n;
        body3.push_back(half1[i]);
    }
    body3.push_back(make_pair(0,0));

    glBegin(GL_TRIANGLE_FAN); //third concave 2
        for(int i=0;i<body3.size();i++){
            glVertex3f(body3[i].first,body3[i].second,-4);
        }
    glEnd();

    body4.push_back(make_pair(7,5));
    body4.push_back(make_pair(10,5));
    body4.push_back(make_pair(10,0));
    for(int i=0;i<half2.size();i++){
        half2[i].first+=2*n;
        body4.push_back(half2[i]);
    }
    body4.push_back(make_pair(5,3));
    body4.push_back(make_pair(5,5));

    glBegin(GL_TRIANGLE_FAN); //fourth concave 2
        for(int i=0;i<body4.size();i++){
            glVertex3f(body4[i].first,body4[i].second,-4);
        }
    glEnd();

    ///body construction

    body1.clear();
    body1.push_back(make_pair(10,5));
    body1.push_back(make_pair(-10,5));
    body1.push_back(make_pair(-10,0));

    sort(half1.begin(),half1.end());
    sort(half2.begin(),half2.end());
    for(int i=0;i<half1.size();i++){
        half1[i].first -= 2*n;
        body1.push_back(half1[i]);
    }
    for(int i=0;i<half2.size();i++){
        half2[i].first -= 2*n;
        body2.push_back(half2[i]);
    }
    body1.push_back(make_pair(0,0));
    for(int i=0;i<half1.size();i++){
        half1[i].first += 2*n;
        body1.push_back(half1[i]);
    }
    for(int i=0;i<half2.size();i++){
        half2[i].first += 2*n;
        body2.push_back(half2[i]);
    }
    body1.push_back(make_pair(10,0));

    glBegin(GL_QUAD_STRIP);
        glColor3d(1,.5,0);
        for(int i=0;i<body1.size();i++){
            glVertex3f(body1[i].first,body1[i].second,4);
            glVertex3f(body1[i].first,body1[i].second,-4);
        }
        glVertex3f(body1[0].first,body1[0].second,4);
        glVertex3f(body1[0].first,body1[0].second,-4);
    glEnd();


    /// wheel
    point.clear();
    for(int i=0;i<=360;i++){
        double x = r * cos(i* pi /180 ) ;
        double y = r * sin(i* pi /180) ;
        point.push_back(make_pair(x+n,y));
    }
    glColor3d(0,0,0);
    glBegin(GL_POLYGON);//right font circle
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=point.size()-1;i>=0;i--){
            glVertex3f(point[i].first,point[i].second,3);
        }
    glEnd();
    glBegin(GL_POLYGON);
        glColor3d(0,0,0); //right back
         for(int i=point.size()-1;i>=0;i--){
            glVertex3f(point[i].first,point[i].second,-5);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,-3);
        }
    glEnd();
    glColor3d(0,0,0);
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point[i].first,point[i].second,3);
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,-3);
            glVertex3f(point[i].first,point[i].second,-5);
        }
    glEnd();
    for(int i=0;i<point.size();i++){
        point[i].first-=2*n;
    }

    glBegin(GL_POLYGON);//left font circle
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=point.size()-1;i>=0;i--){
            glVertex3f(point[i].first,point[i].second,3);
        }
    glEnd();
    glBegin(GL_POLYGON);
        glColor3d(0,0,0); //left     back
         for(int i=point.size()-1;i>=0;i--){
            glVertex3f(point[i].first,point[i].second,-5);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,-3);
        }
    glEnd();
    glColor3d(0,0,0);
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point[i].first,point[i].second,3);
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,-3);
            glVertex3f(point[i].first,point[i].second,-5);
        }
    glEnd();


    for(int i=0;i<point.size();i++){
        point[i].first  = cos(i* pi /180 ) + n;
        point[i].second = sin(i* pi /180 ) ;
    }

    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point[i].first,point[i].second,-5);
        }
    glEnd();
    for(int i=0;i<point.size();i++){
        point[i].first  = cos(i* pi /180 ) - n;
        point[i].second = sin(i* pi /180 ) ;
    }
    glColor3d(0,0,0);
    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<point.size();i++){
            glVertex3f(point[i].first,point[i].second,5);
            glVertex3f(point[i].first,point[i].second,-5);
        }
    glEnd();



    glBegin(GL_QUADS); ///upper body
    glColor3d(1,.5,0);
        glVertex3f(4,9,3);
        glVertex3f(-7,9,3);
        glVertex3f(-7,5,3);
        glVertex3f(4,5,3);

        glVertex3f(-7,9,3);
        glVertex3f(-7,9,-3);
        glVertex3f(-7,5,-3);
        glVertex3f(-7,5,3);

        glVertex3f(-7,9,-3);
        glVertex3f(4,9,-3);
        glVertex3f(4,5,-3);
        glVertex3f(-7,5,-3);

        glVertex3f(4,9,3);
        glVertex3f(4,9,-3);
        glVertex3f(-7,9,-3);
        glVertex3f(-7,9,3);

        glVertex3f(4,9,-3);
        glVertex3f(4,9,3);
        glVertex3f(4,5,3);
        glVertex3f(4,5,-3);

    glEnd();
    glBegin(GL_QUADS);  ///glass
        glColor3d(0,0,1);
        ///
        glVertex3f(3,8,4);
        glVertex3f(-6,8,4);
        glVertex3f(-6,5,4);
        glVertex3f(3,5,4);

        glVertex3f(3,5,3);
        glVertex3f(3,8,3);
        glVertex3f(3,8,4);
        glVertex3f(3,5,4);

        glVertex3f(3,8,4);
        glVertex3f(3,8,3);
        glVertex3f(-6,8,3);
        glVertex3f(-6,8,4);

        glVertex3f(-6,8,4);
        glVertex3f(-6,8,3);
        glVertex3f(-6,5,3);
        glVertex3f(-6,5,4);


        ///
        glVertex3f(-8,8,2);
        glVertex3f(-8,8,-2);
        glVertex3f(-8,5,-2);
        glVertex3f(-8,5,2);

        glVertex3f(-8,8,2);
        glVertex3f(-8,5,2);
        glVertex3f(-7,5,2);
        glVertex3f(-7,8,2);

        glVertex3f(-8,8,2);
        glVertex3f(-7,8,2);
        glVertex3f(-7,8,-2);
        glVertex3f(-8,8,-2);

        glVertex3f(-8,8,-2);
        glVertex3f(-7,8,-2);
        glVertex3f(-7,5,-2);
        glVertex3f(-8,5,-2);


        ///
        glVertex3f(-6,8,-4);
        glVertex3f(3,8,-4);
        glVertex3f(3,5,-4);
        glVertex3f(-6,5,-4);

        glVertex3f(-6,8,-4);
        glVertex3f(-6,5,-4);
        glVertex3f(-6,5,-3);
        glVertex3f(-6,8,-3);

        glVertex3f(-6,8,-4);
        glVertex3f(-6,8,-3);
        glVertex3f(3,8,-3);
        glVertex3f(3,8,-4);

        glVertex3f(3,8,-4);
        glVertex3f(3,8,-3);
        glVertex3f(3,5,-3);
        glVertex3f(3,5,-4);

        ///
        glVertex3f(5,8,-2);
        glVertex3f(5,8,2);
        glVertex3f(5,5,2);
        glVertex3f(5,5,-2);

        glVertex3f(4,8,-2);
        glVertex3f(5,8,-2);
        glVertex3f(5,5,-2);
        glVertex3f(4,5,-2);

        glVertex3f(5,8,-2);
        glVertex3f(4,8,-2);
        glVertex3f(4,8,2);
        glVertex3f(5,8,2);

        glVertex3f(5,8,2);
        glVertex3f(4,8,2);
        glVertex3f(4,5,2);
        glVertex3f(5,5,2);
    glEnd();
    glBegin(GL_QUADS); ///font protector
        glColor3d(.3,.3,.3);
        glVertex3f(10.5,1,-3);
        glVertex3f(10.5,2,-3);
        glVertex3f(10.5,2,3);
        glVertex3f(10.5,1,3);

        glVertex3f(10.5,2,-3);
        glVertex3f(10.5,1,-3);
        glVertex3f(10,1,-3);
        glVertex3f(10,2,-3);

        glVertex3f(10.5,2,-3);
        glVertex3f(10,2,-3);
        glVertex3f(10,2,3);
        glVertex3f(10.5,2,3);

        glVertex3f(10.5,2,3);
        glVertex3f(10,2,3);
        glVertex3f(10,1,3);
        glVertex3f(10.5,1,3);

///back protector
        glVertex3f(-10.5,1,3);
        glVertex3f(-10,1,3);
        glVertex3f(-10,1,-3);
        glVertex3f(-10.5,1,-3);

        glVertex3f(-10.5,1,3);
        glVertex3f(-10.5,2,3);
        glVertex3f(-10.5,2,-3);
        glVertex3f(-10.5,1,-3);

        glVertex3f(-10.5,2,3);
        glVertex3f(-10.5,1,3);
        glVertex3f(-10,1,3);
        glVertex3f(-10,2,3);



        glVertex3f(-10.5,2,3);
        glVertex3f(-10,2,3);
        glVertex3f(-10,2,-3);
        glVertex3f(-10.5,2,-3);

        glVertex3f(-10.5,2,-3);
        glVertex3f(-10,2,-3);
        glVertex3f(-10,1,-3);
        glVertex3f(-10.5,1,-3);

///back signal
        glColor3d(1,0,0);
        glVertex3f(-10.5,3,3);
        glVertex3f(-10,3,3);
        glVertex3f(-10,3,-3);
        glVertex3f(-10.5,3,-3);

        glVertex3f(-10.5,3,3);
        glVertex3f(-10.5,4,3);
        glVertex3f(-10.5,4,-3);
        glVertex3f(-10.5,3,-3);

        glVertex3f(-10.5,4,3);
        glVertex3f(-10.5,3,3);
        glVertex3f(-10,3,3);
        glVertex3f(-10,4,3);



        glVertex3f(-10.5,4,3);
        glVertex3f(-10,4,3);
        glVertex3f(-10,4,-3);
        glVertex3f(-10.5,4,-3);

        glVertex3f(-10.5,4,-3);
        glVertex3f(-10,4,-3);
        glVertex3f(-10,3,-3);
        glVertex3f(-10.5,3,-3);


    glEnd();
    vector<pair<double,double> >big=circle(.75),sm=circle(.35);
    glColor3d(1,1,0);
    glBegin(GL_POLYGON);
        for(int i=0;i<big.size();i++){
            glVertex3f(10.0001,big[i].first+4,big[i].second+2.5);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=0;i<sm.size();i++){
            glVertex3f(10.35,sm[i].first+4,sm[i].second+2.5);
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<big.size();i++){
            glVertex3f(10,big[i].first+4,big[i].second+2.5);
            glVertex3f(10.35,sm[i].first+4,sm[i].second+2.5);
        }

    glEnd();


    glBegin(GL_POLYGON);
        for(int i=0;i<big.size();i++){
            glVertex3f(10.0001,big[i].first+4,big[i].second-2.5);
        }
    glEnd();
    glBegin(GL_POLYGON);
        for(int i=0;i<sm.size();i++){
            glVertex3f(10.35,sm[i].first+4,sm[i].second-2.5);
        }
    glEnd();

    glBegin(GL_QUAD_STRIP);
        for(int i=0;i<big.size();i++){
            glVertex3f(10,big[i].first+4,big[i].second-2.5);
            glVertex3f(10.35,sm[i].first+4,sm[i].second-2.5);
        }

    glEnd();

    glPopMatrix();






}
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1040,780);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(car);
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
