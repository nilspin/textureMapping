#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QGLViewer/qglviewer.h>
#include <GL/glu.h>

using namespace qglviewer;

static GLuint textureID ;
static GLubyte *image_map_out ;

class viewerWidget : public QGLViewer
{
    Q_OBJECT;
public:
    viewerWidget();
    virtual void draw();
    virtual void init();
    //GLuint textureID;
};

#endif // VIEWERWIDGET_H
