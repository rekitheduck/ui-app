#ifndef LOADERWIDGET_H
#define LOADERWIDGET_H

#include <QWidget>

class LoaderWidget : public QWidget {
  Q_OBJECT
public:
  LoaderWidget(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;

public slots:
  void incrementProgress();

signals:
  void finishedLoading();

private:
  float loaded_percentage_{0.0f};
};

#endif