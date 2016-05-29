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

void init(void)
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_FLAT);
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: // ESC
            exit(0);
        case 'b':
            bezier = !bezier;
    }
    
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
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
    
    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON){
        if (state == GLUT_DOWN){
            printf("%d %d\n", x, y);
            int pontoFind = MathUtil::findPonto(pontos, x, y);
            if(pontoFind > -1){
                while(state == GLUT_DOWN){
                    
                }
            }else{
                pontos.push_back(Ponto(x, y));
            }
        }
    }else if(button == GLUT_RIGHT_BUTTON){
        if (state == GLUT_DOWN){
            int pontoFind = MathUtil::findPonto(pontos, x, y);
            if(pontoFind > -1)
                pontos.erase(pontos.begin() + pontoFind);
        }    
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (WINDOW_W, WINDOW_H);
    glutInitWindowPosition (100, 100);

    glutCreateWindow("Projeto PG");
    glClearColor(1.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW); // estou alterando a matriz de do modelo da cena
    glLoadIdentity();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouseClick);

    glutMainLoop();
    return 0;
}
