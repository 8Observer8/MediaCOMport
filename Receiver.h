#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <stdexcept>
#include <string>
#include "PortError.h"

class Receiver : public QObject {
    Q_OBJECT
public:

    Receiver( const QString &portName = QString( "COM2" ),
              QSerialPort::BaudRate baudRate = QSerialPort::Baud9600,
              QSerialPort::DataBits dataBits = QSerialPort::Data8,
              QSerialPort::Parity parity = QSerialPort::NoParity,
              QSerialPort::StopBits stopBits = QSerialPort::OneStop,
              QSerialPort::FlowControl flowControl = QSerialPort::NoFlowControl );

    void run( ) throw( PortError );

signals:
    void signalReceivedData( QByteArray data );

private slots:
    void slotReadyRead( );

private:
    QSerialPort m_serialPort;
    QSerialPort::BaudRate m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::Parity m_parity;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::FlowControl m_flowControl;
};

#endif // RECEIVER_H
