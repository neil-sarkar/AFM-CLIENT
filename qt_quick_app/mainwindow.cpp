#include "mainwindow.h"
#include "afm.h"
#include <QWebEnginePage>
//#include <QWebElementCollection>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QWebEngineSettings>
#include <QNetworkRequest>
#include "web_file_dialog.h"

MainWindow::MainWindow(AFM* afm, WebFileDialog* folder_picker)
{
    //If you want to provide support for web sites that allow the user to open new windows, such as pop-up windows, you can subclass QWebEngineView and reimplement the createWindow() function.

    // Core objects we will expose to JavaScript
    m_afm = afm;
    m_folder_picker = folder_picker;

    // commented out because we just call addJSObject manually now and pass in the appropriate page
    // QObject::connect(m_main_app_page, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject())); // Signal is emitted before frame loads any web content:

    addJSObject(&m_welcome_page);
    addJSObject(&m_main_app_page);
    addJSObject(&m_force_curve_page);
    m_welcome_page.(QUrl("qrc:/html/home.html"));
    m_main_app_page.(QUrl("qrc:/html/main.html"));
    setPage(&m_welcome_page);

    set_global_web_settings();
}

void MainWindow::set_global_web_settings() {
    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, true);

    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::DeveloperExtrasEnabled, true);
    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, true);
    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
//    QWebEngineSettings::clearMemoryCaches();
}

MainWindow::MainWindow(CustomPage* custom_page) {
    setPage(custom_page);
    set_global_web_settings();
    QObject::connect(page()->, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));
}

void MainWindow::addJSObject(CustomPage* page) {
    // For this method to work without crashing the program, all initialization must be done first.
    page->addToJavaScriptWindowObject(QString("afm"), m_afm);
    page->addToJavaScriptWindowObject(QString("main_window"), this);
    page->addToJavaScriptWindowObject(QString("sweeper"), m_afm->sweeper);
    page->addToJavaScriptWindowObject(QString("dds"), m_afm->sweeper->dds);
    page->addToJavaScriptWindowObject(QString("approacher"), m_afm->approacher);
    page->addToJavaScriptWindowObject(QString("scanner"), m_afm->scanner);
    page->addToJavaScriptWindowObject(QString("motor"), m_afm->motor);
    page->addToJavaScriptWindowObject(QString("pid"), m_afm->scanner->pid);
    page->addToJavaScriptWindowObject(QString("folder_picker"), m_folder_picker);
    page->addToJavaScriptWindowObject(QString("force_curve_generator"), m_afm->force_curve_generator);

    peripheral_collection::iterator i;
    for (i = m_afm->PGA_collection.begin(); i != m_afm->PGA_collection.end(); ++i) {
        QString name = "pga_" + i.key();
        page->addToJavaScriptWindowObject(name, i.value());
    }
    for (i = m_afm->DAC_collection.begin(); i != m_afm->DAC_collection.end(); ++i) {
        QString name = "dac_" + i.key();
        page->addToJavaScriptWindowObject(name, i.value());
    }
    for (i = m_afm->ADC_collection.begin(); i != m_afm->ADC_collection.end(); ++i) {
        QString name = "adc_" + i.key();
        page->addToJavaScriptWindowObject(name, i.value());
    }
    page->settings()->setMaximumPagesInCache(0);
}

void MainWindow::log_cpp(QString text) {
    qDebug() << text;
}

void MainWindow::load_main_app_page() {
    if (m_main_app_page.baseUrl().isEmpty())
        m_main_app_page.(QUrl("qrc:/html/main.html"));
    setPage(&m_main_app_page);
}

void MainWindow::load_home_page() {
    setPage(&m_welcome_page);
}

void MainWindow::pop_out_force_curve_page() {
    qDebug() << "Opening force curve page";
    createWindow(&m_force_curve_page);
}

QWebEngineView* MainWindow::createWindow(CustomPage* page) {
    MainWindow *webView= new MainWindow(page);
    webView->m_afm = m_afm;
    if (page->baseUrl().isEmpty())
        webView->page()->(QUrl("qrc:/html/force_curve.html"));
    webView->setAttribute(Qt::WA_DeleteOnClose, true);
    webView->show();
    return webView;
}

CustomPage::CustomPage() {
    QObject::connect(this, SIGNAL(downloadRequested(const QNetworkRequest&)), this, SLOT(downloadRequestedHandler(const QNetworkRequest&)));
    QObject::connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(handle(QNetworkReply*)));
}

void CustomPage::javaScriptAlert(const QString &msg) {
    qDebug() << "js alert";
}

void CustomPage::handle(QNetworkReply* msg) {
    qDebug() << "handling unsupported content";
}

void CustomPage::downloadRequestedHandler(const QNetworkRequest & request) {
    qDebug() << "download requested"; // request.url has the image of interest from the download buttons of highcharts.
}
