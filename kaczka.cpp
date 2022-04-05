#include "kaczka.h"
#include <QDebug>

Kaczka::Kaczka()
{
    this->zmienAnimacje(1);
    this->setScale(2.5);
    this->kolor = 1 + (rand() % 3);
    this->zywa = true;
    this->szybkoscX = 12.0 + ((rand() % 20) / 10.0);
    this->szybkoscY = 0.0;
}

void Kaczka::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Kaczka kliknieta";
    emit kaczkaKliknietaSignal();
}

//jesli animacja to -1, to kaczka bedzie miala obrazek martwej
void Kaczka::zmienAnimacje(int animacja) {
    // np: :/obrazki/kaczka1_1.png
    if (animacja != -1)
        this->setPixmap(QPixmap(QString(":/obrazki/kaczka") + QString::number(this->kolor) + QString("_") + QString::number(animacja) + QString(".png")));
    else
        this->setPixmap(QPixmap(QString(":/obrazki/kaczka") + QString::number(this->kolor) + QString("_martwa.png")));
}
