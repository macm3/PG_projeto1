#include <GLUT/GLUT.h>
#include <glm/glm.hpp>
#include <OpenGL/gl.h>
#include <iostream>
#include <vector>
#include "ponto.h"
#include "mathutil.h"

using namespace std;

const int WINDOW_W = 500;
const int WINDOW_H = 500;

vector <Ponto> pontos;
bool bezier = false;

// class Point
// {
// public:
// Point(int x, int y) {
//     this->x = x;
//     this->y = y;
// }

// private:
//     int x;
//     int y;
// };

// vector<Point> myvector;

void init(void)
{
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void handleKeypress(unsigned char key, int x, int y)
{
    // switch (key)
    // {
    //     case 27:
    //         exit(0);
    // }

    //Monitoria Marcel
    switch (key) {
        case 27: // ESC
            exit(0);
        case 'b':
            bezier = !bezier;
    }
    
    glutPostRedisplay();
    // --Monitoria Marcel
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // glBegin(GL_QUADS);
    //     glColor3f(0.0, 1.0, 0.0);
    //     glVertex2f(0, 0);
    //     glVertex2f(5, 0);
    //     glVertex2f(5, 5);
    //     glVertex2f(0, 5);
    // glEnd();

    //Marcel Monitoria
    if(pontos.size() > 0) {
        
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0f, 1.0f, 1.0f);
    
        if (pontos.size() > 1) {
            if (bezier) {
                Ponto p(0,0);
                for (float t = 0.0; t <= 1.0; t += 0.01) {
                    MathUtil::bezier(pontos, t, p);
                    glVertex2f(p.x, p.y);
                }
            }
            else {
                for (auto p : pontos)
                    glVertex2d(p.x, p.y);
            }
        }
        else {
            auto p = pontos.front();
            glVertex2d(p.x, p.y);
        }
        
        glEnd();
        
        
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 1.0f, 0.0f);
        
        for(auto p : pontos)
            glVertex2d(p.x, p.y);
        
        glEnd();
    }
    // --Monitoria Marcel
    
    glFlush();
}

// void mouseHandle(int button, int state, int x, int y)
// {
//     if(button == GLUT_LEFT_BUTTON) {
//         myvector.push_back(Point(x, y));
//     }
// }

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // if (w <= h)
    //     glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,
    //             5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
    // else
    //     glOrtho(-5.0*(GLfloat)w/(GLfloat)h,
    //             5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
    
    //Monitoria Marcel
    glOrtho(0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
    //-- Monitoria Marcel
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Monitoria Marcel
void handleMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
            pontos.push_back(Ponto(x, y));
    
    glutPostRedisplay();
}
// --Monitoria Marcel

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    //glutCreateWindow ("Curva de Bezier");
    //init ();

    //Monitoria Marcel
    glutCreateWindow("Exemplo OpenGL");
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW); // estou alterando a matriz de do modelo da cena
    glLoadIdentity();
    // --Monitoria Marcel

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);

    //glutMouseFunc(mouseHandle);

    //Monitoria Marcel
    glutMouseFunc(handleMouseClick);
    // --Monitoria Marcel

    glutMainLoop();
    return 0;
}
