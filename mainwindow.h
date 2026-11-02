#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDial"
#include <QAudioDecoder>
#include <QMediaPlayer>
#include <QAudioBufferOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void onAudioBufferReady();
    void onPositionChanged(qint64 position);
    void onBufferProgressChanged(float filled);
    void onAudioBufferReceived(const QAudioBuffer &buffer);

signals:
    void audioDataReady(QAudioFormat format);

private:
    Ui::MainWindow *ui;

    QDial *level;
    QAudioDecoder *decoder = nullptr;
    QMediaPlayer *m_player = nullptr;
    QAudioOutput *m_ao = nullptr;
    QAudioBufferOutput *m_abo = nullptr;
};
#endif // MAINWINDOW_H
