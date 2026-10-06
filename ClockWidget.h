#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QLabel>
#include <QWidget>

class ClockWidget : public QWidget {
  Q_OBJECT
public:
  ClockWidget(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  void updateTimeLabels();

  QLabel *hour_label_{nullptr};
  QLabel *minute_label_{nullptr};
  QLabel *day_of_week_label_{nullptr};
  QLabel *day_month_label_{nullptr};
};

#endif