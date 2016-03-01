#include "web_file_dialog.h"

WebFileDialog::WebFileDialog(QObject *parent) : QObject(parent) {}

void WebFileDialog::showOpenFileDialog() {
    QString path = QFileDialog::getExistingDirectory();
    if (path.isEmpty()) {
        return;
    } else {
        set_path(path);
    }
}

QString WebFileDialog::path() {
	return m_path;
}

void WebFileDialog::set_path(QString path) {
	m_path = path;
	qDebug() << "Setting path to " << m_path;
	emit path_changed(m_path);
}
