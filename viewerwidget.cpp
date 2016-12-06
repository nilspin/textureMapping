#include "viewerwidget.h"
#include <QImage>
#include <QGLWidget>

viewerWidget::viewerWidget()
{
}

void viewerWidget::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //glColor3f(1.0,0,0);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0);
    glVertex3f(-0.5,-0.5,0);
    glTexCoord2d(0,1);
    glVertex3f(-0.5,0.5,0);
    glTexCoord2d(1,1);
    glVertex3f(0.5,0.5,0);
    glTexCoord2d(1,0);
    glVertex3f(0.5,-0.5,0);
    glEnd();
}

void viewerWidget::init()
{
    restoreStateFromFile();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.3,0.3,0.3,1.0);
    QImage img("etopo60-texture.bmp");
    QImage glImg = QGLWidget::convertToGLFormat(img);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glImg.width(), glImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, glImg.bits());
    glBindTexture(GL_TEXTURE_2D, 0);
}
