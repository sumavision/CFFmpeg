#include "mainwindow.h"
#include <QPainter>
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_videoPlayer = new VideoPlayer();
    m_videoPlayer->start();

    m_glDisplay = new CQOpenGLDisplay(this);
    setCentralWidget(m_glDisplay);
    m_glDisplay->show();
    connect(m_videoPlayer,&VideoPlayer::sig_GetYUV,m_glDisplay,&CQOpenGLDisplay::openGLVideoPlayer);
}

MainWindow::~MainWindow()
{
    delete m_glDisplay;

    delete m_videoPlayer;
}
