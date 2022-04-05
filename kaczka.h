#ifndef KACZKA_H
#define KACZKA_H

#include <QGraphicsPixmapItem>

class Kaczka : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Kaczka();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void zmienAnimacje(int animacja); // 1, 2, 3
    bool zywa;
    qreal szybkoscX, szybkoscY;
    int kolor = 1; // 1, 2, 3
signals:
    void kaczkaKliknietaSignal();
};

#endif // KACZKA_H
