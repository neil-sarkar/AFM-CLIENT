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

private:
    void addJSObject();
    QNetworkAccessManager * m_network;
    QNetworkDiskCache * m_cache;
};

#endif // MAINWINDOW_H
