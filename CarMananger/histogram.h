#ifndef HISTOGRAM_H
#define HISTOGRAM_H

// Histogram.h 柱状图类的声明
// 名词解释：Histogram 柱状图
// pillar 柱子

#include <QVector>
#include <QWidget>

// 前向声明
QT_BEGIN_NAMESPACE
class QColor;
class QRect;
class QString;
class QPaintDevice;
QT_END_NAMESPACE

class HistogramItem
{
public:
	QString m_Name;
	qreal	m_Value;
	QColor	m_PillarColor;
	QRect	m_PillarRect;
};

class Histogram : public QWidget
{
public:
    Histogram( QWidget* parent = 0 );
	void AddItem( QString name, qreal value,
				  QColor pillarColor );
	void SetMaxValue( quint32 maxValue );	// 设置最大值，以便绘图
	void Paint( QPaintDevice* pDevice );	// 绘图
    void Clear();   // 清空所有已添加的Item

protected:
    void paintEvent(QPaintEvent *);

private:
    void DrawAxis( QPaintDevice* pDevice, QPainter* pPainter );     // 绘制坐标轴
	void DrawPillars( QPaintDevice* pDevice, QPainter* pPainter );	// 绘制柱子
	void DrawText( QPainter *pPainter );		// 绘制文字
	void DrawScale( QPaintDevice* pDevice, QPainter* pPainter );	// 绘制刻度

	enum HistogramOptions
	{
		blankWidth		= 64,		// 两个柱子间的空格大小
		pillarIndent	= 0,		// 首个柱子缩进的大小
		xAxisOffset		= 16,		// X轴的偏移（相对于左边界）
		yAxisOffset		= 16,		// Y轴的偏移（相对于下边界）
		textRectHeight	= 32		// 文字矩形框的高
    };

	qreal							m_MaxValue;
	QVector<HistogramItem>			m_VecItems;
};

#endif // HISTOGRAM_H
