#include "add_math_plot.h"
#include "ui_add_math_plot.h"
#include <QDebug>
#include <QMessageBox>
#include <QFont>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include "math_plot.h"
#include "plotwidget.h"

AddMathPlotDialog::AddMathPlotDialog(PlotDataMapRef &plotMapData,
                                     const std::unordered_map<std::string, MathPlotPtr> &mapped_math_plots,
                                     QWidget *parent) :
    QDialog(parent),
    _plot_map_data(plotMapData),
    _math_plots(mapped_math_plots),
    ui(new Ui::AddMathPlotDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("Create a custom timeseries (EXPERIMENTAL)");

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    ui->globalVarsTextField->setFont(fixedFont);
    ui->mathEquation->setFont(fixedFont);
    ui->snippetTextEdit->setFont(fixedFont);

    QStringList numericPlotNames;
    for(const auto &p : _plot_map_data.numeric)
    {
        QString name = QString::fromStdString(p.first);
        numericPlotNames.push_back(name);
    }
    numericPlotNames.sort(Qt::CaseInsensitive);
    for(const QString& name : numericPlotNames)
    {
        ui->linkedChannelCombobox->addItem(name);
        ui->curvesListWidget->addItem(name);
    }

    createSnippets();
}

AddMathPlotDialog::~AddMathPlotDialog()
{
    delete ui;
}

void AddMathPlotDialog::setLinkedPlotName(const QString &linkedPlotName)
{
    ui->linkedChannelCombobox->setCurrentText(linkedPlotName);
}

void AddMathPlotDialog::accept()
{
    try {
        std::string plotName = getName().toStdString();
        if(_isNewPlot)
        {
            // check if name is unique
            if(_plot_map_data.numeric.count(plotName) != 0)
            {
                throw std::runtime_error("plot name already exists");
            }
        }
        _plot = std::make_shared<MathPlot>(getLinkedData().toStdString(),
                                           plotName,
                                           getGlobalVars(),
                                           getEquation());
        QDialog::accept();
    }
    catch (const std::runtime_error &e) {
        _plot.reset();
        QMessageBox::critical(this, "Error", "Failed to create math plot : "
                              + QString::fromStdString(e.what()));
    }
}

QString AddMathPlotDialog::getLinkedData() const
{
    return ui->linkedChannelCombobox->currentText();
}

QString AddMathPlotDialog::getGlobalVars() const
{
    return ui->globalVarsTextField->toPlainText();
}

QString AddMathPlotDialog::getEquation() const
{
    return ui->mathEquation->toPlainText();
}

QString AddMathPlotDialog::getName() const
{
    return ui->nameLineEdit->text();
}


void AddMathPlotDialog::editExistingPlot(MathPlotPtr data)
{
    ui->globalVarsTextField->setPlainText(data->globalVars());
    ui->mathEquation->setPlainText(data->equation());
    setLinkedPlotName(QString::fromStdString(data->linkedPlotName()));
    ui->pushButtonDone->setText("Update");
    ui->nameLineEdit->setText(QString::fromStdString(data->name()));
    ui->nameLineEdit->setEnabled(false);

    _isNewPlot = false;
}

MathPlotPtr AddMathPlotDialog::getMathPlotData() const
{
    return _plot;
}

void AddMathPlotDialog::on_curvesListWidget_doubleClicked(const QModelIndex &index)
{
    QString appendString = QString("$$%1$$").arg(ui->curvesListWidget->item(index.row())->text());
    if(ui->globalVarsTextField->hasFocus())
    {
        ui->globalVarsTextField->insertPlainText(appendString);
    }
    else if(ui->mathEquation->hasFocus())
    {
        ui->mathEquation->insertPlainText(appendString);
    }
}

void AddMathPlotDialog::createSnippets()
{
    _snipped_examples.clear();
    _snipped_recent.clear();

    QFile file("://resources/snippets.xml");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Error", QString("Failed to open snippets.xml file"));
    }
    QDomDocument doc;
    QString parseErrorMsg;
    int parseErrorLine;
    if(!doc.setContent(&file, false, &parseErrorMsg, &parseErrorLine))
    {
        QMessageBox::critical(nullptr, "Error",
                              QString("Failed to parse snippets.xml, error %1 at line %2").arg(parseErrorMsg).arg(parseErrorLine));
    }
    else
    {
        QDomElement docElem = doc.documentElement();
        QDomNode n = docElem.firstChild();
        while(!n.isNull()) {
            QDomElement e = n.toElement(); // try to convert the node to an element.
            if(!e.isNull() && e.tagName() == "snippet") {
                SnippetData snippet;
                snippet.name = e.attribute("name");
                snippet.globalVars = e.firstChildElement("global").text().trimmed();
                snippet.equation = e.firstChildElement("equation").text().trimmed();
                _snipped_examples.emplace_back(snippet);
            }
            n = n.nextSibling();
        }
    }

    std::vector<SnippetData> snippets;

    for( const auto& it: _math_plots)
    {
        const auto& math_plot = it.second;
        SnippetData snippet;
        snippet.name = QString::fromStdString(math_plot->name());
        snippet.globalVars = math_plot->globalVars();
        snippet.equation = math_plot->equation();
        _snipped_recent.emplace_back(snippet);
    }

    for(const SnippetData &d : _snipped_examples)
    {
        ui->snippetsListWidget->addItem(d.name);
    }

    for(const SnippetData &d : _snipped_recent )
    {
        ui->snippetsListRecent->addItem(d.name);
    }
}


void AddMathPlotDialog::on_snippetsListWidget_currentRowChanged(int currentRow)
{
    const SnippetData& snippet = _snipped_examples.at(static_cast<size_t>(currentRow));
    QString desc = QString("%1\n\nfunction calc(time,value)\n{\n%2\n}").arg(snippet.globalVars).arg(snippet.equation);
    ui->snippetTextEdit->setPlainText(desc);
}

void AddMathPlotDialog::on_snippetsListWidget_doubleClicked(const QModelIndex &index)
{
    const SnippetData& snippet = _snipped_examples.at(static_cast<size_t>(index.row()));
    ui->globalVarsTextField->setPlainText(snippet.globalVars);
    ui->mathEquation->setPlainText(snippet.equation);
}

void AddMathPlotDialog::on_snippetsListRecent_currentRowChanged(int currentRow)
{
    const SnippetData& snippet = _snipped_recent.at(static_cast<size_t>(currentRow));
    QString desc = QString("%1\n\nfunction calc(time,value)\n{\n%2\n}").arg(snippet.globalVars).arg(snippet.equation);
    ui->snippetTextEdit->setPlainText(desc);
}

void AddMathPlotDialog::on_snippetsListRecent_doubleClicked(const QModelIndex &index)
{
    const SnippetData& snippet = _snipped_recent.at(static_cast<size_t>(index.row()));
    ui->globalVarsTextField->setPlainText(snippet.globalVars);
    ui->mathEquation->setPlainText(snippet.equation);
}
