#include "qnitexyartist.h"
#include "qniteaxes.h"
#include "qniteaxis.h"
#include "qniteclipper.h"
#include "qnitemapper.h"

QniteXYArtist::QniteXYArtist(QQuickItem *parent)
    : QniteArtist(parent), m_clipper{nullptr}, m_xMapper{nullptr},
      m_yMapper{nullptr} {}

QniteXYArtist::~QniteXYArtist() {}

const QList<qreal> &QniteXYArtist::xValues() { return m_xValues; }

void QniteXYArtist::setXValues(const QList<qreal> &values) {
  if (m_xValues != values) {
    m_xValues = values;
    // TODO: transform the values here and cache
    emit xValuesChanged();
    update();

    // clear the current selection after any changes on X values
    clearSelection();
  }
}

const QList<qreal> &QniteXYArtist::yValues() { return m_yValues; }

void QniteXYArtist::setYValues(const QList<qreal> &values) {
  if (m_yValues != values) {
    m_yValues = values;
    // TODO: transform the values here and cache
    emit yValuesChanged();
    update();

    // clear the current selection after any changes on Y values
    clearSelection();
  }
}

QniteMapper *QniteXYArtist::xMapper() const { return m_xMapper; }

void QniteXYArtist::setXMapper(QniteMapper *mapper) {
  // TODO: when the mapper is set we should
  // connect to its factorChanged event and trigger an update
  // and disconnect the previous one
  if (mapper != m_xMapper) {
    m_xMapper = mapper;
    // TODO: emit a signal??
  }
}

QniteMapper *QniteXYArtist::yMapper() const { return m_yMapper; }

void QniteXYArtist::setYMapper(QniteMapper *mapper) {
  // TODO: when the mapper is set we should
  // connect to its factorChanged event and trigger an update
  // and disconnect the previous one
  if (mapper != m_yMapper) {
    m_yMapper = mapper;
    // TODO: emit a signal??
  }
}

QniteClipper *QniteXYArtist::clipper() const { return m_clipper; }

void QniteXYArtist::setClipper(QniteClipper *clipper) {
  if (m_clipper != clipper) {
    m_clipper = clipper;
    // TODO: signal????
  }
}

const QList<qreal> &QniteXYArtist::xMapped() const { return m_xMapped; }

const QList<qreal> &QniteXYArtist::yMapped() const { return m_yMapped; }

const QList<qreal> &QniteXYArtist::xProcessed() const { return m_xProcessed; }

const QList<qreal> &QniteXYArtist::yProcessed() const { return m_yProcessed; }

void QniteXYArtist::processData() {
  if (qMin(xValues().size(), yValues().size()) < 1) {
    return;
  }

  // get bounds
  qreal xLower = axes()->axisX()->lowerBound();
  qreal xUpper = axes()->axisX()->upperBound();
  qreal yLower = axes()->axisY()->lowerBound();
  qreal yUpper = axes()->axisY()->upperBound();

  // TODO: this should be improved. clipping should be done only when bounds
  // changes and transform should always be performed
  QList<qreal> xClipped;
  QList<qreal> yClipped;
  // clip non visible data
  if (clipper() != nullptr) {
    clipper()->clip(xValues(), yValues(), xLower, xUpper, yLower, yUpper,
                    xClipped, yClipped);
  } else {
    xClipped = xValues();
    yClipped = yValues();
  }

  // map to display
  m_xMapped = xMapper()->mapTo(xLower, xUpper, 0, width(), xClipped);
  m_yMapped = yMapper()->mapTo(yLower, yUpper, 0, height(), yClipped, true);

  // TODO: this is ugly and inefficient; move into a pipeline or something
  // similar move to the output area
  m_xProcessed = m_xMapped;
  m_yProcessed = m_yMapped;
}

void QniteXYArtist::updateAxes() {
  QniteArtist::updateAxes();

  QniteAxes *axes = this->axes();
  if (axes != nullptr) {
    // TODO: find a better way to handle axis bindings
    if (axes->axisX() != nullptr)
      this->setXMapper(axes->axisX()->mapper());

    if (axes->axisY() != nullptr)
      this->setYMapper(axes->axisY()->mapper());

    disconnect(axes, SIGNAL(axisXChanged()), this, 0);
    disconnect(axes, SIGNAL(axisYChanged()), this, 0);

    connect(axes, &QniteAxes::axisXChanged, this,
            [=]() { this->setXMapper(axes->axisX()->mapper()); });
    connect(axes, &QniteAxes::axisYChanged, this,
            [=]() { this->setYMapper(axes->axisY()->mapper()); });
  }
}
