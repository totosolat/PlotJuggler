#pragma once

#include <memory>
#include <string>
#include <QWidget>
#include <QString>
#include <QDomDocument>
#include <QJSEngine>
#include <include/PlotJuggler/plotdata.h>

class MathPlot;
class QJSEngine;
typedef std::shared_ptr<MathPlot> MathPlotPtr;

class MathPlot
{
public:
    MathPlot(const std::string &linkedPlot,
             const std::string &plotName,
             const QString &globalVars,
             const QString &equation);

    void refresh(const PlotDataMapRef &plotData);

    const std::string& name() const;

    const std::string& linkedPlotName() const;

    const QString& globalVars() const;

    const QString& equation() const;

    PlotData& plotData();

    QDomElement xmlSaveState(QDomDocument &doc) const;

    bool xmlLoadState(QDomElement &plotmatrix_element );

private:
    void addJavascriptDependencies(QJSEngine &engine);

    std::string _linkedPlot;
    std::string _plotName;
    QString _globalVars;
    QString _calcEquation;
    PlotData _plot_data;
    std::vector<std::string> _used_channels;
};

