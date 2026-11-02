#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaPlayer>
#include <QAudioDecoder>
#include <QUrl>
#include <QAudioFormat>

#include <stdio.h>
#include <sndfile.h>
#include <QDebug>
#include <QMediaMetaData>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "octapedal_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    SF_INFO info;
    auto sf = sf_open("/home/lusa/Toots Thielemans - Footprints/1.wav",
            SFM_READ,&info);

    int format_snd = sf_format_check (&info) ;

    auto rate = info.samplerate;

    qDebug() << &sf;

    MainWindow w;


    w.show();
    w.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    return QApplication::exec();
}
