#include "qniteaxis.h"

/*! TODO: add docs
 */
QniteAxis::QniteAxis(QQuickItem *parent)
    : QniteArtist(parent), m_size{0}, m_lowerBound{0}, m_upperBound{0},
      m_flip{false}, m_position{0}, m_mapper{nullptr}, m_ticker{nullptr} {}

void QniteAxis::setSize(qreal size) {
  if (!qFuzzyCompare(m_size, size)) {
    m_size = size;
    Q_EMIT sizeChanged();

    processData();
  }
}

void QniteAxis::setLowerBound(qreal bound) {
  if (!qFuzzyCompare(m_lowerBound, bound)) {
    m_lowerBound = bound;
    Q_EMIT lowerBoundChanged();

    processData();
  }
}

void QniteAxis::setUpperBound(qreal bound) {
  if (!qFuzzyCompare(m_upperBound, bound)) {
    m_upperBound = bound;
    Q_EMIT upperBoundChanged();

    processData();
  }
}

void QniteAxis::setFlip(bool flip) {
  if (m_flip != flip) {
    m_flip = flip;
    Q_EMIT flipChanged();

    processData();
  }
}

void QniteAxis::setTicker(QniteTicker *ticker) {
  if (m_ticker != ticker) {
    m_ticker = ticker;
    Q_EMIT tickerChanged();
  }
}

void QniteAxis::setMapper(QniteMapper *mapper) {
  if (m_mapper != mapper) {
    m_mapper = mapper;
    Q_EMIT mapperChanged();
  }
}

QList<qreal> QniteAxis::majorTicks() const { return m_majorTicks; }

QList<qreal> QniteAxis::minorTicks() const { return m_minorTicks; }

qreal QniteAxis::position() const { return m_position; }
