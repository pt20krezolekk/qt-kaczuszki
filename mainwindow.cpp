#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    statusBar()->hide();
    wynik = 0;
    najlepszyWynik = 0;
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(this->scene);
    QPixmap tlo = QPixmap(":/obrazki/tlo.png");
    widthTlo = tlo.width();
    heightTlo = tlo.height();
    resize(widthTlo, heightTlo);
    this->scene->addPixmap(tlo);
    textWynik = new QGraphicsTextItem();
    this->scene->addItem(textWynik);
    textNajlepszyWynik = new QGraphicsTextItem();
    textNajlepszyWynik->setPos(0, 35);
    this->scene->addItem(textNajlepszyWynik);
    zaktualizujTextWynik();
    this->timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::tick);
    timer->start(25);

    dodajKaczke();
}

void MainWindow::tick() {
    liczbaTickow++;
    for (int i = 0; i < kaczki.length(); i++) {
        Kaczka* kaczka = kaczki[i];
        if (kaczka->zywa) {
            kaczka->setPos(kaczka->pos() + QPointF(kaczka->szybkoscX, kaczka->szybkoscY));
            const int animacje[] = {1, 2, 3, 2};
            kaczka->zmienAnimacje(animacje[((liczbaTickow / 6) % 4)]);
            //kaczka odleciala

            if (kaczka->pos().x() + kaczka->pixmap().width() > widthTlo
                || kaczka->pos().y() < kaczka->pixmap().height() * 2.5
                || kaczka->pos().y() > heightTlo - kaczka->pixmap().height() * 2.5) {
                qDebug() << "kaczka wyszla poza okno, reset gry: " << kaczka->pos().x() << " " << kaczka->pos().y();
                for (int i = 0; i < this->kaczki.length(); i++) {
                    this->scene->removeItem(kaczki[i]);
                    delete kaczki[i];
                }
                kaczki.clear();
                wynik = 0;
                zaktualizujTextWynik();
                return;
                //this->scene->removeItem(kaczka);
                //delete kaczka;
                //kaczki.removeAt(i);
            }

        } else {
            kaczka->setPos(kaczka->pos() + QPointF(0.0, 25.0));

            //kaczka wypadla poza scene (umarla)
            if (kaczka->pos().y() > heightTlo - kaczka->pixmap().height() * 2.5) {
                this->scene->removeItem(kaczka);
                delete kaczka;
                kaczki.removeAt(i);
            }
        }
    }

    if (kaczki.length() == 0) {
        for (int i = 0; i < 1 + (wynik / 10); i++) {
            dodajKaczke();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dodajKaczke() {
    Kaczka* kaczka = new Kaczka();
    int yKaczki = 100 + (rand() % 600);
    qDebug() << yKaczki;
    kaczka->setPos(0, yKaczki);
    if (yKaczki > heightTlo / 2)
        kaczka->szybkoscY = -1.0;
    else
        kaczka->szybkoscY = 1.0;
    this->scene->addItem(kaczka);
    kaczki.push_back(kaczka);
   // connect(kaczka, &Kaczka::kaczkaKliknietaSignal, this, &MainWindow::kaczkaKliknietaSlot);
    connect(kaczka, SIGNAL(kaczkaKliknietaSignal()), this, SLOT(kaczkaKliknietaSlot()));
}

void MainWindow::kaczkaKliknietaSlot() {
    Kaczka* kaczka = (Kaczka*)sender();
    if (!kaczka->zywa)
        return;
    kaczka->zywa = false;
    kaczka->zmienAnimacje(-1);
    this->wynik++;

    if (this->wynik > this->najlepszyWynik)
        this->najlepszyWynik = this->wynik;

    zaktualizujTextWynik();
}

void MainWindow::zaktualizujTextWynik() {
    this->textWynik->setHtml(QString("<b style='font-size:32px;color:white;'>Wynik: ") + QString::number(this->wynik) + QString("</b>"));
    this->textNajlepszyWynik->setHtml(QString("<b style='font-size:32px;color:white;'>Najlepszy wynik: ") + QString::number(this->najlepszyWynik) + QString("</b>"));
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    //cheaty
    for (int i = 0; i < kaczki.length(); i++) {
        emit kaczki[i]->kaczkaKliknietaSignal();
    }
}
