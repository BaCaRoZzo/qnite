#ifndef QNITE_SELECT_TOOL_H
#define QNITE_SELECT_TOOL_H

#include "qniteselectiontool.h"

class QnitePen;
class QniteArtist;
class QnitePathSelectionTool : public QniteSelectionTool {
  Q_OBJECT
  Q_PROPERTY(
      QVariantList selectionPath READ selectionPath NOTIFY selectionPathChanged)
  Q_PROPERTY(QnitePen *pen READ pen CONSTANT)

public:
  explicit QnitePathSelectionTool(QQuickItem *parent = Q_NULLPTR);
  virtual ~QnitePathSelectionTool() Q_DECL_OVERRIDE {}

  QVariantList selectionPath() const;

  QnitePen *pen() const { return m_pen; }

  virtual void begin(const QPoint &point);
  virtual void append(const QPoint &point);
  virtual void end();

  QNanoQuickItemPainter *createItemPainter() const Q_DECL_OVERRIDE;

Q_SIGNALS:
  void selectionPathChanged();

protected:
  virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
  virtual bool doSelect(QniteArtist *) Q_DECL_OVERRIDE;

  //  QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);

  QList<QPoint> m_selection;

private:
  friend class QnitePathPainter;

  QnitePen *m_pen;
};

#endif // QNITE_SELECT_TOOL_H
