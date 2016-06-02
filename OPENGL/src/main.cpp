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
bool normal = true;
float valorT = 0.01;
bool exibePontos = true;
int estado;

// Constantes do programa
#define FPS         30  // Quantidade de atualizacoes por segundo do programa
#define IDLE        -2  // Nada a fazer
#define MODIFIED    -1  // A tela foi modificada

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
            break;
        case 'p':
            if(pontos.size() > 0) pontos = MathUtil::degreeElevation(pontos);
            break;
        case 'm':
            exibePontos = !exibePontos;
            break;
        case 'n':
            normal = !normal;
            break;
        // case '=':
        //     if(valorT < 0.1) valorT = valorT*10;
        //     break;
        // case '-':
        //     if(valorT > 0.00001) valorT = valorT/10.0;
        //     break;
    }
    glutPostRedisplay();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(pontos.size() > 0) {
        
        //glBegin(GL_LINE_STRIP);
        //glColor3f(1.0f, 1.0f, 1.0f);
    
        if (pontos.size() > 1) {
            
            if(bezier){
                glBegin(GL_LINE_STRIP);
                glColor3f(1.0f, 1.0f, 1.0f);
                for (float t = 0.000; t <= 1.1; t += 0.1) {
                    printf("%f\n", t);
                    Ponto p = MathUtil::deCasteljau(pontos, t);
                    glVertex2f(p.x, p.y);
                }
                glEnd();
            }

            if (normal) {
                glBegin(GL_LINE_STRIP);
                glColor3f(0.0f, 1.0f, 0.0f);
                for (auto p : pontos)
                    glVertex2d(p.x, p.y);
                glEnd();
            }

        }
        else {
            glBegin(GL_LINE_STRIP);
            glColor3f(1.0f, 1.0f, 1.0f);
            auto p = pontos.front();
            glVertex2d(p.x, p.y);
            glEnd();
        }
        //glEnd();
        
        // desenha os pontos
        if(exibePontos) {
            glPointSize(5.0f);
            glBegin(GL_POINTS);
            glColor3f(1.0f, 1.0f, 0.0f);
            
            for(auto p : pontos)
                glVertex2d(p.x, p.y);
            glEnd();
        }
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
    if (estado == IDLE && button == GLUT_LEFT_BUTTON){
        if (state == GLUT_DOWN){
            int pontoFind = MathUtil::findPonto(pontos, x, y);
            if(pontoFind > -1){// movimenta o ponto
                estado = pontoFind;
            }else{
                pontos.push_back(Ponto(x, y));
            }
        }
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        estado = MODIFIED;

    }else if(estado == IDLE && button == GLUT_RIGHT_BUTTON){//botão para deletar
        if (state == GLUT_DOWN){
            int pontoFind = MathUtil::findPonto(pontos, x, y);
            if(pontoFind > -1)
                pontos.erase(pontos.begin() + pontoFind);
                estado = MODIFIED;
        }    
    }
    glutPostRedisplay();
}

void handleMotion(int x, int y)
{
    if((estado != MODIFIED) && (estado != IDLE)){
        pontos[estado].x = x;
        pontos[estado].y = y;
    }
}

void loop(int id)
{
    if(estado == MODIFIED){
        display();
        estado = IDLE;
    }
    else if(estado != IDLE){
        display();
    }
    glutTimerFunc(1000/FPS, loop, id);
}

void myinit()
{
    srand(time(NULL));
    estado = MODIFIED;
    loop(0);
    pontos.clear();
}

void hadleSpecialKeyboard(int key, int x, int y)
{
    if(key == GLUT_KEY_F5){
        myinit();
    }
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
    glutMotionFunc(handleMotion);
    glutSpecialUpFunc(hadleSpecialKeyboard);

    myinit();

    glutMainLoop();
    return 0;
}
