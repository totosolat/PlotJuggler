#ifndef CURVESTATISTICS_H
#define CURVESTATISTICS_H

#include <qwt_plot_marker.h>
#include <qwt_plot.h>


class CurveStatistics: public QObject
{
    Q_OBJECT

public:
    explicit CurveStatistics(QwtPlot *plot);

public slots:
    void actualiseValues();

    void activate(bool activate);

private:
    std::vector<QwtPlotMarker*> _marker;
    QwtPlotMarker* _text_marker;
    QwtPlot* _plot;
    bool _visible;


};

#endif // CURVESTATISTICS_H
