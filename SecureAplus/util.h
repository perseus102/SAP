#pragma once
#include <QtXml>
#include <QSvgRenderer>
#include <QWidget>
#include <qDebug>
#include <QVBoxLayout>
#include <QLabel>
#include "Config.h"
#include "define.h"
#include <QIcon>
#include <QPainter>

class util
{
public:
	static util* getInstance();
	~util();

	QIcon ChangeSVGColor(QString  svgPath, QString Color);

	void SetAttrRecur(QDomElement  elem, QString strtagname, QString strattr, QString strattrval);

private:
	util();
	static util* m_instance;

};

