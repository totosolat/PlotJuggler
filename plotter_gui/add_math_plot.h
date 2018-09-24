#ifndef AddMathPlotDialog_H
#define AddMathPlotDialog_H

#include <QDialog>
#include <QListWidgetItem>
#include <qwt_plot_curve.h>
#include "PlotJuggler/plotdata.h"
#include "math_plot.h"

namespace Ui {
class AddMathPlotDialog;
}

class AddMathPlotDialog : public QDialog
{
    Q_OBJECT

    struct SnippetData{
        QString name;
        QString globalVars;
        QString equation;
    };

public:
    explicit AddMathPlotDialog(PlotDataMapRef &plotMapData,
                               const std::unordered_map<std::string, MathPlotPtr>& _mapped_math_plots,
                               QWidget *parent);
    virtual ~AddMathPlotDialog() override;

    void setLinkedPlotName(const QString &linkedPlotName);
    virtual void accept() override;

    QString getLinkedData() const;
    QString getGlobalVars() const;
    QString getEquation() const;
    QString getName() const;
    const PlotData& getPlotData() const;
    void editExistingPlot(MathPlotPtr data);
    MathPlotPtr getMathPlotData() const;

private slots:

    void on_curvesListWidget_doubleClicked(const QModelIndex &index);

    void on_snippetsListWidget_currentRowChanged(int currentRow);

    void on_snippetsListWidget_doubleClicked(const QModelIndex &index);

    void on_snippetsListRecent_currentRowChanged(int currentRow);

    void on_snippetsListRecent_doubleClicked(const QModelIndex &index);

private:
    void createSnippets();


    PlotDataMapRef &_plot_map_data;
    const std::unordered_map<std::string, MathPlotPtr> &_math_plots;
    Ui::AddMathPlotDialog *ui;

    MathPlotPtr _plot;
    bool _isNewPlot = true;

    std::vector<SnippetData> _snipped_examples;
    std::vector<SnippetData> _snipped_recent;
};

#endif // AddMathPlotDialog_H
