#include "qnitestrippainter.h"
#include "qniteaxes.h"
#include "qniteaxis.h"
#include "qnitemapper.h"
#include "qnitestrip.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(qnitestrippainter, "qnite.qnitestrippainter")

QniteStripPainter::QniteStripPainter()
    : m_continuousDrawning{true}, m_xBoundValue{0.0},
      m_fillColor_BackUp{QColor()}, m_drawStepped_Backup{false} {}

void QniteStripPainter::synchronize(QNanoQuickItem *item) {
  qCDebug(qnitestrippainter) << "synchronizing qniteline";

  QniteLinePainter::synchronize(item);

  auto stripItem = static_cast<QniteStrip *>(item);
  if (stripItem != Q_NULLPTR) {
    m_xBoundValue = stripItem->width();
    m_continuousDrawning = stripItem->continuousDrawning();
  }
}

void QniteStripPainter::paint(QNanoPainter *painter) {
  qCDebug(qnitestrippainter) << "painting qniteline";

  auto &pen = m_selected ? m_selectedPen : m_pen;
  if (m_continuousDrawning) {
    // overriding base class settings to match strip line behaviour
    m_fillColor_BackUp = pen.fill;
    pen.fill = QColor();
    m_drawStepped_Backup = m_drawStepped;
    m_drawStepped = true;
  } else {
    m_drawStepped = m_drawStepped_Backup;
    pen.fill = m_fillColor_BackUp;
  }

  QniteLinePainter::paint(painter);

  // add line to the end of the graph
  if (m_continuousDrawning) {
    painter->beginPath();
    painter->moveTo(float(m_xs.last()), float(m_ys.last()));
    painter->lineTo(float(m_xBoundValue), float(m_ys.last()));
    painter->stroke();
  }
}
