// http://martinjudd.com/select-local-files-in-a-qt-html5-application-using-qfiledialog-from-a-qwebview/


#ifndef WEBFILEDIALOG_H
#define WEBFILEDIALOG_H

#include <QObject>
#include <QFileDialog>
#include <QDebug>

class WebFileDialog : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE set_path NOTIFY path_changed)
public:
    explicit WebFileDialog(QObject *parent = 0);
    QString path();
    void set_path(QString);

signals:
    void path_changed(QString);

public slots:
    void showOpenFileDialog();

private:
    QString m_path;
};

#endif // WEBFILEDIALOG_H

