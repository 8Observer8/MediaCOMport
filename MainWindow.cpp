
#include <QDebug>
#include <QMessageBox>
#include <SettingsDialog.h>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize( this->size() );

    this->setWindowIcon( QIcon( ":/IconWindow" ) );

    ui->startPauseButton->setIcon( QIcon( ":/IconPlayPause" ) );
    ui->stopButton->setIcon( QIcon( ":/IconStop" ) );
    ui->backButton->setIcon( QIcon( ":/IconBack" ) );
    ui->nextButton->setIcon( QIcon( ":/IconNext" ) );
    ui->soundButton->setIcon( QIcon( ":/IconSound" ) );
    ui->volumeDownButton->setIcon( QIcon( ":/IconVolumeDown" ) );
    ui->volumeUpButton->setIcon( QIcon( ":/IconVolumeUp" ) );
    ui->toTrayButton->setIcon( QIcon( ":/IconToTray" ) );

    m_receiver = new Receiver;
    runReceiver();

    createActions();
    createTrayIcon();
}

MainWindow::~MainWindow()
{
    delete m_receiver;
    delete ui;
}

void MainWindow::on_startPauseButton_clicked()
{
    emitClickedKey( Key_Media_Play_Pause );
}

void MainWindow::on_stopButton_clicked()
{
    emitClickedKey( Key_Media_Stop );
}

void MainWindow::on_backButton_clicked()
{
    emitClickedKey( Key_Media_Back );
}

void MainWindow::on_nextButton_clicked()
{
    emitClickedKey( Key_Media_Next );
}

void MainWindow::on_soundButton_clicked()
{
    emitClickedKey( Key_Media_Mute );
}

void MainWindow::on_volumeDownButton_clicked()
{
    emitClickedKey( Key_Media_VolumeDown );
}

void MainWindow::on_volumeUpButton_clicked()
{
    emitClickedKey( Key_Media_VolumeUp );
}

void MainWindow::on_toTrayButton_clicked()
{
    this->hide();
}

void MainWindow::emitClickedKey(int key)
{
    // Моделируем нажатие клавиши
    keybd_event( key, 0, 0, 0 );

    // Моделируем возврат клавиши в не нажатое состояние
    keybd_event( key, 0, KEYEVENTF_KEYUP, 0 );
}

void MainWindow::runReceiver()
{
    try {
        m_receiver->run();
        connect( m_receiver, SIGNAL( signalReceivedData( QByteArray ) ),
                 this, SLOT( slotReceiveData( QByteArray ) ) );
    } catch ( const PortError &e ) {
        QString message( e.what() );
        QMessageBox::information( this, tr( "Error" ), message );
        return;
    } catch( ... ) {
        QString message( "Error: unknown exception" );
        QMessageBox::information( this, tr( "Error" ), message );
        return;
    }
}

void MainWindow::createActions()
{
    m_playPauseAction = new QAction( tr( "Play\\Pause" ), this );
    connect( m_playPauseAction, SIGNAL( triggered() ),
             this, SLOT( on_startPauseButton_clicked() ) );

    m_stopAction = new QAction( tr( "Stop" ), this );
    connect( m_stopAction, SIGNAL( triggered() ),
             this, SLOT( on_stopButton_clicked() ) );

    m_muteAction = new QAction( tr( "Mute" ), this );
    connect( m_muteAction, SIGNAL( triggered() ),
             this, SLOT( on_soundButton_clicked() ) );

    m_backAction = new QAction( tr( "Back" ), this );
    connect( m_backAction, SIGNAL( triggered() ),
             this, SLOT( on_backButton_clicked() ) );

    m_nextAction = new QAction( tr( "Next" ), this );
    connect( m_nextAction, SIGNAL( triggered() ),
             this, SLOT( on_nextButton_clicked() ) );

    m_minimizeAction = new QAction( tr( "Mi&nimize" ), this );
    connect( m_minimizeAction, SIGNAL( triggered() ),
             this, SLOT( hide() ) );

    m_maximizeAction = new QAction( tr( "Ma&ximize" ), this );
    connect( m_maximizeAction, SIGNAL( triggered() ),
             this, SLOT( showMaximized() ) );
}

void MainWindow::createTrayIcon()
{
    m_trayIconMenu = new QMenu( this );
    m_trayIconMenu->addAction( m_playPauseAction );
    m_trayIconMenu->addAction( m_stopAction );
    m_trayIconMenu->addAction( m_muteAction );
    m_trayIconMenu->addAction( m_backAction );
    m_trayIconMenu->addAction( m_nextAction );
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction( m_minimizeAction );
    m_trayIconMenu->addAction( m_maximizeAction );

    m_trayIcon = new QSystemTrayIcon( this );
    m_trayIcon->setIcon( QIcon( ":/IconWindow" ) );
    m_trayIcon->setToolTip( tr("Media COM port") );
    m_trayIcon->setContextMenu( m_trayIconMenu );
    m_trayIcon->show();
}

void MainWindow::slotReceiveData(const QByteArray &data)
{
    QString text( data );

    if ( text == QString( "DADA01" ) ) {
        on_startPauseButton_clicked();
    } else if ( text == QString( "DADA02" ) ) {
        on_stopButton_clicked();
    } else if ( text == QString( "DADA03" ) ) {
        on_backButton_clicked();
    } else if ( text == QString( "DADA04" ) ) {
        on_nextButton_clicked();
    } else if ( text == QString( "DADA05" ) ) {
        on_soundButton_clicked();
    } else if ( text == QString( "DADA06" ) ) {
        on_volumeUpButton_clicked();
    } else if ( text == QString( "DADA07" ) ) {
        on_volumeDownButton_clicked();
    } else {
        QString message( "Error: unknown command from the COM-port" );
        QMessageBox::information( this, tr( "Error" ), message );
    }
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog dialog;
    dialog.setModal( true );
    connect( &dialog, SIGNAL( signalSetSettings( QString,QString ) ),
             this, SLOT( slotSetSettings(QString,QString) ) );
    dialog.exec();
}

void MainWindow::slotSetSettings( const QString &portName,
                      const QString &portSpeed )
{
    delete m_receiver;

    QSerialPort::BaudRate convertedPortSpeed =
            static_cast<QSerialPort::BaudRate>( portSpeed.toInt() );

    m_receiver = new Receiver( portName, convertedPortSpeed );

    runReceiver();
}
