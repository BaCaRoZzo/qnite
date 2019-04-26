#include "qnitepen.h"

QnitePen::PenData::PenData()
    : stroke{"black"}, fill{}, width{2}, join{LineJoin::JOIN_MITER},
      cap{LineCap::CAP_SQUARE}, radius{5} {}

QnitePen::QnitePen(QObject *parent) : QObject{parent} {}

void QnitePen::setStroke(QColor stroke) {
  if (m_data.stroke != stroke) {
    m_data.stroke = stroke;
    Q_EMIT strokeChanged();
    Q_EMIT penChanged();
  }
}

void QnitePen::setFill(QColor fill) {
  if (m_data.fill != fill) {
    m_data.fill = fill;
    Q_EMIT fillChanged();
    Q_EMIT penChanged();
  }
}

void QnitePen::setWidth(qreal width) {
  if (qFuzzyCompare(m_data.width, width)) {
    m_data.width = width;
    Q_EMIT widthChanged();
    Q_EMIT penChanged();
  }
}

void QnitePen::setJoin(LineJoin join) {
  if (m_data.join != join) {
    m_data.join = join;
    Q_EMIT joinChanged();
    Q_EMIT penChanged();
  }
}

void QnitePen::setCap(LineCap cap) {
  if (m_data.cap != cap) {
    m_data.cap = cap;
    Q_EMIT capChanged();
    Q_EMIT penChanged();
  }
}

void QnitePen::setRadius(qreal radius) {
  if (qFuzzyCompare(m_data.radius, radius)) {
    m_data.radius = radius;
    Q_EMIT radiusChanged();
    Q_EMIT penChanged();
  }
}
