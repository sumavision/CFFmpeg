#include "videoplayer.h"
#include <iostream>

using namespace std;

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/pixfmt.h"
#include "libavutil/imgutils.h"
}

VideoPlayer::VideoPlayer()
{

}
VideoPlayer::~VideoPlayer()
{
    this->terminate();
}

void VideoPlayer::run()
{
    //编解码器初始化
    av_register_all();
    avformat_network_init();

    //打开视频文件
    string filePath = "F:/workdir_other/ffmpeg/test.avi";
    const char *url = filePath.c_str();

    //new AVFormatContext
    AVFormatContext *pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&pFormatCtx,url,NULL,NULL) != 0)
    {
        cout<<"avformat_open_input,open the file fail";
        return;
    }
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
            cout<<"Could't find stream infomation.";
            return;
    }

    //查找视频中包含的流信息
    int videoStreams = -1;
    for(unsigned int i = 0;i < pFormatCtx->nb_streams;i++)
    {
        if(pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStreams = i;
        }
    }
    if(videoStreams == -1)
    {
        cout<<"can not find the video streams";
        return;
    }

    //解码器
    AVCodecContext *pCodecCtx = avcodec_alloc_context3(NULL);
    if(avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStreams]->codecpar) < 0)
    {
        cout<<"avcodec_parameters_to_context fail";
        return;
    }
    AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec == NULL)
    {
        cout<<"can not find the codec";
        return;
    }

    if(avcodec_open2(pCodecCtx,pCodec,NULL)<0)
    {
        cout<<"can not open the codec";
        return;
    }

    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameYUV = av_frame_alloc();

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx->width,pCodecCtx->height,1);

    uint8_t * out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(pFrameYUV->data,pFrameYUV->linesize ,out_buffer, AV_PIX_FMT_YUV420P,pCodecCtx->width, pCodecCtx->height,1);

    //读取视频
    int videoSize = pCodecCtx->width*pCodecCtx->height;
    //分配一个packet
    AVPacket *pPacket = (AVPacket *)malloc(sizeof(AVPacket));
    //分配packet的数据
    av_new_packet(pPacket,videoSize);
    //输出视频信息
    //Output Info-----------------------------
    cout<<"--------------- File Information ----------------\n";
    av_dump_format(pFormatCtx, 0, url, 0);
    cout<<"-------------------------------------------------\n";

    struct SwsContext *img_convert_ctx;
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                                     AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

    FILE *fp_yuv=fopen("output.yuv","wb+");

    int ret;
    char errorBuf[256];
    while(av_read_frame(pFormatCtx,pPacket)>=0)
    {
        if(pPacket->stream_index == videoStreams)
        {
            ret = avcodec_send_packet(pCodecCtx,pPacket);
            if(ret != 0)
            {
                av_strerror(ret,errorBuf,sizeof(errorBuf));
            }
            ret = avcodec_receive_frame(pCodecCtx,pFrame);
            if(ret != 0)
            {
                av_strerror(ret,errorBuf,sizeof(errorBuf));
            }
            sws_scale(img_convert_ctx,(const unsigned char * const *) pFrame->data,pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);

            emit sig_GetYUV(pFrameYUV->data[0],pFrameYUV->data[1],pFrameYUV->data[2],pCodecCtx->width, pCodecCtx->height);
            msleep(40);
        }
        av_packet_unref(pPacket);
    }
    sws_freeContext(img_convert_ctx);
    fclose(fp_yuv);

    av_free(out_buffer);
    av_free(pFrameYUV);
    av_free(pFrame);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
}
