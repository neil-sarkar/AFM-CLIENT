#ifndef FIRMWARE_UPDATER_H
#define FIRMWARE_UPDATER_H
#include <QObject>
#include <QSerialPort>

class FirmwareUpdater: public QObject
{
Q_OBJECT
	public:
        explicit FirmwareUpdater(QObject *parent = 0);
        ~FirmwareUpdater();
		Q_INVOKABLE void close();

	signals:
        void to_console(QString);
        void start_timer();
        void stop_timer();
        void close_conn();
        void push_to_AFM(QString);

	public slots:
		void update_firmware(QString);	

	private:
		QString get_serial_port_name();
		bool check_device_ID(const quint32 &address);
		void stop_current_serial();
		void serial_write(const QString &str);	
		void serial_write(const QByteArray &data);
		bool write_applet (const quint32 &address, QByteArray *data);
		bool serial_write_word(const quint32 &address, quint32 data);
		QByteArray serial_read(int minBytes = 0, int timeout = 10);
		quint32 serial_read_word(quint32 address, int timeout = 10);
        bool load_file (const QString &file_path);
        bool run_applet(int cmd, int* args, int length);
        bool go(const quint32 &address);
        void check_mail();
        bool write_to_flash();
        bool open();

		QByteArray m_bin_buf;
		QString m_portname;
		QString m_mcu_bin;
		int m_baudrate;
		QSerialPort *m_serial;
		quint32 m_buff_addr;
		quint32 m_buff_size;
		quint32 m_mem_size;

		static const quint32 APPLET_CODE_ADDR;
		static const quint32 APPLET_MAIL_ADDR;
		static const int MAX_BUF_SIZE;
		static const quint32 PAGE_SIZE;
		static const quint32 CIRD_REG_ADDR;
		static const QString LOWLEVEL_PATH;
		static const QString FLASH_PATH;
		static const QString MEMS_PATH;
};

#endif // FIRMWARE_UPDATER_H

