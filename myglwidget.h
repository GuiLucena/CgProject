#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include<QGLWidget>
#include<QtOpenGL>
#include<GL/glu.h>

class MyGlWidget : public QGLWidget
{
public:
    MyGlWidget(QWidget *parent = 0);
    ~MyGlWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
};

#endif // MYGLWIDGET_H
