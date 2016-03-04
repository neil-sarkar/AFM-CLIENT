#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "afm.h"
#include "serial_port.h"
#include "web_file_dialog.h"
#include <QWebView>
#include <QWebElementCollection>
#include <QNetworkDiskCache>


class CustomPage: public QWebPage
{
    Q_OBJECT
public:
    CustomPage();
    void javaScriptAlert(QWebFrame * frame, const QString & msg); // doesn't work
public slots:
        void downloadRequestedHandler(const QNetworkRequest & request);
        void handle(QNetworkReply* msg);
};

class MainWindow : public QWebView
{
Q_OBJECT
public:
    explicit MainWindow(AFM*, SerialPort*, WebFileDialog*);
    MainWindow(CustomPage*);
    Q_INVOKABLE void log_cpp(QString text); // takes in things from JS to log
    Q_INVOKABLE void load_main_app_page();
    Q_INVOKABLE void load_home_page();
    Q_INVOKABLE QWebView* createWindow(CustomPage*);
    Q_INVOKABLE void pop_out_force_curve_page();
    AFM* m_afm;
    SerialPort* m_serial_port;

private slots:
    void addJSObject(CustomPage* page);

private:
    void set_global_web_settings();
    QNetworkAccessManager * m_network;
    QNetworkDiskCache * m_cache;
    CustomPage m_welcome_page;
    CustomPage m_main_app_page;
    CustomPage m_force_curve_page;
    WebFileDialog* m_folder_picker;
};
#endif // MAINWINDOW_H
