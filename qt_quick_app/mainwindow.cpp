#include "mainwindow.h"
#include "afm.h"
#include <QWebFrame>
#include <QWebElementCollection>
#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QWebSettings>
#include <QNetworkRequest>
#include "web_file_dialog.h"

MainWindow::MainWindow(AFM* afm, WebFileDialog* folder_picker, double zoom_factor, FirmwareUpdater* firmware_updater)
{
    //If you want to provide support for web sites that allow the user to open new windows, such as pop-up windows, you can subclass QWebView and reimplement the createWindow() function.

    // Core objects we will expose to JavaScript
    m_afm = afm;
    m_folder_picker = folder_picker;
    m_firmware_updater = firmware_updater;

    // commented out because we just call addJSObject manually now and pass in the appropriate page
    // QObject::connect(m_main_app_page.mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject())); // Signal is emitted before frame loads any web content:

    page()->setNetworkAccessManager(m_network);
    addJSObject(&m_welcome_page);
    addJSObject(&m_main_app_page);
    addJSObject(&m_force_curve_page);
    m_welcome_page.mainFrame()->load(QUrl("qrc:/html/home.html"));
    m_main_app_page.mainFrame()->load(QUrl("qrc:/html/main.html"));
    m_force_curve_page.mainFrame()->load(QUrl("qrc/html/force_curve.html"));
    // set zoom factor for each page to ensure proper scaling for high DPI displays
    qDebug() << "Initial Zoom Factor " << m_welcome_page.mainFrame()->zoomFactor();
    m_welcome_page.mainFrame()->setZoomFactor(zoom_factor);
    m_main_app_page.mainFrame()->setZoomFactor(zoom_factor);
    m_force_curve_page.mainFrame()->setZoomFactor(zoom_factor);
    qDebug() << "New Zoom Factor " << m_welcome_page.mainFrame()->zoomFactor();
    setPage(&m_welcome_page);
    setMinimumSize(640, 480);

    set_global_web_settings();
    setContextMenuPolicy(Qt::DefaultContextMenu);
    QObject::connect(m_welcome_page.mainFrame(), SIGNAL(loadFinished(bool)), this, SLOT(welcomePageLoadFinished()));
}

void MainWindow::set_global_web_settings() {
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);

    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls, true);
//    QWebSettings::clearMemoryCaches();
}

MainWindow::MainWindow(CustomPage* custom_page) {
    setPage(custom_page);
    set_global_web_settings();
    //QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));
}

void MainWindow::addJSObject(CustomPage* page) {
    // For this method to work without crashing the program, all initialization must be done first.
    page->mainFrame()->addToJavaScriptWindowObject(QString("afm"), m_afm);
    page->mainFrame()->addToJavaScriptWindowObject(QString("main_window"), this);
    page->mainFrame()->addToJavaScriptWindowObject(QString("sweeper"), m_afm->sweeper);
    page->mainFrame()->addToJavaScriptWindowObject(QString("dds"), m_afm->sweeper->dds);
    page->mainFrame()->addToJavaScriptWindowObject(QString("approacher"), m_afm->approacher);
    page->mainFrame()->addToJavaScriptWindowObject(QString("scanner"), m_afm->scanner);
    page->mainFrame()->addToJavaScriptWindowObject(QString("motor"), m_afm->motor);
    page->mainFrame()->addToJavaScriptWindowObject(QString("pid"), m_afm->scanner->pid);
    page->mainFrame()->addToJavaScriptWindowObject(QString("folder_picker"), m_folder_picker);
    page->mainFrame()->addToJavaScriptWindowObject(QString("force_curve_generator"), m_afm->force_curve_generator);
    //page->mainFrame()->addToJavaScriptWindowObject(QString("firmware_updater"), m_firmware_updater);

    peripheral_collection::iterator i;
    for (i = m_afm->PGA_collection.begin(); i != m_afm->PGA_collection.end(); ++i) {
        QString name = "pga_" + i.key();
        page->mainFrame()->addToJavaScriptWindowObject(name, i.value());
    }
    for (i = m_afm->DAC_collection.begin(); i != m_afm->DAC_collection.end(); ++i) {
        QString name = "dac_" + i.key();
        page->mainFrame()->addToJavaScriptWindowObject(name, i.value());
    }
    for (i = m_afm->ADC_collection.begin(); i != m_afm->ADC_collection.end(); ++i) {
        QString name = "adc_" + i.key();
        page->mainFrame()->addToJavaScriptWindowObject(name, i.value());
    }
    page->settings()->setMaximumPagesInCache(0);
}

void MainWindow::welcomePageLoadFinished() {
    emit loadFinished();
}

void MainWindow::log_cpp(QString text) {
    qDebug() << text;
}

void MainWindow::load_main_app_page() {
    if (m_main_app_page.mainFrame()->baseUrl().isEmpty())
        m_main_app_page.mainFrame()->load(QUrl("qrc:/html/main.html"));
    clearFocus();
    setPage(&m_main_app_page);
}

void MainWindow::load_home_page() {
    setPage(&m_welcome_page);
}

void MainWindow::pop_out_force_curve_page() {
    qDebug() << "Opening force curve page";
    createWindow(&m_force_curve_page);
}

QWebView* MainWindow::createWindow(CustomPage* page) {
    MainWindow *webView= new MainWindow(page);
    webView->m_afm = m_afm;
    if (page->mainFrame()->baseUrl().isEmpty())
        webView->page()->mainFrame()->load(QUrl("qrc:/html/force_curve.html"));
    webView->setAttribute(Qt::WA_DeleteOnClose, true);
    webView->setContextMenuPolicy(Qt::NoContextMenu);
    webView->show();
    return webView;
}

CustomPage::CustomPage() {
    QObject::connect(this, SIGNAL(downloadRequested(const QNetworkRequest&)), this, SLOT(downloadRequestedHandler(const QNetworkRequest&)));
    QObject::connect(this, SIGNAL(unsupportedContent(QNetworkReply*)), this, SLOT(handle(QNetworkReply*)));
}

void CustomPage::javaScriptAlert(QWebFrame *frame, const QString &msg) {
    Q_UNUSED(frame);
    Q_UNUSED(msg);
    qDebug() << "js alert";
}

void CustomPage::handle(QNetworkReply* msg) {
    Q_UNUSED(msg);
    qDebug() << "handling unsupported content";
}

void CustomPage::downloadRequestedHandler(const QNetworkRequest & request) {
    Q_UNUSED(request);
    qDebug() << "download requested"; // request.url has the image of interest from the download buttons of highcharts.
}
