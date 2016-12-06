#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QGLViewer/qglviewer.h>

using namespace qglviewer;

class viewerWidget : public QGLViewer
{
    Q_OBJECT;
public:
    viewerWidget();
    virtual void draw();
    virtual void init();
    GLuint textureID;
};

#endif // VIEWERWIDGET_H
