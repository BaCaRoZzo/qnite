#ifndef QNITE_AXIS_H
#define QNITE_AXIS_H

#include <QQuickItem>

class QniteMapper;
class QniteTicker;
class QniteAxisTick: public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal thick READ thick WRITE setThick NOTIFY thickChanged)
    Q_PROPERTY(qreal majSize READ majSize WRITE setMajSize NOTIFY majSizeChanged)
    Q_PROPERTY(qreal minSize READ minSize WRITE setMinSize NOTIFY minSizeChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
  public:
    explicit QniteAxisTick(QObject* parent = 0);
    virtual ~QniteAxisTick();

    qreal thick() const;
    void setThick(qreal thick);
    qreal majSize() const;
    void setMajSize(qreal size);
    qreal minSize() const;
    void setMinSize(qreal size);

    QColor color() const;
    void setColor(const QColor& color);

  Q_SIGNALS:
    void thickChanged();
    void majSizeChanged();
    void minSizeChanged();
    void colorChanged();

  private:
    qreal m_thick;
    qreal m_majSize;
    qreal m_minSize;
    QColor m_color;
};

class QniteAxis: public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal lowerBound READ lowerBound WRITE setLowerBound NOTIFY lowerBoundChanged)
    Q_PROPERTY(qreal upperBound READ upperBound WRITE setUpperBound NOTIFY upperBoundChanged)

    Q_PROPERTY(QniteAxisTick* tick READ tick CONSTANT)
    Q_PROPERTY(QniteMapper* mapper READ mapper WRITE setMapper NOTIFY mapperChanged)
    Q_PROPERTY(QniteTicker* ticker READ ticker CONSTANT)

    Q_PROPERTY(QList<qreal> majorTicks READ majorTicks NOTIFY majorTicksChanged)

  public:
    explicit QniteAxis(QQuickItem* parent = 0);
    virtual ~QniteAxis();

    qreal lowerBound() const;
    void setLowerBound(qreal bound);
    qreal upperBound() const;
    void setUpperBound(qreal bound);

    QniteAxisTick* tick() const;
    QniteTicker* ticker() const;

    QList<qreal> majorTicks() const;

    QniteMapper* mapper() const;
    void setMapper(QniteMapper* mapper);

  Q_SIGNALS:
    void lowerBoundChanged();
    void upperBoundChanged();

    void mapperChanged();
    void majorTicksChanged();

  protected Q_SLOTS:
    void initTicker();

  private:
    qreal m_lowerBound;
    qreal m_upperBound;

    QniteAxisTick* m_tick;
    QniteMapper* m_mapper;
    QniteTicker* m_ticker;

    QList<qreal> m_majorTicks;
};

#endif // QNITE_AXIS_H
