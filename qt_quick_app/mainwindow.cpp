#include "mainwindow.h"
#include "afm.h"
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkDiskCache>
#include <QStandardPaths>

MainWindow::MainWindow(AFM* afm)
{
    //If you want to provide support for web sites that allow the user to open new windows, such as pop-up windows, you can subclass QWebView and reimplement the createWindow() function.

    m_network = new QNetworkAccessManager(this);
    m_cache = new QNetworkDiskCache(this);
    m_cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/imageanalyzer");
    m_cache->setMaximumCacheSize(1000000); //set the cache to 10megs
    m_network->setCache(m_cache);
    setPage(&m_welcome_page);
    page()->setNetworkAccessManager(m_network);


    m_afm = afm;

    // Signal is emitted before frame loads any web content:
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));

    // qrc:// URLs refer to resources. See imagenalayzer.qrc

    QUrl startURL = QUrl("qrc:/test.html");
    m_welcome_page.mainFrame()->load(startURL);
    QUrl sweepURL = QUrl("qrc:/sweep.html");
    m_sweep_page.mainFrame()->load(sweepURL);

//    setPage(&m_sweep_page);

//    setUrl(startURL);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

void MainWindow::addJSObject() {
    qDebug() << "called here";
    page()->mainFrame()->addToJavaScriptWindowObject(QString("afm"), m_afm);
    page()->mainFrame()->evaluateJavaScript("console.log('testing test');");
}
