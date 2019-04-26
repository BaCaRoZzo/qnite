#ifndef QNITE_LINEAR_AXIS_H
#define QNITE_LINEAR_AXIS_H

#include "qniteaxis.h"

class QniteLinearAxis : public QniteAxis {
public:
  explicit QniteLinearAxis(QQuickItem *parent = Q_NULLPTR);
  virtual ~QniteLinearAxis() {}

public Q_SLOTS:
  virtual void processData();
};

#endif // QNITE_LINEAR_AXIS_H
