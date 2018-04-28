#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QThread>
#include <QImage>

class VideoPlayer : public QThread
{
    Q_OBJECT

public:
    VideoPlayer();

    ~VideoPlayer();

    void run();

signals:
    void sig_GetYUV(uchar * y_data,uchar *u_data, uchar *v_data,int width,int height);

};

#endif // VIDEOPLAYER_H
