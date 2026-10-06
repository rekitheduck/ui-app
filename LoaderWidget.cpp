#include "LoaderWidget.h"

#include <QPainter>
#include <QPainterPath>

LoaderWidget::LoaderWidget(QWidget *parent) {}

void LoaderWidget::paintEvent(QPaintEvent *event) {

  constexpr float radius = 200.0f;
  constexpr float loader_thickness = 40.0f;
  const auto loaded_degrees = 360.0f * loaded_percentage_ / 100.0f;

  QPainter painter(this);
  QPen pen;
  pen.setColor(Qt::transparent);
  painter.setPen(pen);
  painter.setRenderHint(QPainter::Antialiasing);

  QBrush blue_fill_brush(QColor(0, 0, 191));
  painter.setBrush(blue_fill_brush);

  const auto center_pos = rect().center();
  QRectF middle_rect_outer = QRectF(
      center_pos.x() - radius, center_pos.y() - radius, radius * 2, radius * 2);
  QRectF middle_rect_inner = QRectF(center_pos.x() - radius + loader_thickness,
                                    center_pos.y() - radius + loader_thickness,
                                    (radius - loader_thickness) * 2.0f,
                                    (radius - loader_thickness) * 2.0f);

  // Construct the loader path
  QPainterPath loader_path;

  loader_path.moveTo(center_pos + QPointF{0, -radius});
  loader_path.arcTo(middle_rect_outer, 90, -loaded_degrees);

  // Get position for the circle at the end section
  auto end_vec = loader_path.currentPosition() - center_pos;
  const auto dist_to_p1 =
      std::sqrt(std::pow(end_vec.x(), 2) + std::pow(end_vec.y(), 2));
  const auto dist_to_endmid = dist_to_p1 - loader_thickness * 0.5f;
  const auto dist_mult = dist_to_endmid / dist_to_p1;

  const auto end_mid = (end_vec * dist_mult) + center_pos;

  loader_path.arcTo(middle_rect_inner, 90.0f - loaded_degrees, loaded_degrees);
  loader_path.closeSubpath();

  // Draw the loading bar!
  painter.drawPath(loader_path);

  // Draw the start ellipsis
  painter.drawEllipse(center_pos +
                          QPointF{0, -radius + loader_thickness * 0.5f},
                      loader_thickness * 0.5f, loader_thickness * 0.5f);

  // Draw the end ellipsis
  painter.drawEllipse(end_mid, loader_thickness * 0.5f,
                      loader_thickness * 0.5f);
  painter.setPen(Qt::white);

  // Draw the actual percentage
  QFont counter_font = QFont("Helvetica", 50);
  counter_font.setBold(true);
  painter.setFont(counter_font);
  painter.drawText(QRect(center_pos.x() - 120, center_pos.y() - 65, 140, 100),
                   Qt::AlignRight, QString::number(loaded_percentage_));

  // Draw the "Initializing" text
  QFont initializing_text_font = QFont("Helvetica", 20);
  painter.setFont(initializing_text_font);
  painter.drawText(QRect(center_pos.x() - 250, center_pos.y() - 15, 500, 100),
                   Qt::AlignCenter, "INITIALIZING");

  // Draw the % symbol
  QFont percentage_symbol_font = QFont("Helvetica", 35);
  painter.setFont(percentage_symbol_font);
  painter.setPen(QPen(Qt::gray));
  painter.drawText(QRect(center_pos.x() + 25, center_pos.y() - 45, 140, 100),
                   Qt::AlignLeft, "%");
}

void LoaderWidget::incrementProgress() {
  if (loaded_percentage_ < 100) {
    loaded_percentage_++;
    update();
  } else {
    emit finishedLoading();
  }
}
