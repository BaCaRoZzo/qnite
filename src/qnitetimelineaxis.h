#ifndef QNITETIMELINEAXIS_H
#define QNITETIMELINEAXIS_H

#include "qnitelinearaxis.h"

class QniteTimelineAxis : public QniteAxis {
  Q_OBJECT
  Q_PROPERTY(QString formattingString READ formattingString WRITE
                 setFormattingString NOTIFY formattingStringChanged)
public:
  explicit QniteTimelineAxis(QQuickItem *parent = Q_NULLPTR);
  virtual ~QniteTimelineAxis() {}

  QString formattingString() const;
  void setFormattingString(QString format);

Q_SIGNALS:
  void formattingStringChanged();

public Q_SLOTS:
  virtual void processData();

protected:
  QString m_formatString;
};

#endif // QNITETIMELINEAXIS_H
