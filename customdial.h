#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QDial>

#pragma once

#include <QDial>
#include <QPixmap>
#include <QPaintEvent>

class CustomDial : public QDial {
    Q_OBJECT

public:
    explicit CustomDial(QWidget *parent = nullptr);

    // Функції для встановлення картинок з коду
    void setDialImages(const QString &bgPath, const QString &pointerPath);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_background;
    QPixmap m_pointer;
};

#endif // CUSTOMDIAL_H
