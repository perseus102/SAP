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

private:
	Ui::Search ui;
	
	SearchButton*	m_searchButton;
	QLineEdit*		m_searchLabel;
	QStringListModel m_wordList;
	QVBoxLayout*	m_layout;
	QWidget*		m_searchWg;
	QCompleter *completer;
	void setStyle();
	
};
