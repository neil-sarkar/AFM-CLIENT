#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWebView>
#include <QWebElementCollection>
#include <QNetworkDiskCache>

class MainWindow : public QWebView
{
Q_OBJECT
public:
    explicit MainWindow();

private slots:
    void addJSObject();

private:
    QNetworkAccessManager * m_network;
    QNetworkDiskCache * m_cache;
    QWebPage m_welcome_page;
    QWebPage m_sweep_page;
};

#endif // MAINWINDOW_H
