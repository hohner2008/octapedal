#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include "customdial.h"
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include "ui/controls/RotaryKnob.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudioBufferOutput>
#include <QAudioBuffer>
#include <QVarLengthArray>
#include "audio.h"

#include <QThreadPool>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    QAudioDecoder decoder;
     this->decoder = &decoder;

       QAudioFormat format;
     format.setSampleRate(44100);
    format.setChannelCount(2);
     format.setSampleFormat(QAudioFormat::Int16);
     this->decoder->setAudioFormat(format);

    this->decoder->setSource(QUrl::fromLocalFile("/home/lusa/Toots Thielemans - Footprints/1.wav"));
     this->decoder->start();

    MainWindow::connect(this->decoder, &QAudioDecoder::bufferReady, this, &MainWindow::onAudioBufferReady);
    MainWindow::connect(this->decoder, &QAudioDecoder::positionChanged, this, &MainWindow::onPositionChanged);

    if(this->decoder->isDecoding()){
         qDebug() << "Decoding startes!";
        qDebug() << this->decoder->isSupported();
         qDebug() << "error:" << this->decoder->errorString();
        qDebug() << this->decoder->duration();
         qDebug() <<"buffer not ->" << this->decoder->bufferAvailable();
    }

    this->m_player = new QMediaPlayer();
    this->m_ao = new QAudioOutput();
    this->m_abo = new QAudioBufferOutput();

    connect(this->m_abo, &QAudioBufferOutput::audioBufferReceived, this, &MainWindow::onAudioBufferReceived);
    this->m_player->setAudioOutput(m_ao);
    this->m_player->setAudioBufferOutput(this->m_abo);

    connect(this->m_player, &QMediaPlayer::positionChanged, this, &MainWindow::onPositionChanged);
    connect(this->m_player, &QMediaPlayer::bufferProgressChanged, this, &MainWindow::onBufferProgressChanged);
    this->m_player->setSource(QUrl::fromLocalFile("/home/lusa/Toots Thielemans - Footprints/1.wav"));
    this->m_player->play();

     auto layout = this->ui->centralwidget->findChild<QGridLayout *>("knobsGrid");
    qDebug() << "layout: " << &layout;

    auto valueKnob = new Octapedal::RotaryKnob(this);
     layout->addWidget(valueKnob,0,0,Qt::AlignCenter);
     auto toneKnob = new Octapedal::RotaryKnob(this);
    layout->addWidget(toneKnob,0,1,Qt::AlignCenter);

    auto valueLabel = new QLabel(this);
    valueLabel->setText("Value");
    layout->addWidget(valueLabel,1,0,Qt::AlignCenter);

    auto toneLabel = new QLabel(this);
    toneLabel->setText("Tone");
    layout->addWidget(toneLabel,1,1,Qt::AlignCenter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAudioBufferReady(){
    qDebug() << "Buffer ready";
    auto buffer = this->decoder->read();
}

void MainWindow::onPositionChanged(qint64 position){
    qDebug() << position;

}

void MainWindow::onBufferProgressChanged(float filled){
    if(filled == 1){


    }
}

void MainWindow::onAudioBufferReceived(const QAudioBuffer &buffer){

    QThreadPool pool;
    auto max = pool.maxThreadCount();

    auto audio = new Audio(buffer,this);
    auto valid = buffer.isValid();
    qDebug() << valid;
    auto format = buffer.format();
    auto count = buffer.byteCount();
    auto data = buffer.constData<std::int16_t>();
    auto int16count = count/sizeof(std::int16_t);

    QVarLengthArray<std::int16_t> list;
    list.append(data, int16count);

    const auto *frames = buffer.constData<QAudioBuffer::S16S>();
    auto v = frames[0].channels[0] + frames[0].channels[1];


    auto frameCount = buffer.frameCount();
    auto samleFormat = format.sampleFormat();


}