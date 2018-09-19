#ifndef ROSOUT_PUBLISHER_ROS_H
#define ROSOUT_PUBLISHER_ROS_H

#include <QObject>
#include <QtPlugin>
#include <QMainWindow>
#include <map>
#include <ros/ros.h>
#include "PlotJuggler/statepublisher_base.h"
#include <rosgraph_msgs/Log.h>
#include "logwidget.hpp"

class RosoutWindow: public QMainWindow
{
    Q_OBJECT
public:
    RosoutWindow():QMainWindow() {}
    ~ RosoutWindow(){}

    void closeEvent ( QCloseEvent* ) override{
        emit closed();
    }
signals:
    void closed();
};


class  RosoutPublisher: public QObject, StatePublisher
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.icarustechnology.PlotJuggler.StatePublisher" "../statepublisher.json")
    Q_INTERFACES(StatePublisher)

public:
    RosoutPublisher();

    virtual void updateState(double current_time) override;
    virtual const char* name() const override { return "RosoutPublisherROS"; }
    virtual ~RosoutPublisher();

    virtual bool enabled() const override { return _enabled; }

public slots:
    virtual void setEnabled(bool enabled) override;

private slots:

    void onWindowClosed();

private:

    bool _enabled;
    int64_t _minimum_time_usec, _maximum_time_usec;

    LogsTableModel* _tablemodel;
    rqt_console_plus::LogWidget* _log_widget;

    std::vector<const PlotDataAny *> findRosoutTimeseries();
    void syncWithTableModel(const std::vector<const PlotDataAny *> &logs_timeseries);

    RosoutWindow* _log_window;
signals:
    void timeRangeChanged(TimePoint time_min, TimePoint time_max);
};



#endif // ROSOUT_PUBLISHER_ROS_H
