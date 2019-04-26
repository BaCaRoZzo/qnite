#include "qniteline.h"
#include "qniteaxes.h"
#include "qniteaxis.h"
#include "qnitelinepainter.h"

#include <QLoggingCategory>
#include <QSGNode>

Q_LOGGING_CATEGORY(qniteline, "qnite.line")

constexpr auto SELECTION_TOLERANCE = 50;

QniteLine::QniteLine(QQuickItem *parent)
    : QniteXYArtist(parent), m_selected{false}, m_drawSymbols{true},
      m_drawStepped{false} {}

/*!
  Temporary implementation of the selection logic for lines.

TODO: fix the implementation
TODO: can we assume data is alwayws already mapped at this point?
*/
bool QniteLine::select(QPoint p) {
  bool accepted = false;

  // get the distance from the first point on the path
  int dataSize = xMapped().size();
  for (int i = 0; i < dataSize; ++i) {
    QPoint cp(static_cast<int>(xMapped().at(i)),
              static_cast<int>(yMapped().at(i)));
    QPoint d = p - cp;
    if (d.manhattanLength() < SELECTION_TOLERANCE) {
      m_selected = true;
      accepted = true;
      axes()->setOnTop(this);
      Q_EMIT selectedChanged();
      update();
      break;
    }
  }

  return accepted;
}

bool QniteLine::select(const QList<QPoint> &path) {
  if (path.size()) {
    return select(path.first());
  }

  return false;
}

void QniteLine::clearSelection() {
  m_selected = false;
  Q_EMIT selectedChanged();
  update();
}

void QniteLine::setDrawSymbols(bool drawSymbols) {
  if (this->m_drawSymbols != drawSymbols) {
    this->m_drawSymbols = drawSymbols;
    Q_EMIT drawSymbolsChanged();
    update();
  }
}

void QniteLine::setDrawStepped(bool drawStepped) {
  if (this->m_drawStepped != drawStepped) {
    this->m_drawStepped = drawStepped;
    Q_EMIT drawSteppedChanged();
    update();
  }
}

QNanoQuickItemPainter *QniteLine::createItemPainter() const {
  qCDebug(qniteline) << "creating item painter";
  return new QniteLinePainter();
}
