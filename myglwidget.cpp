#include "myglwidget.h"

MyGlWidget::MyGlWidget(QWidget *parent) :
    QGLWidget(parent)
{
    matrixSize =  2;
    xInit = 0;
    yInit = 0;
    xFin = 0;
    yFin = 0;
    ddaEnabled = false;
    midlePointEnabled = false;
    lineEqEnabled = false;
    meshEnabled = false;
    origLineEnabled = false;
}


int matrixSize;
int xInit;
int yInit;
int xFin;
int yFin;
bool ddaEnabled;
bool midlePointEnabled;
bool lineEqEnabled;
bool meshEnabled;
bool origLineEnabled;


void MyGlWidget::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
}

void MyGlWidget::paintGL()
{
    glLoadIdentity();
    gluOrtho2D(0, matrixSize, 0,matrixSize);
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(meshEnabled == true)
        drawGrid();
    if(ddaEnabled == true)
        DDA(xInit,yInit,xFin,yFin);
    if(midlePointEnabled == true)
        middlePoint(xInit,yInit,xFin,yFin);
    if(lineEqEnabled == true)
        lineEquation(xInit,yInit,xFin,yFin);
    if(origLineEnabled ==true)
        origLine(xInit,yInit,xFin,yFin);
    glFlush();
}

void MyGlWidget::resizeGL(int wid, int heig)
{
    glMatrixMode(GL_MODELVIEW );
    squareViewport(wid,heig);
}

void MyGlWidget::drawPoint(int x , int y)
{
    glBegin(GL_QUADS);
    glVertex3f(x,y,0);
    glVertex3f(x,y+1,0);
    glVertex3f(x+1,y+1,0);
    glVertex3f(x+1,y,0);
    glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * 3.141592;

    glBegin(GL_LINE_LOOP);
    for(i = 0; i <= lineAmount;i++) {
        glVertex2f(
                    x + (radius * cos(i *  twicePi / lineAmount)),
                    y + (radius* sin(i * twicePi / lineAmount))
                    );
    }
    glEnd();
}

void MyGlWidget::setpixel(int x, int y)
{
    drawHollowCircle(x,y,0.3);
    drawPoint(x,y);
}

void MyGlWidget::drawGrid()
{
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    for(int i = 0 ; i <= matrixSize; i++)
    {
        glVertex3f(0,i,0);
        glVertex3f(matrixSize,i,0);
        glVertex3f(i,0,0);
        glVertex3f(i,matrixSize,0);
    }
    glEnd();
}

void MyGlWidget::squareViewport(int wid, int heig)
{
    int size,lefttBoder,downBorder;
    if(heig < wid)
    {
        size = heig;
        lefttBoder = (wid-heig)/2;
        downBorder = 0;
    }
    else
    {
        size = wid;
        downBorder = (heig - wid)/2;
        lefttBoder = 0;
    }
    glViewport(lefttBoder,downBorder,size,size);
}

void MyGlWidget::changeMatrizSize(int size)
{
    matrixSize = size;
    update();
}

void MyGlWidget::updateXInit(int value)
{
    xInit = value;
    update();
}
void MyGlWidget::updateYInit(int value)
{
    yInit = value;
    update();
}
void MyGlWidget::updateXFin(int value)
{
    xFin = value;
    update();
}
void MyGlWidget::updateYFin(int value)
{
    yFin = value;
    update();
}
void MyGlWidget::enableDDA(bool value)
{
    ddaEnabled = value;
    update();
}
void MyGlWidget::enableMidlePoint(bool value)
{
    midlePointEnabled = value;
    update();
}
void MyGlWidget::enableLineEq(bool value)
{
    lineEqEnabled = value;
    update();
}
void MyGlWidget::enableMesh(bool value)
{
    meshEnabled = value;
    update();
}
void MyGlWidget::enableOrigLine(bool value)
{
    origLineEnabled = value;
    update();
}

void MyGlWidget::origLine(int x1,int y1,int x2, int y2)
{
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);
    glEnd();

}

int Round(float x)
{
    return x + 0.5;
}

void MyGlWidget::DDA(int X1,int Y1,int X2, int Y2)
{
    glColor3f(0,0,1);
    int Length;
    int * end;
    float X,Y,Xinc,Yinc;
    float * actualPlace;

    Length = abs(X2 - X1);
    actualPlace= &X;
    end = &X2;
    if (abs(Y2 -Y1) > Length)
    {
        actualPlace= &Y;
        end = &Y2;
        Length = abs(Y2-Y1);
    }
    if(Length == 0)
        return;
    Xinc = (X2 - X1)/(float)Length;
    Yinc = (Y2 -Y1)/(float)Length;
    X = X1;
    Y = Y1;

    while((*actualPlace)<=(*end))
    {
        setpixel(Round(X),Round(Y));
        X = X + Xinc;
        Y = Y + Yinc;
    }
}

void MyGlWidget::middlePoint(int x1,int y1,int x2, int y2)
{
    glColor3f(0,0,0);
    int dx,dy,incE,incNE,d,x,y;
    float coefInc;
    dx = x2-x1;
    dy = y2-y1;
    x = x1;
    y = y1;
    coefInc = dy/(float)dx;
    setpixel(x,y);
    if(coefInc <= 1)
    {
        incE = 2*dy;
        incNE = 2*(dy-dx);
        d = 2*dy-dx;
        while(x < x2)
        {
            if(d <= 0)
            {
                d = d+incE;
                x= x+1;
            }
            else
            {
                d=d+incNE;
                x = x+1;
                y = y+1;
            }
            setpixel(x,y);
        }
    }
    else
    {
        incE = 2*dx;
        incNE = 2*(dx-dy);
        d = 2*dx-dy;
        while(y < y2)
        {
            if(d <= 0)
            {
                d = d+incE;
                y= y+1;
            }
            else
            {
                d=d+incNE;
                x = x+1;
                y = y+1;
            }
            setpixel(x,y);
        }
    }

}

void MyGlWidget::lineEquation(int x1,int y1,int x2, int y2)
{
    glColor3f(0,1,0);
    int dx,dy;
    float inc,x,y,b;
    x = x1;
    y = y1;
    dx = x2-x1;
    dy = y2-y1;
    if(dx == 0)
    {
        while(y <=y2)
        {
            setpixel(Round(x),Round(y));
            y++;
        }
    }
    else if(dy == 0)
    {
        while(x <=x2)
        {
            setpixel(Round(x),Round(y));
            x++;
        }
    }
    else
    {
        inc = dy/(float)dx;
        b = y1 - (inc*x1);
        if(inc <= 1)
        {
            while(x <x2)
            {
                y = (inc*x) + b;
                setpixel(Round(x),Round(y));
                x++;
            }
        }
        else
        {
            while(y <y2)
            {
                x = (y-b)/ inc;
                setpixel(Round(x),Round(y));
                y++;
            }
        }
    }
}


