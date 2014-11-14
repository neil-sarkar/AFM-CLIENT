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
#include <qwt3d_surfaceplot.h>


using namespace MyPlot;

void Plot::SetPlot(PlotFields& fieldsIn, QWidget *parent)

{
    PlotFields fields = fieldsIn;
    this->dataCount = 0;
    this->setAutoReplot( false );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setBorderRadius( 10 );
    this->setCanvas( canvas );

    this->plotLayout()->setAlignCanvasToScales( true );

    // sometimes, title takes up too much space
    if (fields.displayTitle) {
        QwtText title(fields.title);
        title.setFont(QFont("Times", 12, QFont::Bold));
        this->setTitle(title);
    }

    this->setAxisTitle( QwtPlot::xBottom, fields.xLabel );
    this->setAxisScale( QwtPlot::xBottom, fields.xAxis.first, fields.xAxis.second );
    this->setAxisAutoScale( QwtPlot::xBottom, fields.autoScale );

    this->setAxisTitle( QwtPlot::yLeft, fields.yLabel );
    this->setAxisScale( QwtPlot::yLeft, fields.yAxis.first, fields.yAxis.second );
    this->setAxisAutoScale( QwtPlot::yLeft, fields.autoScale );

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
    this->setContentsMargins( margin, margin, margin, margin );

    QwtPlotGrid *grid = new QwtPlotGrid;
    grid->enableX( true );
    grid->enableY( true );
    grid->setMajorPen( Qt::white, 0, Qt::DotLine );
    grid->attach( this );

    this->setCanvasBackground( QColor( "Black" ) );

    QwtPlotCurve *curve = new QwtPlotCurve( fields.title );
    curve->setPen( fields.color );
    curve->attach( this );

    this->mCurve = curve;
    this->xAxisStart = fields.xAxis.first;
    this->xAxisRange = fields.xAxis.second - fields.xAxis.first;
    this->autoScale = fields.autoScale;

    //connect(this, SIGNAL(clicked(QPointF)),this,SLOT(displayPoint(QPointF)));

}

// TODO: I cannot seem to be able to get this slot to activate upon clicking
void Plot::displayPoint(const QPointF& p) {
    qDebug() << "I am here";
    QMessageBox msgBox;
    msgBox.setText(QString("%1 %2").arg(QString::number(p.x()), QString::number(p.y())));
    msgBox.exec();
}

void Plot::setAutoScale(bool val) {
    this->autoScale = val;
    this->setAxisAutoScale( QwtPlot::xBottom, val );
    this->setAxisAutoScale( QwtPlot::yLeft, val );

    if ( this->autoScale == false ) {
        this->setAxisScale( QwtPlot::xBottom, xData[dataCount-1], xData[dataCount-1] + xAxisRange );
        this->xAxisStart = xData[dataCount-1];
        this->dataCount = 0;
        this->xData.clear();
        this->yData.clear();
    }
}

void Plot::setMarker(bool val) {
    zoomer->setTrackerMode( val == true ? \
                            QwtPlotPicker::AlwaysOn : QwtPlotPicker::AlwaysOff );
}

void Plot::update(double x, double y, bool toReplot ) {
    if ( dataCount == BUFFER ) {
        this->xData.pop_front();
        this->yData.pop_front();
    } else {
        this->dataCount++;
    }

    if ( !this->autoScale ) {
        if ( x >= (this->xAxisStart + this->xAxisRange) ) {
            this->dataCount = 1;
            this->xData.clear();
            this->yData.clear();
            this->setAxisScale( QwtPlot::xBottom, x, x + xAxisRange );
            this->xAxisStart = x;
        }
    }
    this->xData.push_back( x );
    this->yData.push_back( y );
    this->mCurve->setRawSamples(xData.data(), yData.data(), dataCount );

    if ( toReplot )
        this->replot();
}
