#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "videoplayer.h"
#include "cqopengldisplay.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    VideoPlayer *m_videoPlayer;

    QImage m_image;

    CQOpenGLDisplay *m_glDisplay;

};

#endif // MAINWINDOW_H
