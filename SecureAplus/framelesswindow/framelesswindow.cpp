#include "framelesswindow.h"
FramelessWindow::FramelessWindow(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::FramelessWindow),
	m_bMousePressed(false),
	m_bDragTop(false),
	m_bDragLeft(false),
	m_bDragRight(false),
	m_bDragBottom(false) {
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
	// append minimize button flag in case of windows,
	// for correct windows native handling of minimize function
#if defined(Q_OS_WIN)
	setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);
#endif
	setAttribute(Qt::WA_NoSystemBackground, true);
	setAttribute(Qt::WA_TranslucentBackground);

	ui->setupUi(this);
	ui->restoreButton->setVisible(false);

	// shadow under window title text
	QGraphicsDropShadowEffect *textShadow = new QGraphicsDropShadowEffect;
	textShadow->setBlurRadius(4.0);
	textShadow->setColor(QColor(0, 0, 0));
	textShadow->setOffset(0.0);
	ui->titleText->setGraphicsEffect(textShadow);
	// window shadow
	QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
	windowShadow->setBlurRadius(9.0);
	windowShadow->setColor(palette().color(QPalette::Highlight));
	windowShadow->setOffset(0.0);
	ui->windowFrame->setGraphicsEffect(windowShadow);

	if (AppSetting::getInstance()->getManagedByServer())
	{
		ui->managedServer->setFont(SMALL_FONT);
		//ui->managedServer->setAlignment(Qt::AlignLeft);
		ui->managedServer->setText(" (Managed by Management Server)");
		ui->managedServer->setVisible(true);
		ui->managedServer->setStyleSheet("QLabel{color: " +MANAGED_BY_SERVER_LTDT +"}");
	}

	QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this,
		&FramelessWindow::on_applicationStateChanged);
	setMouseTracking(true);

	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &FramelessWindow::changeTheme);

	connect(AppSetting::getInstance(), &AppSetting::signal_getAppGeometry, this, &FramelessWindow::setAppGeometry);
	// important to watch mouse move from all child widgets
	QApplication::instance()->installEventFilter(this);

	setWindowIcon();
}

FramelessWindow::~FramelessWindow() { delete ui; }

void FramelessWindow::on_restoreButton_clicked() {
	ui->restoreButton->setVisible(false);

	ui->maximizeButton->setVisible(true);

	setWindowState(Qt::WindowNoState);
	AppSetting::getInstance()->setFullScreen(false);
	hide();
	show();
}

void FramelessWindow::on_maximizeButton_clicked() {
	ui->restoreButton->setVisible(true);
	ui->maximizeButton->setVisible(false);
	this->setWindowState(Qt::WindowMaximized);
	this->showMaximized();
	styleWindow(true, false);
	AppSetting::getInstance()->setFullScreen(true);

}

void FramelessWindow::changeEvent(QEvent *event) {
	if (event->type() == QEvent::WindowStateChange) {
		if (windowState().testFlag(Qt::WindowNoState)) {
			ui->restoreButton->setVisible(false);
			ui->maximizeButton->setVisible(true);
			styleWindow(true, true);
			event->ignore();
		}
		else if (windowState().testFlag(Qt::WindowMaximized)) {
			ui->restoreButton->setVisible(true);
			ui->maximizeButton->setVisible(false);
			styleWindow(true, false);
			event->ignore();
		}
	}
	event->accept();
}

void FramelessWindow::setContent(QWidget *w) {
	ui->windowContent->layout()->addWidget(w);
}

void FramelessWindow::setWindowTitle(const QString &text) {
	ui->titleText->setText(text);
}

void FramelessWindow::setWindowIcon() {
	QIcon AppIcon(APP_ICON);
	QIcon titleTextIcon(TITLE_TEXT_ICON);
	ui->icon->setPixmap(AppIcon.pixmap(30, 30));
	ui->icon->setAlignment(Qt::AlignCenter);
	ui->titleText->setPixmap(titleTextIcon.pixmap(78, 17));


}

void FramelessWindow::styleWindow(bool bActive, bool bNoState) {
	
	/* Get background color from file */
	QString background_color = getBackroundColor();
	/* Active window */
	if (bActive) {
		if (bNoState) {
			layout()->setMargin(15);
			ui->windowTitlebar->setStyleSheet(
				"#windowTitlebar{border: 0px none palette(shadow); "
				"border-top-left-radius:0px; border-top-right-radius:5px;"
				"background-color:" + background_color + ";}");
			ui->windowFrame->setStyleSheet(
				"#windowFrame{border:1px solid palette(highlight);" 
				"border-radius:0px 0px 0px 0px;"
				"background-color:" + background_color + ";}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow) delete oldShadow;
			QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
			windowShadow->setBlurRadius(9.0);
			windowShadow->setColor(palette().color(QPalette::Highlight));
			windowShadow->setOffset(0.0);
			ui->windowFrame->setGraphicsEffect(windowShadow);
		}
		else {
			layout()->setMargin(0);
			ui->windowTitlebar->setStyleSheet(
				"#windowTitlebar{border: 0px none palette(shadow); "
				"border-top-left-radius:0px; border-top-right-radius:0px;"
				"background-color:" + background_color + ";}");
			ui->windowFrame->setStyleSheet(
				"#windowFrame{border:1px solid palette(dark);"
				"border-radius:0px 0px 0px 0px;"
				"background-color:" + background_color + ";}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow) delete oldShadow;
			ui->windowFrame->setGraphicsEffect(nullptr);
		}  // if (bNoState) else maximize
	}
	/* Unactive window */
	else {
		if (bNoState) {
			layout()->setMargin(15);
			ui->windowTitlebar->setStyleSheet(
				"#windowTitlebar{border: 0px none palette(shadow);"
				"border-top-left-radius:5px; border-top-right-radius:5px;"
				"background-color:" + background_color + ";}");
			ui->windowFrame->setStyleSheet(
				"#windowFrame{border:1px solid #000000; border-radius:0px 0px 0px 0px;"
				"background-color:" + background_color + ";}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow) delete oldShadow;
			QGraphicsDropShadowEffect *windowShadow = new QGraphicsDropShadowEffect;
			windowShadow->setBlurRadius(9.0);
			windowShadow->setColor(palette().color(QPalette::Shadow));
			windowShadow->setOffset(0.0);
			ui->windowFrame->setGraphicsEffect(windowShadow);
		}
		else {
			layout()->setMargin(0);
			ui->windowTitlebar->setStyleSheet(
				"#titlebarWidget{border: 0px none palette(shadow); "
				"border-top-left-radius:0px; border-top-right-radius:0px; "
				"background-color:" + background_color + ";}");
			ui->windowFrame->setStyleSheet(
				"#windowFrame{border:1px solid palette(shadow); border-radius:0px 0px 0px 0px;"
				"background-color:" + background_color + ";}");
			QGraphicsEffect *oldShadow = ui->windowFrame->graphicsEffect();
			if (oldShadow) delete oldShadow;
			ui->windowFrame->setGraphicsEffect(nullptr);
		}  // if (bNoState) { else maximize
	}    // if (bActive) { else no focus


	/* Set style for title bar button */
	ui->helpButton->setStyleSheet("#helpButton{background-color:none;"
		"border:none; width:44px; height:30px; padding:4px;"
		"image:url("+ HELP_ICON +");}"
		"#helpButton:hover:!pressed {border: 1px solid" + background_color + ";}");

	ui->minimizeButton->setStyleSheet("#minimizeButton{background-color:none;"
		"border:none; width:30px; height:30px; padding:4px;"
		"image:url(" + MINIMIZE_ICON + ");}"
		"#minimizeButton:hover:!pressed {border: 1px solid" + background_color + ";}");

	ui->restoreButton->setStyleSheet("#restoreButton{background-color:none;"
		"border:none; width:30px; height:30px; padding:4px;"
		"image:url(" + RESTORE_ICON + ");}"
		"#restoreButton:hover:!pressed {border: 1px solid" + background_color + ";}");

	ui->maximizeButton->setStyleSheet("#maximizeButton{background-color:none;"
		"border:none; width:30px; height:30px; padding:4px;"
		"image:url(" + MAXIMIZE_ICON + ");}"
		"#maximizeButton:hover:!pressed {border: 1px solid" + background_color + ";}");

	ui->closeButton->setStyleSheet("#closeButton{background-color:none;"
		"border:none; width:30px; height:30px; padding:4px;"
		"image:url(" + CLOSE_ICON + ");}"
		"#closeButton:hover:!pressed {border: 1px solid" + background_color + ";}");

}

void FramelessWindow::on_applicationStateChanged(Qt::ApplicationState state) {
	if (windowState().testFlag(Qt::WindowNoState)) {
		if (state == Qt::ApplicationActive) {
			styleWindow(true, true);
		}
		else {
			styleWindow(false, true);
		}
	}
	else if (windowState().testFlag(Qt::WindowFullScreen)) {
		if (state == Qt::ApplicationActive) {
			styleWindow(true, false);
		}
		else {
			styleWindow(false, false);
		}
	}
}

void FramelessWindow::on_minimizeButton_clicked() {
	setWindowState(Qt::WindowMinimized);
}

void FramelessWindow::on_closeButton_clicked() { close(); }

void FramelessWindow::on_windowTitlebar_doubleClicked() {
	if (windowState().testFlag(Qt::WindowNoState)) {
		on_maximizeButton_clicked();
	}
	else if (windowState().testFlag(Qt::WindowFullScreen)) {
		on_restoreButton_clicked();
	}
}

void FramelessWindow::on_helpButton_clicked()
{
	QDesktopServices::openUrl(QUrl(HELP_LINK));
}

void FramelessWindow::setAppGeometry()
{
	AppSetting::getInstance()->setAppGeometry(this->geometry());
}

void FramelessWindow::mouseDoubleClickEvent(QMouseEvent *event) {
	Q_UNUSED(event);
}

void FramelessWindow::checkBorderDragging(QMouseEvent *event) {
	if (isMaximized()) {
		return;
	}

	QPoint globalMousePos = event->globalPos();
	if (m_bMousePressed) {
		QScreen *screen = QGuiApplication::primaryScreen();
		// available geometry excludes taskbar
		QRect availGeometry = screen->availableGeometry();
		int h = availGeometry.height();
		int w = availGeometry.width();
		QList<QScreen *> screenlist = screen->virtualSiblings();
		if (screenlist.contains(screen)) {
			QSize sz = QApplication::desktop()->size();
			h = sz.height();
			w = sz.width();
		}

		// top right corner
		if (m_bDragTop && m_bDragRight) {
			int diff =
				globalMousePos.x() - (m_StartGeometry.x() + m_StartGeometry.width());
			int neww = m_StartGeometry.width() + diff;
			diff = globalMousePos.y() - m_StartGeometry.y();
			int newy = m_StartGeometry.y() + diff;
			if (neww > 0 && newy > 0 && newy < h - 50) {
				QRect newg = m_StartGeometry;
				newg.setWidth(neww);
				newg.setX(m_StartGeometry.x());
				newg.setY(newy);
				setGeometry(newg);
			}
		}
		// top left corner
		else if (m_bDragTop && m_bDragLeft) {
			int diff = globalMousePos.y() - m_StartGeometry.y();
			int newy = m_StartGeometry.y() + diff;
			diff = globalMousePos.x() - m_StartGeometry.x();
			int newx = m_StartGeometry.x() + diff;
			if (newy > 0 && newx > 0) {
				QRect newg = m_StartGeometry;
				newg.setY(newy);
				newg.setX(newx);
				setGeometry(newg);
			}
		}
		// bottom left corner
		else if (m_bDragBottom && m_bDragLeft) {
			int diff =
				globalMousePos.y() - (m_StartGeometry.y() + m_StartGeometry.height());
			int newh = m_StartGeometry.height() + diff;
			diff = globalMousePos.x() - m_StartGeometry.x();
			int newx = m_StartGeometry.x() + diff;
			if (newh > 0 && newx > 0) {
				QRect newg = m_StartGeometry;
				newg.setX(newx);
				newg.setHeight(newh);
				setGeometry(newg);
			}
		}
		// bottom right corner
		else if (m_bDragBottom && m_bDragRight) {
			int diff =
				globalMousePos.y() - (m_StartGeometry.y() + m_StartGeometry.height());
			int neww = m_StartGeometry.width() + diff;
			//int newy = m_StartGeometry.y() + diff;
			int newh = m_StartGeometry.height() + diff;
			//if (newh > 0 && newy > 0) 
			if (newh > 0) {
				QRect newg = m_StartGeometry;
				newg.setHeight(newh);
				newg.setWidth(neww);
				setGeometry(newg);
			}
		}
		// Top border
		else if (m_bDragTop) {
			int diff = globalMousePos.y() - m_StartGeometry.y();
			int newy = m_StartGeometry.y() + diff;
			if (newy > 0 && newy < h - 50) {
				QRect newg = m_StartGeometry;
				newg.setY(newy);
				//setGeometry(newg);
			}
		}
		// Left border
		else if (m_bDragLeft) {
			int diff = globalMousePos.x() - m_StartGeometry.x();
			int newx = m_StartGeometry.x() + diff;
			if (newx > 0 && newx < w - 50) {
				QRect newg = m_StartGeometry;
				newg.setX(newx);
				//setGeometry(newg);
			}
		}
		// Right border
		else if (m_bDragRight) {
			int diff =
				globalMousePos.x() - (m_StartGeometry.x() + m_StartGeometry.width());
			int neww = m_StartGeometry.width() + diff;
			if (neww > 0) {
				QRect newg = m_StartGeometry;
				newg.setWidth(neww);
				newg.setX(m_StartGeometry.x());
				//setGeometry(newg);
			}
		}
		// Right bottom
		else if (m_bDragBottom) {
			int diff =
				globalMousePos.y() - (m_StartGeometry.y() + m_StartGeometry.height());
			int newh = m_StartGeometry.height() + diff;
			if (newh > 0) {
				QRect newg = m_StartGeometry;
				newg.setHeight(newh);
				newg.setY(m_StartGeometry.y());
				//setGeometry(newg);
			}
		}
	}
	else {
		// no mouse pressed
		if (leftBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
			setCursor(Qt::SizeFDiagCursor);
		}
		else if (rightBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
			setCursor(Qt::SizeBDiagCursor);
		}
		else if (rightBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)) {
			setCursor(Qt::SizeFDiagCursor);

		}
		else if (leftBorderHit(globalMousePos) &&
			bottomBorderHit(globalMousePos)) {
			setCursor(Qt::SizeBDiagCursor);
		}
		else {
			if (topBorderHit(globalMousePos)) {
				setCursor(Qt::ArrowCursor);
			}
			else if (leftBorderHit(globalMousePos)) {
				setCursor(Qt::ArrowCursor);
			}
			else if (rightBorderHit(globalMousePos)) {
				setCursor(Qt::ArrowCursor);
			}
			else if (bottomBorderHit(globalMousePos)) {
				setCursor(Qt::ArrowCursor);
			}
			else {
				m_bDragTop = false;
				m_bDragLeft = false;
				m_bDragRight = false;
				m_bDragBottom = false;
				setCursor(Qt::ArrowCursor);
			}
		}
	}
}

// pos in global virtual desktop coordinates
bool FramelessWindow::leftBorderHit(const QPoint &pos) {
	const QRect &rect = this->geometry();
	if (pos.x() >= rect.x() && pos.x() <= rect.x() + CONST_DRAG_BORDER_SIZE) {
		return true;
	}
	return false;
}

/* Right border mouse hit */
bool FramelessWindow::rightBorderHit(const QPoint &pos) {
	const QRect &rect = this->geometry();
	int tmp = rect.x() + rect.width();
	if (pos.x() <= tmp && pos.x() >= (tmp - CONST_DRAG_BORDER_SIZE)) {
		return true;
	}
	return false;
}

/* Top border mouse hit */
bool FramelessWindow::topBorderHit(const QPoint &pos) {
	const QRect &rect = this->geometry();
	if (pos.y() >= rect.y() && pos.y() <= rect.y() + CONST_DRAG_BORDER_SIZE) {
		return true;
	}
	return false;
}

/* Bottom border mouse hit */
bool FramelessWindow::bottomBorderHit(const QPoint &pos) {
	const QRect &rect = this->geometry();
	int tmp = rect.y() + rect.height();
	if (pos.y() <= tmp && pos.y() >= (tmp - CONST_DRAG_BORDER_SIZE)) {
		return true;
	}
	return false;
}

void FramelessWindow::mousePressEvent(QMouseEvent *event) {
	if (isMaximized()) {
		return;
	}

	m_bMousePressed = true;
	m_StartGeometry = this->geometry();
	setAppGeometry();

	QPoint globalMousePos = mapToGlobal(QPoint(event->x(), event->y()));

	/* Set cursor for mouse */
	if (leftBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
		m_bDragTop = true;
		m_bDragLeft = true;
		setCursor(Qt::SizeFDiagCursor);
	}
	else if (rightBorderHit(globalMousePos) && topBorderHit(globalMousePos)) {
		m_bDragRight = true;
		m_bDragTop = true;
		setCursor(Qt::SizeBDiagCursor);
	}
	else if (rightBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)) {
		m_bDragRight = true;
		m_bDragBottom = true;
		setCursor(Qt::SizeFDiagCursor);

	}
	else if (leftBorderHit(globalMousePos) && bottomBorderHit(globalMousePos)) {
		m_bDragLeft = true;
		m_bDragBottom = true;
		setCursor(Qt::SizeBDiagCursor);
	}
	else {
		if (topBorderHit(globalMousePos)) {
			m_bDragTop = true;
			setCursor(Qt::ArrowCursor);
		}
		else if (leftBorderHit(globalMousePos)) {
			m_bDragLeft = true;
			setCursor(Qt::ArrowCursor);
		}
		else if (rightBorderHit(globalMousePos)) {
			m_bDragRight = true;
			setCursor(Qt::ArrowCursor);
		}
		else if (bottomBorderHit(globalMousePos)) {
			m_bDragBottom = true;
			setCursor(Qt::ArrowCursor);
		}
	}
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent *event) {
	Q_UNUSED(event);
	if (isMaximized()) {
		return;
	}

	m_bMousePressed = false;
	bool bSwitchBackCursorNeeded =
		m_bDragTop || m_bDragLeft || m_bDragRight || m_bDragBottom;
	m_bDragTop = false;
	m_bDragLeft = false;
	m_bDragRight = false;
	m_bDragBottom = false;
	if (bSwitchBackCursorNeeded) {
		setCursor(Qt::ArrowCursor);
	}
}

bool FramelessWindow::eventFilter(QObject *obj, QEvent *event) {
	if (isMaximized()) {
		return QWidget::eventFilter(obj, event);
	}

	// check mouse move event when mouse is moved on any object
	if (event->type() == QEvent::MouseMove) {
		QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
		if (pMouse) {
			checkBorderDragging(pMouse);
		}
	}
	// press is triggered only on frame window
	else if (event->type() == QEvent::MouseButtonPress && obj == this) {
		QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
		if (pMouse) {
			mousePressEvent(pMouse);
		}
	}
	else if (event->type() == QEvent::MouseButtonRelease) {
		if (m_bMousePressed) {
			QMouseEvent *pMouse = dynamic_cast<QMouseEvent *>(event);
			if (pMouse) {
				mouseReleaseEvent(pMouse);
			}
		}
	}

	return QWidget::eventFilter(obj, event);
}

QString FramelessWindow::getBackroundColor()
{
	/* Default Light mode */
	QString colorCode = "#055598";

	if (AppSetting::getInstance()->getTheme() == Theme_Type::Light_Theme)
	{
		colorCode = BACKGROUND_LIGHT_MODE;
	}
	else if (AppSetting::getInstance()->getTheme() == Theme_Type::Dark_Theme)
	{
		colorCode = BACKGROUND_DARK_MODE;
	}

	return colorCode;
}

/* Slot when change theme */
void FramelessWindow::changeTheme()
{
	if (windowState().testFlag(Qt::WindowNoState)) {
		styleWindow(true, true);
	}
	else if (windowState().testFlag(Qt::WindowMaximized)) {
		styleWindow(true, false);
	}
}