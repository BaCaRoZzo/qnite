#include "qniteticker.h"

#define DEFAULT_NUM_STEPS 0
#define DEFAULT_LOWER_B 0
#define DEFAULT_UPPER_B 0

/*!
  \qmltype Ticker
  \instantiates QniteTicker
  \ingroup scaling
  \inqmlmodule Qnite
  \brief Divide axes scales into tickers

TODO: add a long description
*/
QniteTicker::QniteTicker(QObject *parent)
    : QObject(parent), m_lowerBound{DEFAULT_LOWER_B},
      m_upperBound{DEFAULT_UPPER_B}, m_numSteps{DEFAULT_NUM_STEPS} {}

QList<qreal> QniteTicker::values() const { return m_values; }

void QniteTicker::setValues(const QList<qreal> &values) {
  if (m_values != values) {

    m_values = values;
    Q_EMIT valuesChanged();

    // compute min and max bounds
    std::sort(m_values.begin(), m_values.end(), std::less<qreal>());
    setBoundaries(m_values.first(), m_values.last());
  }
}

QList<qreal> QniteTicker::minorTicks() const { return m_minorTicks; }

void QniteTicker::setMinorTicks(const QList<qreal> &ticks) {
  if (m_minorTicks != ticks) {
    m_minorTicks = ticks;
    Q_EMIT minorTicksChanged();
  }
}

const QList<qreal> &QniteTicker::majorTicks() const { return m_majorTicks; }

void QniteTicker::setMajorTicks(const QList<qreal> &ticks) {
  if (m_majorTicks != ticks) {
    m_majorTicks = ticks;
    Q_EMIT majorTicksChanged();
  }
}

void QniteTicker::setNumSteps(int steps) {
  if (m_numSteps != steps) {
    m_numSteps = steps;
    Q_EMIT numStepsChanged();

    // ticks need to be rebuilt
    doBuildTicks();
  }
}

void QniteTicker::setBoundaries(qreal lower, qreal upper) {
  bool modified = false;

  if (!qFuzzyCompare(m_lowerBound, lower)) {
    m_lowerBound = lower;
    modified = true;
  }

  if (!qFuzzyCompare(m_upperBound, upper)) {
    m_upperBound = upper;
    modified = true;
  }

  if (modified) {
    Q_EMIT boundariesChanged();

    // ticks need to be rebuilt
    doBuildTicks();
  }
}

void QniteTicker::reset() {
  m_lowerBound = DEFAULT_LOWER_B;
  m_upperBound = DEFAULT_UPPER_B;
  m_numSteps = DEFAULT_NUM_STEPS;
  m_values.clear();
  m_minorTicks.clear();
  m_majorTicks.clear();
}

QList<qreal> QniteTicker::boundaries() const {
  QList<qreal> ret;
  ret << m_lowerBound << m_upperBound;
  return ret;
}

void QniteTicker::doBuildTicks() {
  buildTicks();
  Q_EMIT tickersBuilt();
}
