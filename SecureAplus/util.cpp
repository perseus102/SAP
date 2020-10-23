#include "util.h"

util* util::m_instance = nullptr;

util * util::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new util();
	}

	return m_instance;
}

util::util()
{

}

util::~util()
{
}

QIcon util::ChangeSVGColor(QString svgPath, QString Color)
{
	// open svg resource load contents to qbytearray
	QFile file(svgPath);
	file.open(QIODevice::ReadOnly);
	QByteArray baData = file.readAll();
	// load svg contents to xml document and edit contents
	QDomDocument doc;
	doc.setContent(baData);
	// recurivelly change color
	SetAttrRecur(doc.documentElement(), "path", "fill", Color);
	// create svg renderer with edited contents
	QSvgRenderer svgRenderer(doc.toByteArray());
	// create pixmap target (could be a QImage)
	QPixmap pix(svgRenderer.defaultSize());
	pix.fill(Qt::transparent);
	// create painter to act over pixmap
	QPainter pixPainter(&pix);
	// use renderer to render over painter which paints on pixmap
	svgRenderer.render(&pixPainter);
	QIcon icon(pix);

	return icon;
}

void util::SetAttrRecur(QDomElement elem, QString strtagname, QString strattr, QString strattrval)
{
	// if it has the tagname then overwritte desired attribute
	if (elem.tagName().compare(strtagname) == 0)
	{
		elem.setAttribute(strattr, strattrval);
	}
	// loop all children
	for (int i = 0; i < elem.childNodes().count(); i++)
	{
		if (!elem.childNodes().at(i).isElement())
		{
			continue;
		}
		SetAttrRecur(elem.childNodes().at(i).toElement(), strtagname, strattr, strattrval);
	}
}

