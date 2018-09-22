#include "math_plot.h"

#include <QFile>
#include <QMessageBox>

MathPlot::MathPlot(const std::string &linkedPlot,
                   const std::string &plotName,
                   const QString &globalVars,
                   const QString &equation):
    _linkedPlot(linkedPlot),
    _plotName(plotName),
    _globalVars(globalVars),
    _calcEquation(equation),
    _plot_data(plotName)
{
    addJavascriptDependencies(_jsEngine);

    QString qLinkedPlot = QString::fromStdString(_linkedPlot);

    QString replaced_equation = _calcEquation;
    while(true)
    {
        int pos1=replaced_equation.indexOf("$$");
        if(pos1 == -1){
            break;
        }

        int pos2 = replaced_equation.indexOf("$$", pos1+2);
        if(pos2 == -1)
        {
            throw std::runtime_error("syntax error : invalid use of $$ macro");
        }

        QString channel_name = replaced_equation.mid(pos1+2, pos2-pos1-2);

        if(channel_name == qLinkedPlot)
        {
            // special case : user entered linkedPlot ; no need to add another channel
            replaced_equation.replace(QStringLiteral("$$%1$$").arg(channel_name), QStringLiteral("value"));
        }
        else
        {
            QString jsExpression = QString("CHANNEL_VALUES[%1]").arg(_used_channels.size());
            replaced_equation.replace(QStringLiteral("$$%1$$").arg(channel_name), jsExpression);
            _used_channels.push_back(channel_name.toStdString());
        }
    }
    _calcEquation = replaced_equation;

    //qDebug() << "final equation string : " << replaced_equation;

    QJSValue globalVarResult = _jsEngine.evaluate(_globalVars);
    if(globalVarResult.isError())
    {
        throw std::runtime_error("JS Engine : " + globalVarResult.toString().toStdString());
    }
    QString calcMethodStr = QString("function calc(time, value, CHANNEL_VALUES){with (Math){\n%1\n}}").arg(_calcEquation);
    _jsEngine.evaluate(calcMethodStr);
}

void MathPlot::refresh(const PlotDataMapRef &plotData)
{
    QJSValue calcFct = _jsEngine.evaluate("calc");

    if(calcFct.isError())
    {
        throw std::runtime_error("JS Engine : " + calcFct.toString().toStdString());
    }

    auto src_data_it = plotData.numeric.find(_linkedPlot);
    if(src_data_it == plotData.numeric.end())
    {
        throw std::runtime_error("invalid linked data channel");
    }
    const PlotData *src_data = &src_data_it->second;

    _plot_data.clear();

    for(size_t i=0; i < src_data->size(); ++i)
    {
        const PlotData::Point &old_point = src_data->at(i);

        QJSValue chan_values = _jsEngine.newArray(static_cast<quint32>(_used_channels.size()));
        for(int chan_index = 0; chan_index < _used_channels.size(); ++chan_index)
        {
            const auto& channel = _used_channels[chan_index];
            auto it = plotData.numeric.find(channel);
            if(it == plotData.numeric.end())
            {
                throw std::runtime_error("Invalid channel name");
            }
            const PlotData* chan_data = &(it->second);

            double value;
            int index = chan_data->getIndexFromX(old_point.x);
            if(index != -1)
                value = chan_data->at(static_cast<size_t>(index)).y;
            else
                value = std::numeric_limits<double>::quiet_NaN();

            chan_values.setProperty(static_cast<quint32>(chan_index), QJSValue(value));
        }

        PlotData::Point new_point;
        new_point.x = old_point.x;
        //jsEngine.globalObject().setProperty("CHANNEL_VALUES", chan_values); // this would be another method to share the array
        QJSValue jsData = calcFct.call({QJSValue(old_point.x), QJSValue(old_point.y), chan_values});
        if(jsData.isError())
        {
            throw std::runtime_error("JS Engine : " + jsData.toString().toStdString());
        }
        new_point.y = jsData.toNumber();

        _plot_data.pushBack(new_point);
    }
}

const std::string &MathPlot::getName() const
{
    return _plotName;
}

const std::string &MathPlot::getLinkedPlot() const
{
    return _linkedPlot;
}

const QString &MathPlot::getGlobalVars() const
{
    return _globalVars;
}

const QString &MathPlot::getEquation() const
{
    return _calcEquation;
}

PlotData &MathPlot::plotData()
{
    return _plot_data;
}

void MathPlot::addJavascriptDependencies(QJSEngine &engine)
{
    static QStringList files{":/js/resources/common.js", ":/js/resources/geographiclib.min.js" };
    for(QString fileName : files)
    {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly))
        {
            QString commonData = QString::fromUtf8(file.readAll());
            QJSValue out = engine.evaluate(commonData);
            if(out.isError())
            {
                qWarning() << "JS Engine : " << out.toString();
            }
        }
    }
}


