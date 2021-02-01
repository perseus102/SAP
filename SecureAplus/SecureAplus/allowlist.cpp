#include "allowlist.h"

AllowList::AllowList(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	m_layout = new QVBoxLayout();
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);

	QWidget* statusWg = new QWidget();
	statusWg->setFixedHeight(220);

	QVBoxLayout* statusLayout = new QVBoxLayout();
	statusLayout->setContentsMargins(30, 0, 40, 0);
	statusLayout->setSpacing(0);
	statusWg->setLayout(statusLayout);

	m_status = new QLabel();
	m_status->setFont(LARGE_FONT);
	m_status->setFixedHeight(20);

	QLabel* statusTopSpacer = new QLabel();
	statusTopSpacer->setFixedHeight(15);

	m_allistCreation = new AllowListStatus(AllowList_Type::Allist_Creation, AllowList_States::Allist_Building);
	m_allistCreation->setAllowListName("Allowlist Creation");
	m_allistCreation->setStatusText("Building ...");

	QLabel* allistCreationSpacer = new QLabel();
	allistCreationSpacer->setFixedHeight(10);

	m_allistService = new AllowListStatus(AllowList_Type::Allist_Service, AllowList_States::Allist_Running);
	m_allistService->setAllowListName("Application Allowlisting Service");
	m_allistService->setStatusText("Running");

	QLabel* allistServiceSpacer = new QLabel();
	allistServiceSpacer->setFixedHeight(10);

	m_allistDriver = new AllowListStatus(AllowList_Type::Allist_Driver, AllowList_States::Allist_Running);
	m_allistDriver->setAllowListName("Application Allowlisting Driver");
	m_allistDriver->setStatusText("Running");
	QLabel* statusBottom = new QLabel();

	statusLayout->addWidget(m_status);
	statusLayout->addWidget(statusTopSpacer);
	statusLayout->addWidget(m_allistCreation);
	statusLayout->addWidget(allistCreationSpacer);
	statusLayout->addWidget(m_allistService);
	statusLayout->addWidget(allistServiceSpacer);
	statusLayout->addWidget(m_allistDriver);
	statusLayout->addWidget(statusBottom);

	m_statusLine = new QLabel();
	m_statusLine->setFixedHeight(2);

	QWidget* imExportWg = new QWidget();
	imExportWg->setFixedHeight(115);
	QVBoxLayout* imExportLayout = new QVBoxLayout();
	imExportLayout->setSpacing(0);
	imExportLayout->setContentsMargins(30, 0, 0, 0);
	imExportWg->setLayout(imExportLayout);

	QLabel* imExportTopSpacer = new QLabel();
	imExportTopSpacer->setFixedHeight(15);

	m_imExport = new QLabel();
	m_imExport->setFont(LARGE_FONT);
	m_imExport->setFixedHeight(20);

	QLabel* imExportSpacer = new QLabel();
	imExportSpacer->setFixedHeight(12);

	m_imExportDesc = new QLabel();
	m_imExportDesc->setFont(SMALL_FONT);
	m_imExportDesc->setFixedHeight(15);

	QLabel* imExportDescSpacer = new QLabel();
	imExportDescSpacer->setFixedHeight(12);

	QWidget* imExportBtnWg = new QWidget();
	imExportBtnWg->setFixedHeight(28);
	QHBoxLayout* imExportBtnLayout = new QHBoxLayout();
	imExportBtnLayout->setSpacing(0);
	imExportBtnLayout->setContentsMargins(0, 0, 0, 0);
	imExportBtnWg->setLayout(imExportBtnLayout);

	m_exportAllistBtn = new QPushButton();
	m_exportAllistBtn->setFixedSize(120, 28);

	QLabel* centerBtnSpacer = new QLabel();
	centerBtnSpacer->setFixedWidth(8);

	m_importAllistBtn = new QPushButton();
	m_importAllistBtn->setFixedSize(120, 28);

	QLabel* rightBtnSpacer = new QLabel();

	imExportBtnLayout->addWidget(m_exportAllistBtn);
	imExportBtnLayout->addWidget(centerBtnSpacer);
	imExportBtnLayout->addWidget(m_importAllistBtn);
	imExportBtnLayout->addWidget(rightBtnSpacer);

	QLabel* imExportBottomSpacer = new QLabel();

	m_imExportLine = new QLabel();
	m_imExportLine->setFixedHeight(2);

	imExportLayout->addWidget(imExportTopSpacer);
	imExportLayout->addWidget(m_imExport);
	imExportLayout->addWidget(imExportSpacer);
	imExportLayout->addWidget(m_imExportDesc);
	imExportLayout->addWidget(imExportDescSpacer);
	imExportLayout->addWidget(imExportBtnWg);
	imExportLayout->addWidget(imExportBottomSpacer);


	QWidget* compactWg = new QWidget();
	compactWg->setFixedHeight(180);
	QVBoxLayout* compactLayout = new QVBoxLayout();
	compactLayout->setSpacing(0);
	compactLayout->setContentsMargins(30, 0, 0, 0);
	compactWg->setLayout(compactLayout);

	QLabel* compactTopSpacer = new QLabel();
	compactTopSpacer->setFixedHeight(15);

	m_compactAllowList = new QLabel();
	m_compactAllowList->setFont(LARGE_FONT);
	m_compactAllowList->setFixedHeight(20);

	QLabel* compactSpacer = new QLabel();
	compactSpacer->setFixedHeight(10);

	m_compactAllowListDesc = new QLabel();
	m_compactAllowListDesc->setFont(SMALL_FONT);
	m_compactAllowListDesc->setFixedHeight(15);

	QLabel* compactDescSpacer = new QLabel();
	compactDescSpacer->setFixedHeight(10);

	QWidget *slowWg = new QWidget();
	slowWg->setFixedHeight(20);
	QHBoxLayout* slowLayout = new QHBoxLayout();
	slowLayout->setSpacing(8);
	slowLayout->setContentsMargins(0, 0, 0, 0);
	slowWg->setLayout(slowLayout);

	m_slowBtn = new SAPRadioButton();
	m_slowBtn->setFixedSize(20, 20);
	m_slowBtn->setButtonChecked(Qt::Checked);

	m_slowText = new ClickableLabel();
	m_slowText->setFont(FONT);
	m_slowText->setAlignment(Qt::AlignCenter);
	setSlowText("Slow");
	QLabel* slowLeft = new QLabel();

	slowLayout->addWidget(m_slowBtn);
	slowLayout->addWidget(m_slowText);
	slowLayout->addWidget(slowLeft);

	QLabel* centerBtn = new QLabel();
	centerBtn->setFixedHeight(10);

	QWidget *fastWg = new QWidget();
	fastWg->setFixedHeight(20);

	QHBoxLayout* fastLayout = new QHBoxLayout();
	fastLayout->setSpacing(8);
	fastLayout->setContentsMargins(0, 0, 0, 0);
	fastWg->setLayout(fastLayout);

	m_fastBtn = new SAPRadioButton();
	m_fastBtn->setFixedSize(20, 20);
	m_fastBtn->setButtonChecked(Qt::Unchecked);

	m_fastText = new ClickableLabel();
	m_fastText->setFont(FONT);
	m_fastText->setAlignment(Qt::AlignCenter);
	setFastText("Fast");

	QLabel* fastLeft = new QLabel();

	fastLayout->addWidget(m_fastBtn);
	fastLayout->addWidget(m_fastText);
	fastLayout->addWidget(fastLeft);

	QLabel* compactAllistSpacer = new QLabel();
	compactAllistSpacer->setFixedHeight(15);

	m_compactAllistBtn = new QPushButton();
	m_compactAllistBtn->setFixedSize(120, 28);

	compactLayout->addWidget(compactTopSpacer);
	compactLayout->addWidget(m_compactAllowList);
	compactLayout->addWidget(compactSpacer);
	compactLayout->addWidget(m_compactAllowListDesc);
	compactLayout->addWidget(compactDescSpacer);
	compactLayout->addWidget(slowWg);
	compactLayout->addWidget(centerBtn);
	compactLayout->addWidget(fastWg);
	compactLayout->addWidget(compactAllistSpacer);
	compactLayout->addWidget(m_compactAllistBtn);

	QLabel* spacerBottom = new QLabel();

	m_layout->addWidget(statusWg);
	m_layout->addWidget(m_statusLine);

	m_layout->addWidget(imExportWg);
	m_layout->addWidget(m_imExportLine);

	m_layout->addWidget(compactWg);
	m_layout->addWidget(spacerBottom);

	setLayout(m_layout);
	setStyle();
	setLabelText();
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &AllowList::changeTheme);
	connect(m_slowBtn, &SAPRadioButton::clicked, this, &AllowList::radioButtonClicked);
	connect(m_fastBtn, &SAPRadioButton::clicked, this, &AllowList::radioButtonClicked);
	connect(m_slowText, &ClickableLabel::clicked, this, &AllowList::textClicked);
	connect(m_fastText, &ClickableLabel::clicked, this, &AllowList::textClicked);
}

AllowList::~AllowList()
{
}

void AllowList::radioButtonClicked()
{
	//switch theme
	if (sender() == m_slowBtn)
	{
		m_slowBtn->setButtonChecked(Qt::Checked);
		m_fastBtn->setButtonChecked(Qt::Unchecked);

	}
	else if (sender() == m_fastBtn)
	{
		m_slowBtn->setButtonChecked(Qt::Unchecked);
		m_fastBtn->setButtonChecked(Qt::Checked);
	}
}

void AllowList::textClicked()
{
	if (sender() == m_slowText)
	{
		m_slowBtn->setButtonChecked(Qt::Checked);
		m_fastBtn->setButtonChecked(Qt::Unchecked);

	}
	else if (sender() == m_fastText)
	{
		m_slowBtn->setButtonChecked(Qt::Unchecked);
		m_fastBtn->setButtonChecked(Qt::Checked);
	}
}

void AllowList::setSlowText(QString text)
{
	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_slowText->setFixedWidth(width);
	m_slowText->setFixedHeight(pixelsHigh);
	m_slowText->setText(text);
}

void AllowList::setFastText(QString text)
{
	QFontMetrics fm(FONT);
	int pixelsHigh = fm.height();
	int width = fm.width(text);
	m_fastText->setFixedWidth(width);
	m_fastText->setFixedHeight(pixelsHigh);
	m_fastText->setText(text);
}

void AllowList::setStyle()
{
	switch (AppSetting::getInstance()->getTheme())
	{
	case Theme_Type::Light_Theme:
		m_status->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		m_imExport->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");

		m_imExportDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_compactAllowList->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_LT + ";}");
		m_compactAllowListDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_statusLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");
		m_imExportLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_LT + ";}");

		m_slowText->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_fastText->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_exportAllistBtn->setStyleSheet("QPushButton {background-color:none; color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_importAllistBtn->setStyleSheet("QPushButton {background-color:none; color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");

		m_compactAllistBtn->setStyleSheet("QPushButton {background-color:none; color: " + TAB_CONTENT_DESC_TEXT_LT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_LT + ";}");
		break;

	case Theme_Type::Dark_Theme:
		m_status->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_imExport->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");

		m_imExportDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_compactAllowList->setStyleSheet("QLabel{ color:" + TAB_CONTENT_TITLE_TEXT_DT + ";}");
		m_compactAllowListDesc->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_statusLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_imExportLine->setStyleSheet("QLabel{ background-color:" + LINE_COLOR_DT + ";}");

		m_slowText->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_fastText->setStyleSheet("QLabel{ color:" + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_exportAllistBtn->setStyleSheet("QPushButton {background-color:none; color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_importAllistBtn->setStyleSheet("QPushButton {background-color:none; color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		m_compactAllistBtn->setStyleSheet("QPushButton {background-color:none; color: " + TAB_CONTENT_DESC_TEXT_DT + ";"
			"border-radius:2px;"
			"border: 1px solid " + TAB_CONTENT_DESC_TEXT_DT + ";}");

		break;
		//MORE THEME
	default:
		break;
	}

}

void AllowList::setLabelText()
{
	m_status->setText("Status");
	m_imExport->setText("Import / Export");
	m_imExportDesc->setText("Lorem ipsum dolor sit amit");
	m_compactAllowList->setText("Compact Allow List");
	m_compactAllowListDesc->setText("This operation will delete all allowlist which no longer have physical files on the local disk(s).");
	m_exportAllistBtn->setText("Export Allowlist");
	m_importAllistBtn->setText("Import Allowlist");
	m_compactAllistBtn->setText("Compact Allowlist");

}

void AllowList::setButtonStyle()
{

}

void AllowList::changeTheme()
{
	setStyle();
}