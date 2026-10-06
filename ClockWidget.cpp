#include "ClockWidget.h"

#include <QTimer>

#include <QBoxLayout>
#include <QDateTime>
#include <QLabel>

ClockWidget::ClockWidget(QWidget *parent) {
  auto hour_font = QFont("Arial", 100, 800);
  auto minute_font = QFont("Arial", 94, 400);
  auto day_of_week_font = QFont("Arial", 50, 600);
  auto day_month_font = QFont("Arial", 40, 100);

  QHBoxLayout *offset_from_left_layout = new QHBoxLayout;
  offset_from_left_layout->addSpacing(100);

  QVBoxLayout *main_layout = new QVBoxLayout;
  main_layout->addStretch();
  QHBoxLayout *time_hbox = new QHBoxLayout;
  time_hbox->setAlignment(Qt::AlignBottom);

  hour_label_ = new QLabel("13:");
  hour_label_->setFont(hour_font);
  time_hbox->addWidget(hour_label_);

  minute_label_ = new QLabel("37");
  minute_label_->setFont(minute_font);
  time_hbox->addWidget(minute_label_);

  time_hbox->addStretch();

  main_layout->addLayout(time_hbox);

  day_of_week_label_ = new QLabel("Monday");
  day_of_week_label_->setFont(day_of_week_font);
  main_layout->addWidget(day_of_week_label_);

  day_month_label_ = new QLabel("5 Oct");
  day_month_label_->setFont(day_month_font);
  main_layout->addWidget(day_month_label_);

  main_layout->addStretch();

  offset_from_left_layout->addLayout(main_layout);

  setLayout(offset_from_left_layout);
  updateTimeLabels();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &ClockWidget::updateTimeLabels);
  timer->start(200);
}

void ClockWidget::paintEvent(QPaintEvent *event) {}

void ClockWidget::updateTimeLabels() {
  const auto datetime = QDateTime::currentDateTime();

  const auto time = datetime.time();
  const auto date = datetime.date();
  hour_label_->setText(QString::number(time.hour()) + ":");
  minute_label_->setText(QString("%1").arg(time.minute(), 2, 10, QChar('0')));
  day_of_week_label_->setText(date.toString("dddd"));
  day_month_label_->setText(date.toString("MMM") + " " +
                            QString::number(date.day()));
}
