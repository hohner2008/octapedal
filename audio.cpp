#include "audio.h"

Audio::Audio(QObject *parent)
    : QObject{parent}
{}


Audio::Audio(QAudioBuffer buffer,QObject *parent)
    : QObject{parent}{

    QAudioFormat f = buffer.format();
    auto sf = f.sampleFormat();
    auto cc = f.channelCount();


    if (f != this->m_format){
        if (sf == QAudioFormat::Int16 ){
            if(cc == 2){
                qDebug() << "Channel count is " << cc;

                auto fc = buffer.byteCount()/(2*sizeof(qint16));
                const auto *frames = buffer.constData<QAudioBuffer::S16S>();
                auto audio_data = new QVarLengthArray<qint16>();

                auto count = 0;
                while(count < fc){
                    auto sum = frames[count].channels[0] + frames[count].channels[1];
                    audio_data->append(sum);
                }
                        }
        }
    }


}