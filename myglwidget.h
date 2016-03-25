#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include<QGLWidget>
#include<QtOpenGL>
#include<GL/glu.h>
#include<math.h>

class MyGlWidget : public QGLWidget
{

    Q_OBJECT

public:
    explicit MyGlWidget(QWidget *parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

signals:

public slots:
    void changeMatrizSize(int size);
    void updateXInit(int value);
    void updateYInit(int value);
    void updateXFin(int value);
    void updateYFin(int value);
    void enableDDA(bool value);
    void enableMidlePoint(bool value);
    void enableLineEq(bool value);
    void enableMesh(bool value);
    void enableOrigLine(bool value);

private:
    bool ddaEnabled;
    bool midlePointEnabled;
    bool lineEqEnabled;
    bool meshEnabled;
    bool origLineEnabled;
    int xInit;
    int yInit;
    int xFin;
    int yFin;
    int matrixSize;
    void origLine(int x1,int y1,int x2, int y2);
    void middlePoint(int x1,int y1,int x2, int y2);
    void lineEquation(int x1,int y1,int x2, int y2);
    void drawPoint(int x , int y);
    void drawGrid();
    void squareViewport(int wid, int heig);
    void setpixel(int x, int y);
    void DDA(int xi,int yi,int xf, int yf);

};

#endif // MYGLWIDGET_H
