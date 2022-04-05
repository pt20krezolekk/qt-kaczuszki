#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "kaczka.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event);
public slots:
    void tick();
    void kaczkaKliknietaSlot();
private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsTextItem* textWynik;
    QTimer* timer;
    QList<Kaczka*> kaczki;
    void dodajKaczke();
    void zaktualizujTextWynik();
    int widthTlo, heightTlo, widthKaczka, heightKaczka;
    int wynik;
    int liczbaTickow;
};
#endif // MAINWINDOW_H
