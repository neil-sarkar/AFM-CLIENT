#include "mainwindow.h"
#include "afm.h"
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QWebSettings>

MainWindow::MainWindow(AFM* afm)
{
    //If you want to provide support for web sites that allow the user to open new windows, such as pop-up windows, you can subclass QWebView and reimplement the createWindow() function.

    m_network = new QNetworkAccessManager(this);
    m_cache = new QNetworkDiskCache(this);
    m_cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/imageanalyzer");
    m_cache->setMaximumCacheSize(1000000); //set the cache to 10megs
    m_network->setCache(m_cache);
    m_welcome_page.settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    m_welcome_page.settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    setPage(&m_welcome_page);
    page()->setNetworkAccessManager(m_network);
    m_afm = afm;
    // Signal is emitted before frame loads any web content:
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));

    // qrc:// URLs refer to resources. See imagenalayzer.qrc

    QUrl startURL = QUrl("qrc:/html/main.html");
    m_welcome_page.mainFrame()->load(startURL);
    QUrl sweepURL = QUrl("qrc:/html/sweep.html");
    m_sweep_page.mainFrame()->load(sweepURL);
//    setPage(&m_sweep_page);
//    setUrl(startURL);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
}

void MainWindow::addJSObject() {
    qDebug() << "called here";
    page()->mainFrame()->addToJavaScriptWindowObject(QString("afm"), m_afm);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("main_window"), this);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("sweeper"), m_afm->sweeper);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("approacher"), m_afm->approacher);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("scanner"), m_afm->scanner);
}

void MainWindow::log_cpp(QString text) {
    qDebug() << text;
}

void MainWindow::load_sweep_page() {
    setPage(&m_sweep_page);
}

void MainWindow::load_home_page() {
    setPage(&m_welcome_page);
}

QWebView* MainWindow::createWindow()
{
    QWebView *webView = new QWebView;
    QWebPage *newWeb = new QWebPage(webView);
    webView->setAttribute(Qt::WA_DeleteOnClose, true);
    webView->setPage(newWeb);
    webView->show();

    return webView;
}
