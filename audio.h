#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioBuffer>
#include <QVarLengthArray>
#include <QVariant>

class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);
    explicit Audio(QAudioBuffer buffer,QObject *parent = nullptr);

signals:

private:
    QAudioFormat m_format;
    QVarLengthArray<QVariant> *m_sum_decode_audio = nullptr;
};

#endif // AUDIO_H
