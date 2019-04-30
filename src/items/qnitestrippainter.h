#ifndef QNITESTRIPPAINTER_H
#define QNITESTRIPPAINTER_H

#include "qnitelinepainter.h"

class QniteStripPainter : public QniteLinePainter {
public:
  QniteStripPainter();

  void synchronize(QNanoQuickItem *item) Q_DECL_OVERRIDE;
  void paint(QNanoPainter *painter) Q_DECL_OVERRIDE;

private:
  // draw stepped flag
  bool m_continuousDrawning;
  qreal m_xBoundValue;
};

#endif // QNITESTRIPPAINTER_H
