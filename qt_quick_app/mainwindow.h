#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "afm.h"
#include "web_file_dialog.h"
#include <QWebEngineView>
//#include <QWebElementCollection>
#include <QNetworkDiskCache>


class CustomPage: public QWebEnginePage
{
    Q_OBJECT
public:
    CustomPage();
    void javaScriptAlert(const QString & msg); // doesn't work
public slots:
        void downloadRequestedHandler(const QNetworkRequest & request);
        void handle(QNetworkReply* msg);
};

class MainWindow : public QWebEngineView
{
Q_OBJECT
public:
    explicit MainWindow(AFM*, WebFileDialog*);
    MainWindow(CustomPage*);
    Q_INVOKABLE void log_cpp(QString text); // takes in things from JS to log
    Q_INVOKABLE void load_main_app_page();
    Q_INVOKABLE void load_home_page();
    Q_INVOKABLE QWebEngineView* createWindow(CustomPage*);
    Q_INVOKABLE void pop_out_force_curve_page();
    AFM* m_afm;

private slots:
    void addJSObject(CustomPage* page);

private:
    void set_global_web_settings();
    QNetworkDiskCache * m_cache;
    CustomPage m_welcome_page;
    CustomPage m_main_app_page;
    CustomPage m_force_curve_page;
    WebFileDialog* m_folder_picker;
    QTimer* timer;
};
#endif // MAINWINDOW_H
