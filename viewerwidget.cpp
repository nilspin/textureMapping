#include "viewerwidget.h"
#include <QImage>
#include <QGLWidget>

viewerWidget::viewerWidget()
{
}

void viewerWidget::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //glActiveTexture(GL_TEXTURE0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glEnable(GL_BLEND) ;
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
    glEnable(GL_TEXTURE_2D);

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
    glPopMatrix() ;
    glFlush() ;
    glDisable(GL_TEXTURE_2D) ;
    glDisable(GL_BLEND) ;
}

void viewerWidget::init()
{
    restoreStateFromFile();
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);

    glClearColor(0.3,0.3,0.3,1.0);
    QImage img("etopo60-texture.bmp");
    QImage glImg = QGLWidget::convertToGLFormat(img);
    image_map_out = glImg.bits() ;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, glImg.width(), glImg.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image_map_out);
    //glBindTexture(GL_TEXTURE_2D, 0);
}
