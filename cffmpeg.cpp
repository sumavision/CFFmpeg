#include "cffmpeg.h"

CFFmpeg::CFFmpeg(char *url):QObject()
{

}
void CFFmpeg::init()
{
    //编解码器初始化
    av_register_all();
    avformat_network_init();
}
