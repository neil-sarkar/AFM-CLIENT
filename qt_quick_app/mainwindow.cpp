#include "mainwindow.h"
#include "afm.h"
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QWebSettings>

MainWindow::MainWindow(AFM* afm, SerialPort* serial_port)
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
    m_serial_port = serial_port;
    // Signal is emitted before frame loads any web content:
    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));

    QUrl startURL = QUrl("qrc:/html/main.html");
    m_welcome_page.mainFrame()->load(startURL);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageDatabaseEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
}

void MainWindow::addJSObject() {
    page()->mainFrame()->addToJavaScriptWindowObject(QString("afm"), m_afm);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("main_window"), this);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("sweeper"), m_afm->sweeper);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("approacher"), m_afm->approacher);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("scanner"), m_afm->scanner);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("motor"), m_afm->motor);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("pid"), m_afm->scanner->pid);
    page()->mainFrame()->addToJavaScriptWindowObject(QString("serial_port"), m_serial_port);
    QHash<int, AFMObject*>::iterator i;
    for (i = m_afm->PGA_collection.begin(); i != m_afm->PGA_collection.end(); ++i) {
        QString name = "pga_" + QString::number(i.key());
        page()->mainFrame()->addToJavaScriptWindowObject(name, i.value());
    }
    for (i = m_afm->DAC_collection.begin(); i != m_afm->DAC_collection.end(); ++i) {
        QString name = "dac_" + QString::number(i.key());
        page()->mainFrame()->addToJavaScriptWindowObject(name, i.value());
    }
    for (i = m_afm->ADC_collection.begin(); i != m_afm->ADC_collection.end(); ++i) {
        QString name = "adc_" + QString::number(i.key());
        page()->mainFrame()->addToJavaScriptWindowObject(name, i.value());
    }
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
