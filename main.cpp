#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "ui_audioplayer.h"
int main() {
    int argc = 0;                    // Define a dummy argc
    char *argv[] = { nullptr };
    QApplication app(argc,argv);// Define a dummy argv

    QWidget window;
    Ui::AudioPlayer ui;
    ui.setupUi(&window);
    QMediaPlayer *player = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);

    QObject::connect(ui.playButton, &QPushButton::clicked, player, &QMediaPlayer::play);
    QObject::connect(ui.pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    QObject::connect(ui.stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);

    QObject::connect(ui.volumeSlider, &QSlider::valueChanged, [=](int value){
         audioOutput->setVolume(value / 100.0);  // Volume is a float between 0.0 and 1.0
     });
    window.show();
    return app.exec();

}