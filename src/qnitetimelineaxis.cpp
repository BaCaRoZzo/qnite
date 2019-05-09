#include <QDateTime>

#include "qniteclipper.h"
#include "qnitelinearmapper.h"
#include "qnitelinearticker.h"
#include "qnitetimelineaxis.h"

QniteTimelineAxis::QniteTimelineAxis(QQuickItem *parent)
    : QniteAxis(parent), m_formatString("hh:mm:ss") {
  setMapper(new QniteLinearMapper(this));
  setTicker(new QniteLinearTicker(this));
}

QString QniteTimelineAxis::formattingString() const { return m_formatString; }
void QniteTimelineAxis::setFormattingString(QString format) {
  if (m_formatString != format) {
    m_formatString = format;
    Q_EMIT formattingStringChanged();
  }
}

void QniteTimelineAxis::processData() {
  // avoid ticker initialization when mapper is invalid
  if (m_mapper == nullptr) {
    m_ticker->reset();
  } else {
    m_ticker->setBoundaries(m_lowerBound, m_upperBound);

    m_majorTicks.clear();
    m_minorTicks.clear();
    m_labels.clear();

    // TODO: encapsulate in transformer pipeline
    // clip ticks
    QList<qreal> maj, min;
    QniteClipper clipper;
    clipper.clip(m_ticker->majorTicks(), m_lowerBound, m_upperBound, maj);
    clipper.clip(m_ticker->minorTicks(), m_lowerBound, m_upperBound, min);

    // map to display
    for (auto v : maj) {
      m_majorTicks << m_mapper->mapTo(m_lowerBound, m_upperBound, 0, m_size, v,
                                      m_flip);
    }
    for (auto v : min) {
      m_minorTicks << m_mapper->mapTo(m_lowerBound, m_upperBound, 0, m_size, v,
                                      m_flip);
    }

    for (auto i = 0; i < maj.size(); ++i) {
      m_labels.push_back(QDateTime::fromMSecsSinceEpoch(int(maj.at(i)))
                             .toString(m_formatString));
    }

    // maps the axis position
    m_position =
        m_mapper->mapTo(m_lowerBound, m_upperBound, 0., m_size, 0., m_flip);
  }

  emit labelsChanged();
  emit majorTicksChanged();
  emit minorTicksChanged();
}
