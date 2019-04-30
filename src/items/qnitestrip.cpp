#include "qnitestrip.h"
#include "qnanoquickitempainter.h"
#include "qnitestrippainter.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(qnitestrip, "qnite.qnitestrip")

QniteStrip::QniteStrip(QQuickItem *parent)
    : QniteLine(parent), m_continuousDrawning{false},
      m_fillColor_BackUp{QColor()}, m_drawStepped_Backup{false} {}

bool QniteStrip::continuousDrawning() const { return m_continuousDrawning; }

void QniteStrip::setContinuousDrawning(bool continuousDrawning) {
  if (continuousDrawning != m_continuousDrawning) {
    m_continuousDrawning = continuousDrawning;
    Q_EMIT continuousDrawningChanged();
    // override default setting for continuous drawning
    if (m_continuousDrawning) {
      m_drawStepped_Backup = drawStepped();
      m_fillColor_BackUp = pen()->fill();
      setDrawStepped(true);
      pen()->setFill(QColor());
    } else {
      setDrawStepped(m_drawStepped_Backup);
      pen()->setFill(m_fillColor_BackUp);
    }
    update();
  }
}

QNanoQuickItemPainter *QniteStrip::createItemPainter() const {
  qCDebug(qnitestrip) << "creating item painter";
  return new QniteStripPainter();
}
