#ifndef QNITESTRIP_H
#define QNITESTRIP_H

#include "qniteline.h"

#include <QColor>

class QniteStrip : public QniteLine {
  Q_OBJECT
  Q_PROPERTY(bool continuousDrawning READ continuousDrawning WRITE
                 setContinuousDrawning NOTIFY continuousDrawningChanged)
public:
  QniteStrip(QQuickItem *parent = Q_NULLPTR);

  bool continuousDrawning() const;
  void setContinuousDrawning(bool continuousDrawning);

  QNanoQuickItemPainter *createItemPainter() const Q_DECL_OVERRIDE;

Q_SIGNALS:
  void continuousDrawningChanged();

private:
  bool m_continuousDrawning;
  // back-up painting info
  QColor m_fillColor_BackUp;
  bool m_drawStepped_Backup;
};

#endif // QNITESTRIP_H
