#include "curvestatistics.h"

#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QFontDatabase>
#include <cmath>
#include <limits>

#include <iostream>
using namespace std;

CurveStatistics::CurveStatistics(QwtPlot *plot):
    QObject(plot),
    _plot(plot)
{
    _text_marker = (new QwtPlotMarker);
    _text_marker->attach(plot);

    _visible = true;
}


void CurveStatistics::actualiseValues()
{
    const QwtPlotItemList curves = _plot->itemList( QwtPlotItem::Rtti_PlotCurve );

    QRectF rect;
    rect.setBottom( _plot->canvasMap( QwtPlot::yLeft ).s1() );
    rect.setTop( _plot->canvasMap( QwtPlot::yLeft ).s2() );
    rect.setLeft( _plot->canvasMap( QwtPlot::xBottom ).s1() );
    rect.setRight( _plot->canvasMap( QwtPlot::xBottom ).s2() );

    double text_X_offset = 0;
    std::multimap<double,QString> text_lines;

    for ( int i = curves.size()-1; i >= 0; i-- )
    {
        QwtPlotCurve *curve = static_cast<QwtPlotCurve *>(curves[i]);
        QColor color = curve->pen().color();

        if( _visible )
        {
            // Compute min, max, mean and standard deviation
            double min = std::numeric_limits<double>::max();
            double max = std::numeric_limits<double>::min();
            for (int k=0; k < curve->data()->size(); k++)
            {
              double value = curve->data()->sample(k).y();
              if (value < min)
                min = value;
              else if (value > max)
                max = value;
            }

            double mean = 0.0;
            for (int k=0; k< curve->data()->size(); k++)
            {
                mean += curve->data()->sample(k).y();
            }
            mean /= curve->data()->size();

            double squares_sum = 0.0;
            for (size_t k=0; k< curve->data()->size(); k++ ) {
                squares_sum += std::pow(curve->data()->sample(k).y() - mean, 2);
            }
            const double standard_deviation = std::sqrt(squares_sum / curve->data()->size());

            // Add it to the text
            QString line;
            QString str_min = QString::number(min, 'f', 4);
            QString str_max = QString::number(max, 'f', 4);
            QString str_mean = QString::number(mean, 'f', 4);
            QString str_standard_deviation = QString::number(standard_deviation, 'e', 2);

            line = QString( "<font color=%1>min=%2 ; max=%3 ; mean=%4 ; std_dev=%5 </font>" )
                    .arg(color.name()).arg(str_min).arg(str_max).arg(str_mean).arg(str_standard_deviation);

            text_lines.insert( std::make_pair(42.0, line) );    // FIXME: really useful?
        }
    }

    QwtText mark_text;
    mark_text.setColor( Qt::black );

    QString text_marker_info;

    int count = 0;
    for(auto it = text_lines.rbegin(); it != text_lines.rend(); it++)
    {
        text_marker_info += it->second;
        if( count++ < text_lines.size() -1 )
        {
            text_marker_info += "<br>";
        }
    }

    QColor c( "#FFFFFF" );
    mark_text.setBorderPen( QPen( c, 2 ) );
    c.setAlpha( 220 );
    mark_text.setBackgroundBrush( c );
    mark_text.setText( text_marker_info );
    mark_text.setFont(  QFontDatabase::systemFont(QFontDatabase::FixedFont) );
    mark_text.setRenderFlags(Qt::AlignLeft);

    _text_marker->setLabel(mark_text);
    _text_marker->setLabelAlignment( Qt::AlignRight );
    _text_marker->setXValue(rect.left());
    _text_marker->setYValue(0.5 * (rect.top() + rect.bottom()));
    _text_marker->setVisible(_visible);

}


void CurveStatistics::activate(bool activate)
{
    _visible = activate;
}
