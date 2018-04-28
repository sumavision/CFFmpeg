#ifndef CFFMPEG_H
#define CFFMPEG_H

#include <QObject>
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/pixfmt.h"
#include "libavutil/imgutils.h"
}

/** FFmpeg基础类*/
class CFFmpeg : public QObject
{
    Q_OBJECT
public:
    explicit CFFmpeg(QString url);
    ~CFFmpeg();

    /** 初始化FFmpeg*/
    static void init();
private:
    /** 获取流文件信息*/
    void fmpgAVformatCreate();
signals:

public slots:

private:
    /** 文件路径*/
    QString m_filePath;
};

#endif // CFFMPEG_H
