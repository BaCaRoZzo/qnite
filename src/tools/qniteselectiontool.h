#ifndef QNITESELECTIONTOOL_H
#define QNITESELECTIONTOOL_H

#include "qnitetool.h"

class QniteArtist;
class QniteSelectionTool : public QniteTool {
  Q_OBJECT

public:
  explicit QniteSelectionTool(QQuickItem *parent = Q_NULLPTR);
  virtual ~QniteSelectionTool() {}
  Q_INVOKABLE void reset();

protected:
  void select();
  void clearSelection();
  virtual bool doSelect(QniteArtist *) = 0;
};

#endif // QNITESELECTIONTOOL_H
