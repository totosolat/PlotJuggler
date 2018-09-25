#include "custom_plot.h"

#include <QFile>
#include <QMessageBox>

CustomPlot::CustomPlot(const std::string &linkedPlot,
                   const std::string &plotName,
                   const QString &globalVars,
                   const QString &equation):
    _linked_plot_name(linkedPlot),
    _plot_name(plotName),
    _global_vars(globalVars),
    _function(equation)
{

    QString qLinkedPlot = QString::fromStdString(_linked_plot_name);

    QString replaced_equation = _function;
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
    _function = replaced_equation;

    //qDebug() << "final equation string : " << replaced_equation;

}

void CustomPlot::calculate(PlotDataMapRef &plotData)
{
    QJSEngine jsEngine;

    addJavascriptDependencies(jsEngine);

    QJSValue globalVarResult = jsEngine.evaluate(_global_vars);
    if(globalVarResult.isError())
    {
        throw std::runtime_error("JS Engine : " + globalVarResult.toString().toStdString());
    }
    QString calcMethodStr = QString("function calc(time, value, CHANNEL_VALUES){with (Math){\n%1\n}}").arg(_function);
    jsEngine.evaluate(calcMethodStr);

    QJSValue calcFct = jsEngine.evaluate("calc");

    if(calcFct.isError())
    {
        throw std::runtime_error("JS Engine : " + calcFct.toString().toStdString());
    }

    auto dst_data_it = plotData.numeric.find(_plot_name);
    if(dst_data_it == plotData.numeric.end())
    {
        dst_data_it = plotData.addNumeric(_plot_name);
    }
    PlotData& dst_data = dst_data_it->second;
    // clean up
    dst_data.clear();

    auto src_data_it = plotData.numeric.find(_linked_plot_name);
    if(src_data_it == plotData.numeric.end())
    {
        // failed! keep it empty
        return;
    }
    const PlotData& src_data = src_data_it->second;


    for(size_t i=0; i < src_data.size(); ++i)
    {
        const PlotData::Point &old_point = src_data.at(i);

        QJSValue chan_values = jsEngine.newArray(static_cast<quint32>(_used_channels.size()));
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

        dst_data.pushBack(new_point);
    }
}

const std::string &CustomPlot::name() const
{
    return _plot_name;
}

const std::string &CustomPlot::linkedPlotName() const
{
    return _linked_plot_name;
}

const QString &CustomPlot::globalVars() const
{
    return _global_vars;
}

const QString &CustomPlot::function() const
{
    return _function;
}

void CustomPlot::addJavascriptDependencies(QJSEngine &engine)
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

QDomElement CustomPlot::xmlSaveState(QDomDocument &doc) const
{
    QDomElement snippet = doc.createElement("snippet");
    snippet.setAttribute("name", QString::fromStdString(_plot_name) );

    QDomElement linked = doc.createElement("linkedPlot");
    linked.appendChild( doc.createTextNode( QString::fromStdString(_linked_plot_name)) );
    snippet.appendChild(linked);

    QDomElement global = doc.createElement("global");
    global.appendChild( doc.createTextNode(_global_vars) );
    snippet.appendChild(global);

    QDomElement equation = doc.createElement("equation");
    equation.appendChild( doc.createTextNode(_function) );
    snippet.appendChild(equation);

    return snippet;
}

CustomPlotPtr CustomPlot::createFromXML(QDomElement &element)
{
    auto name   = element.attribute("name").toStdString();
    auto linkedPlot = element.firstChildElement("linkedPlot").text().trimmed().toStdString();
    auto globalVars = element.firstChildElement("global").text().trimmed();
    auto calcEquation = element.firstChildElement("equation").text().trimmed();

    return std::make_shared<CustomPlot>(linkedPlot, name, globalVars, calcEquation );
}

