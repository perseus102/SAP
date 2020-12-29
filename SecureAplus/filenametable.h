#pragma once

#include <QWidget>
#include "ui_filenametable.h"

class FileNameTable : public QWidget
{
	Q_OBJECT

public:
	FileNameTable(QWidget *parent = Q_NULLPTR);
	~FileNameTable();

private:
	Ui::FileNameTable ui;
};
