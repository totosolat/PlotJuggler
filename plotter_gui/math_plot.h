#pragma once

#include <memory>
#include <string>
#include <QWidget>
#include <QString>
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

    void refresh(PlotDataMapRef &plotData);

    const std::string& getName() const;
    const std::string& getLinkedPlot() const;
    const QString& getGlobalVars() const;
    const QString& getEquation() const;
    PlotData& plotData();

private:
    void addJavascriptDependencies(QJSEngine &engine);

    std::string _linkedPlot;
    std::string _plotName;
    QString _globalVars;
    QString _calcEquation;
    PlotData _plot_data;
};

