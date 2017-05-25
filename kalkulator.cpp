#include "kalkulator.h"
#include "ui_kalkulator.h"

Kalkulator::Kalkulator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Kalkulator)
{
    ui->setupUi(this);
}

Kalkulator::~Kalkulator()
{
    delete ui;
}

bool Kalkulator::sprawdzenieNawiasow(QVector<QString> tab, int n) {
    QStack<QString> stos;

    for(int i=0; i<n; i++) {
            if(tab[i] == "(" || tab[i] == ")" || tab[i] == "[" || tab[i] == "]" || tab[i] == "{" || tab[i] == "}") {
                if((tab[0] == ")") || (tab[0] == "]") || (tab[0] == "}")) {
                    ui->label_10->setText("Błędne nawiasy!");
                    return false;
                }
                if((tab[i] == "(") || (tab[i] == "[") || (tab[i] == "{")) stos.push(tab[i]);

                if(tab[i] == ")" && (!stos.empty())) {
                    if(stos.top() == "(") stos.pop();
                    else {
                        ui->label_10->setText("Błędne nawiasy!");
                        return false;
                    }
                }
                if(tab[i] == "]" && (!stos.empty())) {
                    if(stos.top() == "[") stos.pop();
                    else {
                        ui->label_10->setText("Błędne nawiasy!");
                        return false;
                    }
                }
                if(tab[i] == "}" && (!stos.empty())) {
                    if(stos.top() == "{") stos.pop();
                    else {
                        ui->label_10->setText("Błędne nawiasy!");
                        return false;
                    }
                }

                if(tab[i] == "(") l_okraglych_o++;
                if(tab[i] == ")") l_okraglych_z++;
                if(tab[i] == "[") l_kwadratowych_o++;
                if(tab[i] == "]") l_kwadratowych_z++;
                if(tab[i] == "{") l_klamrowych_o++;
                if(tab[i] == "}") l_klamrowych_z++;
            }
        }
        return true;

}

bool Kalkulator::sprawdzenieNawiasow2(int n1, int n2, int n3, int n4, int n5, int n6) {
    if(n1 != n2) {
            ui->label_10->setText("Błędne nawiasy!");
            return false;
        }
        if(n3 != n4) {
            ui->label_10->setText("Błędne nawiasy!");
            return false;
        }
        if(n5 != n6) {
            ui->label_10->setText("Błędne nawiasy!");
            return false;
        }

        return true;
}

bool Kalkulator::isnum(QString t) {
    if(t[0] == 45 || ((t[0] >= 48) && (t[0] <= 57))) return true; // cyfra
    else return false;
}

bool Kalkulator::sprawdzenieSkladni(QVector<QString> tab, int n) {
    for(int i=0; i<n-1; i++) {
        if(isnum(tab[i]) == true && isnum(tab[i+1]) == true) {
            ui->label_10->setText("Błędna składnia!");
            return false;
        }

        else if ((tab[i] == "+" || tab[i] == "~" || tab[i] == "*" || tab[i] == "d" || tab[i] == "m" || tab[i] == "^") &&
                 (tab[i+1] == "+" || tab[i+1] == "~" || tab[i+1] == "*" || tab[i+1] == "d" || tab[i+1] == "m" || tab[i+1] == "^")) {
            ui->label_10->setText("Błędna składnia!");
            return false;
        }

        else if((tab[i] == "+" || tab[i] == "~" || tab[i] == "*" || tab[i] == "d" || tab[i] == "m" || tab[i] == "^") &&
                (tab[i+1] == ")" || tab[i+1] == "]" || tab[i+1] == "}")) {
            ui->label_10->setText("Błędna składnia!");
            return false;
        }

        else if((tab[i] == "(" || tab[i] == "[" || tab[i] == "{") && (tab[i+1] == "+" || tab[i+1] == "~" || tab[i+1] == "*" ||
                tab[i+1] == "d" || tab[i+1] == "m" || tab[i+1] == "^")) {
            ui->label_10->setText("Błędna składnia!");
            return false;
        }
    }
    return true;
}

int Kalkulator::kolejnosc(QString x) {
    if(x == "(" || x == "[" || x == "{") return 0;
    if(x == "+" || x == "~" || x == ")" || x == "]" || x == "}") return 1;
    if(x == "*" || x == "d" || x == "m") return 2;
    if(x == "^") return 3;
}

QVector<QString> Kalkulator::ONP(QVector<QString> tab, int n) {
    QStack<QString> stos;
    QVector<QString> wyjscie;

    for(int i=0; i<n; i++) {
        QString s = tab[i];

        if(s == "+" || s == "~" || s == "*" || s == "d" || s == "m" || s == "^") {
            while(!stos.empty() && kolejnosc(stos.top()) >= kolejnosc(s)){
                wyjscie.push_back(stos.top());
                stos.pop();
            }
            stos.push(s);
        }

        else if(s == "("){
            stos.push(s);
        }
        else if(s == ")") {
            while(stos.top() != "(") {
                wyjscie.push_back(stos.top());
                stos.pop();
            }
            stos.pop();
        }

        else if(s == "[") stos.push(s);
        else if(s == "]") {
            while(stos.top() != "[") {
                wyjscie.push_back(stos.top());
                stos.pop();
            }
            stos.pop();
        }

        else if(s == "{") stos.push(s);
        else if(s == "}") {
            while(stos.top() != "{") {
                wyjscie.push_back(stos.top());
                stos.pop();
            }
            stos.pop();
        }

        else {
            wyjscie.push_back(s);
        }
    }

    while(!stos.empty()) {
        QString tmp = stos.top();
        wyjscie.push_back(tmp);
        stos.pop();
    }

    QString wyjscie2 = "";

    for(int i=0; i<wyjscie.size(); i++) {
        wyjscie2 += wyjscie[i] + " ";
    }

    ui->label_9->setText(wyjscie2);

    return wyjscie;
}

int Kalkulator::obliczanieONP(QVector <QString> wyjscie){
    QStack<QString> stos2;

    for(int i=0; i<wyjscie.size(); i++) {
        if(isnum(wyjscie[i]) == true) {
            stos2.push(wyjscie[i]);
        }

        else if(isnum(wyjscie[i]) == false) {
            QString tmp, tmp2, str;
            tmp = stos2.top();
            int a = atoi(tmp.toStdString().c_str());
            stos2.pop();

            tmp2 = stos2.top();
            int b = atoi(tmp2.toStdString().c_str());
            stos2.pop();

            if(wyjscie[i] == "+") {
                int c = b + a;
                std::ostringstream ss;
                ss << c;
                str = QString::fromStdString(ss.str());
                stos2.push(str);
            }
            else if(wyjscie[i] == "~") {
                int c = b - a;
                std::ostringstream ss;
                ss << c;
                str = QString::fromStdString(ss.str());
                stos2.push(str);
            }
            else if(wyjscie[i] == "*") {
                int c = b * a;
                std::ostringstream ss;
                ss << c;
                str = QString::fromStdString(ss.str());
                stos2.push(str);
            }
            else if(wyjscie[i] == "d") {
                if(b >= 0 && a > 0) {
                    int c = b / a;
                    std::ostringstream ss;
                    ss << c;
                    str = QString::fromStdString(ss.str());
                    stos2.push(str);

                }
                else {
                    ui->label_10->setText("Błędne działanie!");
                    return 0;
                }
            }

            else if(wyjscie[i] == "m") {
                if(b >= 0 && a > 0) {
                    int c = b % a;
                    std::ostringstream ss;
                    ss << c;
                    str = QString::fromStdString(ss.str());
                    stos2.push(str);
                } else {
                    ui->label_10->setText("Błędne działanie!");
                    return 0;
                }
            }
            else if(wyjscie[i] == "^") {
                if(a < 0 || (b == 0 && a == 0)){
                    ui->label_10->setText("Błędne działanie!");
                    return 0;
                }
                else {
                    int c = pow(b, a);
                    std::ostringstream ss;
                    ss << c;
                    str = QString::fromStdString(ss.str());
                    stos2.push(str);
                }
            }
        }
    }
    ui->label_10->setText(stos2.top());
}

QVector<QString> Kalkulator::liczba(QVector<QString> wyr) {
    for(int i=0; i<wyr.length()-1; i++) {
        if(isnum(wyr[i])){
            while(i<wyr.length()-1 && isnum(wyr[i+1])) {
                wyr[i] += wyr[i+1];
                wyr.remove(i+1);
            }
        }
    }

    return wyr;
}

void Kalkulator::on_pushButtonOblicz_clicked()
{
    QString wyrazenie;
    QVector<QString> wyr, wyr2, wyr3;

    if(!ui->lineWyrazenie->text().isEmpty()) {
        wyrazenie = ui->lineWyrazenie->text();
        std::copy(wyrazenie.begin(), wyrazenie.end(), std::back_inserter(wyr));

        wyr2 = liczba(wyr);

        if(sprawdzenieNawiasow(wyr2, wyr2.length()) == false) return;
        else if(sprawdzenieNawiasow(wyr2, wyr2.length()) == true)
            if(sprawdzenieNawiasow2(l_okraglych_o, l_okraglych_z, l_kwadratowych_o, l_kwadratowych_z, l_klamrowych_o, l_klamrowych_z) == false)
                return;
            else
                if(sprawdzenieSkladni(wyr2, wyr2.length()) == true) {
                    QVector<QString> onp = ONP(wyr2, wyr2.length());
                    obliczanieONP(onp);
                }
    }
    else {
        ui->label_9->setText("");
        ui->label_10->setText("Podaj wyrażenie!");
    }

    ui->lineWyrazenie->clear();

}
