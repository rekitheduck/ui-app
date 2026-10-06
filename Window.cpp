#include "Window.h"

#include <QStackedLayout>
#include <QTimer>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include "ClockWidget.h"
#include "LoaderWidget.h"

Window::Window(QWidget *parent) : QWidget(parent) {
  QStackedLayout *layout = new QStackedLayout;

  auto *loader_widget = new LoaderWidget;
  layout->addWidget(loader_widget);
  layout->setStackingMode(QStackedLayout::StackingMode::StackAll);

  setStyleSheet("background-color: black;");
  setLayout(layout);

  // Start the loading
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, loader_widget,
          &LoaderWidget::incrementProgress);
  timer->start(100);

  connect(loader_widget, &LoaderWidget::finishedLoading, [=]() {
    timer->stop();
    disconnect(loader_widget);
    delete timer;

    QGraphicsOpacityEffect *fade_out_effect = new QGraphicsOpacityEffect(this);
    loader_widget->setGraphicsEffect(fade_out_effect);
    QPropertyAnimation *fout_op =
        new QPropertyAnimation(fade_out_effect, "opacity");
    fout_op->setDuration(400);
    fout_op->setStartValue(1);
    fout_op->setEndValue(0);
    fout_op->setEasingCurve(QEasingCurve::InOutCirc);
    fout_op->start(QPropertyAnimation::DeleteWhenStopped);
    connect(fout_op, &QPropertyAnimation::finished,
            [=]() { loader_widget->hide(); });

    auto *clock_widget = new ClockWidget;

    layout->addWidget(clock_widget);
    QGraphicsOpacityEffect *fade_in_effect = new QGraphicsOpacityEffect(this);
    clock_widget->setGraphicsEffect(fade_in_effect);
    QPropertyAnimation *fin_op =
        new QPropertyAnimation(fade_in_effect, "opacity");
    fin_op->setDuration(400);
    fin_op->setStartValue(0);
    fin_op->setEndValue(1);
    fin_op->setEasingCurve(QEasingCurve::InOutCirc);
    fin_op->start(QPropertyAnimation::DeleteWhenStopped);
  });
}