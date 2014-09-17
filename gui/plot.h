#include <qstring.h>
#include <qpair.h>
#include <qvector.h>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>

#define BUFFER 1000

class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer( QWidget *canvas, bool trackerMode ):
        QwtPlotZoomer( canvas )
    {
        setRubberBandPen( QColor( Qt::darkGreen ) );
        setTrackerMode( trackerMode == true ? QwtPlotPicker::AlwaysOn : QwtPlotPicker::AlwaysOff );
    }

protected:
    virtual QwtText trackerTextF( const QPointF &pos ) const
    {
        QwtText text( QString("%1 , %2").arg(QString::number(pos.x()), QString::number(pos.y())) );
        text.setColor( Qt::white );

        QColor c = rubberBandPen().color();
        text.setBorderPen( QPen( c ) );
        text.setBorderRadius( 6 );
        c.setAlpha( 170 );
        text.setBackgroundBrush( c );

        return text;
    }
};


class PlotFields {
  public:
    PlotFields(const QString& titleIn, bool displayTitleIn,
               const QString& xLabelIn, QString yLabelIn,
               const QPair<double,double>& xAxisIn, const QPair<double,double>& yAxisIn,
               const QColor& colorIn, bool autoScaleIn = false, bool displayTrackerIn = false, int bufferSizeIn = BUFFER ) :
    title(titleIn), displayTitle(displayTitleIn), xLabel(xLabelIn), yLabel(yLabelIn), xAxis(xAxisIn), yAxis(yAxisIn), \
    color(colorIn), autoScale(autoScaleIn), displayTracker(displayTrackerIn), bufferSize(bufferSizeIn){}

    QString title;
    bool displayTitle;
    QString xLabel;
    QString yLabel;
    QPair<double,double> xAxis;
    QPair<double,double> yAxis;
    QColor color;
    bool autoScale;
    bool displayTracker;
    int bufferSize;
};

class Plot : public QwtPlot
{
    Q_OBJECT
public:
    Plot( const PlotFields& fields, QWidget * = 0 );
    void update(double x, double y, bool replot = true);
    void setAutoScale(bool val);
    void setMarker(bool val);
    Zoomer* getZoomer() const { return zoomer; }
    void clearData() {
        xData.clear(); yData.clear(); dataCount = 0;
        mCurve->setRawSamples(xData.data(), yData.data(), 0);
    }

private slots:
    void displayPoint(const QPointF&);

private:
    QVector<double> xData;
    QVector<double> yData;
    int dataCount;
    QwtPlotCurve* mCurve;

    PlotFields fields;
    bool autoScale;
    int xAxisStart;
    int xAxisRange;
    Zoomer* zoomer;
};
