#include "qnitestrip.h"
#include "qnanoquickitempainter.h"
#include "qnitestrippainter.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(qnitestrip, "qnite.qnitestrip")

QniteStrip::QniteStrip(QQuickItem *parent)
    : QniteLine(parent), m_continuousDrawning{false} {}

bool QniteStrip::continuousDrawning() const { return m_continuousDrawning; }

void QniteStrip::setContinuousDrawning(bool continuousDrawning) {
  if (continuousDrawning != m_continuousDrawning) {
    m_continuousDrawning = continuousDrawning;
    Q_EMIT continuousDrawningChanged();
    update();
  }
}

QNanoQuickItemPainter *QniteStrip::createItemPainter() const {
  qCDebug(qnitestrip) << "creating item painter";
  return new QniteStripPainter();
}
