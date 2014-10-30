#include <myplot.h>
#include <qapplication.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qcolor.h>
#include <qpushbutton.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_canvas.h>
#include <qwt_picker_machine.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qdebug.h>
#include <math.h>


using namespace MyPlot;

void Plot::SetPlot(PlotFields& fieldsIn, QWidget *parent)

{
    PlotFields fields = fieldsIn;

    this->setAutoReplot( false );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setBorderRadius( 10 );
    setCanvas( canvas );

    plotLayout()->setAlignCanvasToScales( true );

    // sometimes, title takes up too much space
    if (fields.displayTitle) {
        QwtText title(fields.title);
        title.setFont(QFont("Times", 12, QFont::Bold));
        setTitle(title);
    }

    setAxisTitle( QwtPlot::xBottom, fields.xLabel );
    setAxisScale( QwtPlot::xBottom, fields.xAxis.first, fields.xAxis.second );
    setAxisAutoScale( QwtPlot::xBottom, fields.autoScale );

    setAxisTitle( QwtPlot::yLeft, fields.yLabel );
    setAxisScale( QwtPlot::yLeft, fields.yAxis.first, fields.yAxis.second );
    setAxisAutoScale( QwtPlot::yLeft, fields.autoScale );

    // LeftButton for the zooming
    // RightButton: zoom out by 1
    // Ctrl+RighButton: zoom out to full size
    // TODO: when the user right clicks on plot, the data dissapears

    zoomer = new Zoomer( canvas, fields.displayTracker );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::RightButton, Qt::ControlModifier );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3,
        Qt::RightButton );
    //zoomer->setStateMachine(new QwtPickerClickPointMachine());
    //connect(zoomer, SIGNAL(selected(const QPointF&)), this, SLOT(displayPoint(const QPointF&)));

    const int margin = 5;
    setContentsMargins( margin, margin, margin, margin );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX( true );
    grid->enableY( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->attach( this );

    setCanvasBackground( QColor( "Black" ) );

    QwtPlotCurve *curve = new QwtPlotCurve( fields.title );
    curve->setPen( fields.color );
    curve->attach( this );

    mCurve = curve;
    xAxisStart = fields.xAxis.first;
    xAxisRange = fields.xAxis.second - fields.xAxis.first;
    autoScale = fields.autoScale;

}

// TODO: I cannot seem to be able to get this slot to activate upon clicking
void Plot::displayPoint(const QPointF& p) {
    qDebug() << "I am here";
    QMessageBox msgBox;
    msgBox.setText(QString("%1 %2").arg(QString::number(p.x()), QString::number(p.y())));
    msgBox.exec();
}

void Plot::setAutoScale(bool val) {
    autoScale = val;
    setAxisAutoScale( QwtPlot::xBottom, val );
    setAxisAutoScale( QwtPlot::yLeft, val );

    if ( autoScale == false ) {
        setAxisScale( QwtPlot::xBottom, xData[dataCount-1], xData[dataCount-1] + xAxisRange );
        xAxisStart = xData[dataCount-1];
        dataCount = 0;
        xData.clear();
        yData.clear();
    }
}

void Plot::setMarker(bool val) {
    zoomer->setTrackerMode( val == true ? \
                            QwtPlotPicker::AlwaysOn : QwtPlotPicker::AlwaysOff );
}

void Plot::update(double x, double y, bool toReplot ) {
    if ( dataCount == BUFFER ) {
        xData.pop_front();
        yData.pop_front();
    } else {
        dataCount++;
    }

    if ( !autoScale ) {
        if ( x >= (xAxisStart + xAxisRange) ) {
            dataCount = 1;
            xData.clear();
            yData.clear();
            setAxisScale( QwtPlot::xBottom, x, x + xAxisRange );
            xAxisStart = x;
        }
    }
    xData.push_back( x );
    yData.push_back( y );
    mCurve->setRawSamples(xData.data(), yData.data(), dataCount );

    if ( toReplot )
        replot();
}
