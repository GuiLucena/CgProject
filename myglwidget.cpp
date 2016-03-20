#include "myglwidget.h"

MyGlWidget::MyGlWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

MyGlWidget::~MyGlWidget(){ }

void MyGlWidget::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW );
    glLoadIdentity();
    gluOrtho2D(0, 10, 0, 10);
}
void drawPoint(int x , int y){
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
        glVertex3f(x,y,0);
        glVertex3f(x,y+1,0);
        glVertex3f(x+1,y+1,0);
        glVertex3f(x+1,y,0);
     glEnd();
}

void drawGrid(){
    int SIZE = 10;
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        for(int i = 0 ; i <= SIZE; i++)
        {
            glVertex3f(0,i,0);
            glVertex3f(SIZE,i,0);
            glVertex3f(i,0,0);
            glVertex3f(i,SIZE,0);
        }
    glEnd();
}

void MyGlWidget::paintGL()
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawPoint(0,0);
    glFlush();
}

void MyGlWidget::resizeGL(int wid, int heig){
    glViewport(0,0, wid, wid);

}


