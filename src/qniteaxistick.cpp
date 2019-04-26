#include "qniteaxistick.h"

/*! TODO: add docs
 */
QniteAxisTick::QniteAxisTick(QObject *parent)
    : QObject(parent), m_thick{0}, m_majSize{0}, m_minSize{0} {}

QniteAxisTick::~QniteAxisTick() {}

qreal QniteAxisTick::thick() const { return m_thick; }

void QniteAxisTick::setThick(qreal thick) {
  if (!qFuzzyCompare(m_thick, thick)) {
    m_thick = thick;
    Q_EMIT thickChanged();
  }
}

qreal QniteAxisTick::majSize() const { return m_majSize; }

void QniteAxisTick::setMajSize(qreal size) {
  if (!qFuzzyCompare(m_majSize, size)) {
    m_majSize = size;
    Q_EMIT majSizeChanged();
  }
}

qreal QniteAxisTick::minSize() const { return m_minSize; }

void QniteAxisTick::setMinSize(qreal size) {
  if (!qFuzzyCompare(m_minSize, size)) {
    m_minSize = size;
    Q_EMIT minSizeChanged();
  }
}

QColor QniteAxisTick::color() const { return m_color; }

void QniteAxisTick::setColor(const QColor &color) {
  if (m_color != color) {
    m_color = color;
    Q_EMIT colorChanged();
  }
}
