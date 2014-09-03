#include "Receiver.h"

Receiver::Receiver( const QString &portName,
                    QSerialPort::BaudRate baudRate,
                    QSerialPort::DataBits dataBits,
                    QSerialPort::Parity parity,
                    QSerialPort::StopBits stopBits,
                    QSerialPort::FlowControl flowControl ) :
    m_serialPort( portName ),
    m_baudRate( baudRate ),
    m_dataBits( dataBits ),
    m_parity( parity ),
    m_stopBits( stopBits ),
    m_flowControl( flowControl )
{
}

void Receiver::run( ) throw( PortError )
{
    if ( !m_serialPort.open( QIODevice::ReadOnly ) ) {
        throw PortError( "Error: unable to open the port \"" +
                         m_serialPort.portName().toStdString() + "\"" );
    }

    m_serialPort.setBaudRate( m_baudRate );
    m_serialPort.setDataBits( m_dataBits );
    m_serialPort.setParity( m_parity );
    m_serialPort.setStopBits( m_stopBits );
    m_serialPort.setFlowControl( m_flowControl );

    connect( &m_serialPort, SIGNAL( readyRead( ) ),
             this, SLOT( slotReadyRead( ) ) );
}

void Receiver::slotReadyRead( )
{
    QByteArray data;
    data = m_serialPort.readAll( );
    emit signalReceivedData( data );
}
