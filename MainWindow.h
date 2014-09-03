#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <windows.h>
#include "Receiver.h"

#define Key_Media_Play_Pause 0xB3
#define Key_Media_Stop       0xB2
#define Key_Media_Back       0xB1
#define Key_Media_Next       0xB0
#define Key_Media_Mute       0xAD
#define Key_Media_Sound      0xFA
#define Key_Media_VolumeUp   0xAF
#define Key_Media_VolumeDown 0xAE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startPauseButton_clicked();
    void on_stopButton_clicked();
    void on_soundButton_clicked();
    void on_backButton_clicked();
    void on_nextButton_clicked();
    void on_volumeUpButton_clicked();
    void on_volumeDownButton_clicked();
    void on_toTrayButton_clicked();
    void on_actionSettings_triggered();

    void slotReceiveData( const QByteArray &data );
    void slotSetSettings( const QString &portName,
                          const QString &portSpeed );

private:
    void emitClickedKey( int key );
    void runReceiver();
    void createActions();
    void createTrayIcon();

private:
    Ui::MainWindow *ui;
    Receiver *m_receiver;
    QSystemTrayIcon *m_trayIcon;
    QAction *m_minimizeAction;
    QAction *m_maximizeAction;
    QAction *m_restoreAction;
    QAction *m_quitAction;
    QMenu *m_trayIconMenu;

    QAction *m_playPauseAction;
    QAction *m_stopAction;
    QAction *m_muteAction;
    QAction *m_backAction;
    QAction *m_nextAction;
};

#endif // MAINWINDOW_H
