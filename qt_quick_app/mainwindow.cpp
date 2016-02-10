#include "mainwindow.h"
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkDiskCache>
#include <QStandardPaths>

MainWindow::MainWindow()
{
    //If you want to provide support for web sites that allow the user to open new windows, such as pop-up windows, you can subclass QWebView and reimplement the createWindow() function.

    m_network = new QNetworkAccessManager(this);
    m_cache = new QNetworkDiskCache(this);
    m_cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/imageanalyzer");
    m_cache->setMaximumCacheSize(1000000); //set the cache to 10megs
    m_network->setCache(m_cache);
    page()->setNetworkAccessManager(m_network);

//    m_analyzer = new ImageAnalyzer(m_cache, this);

    // Signal is emitted before frame loads any web content:
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
                     this, SLOT(addJSObject()));

    // qrc:// URLs refer to resources. See imagenalayzer.qrc

    QUrl startURL = QUrl("qrc:/test.html");
    m_welcome_page.mainFrame()->load(startURL);
    setPage(&m_welcome_page);
    // Load web content now!
//    setUrl(startURL);
}

void MainWindow::addJSObject() {
//    page()->mainFrame()->addToJavaScriptWindowObject(QString("imageAnalyzer"), m_analyzer);
}
