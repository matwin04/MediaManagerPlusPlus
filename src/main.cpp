#include <QAudioOutput>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMessageBox>
#include "audioData.h"
#include "ui_audioplayer.h"
using namespace std;
audioData* audio = nullptr;
void loadFile(QWidget *parent, Ui::AudioPlayer &ui) {
    QString filepath = QFileDialog::getOpenFileName(parent, "Open File", QDir::homePath(),  "Audio Files (*.mp3 *.wav *.flac *.m4a)");
    if (!filepath.isEmpty()) {
        if (audio) {
            delete audio;
        }
        audio = new audioData(filepath.toStdString());
        ui.mediaInfoTitle->setText(QString::fromStdString(audio->getTitle()));
        ui.mediaInfoArtist->setText(QString::fromStdString(audio->getArtist()));
        ui.mediaInfoAlbum->setText(QString::fromStdString(audio->getAlbum()));
    } else {
        QMessageBox::warning(parent, "Error", "Failed to load the audio file");
    }
}
void playAudio(QWidget *parent) {
    if (audio) {
        audio->playAudio();
    } else {
        QMessageBox::warning(parent, "Error", "No audio file loaded to play");
    }
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    Ui::AudioPlayer ui;
    ui.setupUi(&window);

    QObject::connect(ui.loadButton, &QPushButton::clicked, [&]() {
        loadFile(&window, ui);
    });
    QObject::connect(ui.playButton, &QPushButton::clicked, [&]() {
        playAudio(&window);
    });
    window.show();
    return app.exec();
}