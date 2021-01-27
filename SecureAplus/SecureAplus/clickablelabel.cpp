#include "clickablelabel.h"
#include <qDebug>
ClickableLabel::ClickableLabel(QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);
}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent * event)
{
	Q_UNUSED(event);
	emit clicked();
}
