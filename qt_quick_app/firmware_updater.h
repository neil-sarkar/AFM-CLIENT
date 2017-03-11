#ifndef FIRMWARE_UPDATER_H
#define FIRMWARE_UPDATER_H

#include <QSerialPort>

class FirmwareUpdater: public QObject
{
Q_OBJECT
	public:
        explicit FirmwareUpdater(QObject *parent = 0);
        ~FirmwareUpdater();
		void open();
		Q_INVOKABLE void close();
	signals:
        void to_console(QString);

	public slots:
		void update_firmware();

	private:
		QString get_serial_port_name();
		void serial_write(const QString &str);	
		QByteArray serial_read(int minBytes = 0, int timeout = 10);
		QString m_portname;
		int m_baudrate;
		QSerialPort m_serial;
};

#endif // FIRMWARE_UPDATER_H

