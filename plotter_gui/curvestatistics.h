#ifndef CURVESTATISTICS_H
#define CURVESTATISTICS_H

#include <qwt_plot_textlabel.h>
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
    QwtPlotTextLabel* _text_label;
    QwtPlot* _plot;
    bool _visible;

};

#endif // CURVESTATISTICS_H
