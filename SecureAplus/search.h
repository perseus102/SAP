#pragma once

#include <QWidget>
#include "ui_search.h"
#include <QPushButton>
#include <QLineEdit>
#include <QCompleter>
#include "define.h"
#include "appsetting.h"
#include "util.h"
#include <QAbstractItemView>
#include "sapscrollarea.h"
class SearchButton : public QPushButton
{
	Q_OBJECT
public:
	SearchButton(QWidget* parent = Q_NULLPTR);
	~SearchButton();

public slots:
	void changeTheme();

protected:
	void enterEvent(QEvent*) override;
	void leaveEvent(QEvent*) override;

private:
	void initIcon();
	QIcon icon;
};

class Search : public QWidget
{
	Q_OBJECT

public:
	Search(QWidget *parent = Q_NULLPTR);
	~Search();
private slots:
	void changeTheme();
	void updateWord(QString word);

public slots:
	void addWordList(QString word);
	void removeWordList(QString word);
signals:
	void updateFilter(QStringList list);
	void setFilter(bool isFilter);

private:
	Ui::Search ui;
	
	SearchButton*		m_searchButton;
	QLineEdit*			m_searchLabel;
	QStringListModel	m_wordListModel;
	QStringList			m_wordList;

	QVBoxLayout*	m_layout;
	QWidget*		m_searchWg;
	QCompleter*		completer;
	void setStyle();

};
