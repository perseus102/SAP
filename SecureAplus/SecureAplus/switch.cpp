#include "switch.h"

Animator::Animator(QObject* target, QObject* parent) : QVariantAnimation(parent) {
	setTargetObject(target);
}

Animator::~Animator() {
	stop();
}

QObject* Animator::targetObject() const {
	return target.data();
}

void Animator::setTargetObject(QObject* _target) {
	if (target.data() == _target)
		return;

	if (isRunning()) {
		qWarning("Animation::setTargetObject: you can't change the target of a running animation");
		return;
	}

	target = _target;
}

void Animator::updateCurrentValue(const QVariant& value) {
	Q_UNUSED(value);

	if (!target.isNull()) {
		auto update = QEvent(QEvent::StyleAnimationUpdate);
		update.setAccepted(false);
		QCoreApplication::sendEvent(target.data(), &update);
		if (!update.isAccepted())
			stop();
	}
}

void Animator::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) {
	if (target.isNull() && oldState == Stopped) {
		qWarning("Animation::updateState: Changing state of an animation without target");
		return;
	}

	QVariantAnimation::updateState(newState, oldState);

	if (!endValue().isValid() && direction() == Forward) {
		qWarning("Animation::updateState (%s): starting an animation without end value", targetObject()->metaObject()->className());
	}
}

void Animator::setup(int duration, QEasingCurve easing) {
	setDuration(duration);
	setEasingCurve(easing);
}

void Animator::interpolate(const QVariant& _start, const QVariant& end) {
	setStartValue(_start);
	setEndValue(end);
	start();
}

void Animator::setCurrentValue(const QVariant& value) {
	setStartValue(value);
	setEndValue(value);
	updateCurrentValue(currentValue());
}



SelectionControl::SelectionControl(QWidget* parent) : QAbstractButton(parent) {
	setObjectName("SelectionControl");
	setCheckable(true);
}

SelectionControl::~SelectionControl() {

}

void SelectionControl::enterEvent(QEvent* e) {
	setCursor(Qt::PointingHandCursor);
	QAbstractButton::enterEvent(e);
}

Qt::CheckState SelectionControl::checkState() const {
	return isChecked() ? Qt::Checked : Qt::Unchecked;
}

void SelectionControl::checkStateSet() {

	const auto state = checkState();
	emit stateChanged(state);
	toggle(state);
}

void SelectionControl::nextCheckState() {
	QAbstractButton::nextCheckState();
	SelectionControl::checkStateSet();
}



void Switch::init() {
	setColorStyle();
	setFont(style.font);
	setObjectName("Switch");
	/* setup animations */
	thumbBrushAnimation = new Animator{ this, this };
	trackBrushAnimation = new Animator{ this, this };
	thumbPosAniamtion = new Animator{ this, this };
	thumbPosAniamtion->setup(style.thumbPosAniamtion.duration, style.thumbPosAniamtion.easing);
	trackBrushAnimation->setup(style.trackBrushAnimation.duration, style.trackBrushAnimation.easing);
	thumbBrushAnimation->setup(style.thumbBrushAnimation.duration, style.thumbBrushAnimation.easing);
	/* set init values */
	trackBrushAnimation->setStartValue(colorFromOpacity(style.trackOffBrush, style.trackOffOpacity));
	trackBrushAnimation->setEndValue(colorFromOpacity(style.trackOffBrush, style.trackOffOpacity));
	thumbBrushAnimation->setStartValue(colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity));
	thumbBrushAnimation->setEndValue(colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity));
	/* set standard palettes */
	auto p = palette();
	p.setColor(QPalette::Active, QPalette::ButtonText, style.textColor);
	p.setColor(QPalette::Disabled, QPalette::ButtonText, style.textColor);
	setPalette(p);
	setSizePolicy(QSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed));
	connect(AppSetting::getInstance(), &AppSetting::signal_changeTheme, this, &Switch::changeTheme);

}

QRect Switch::indicatorRect() {
	const auto w = style.indicatorMargin.left() + style.height + style.indicatorMargin.right();
	return ltr(this) ? QRect(0, 0, w, style.height) : QRect(width() - w, 0, w, style.height);
}

QRect Switch::textRect() {
	const auto w = style.indicatorMargin.left() + style.height + style.indicatorMargin.right();
	return ltr(this) ? rect().marginsRemoved(QMargins(w, 0, 0, 0)) : rect().marginsRemoved(QMargins(0, 0, w, 0));
}

Switch::Switch(QWidget* parent) : SelectionControl(parent) {
	init();
}

Switch::Switch(const QString& text, QWidget* parent) : Switch(parent) {
	setText(text);
}

Switch::Switch(const QString& text, const QBrush& brush, QWidget* parent) : Switch(text, parent) {
	style.thumbOnBrush = brush.color();
	style.trackOnBrush = brush.color();
}

Switch::Switch(const QMargins indicatorMargin, bool inContentView, QWidget * parent) : Switch(parent)
{
	style.indicatorMargin = indicatorMargin;
	m_inContentView = inContentView;
	init();
	
}

Switch::~Switch() {

}

QSize Switch::sizeHint() const {
	auto h = style.height;
	auto w = style.indicatorMargin.left() + style.height + style.indicatorMargin.right() + fontMetrics().width(text());

	return QSize(w, h);
}

void Switch::disableToggleAndChecked(bool bdisabled, bool bChecked)
{
	m_disabledColor = bdisabled;
	setColorStyle();
	if (!bdisabled)
	{
		m_disabled = bdisabled;
		setChecked(bChecked);

	}
	else
	{
		setChecked(bChecked);
		m_disabled = bdisabled;
	}
}

void Switch::disableToggle(bool isChecked)
{

}

bool Switch::isDisabled()
{
	return m_disabled;
}

void Switch::paintEvent(QPaintEvent*) {
	/* for desktop usage we do not need Radial reaction */

	QPainter p(this);

	const auto _indicatorRect = indicatorRect();
	const auto _textRect = textRect();
	auto trackMargin = style.indicatorMargin;
	trackMargin.setTop(trackMargin.top() + 2);
	trackMargin.setBottom(trackMargin.bottom() + 2);
	QRectF trackRect = _indicatorRect.marginsRemoved(trackMargin);

	if (isEnabled()) {
		p.setOpacity(1.0);
		p.setPen(Qt::NoPen);
		/* draw track */
		p.setBrush(trackBrushAnimation->currentValue().value<QColor>());
		p.setRenderHint(QPainter::Antialiasing, true);
		p.drawRoundedRect(trackRect, CORNER_RADIUS, CORNER_RADIUS);
		p.setRenderHint(QPainter::Antialiasing, false);
		/* draw thumb */
		trackRect.setX(trackRect.x() - trackMargin.left() - trackMargin.right() - 2 + thumbPosAniamtion->currentValue().toInt());
		auto thumbRect = trackRect;

		if (!shadowPixmap.isNull())
			p.drawPixmap(thumbRect.center() - QPointF(THUMB_RADIUS, THUMB_RADIUS - 1.0), shadowPixmap);

		p.setBrush(thumbBrushAnimation->currentValue().value<QColor>());
		p.setRenderHint(QPainter::Antialiasing, true);
		p.drawEllipse(thumbRect.center(), THUMB_RADIUS - SHADOW_ELEVATION - 1.0, THUMB_RADIUS - SHADOW_ELEVATION - 1.0);
		p.setRenderHint(QPainter::Antialiasing, false);

		/* draw text */
		if (text().isEmpty())
			return;

		p.setOpacity(1.0);
		p.setPen(palette().color(QPalette::Active, QPalette::ButtonText));
		p.setFont(font());
		p.drawText(_textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
	}
	else {
		p.setOpacity(style.trackDisabledOpacity);
		p.setPen(Qt::NoPen);
		// draw track
		p.setBrush(style.trackDisabled);
		p.setRenderHint(QPainter::Antialiasing, true);
		p.drawRoundedRect(trackRect, CORNER_RADIUS, CORNER_RADIUS);
		p.setRenderHint(QPainter::Antialiasing, false);
		// draw thumb
		p.setOpacity(1.0);
		if (!isChecked())
			trackRect.setX(trackRect.x() - trackMargin.left() - trackMargin.right() - 2);
		else
			trackRect.setX(trackRect.x() + trackMargin.left() + trackMargin.right() + 2);
		auto thumbRect = trackRect;

		if (!shadowPixmap.isNull())
			p.drawPixmap(thumbRect.center() - QPointF(THUMB_RADIUS, THUMB_RADIUS - 1.0), shadowPixmap);

		p.setOpacity(1.0);
		p.setBrush(style.thumbDisabled);
		p.setRenderHint(QPainter::Antialiasing, true);
		p.drawEllipse(thumbRect.center(), THUMB_RADIUS - SHADOW_ELEVATION - 1.0, THUMB_RADIUS - SHADOW_ELEVATION - 1.0);

		/* draw text */
		if (text().isEmpty())
			return;

		p.setOpacity(style.disabledTextOpacity);
		p.setPen(palette().color(QPalette::Disabled, QPalette::ButtonText));
		p.setFont(font());
		p.drawText(_textRect, Qt::AlignLeft | Qt::AlignVCenter, text());
	}
}

void Switch::resizeEvent(QResizeEvent* e) {
	shadowPixmap = Style::drawShadowEllipse(THUMB_RADIUS, SHADOW_ELEVATION, QColor(0, 0, 0, 70));
	SelectionControl::resizeEvent(e);
}

void Switch::toggle(Qt::CheckState state) {
	
	if (m_disabled) return;

	if (state == Qt::Checked) {
		const QVariant posEnd = (style.indicatorMargin.left() + style.indicatorMargin.right() + 2) * 2;
		const QVariant thumbEnd = colorFromOpacity(style.thumbOnBrush, style.thumbOnOpacity);
		const QVariant trackEnd = colorFromOpacity(style.trackOnBrush, style.trackOnOpacity);

		if (!isVisible()) {
			thumbPosAniamtion->setCurrentValue(posEnd);
			thumbBrushAnimation->setCurrentValue(thumbEnd);
			trackBrushAnimation->setCurrentValue(trackEnd);
		}
		else {
			thumbPosAniamtion->interpolate(0, posEnd);
			thumbBrushAnimation->interpolate(colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity), thumbEnd);
			trackBrushAnimation->interpolate(colorFromOpacity(style.trackOffBrush, style.trackOffOpacity), trackEnd);
		}
	}
	else { // Qt::Unchecked
		const QVariant posEnd = 0;
		const QVariant thumbEnd = colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity);
		const QVariant trackEnd = colorFromOpacity(style.trackOffBrush, style.trackOffOpacity);

		if (!isVisible()) {
			thumbPosAniamtion->setCurrentValue(posEnd);
			thumbBrushAnimation->setCurrentValue(thumbEnd);
			trackBrushAnimation->setCurrentValue(trackEnd);
		}
		else {
			if (this->isChecked())
			{
				thumbPosAniamtion->interpolate(thumbPosAniamtion->currentValue().toInt(), posEnd);
				thumbBrushAnimation->interpolate(colorFromOpacity(style.thumbOnBrush, style.thumbOnOpacity), thumbEnd);
				trackBrushAnimation->interpolate(colorFromOpacity(style.trackOnBrush, style.trackOnOpacity), trackEnd);
			}
			else
			{
				thumbPosAniamtion->interpolate(thumbPosAniamtion->currentValue().toInt(), posEnd);
				thumbBrushAnimation->interpolate(colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity), thumbEnd);
				trackBrushAnimation->interpolate(colorFromOpacity(style.trackOffBrush, style.trackOffOpacity), trackEnd);
			}

		}
	}
}


void Switch::setColorStyle()
{
	if (m_inContentView)
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			style.trackOnBrush = QColor(TOGGLE_ACTIVE_TRACK_LT);
			style.trackOffBrush = QColor(TOGGLE_INACTIVE_TRACK_LT);
			style.thumbOnBrush = QColor(TOGGLE_ACTIVE_THUMB_LT);
			style.thumbOffBrush = QColor(TOGGLE_INACTIVE_THUMB_LT);
			style.textColor = QColor(TEXT_LIGHT_THEME_COLOR);
			if (m_disabledColor)
			{
				style.trackOnBrush = QColor(TOGGLE_ACTIVE_TRACK_DT);
				style.trackOffBrush = QColor("#CECECE");
				style.thumbOnBrush = QColor(TOGGLE_ACTIVE_THUMB_DT);
				style.thumbOffBrush = QColor("#E5E5E5");
				style.textColor = QColor(TEXT_DARK_THEME_COLOR);
			}
			break;

		case Theme_Type::Dark_Theme:
			style.trackOnBrush = QColor(TOGGLE_ACTIVE_TRACK_DT);
			style.trackOffBrush = QColor(TRACK_UNCHECKED_DARK_THEME_COLOR);
			style.thumbOnBrush = QColor(TOGGLE_ACTIVE_THUMB_DT);
			style.thumbOffBrush = QColor(TOGGLE_INACTIVE_THUMB_DT);
			style.textColor = QColor(TEXT_DARK_THEME_COLOR);
			
			if (m_disabledColor)
			{
				style.trackOnBrush = QColor("#253653");
				style.trackOffBrush = QColor("#253653");
				style.thumbOnBrush = QColor("#929AA9");
				style.thumbOffBrush = QColor("#929AA9");
				style.textColor = QColor(TEXT_DARK_THEME_COLOR);
			}
			break;

			//MORE THEME
		default:
			break;
		}
	}
	else
	{
		switch (AppSetting::getInstance()->getTheme())
		{
		case Theme_Type::Light_Theme:
			style.trackOnBrush = QColor(TRACK_CHECKED_LIGHT_THEME_COLOR);
			style.trackOffBrush = QColor(TRACK_UNCHECKED_LIGHT_THEME_COLOR);
			style.thumbOnBrush = QColor(THUMB_CHECKED_LIGHT_THEME_COLOR);
			style.thumbOffBrush = QColor(THUMB_UNCHECKED_LIGHT_THEME_COLOR);
			style.textColor = QColor(TEXT_LIGHT_THEME_COLOR);

			break;

		case Theme_Type::Dark_Theme:
			style.trackOnBrush = QColor(TRACK_CHECKED_DARK_THEME_COLOR);
			style.trackOffBrush = QColor(TRACK_UNCHECKED_DARK_THEME_COLOR);
			style.thumbOnBrush = QColor(THUMB_CHECKED_DARK_THEME_COLOR);
			style.thumbOffBrush = QColor(THUMB_UNCHECKED_DARK_THEME_COLOR);
			style.textColor = QColor(TEXT_DARK_THEME_COLOR);

			break;

			//MORE THEME
		default:
			break;
		}
	}
}

void Switch::changeTheme()
{
	setColorStyle();
	auto p = palette();
	p.setColor(QPalette::Active, QPalette::ButtonText, style.textColor);
	p.setColor(QPalette::Disabled, QPalette::ButtonText, style.textColor);
	setPalette(p);

	const auto state = checkState();
	if (state == Qt::Checked) {
		const QVariant posEnd = (style.indicatorMargin.left() + style.indicatorMargin.right() + 2) * 2;
		const QVariant thumbEnd = colorFromOpacity(style.thumbOnBrush, style.thumbOnOpacity);
		const QVariant trackEnd = colorFromOpacity(style.trackOnBrush, style.trackOnOpacity);

		thumbPosAniamtion->interpolate(thumbPosAniamtion->currentValue().toInt(), posEnd);
		thumbBrushAnimation->interpolate(colorFromOpacity(style.thumbOnBrush, style.thumbOnOpacity), thumbEnd);
		trackBrushAnimation->interpolate(colorFromOpacity(style.trackOnBrush, style.trackOnOpacity), trackEnd);

	}
	else { // Qt::Unchecked
		const QVariant posEnd = 0;
		const QVariant thumbEnd = colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity);
		const QVariant trackEnd = colorFromOpacity(style.trackOffBrush, style.trackOffOpacity);

		thumbPosAniamtion->interpolate(0, posEnd);
		thumbBrushAnimation->interpolate(colorFromOpacity(style.thumbOffBrush, style.thumbOffOpacity), thumbEnd);
		trackBrushAnimation->interpolate(colorFromOpacity(style.trackOffBrush, style.trackOffOpacity), trackEnd);
}
}
