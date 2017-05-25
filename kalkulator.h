#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <QMainWindow>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QVector>
#include <cstdio>
#include <math.h>
#include <QStack>
#include <iostream>

namespace Ui {
class Kalkulator;
}

class Kalkulator : public QMainWindow {
    Q_OBJECT

public:
    explicit Kalkulator(QWidget *parent = 0);
    ~Kalkulator();

    int l_okraglych_o = 0, l_okraglych_z = 0;
    int l_kwadratowych_o = 0, l_kwadratowych_z = 0;
    int l_klamrowych_o = 0, l_klamrowych_z = 0;

    bool sprawdzenieNawiasow(QVector<QString> tab, int n);
    bool sprawdzenieNawiasow2(int n1, int n2, int n3, int n4, int n5, int n6);
    bool isnum(QString t);
    bool sprawdzenieSkladni(QVector<QString> tab, int n);
    int kolejnosc(QString x);
    QVector<QString> ONP(QVector<QString> tab, int n);
    int obliczanieONP(QVector <QString> wyjscie);
    QVector<QString> liczba(QVector<QString> wyr);

private slots:
    void on_pushButtonOblicz_clicked();

private:
    Ui::Kalkulator *ui;
};

#endif // KALKULATOR_H
