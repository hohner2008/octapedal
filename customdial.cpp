#include "customdial.h"

#include "customdial.h"
#include <QPainter>

CustomDial::CustomDial(QWidget *parent) : QDial(parent) {
    // Вимикаємо стандартне малювання насічок, якщо вони не потрібні
    setNotchesVisible(false);
}

void CustomDial::setDialImages(const QString &bgPath, const QString &pointerPath) {
    m_background.load(bgPath);
    m_pointer.load(pointerPath);
    update(); // Перемалювати віджет
}

void CustomDial::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    // Вмикаємо згладжування для плавності обертання стрілки
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Центр віджета
    QPointF center(width() / 2.0, height() / 2.0);

    // 1. Малюємо фонову картинку (масштабуємо під розмір віджета)
    if (!m_background.isNull()) {
        QPixmap scaledBg = m_background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QRectF bgRect(center.x() - scaledBg.width() / 2.0,
                      center.y() - scaledBg.height() / 2.0,
                      scaledBg.width(), scaledBg.height());
        painter.drawPixmap(bgRect.toRect(), scaledBg);
    }

    // 2. Обчислюємо кут повороту стрілки
    // Стандартний QDial у Qt працює в діапазоні кутів приблизно від -240 до 60 градусів.
    // Переводимо поточне значення (value) у пропорцію кута.
    double range = maximum() - minimum();
    double valuePos = (range > 0) ? (value() - minimum()) / range : 0.0;

    // Розрахунок кута: зазвичай хід QDial складає 270 або 300 градусів.
    // За замовчуванням у Qt: старт з 240° (знизу зліва) до -60° (знизу справа).
    double startAngle = -120.0; // Початковий кут у градусах
    double endAngle = 120.0;    // Кінцевий кут у градусах
    double currentAngle = startAngle + (valuePos * (endAngle - startAngle));

    // 3. Малюємо стрілку з урахуванням повороту
    if (!m_pointer.isNull()) {
        painter.save(); // Зберігаємо стан матриці трансформації

        // Переносимо нуль координат у центр віджета та повертаємо сцену
        painter.translate(center);
        painter.rotate(currentAngle);

        // Масштабуємо стрілку (наприклад, робимо її розміром у 80% від віджета)
        auto pointerSizeF = m_pointer.size();
        int pointerSize = qMin(width(), height()) * 0.8;

        auto mainSize = m_background.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap scaledPointer = m_pointer.scaled(pointerSizeF.height(),pointerSizeF.width(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Малюємо стрілку так, щоб її центр збігався з центром обертання
        QRect pointerRect(0, 0,
                        pointerSizeF.width() - 1, pointerSizeF.height() - 1);

        painter.drawPixmap(pointerRect, scaledPointer);

        painter.restore(); // Повертаємо координати до початкових
    }
}

