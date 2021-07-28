#include<iostream>
#include<windows.h>

#include "Rectangle.h"
#include "Newton.h"
#include "Gauss.h"

using namespace std;
HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);

#pragma region output
//0 - BLACK, 1 - BLUE, 2 - GREEN, 3 - LIGHT BLUE
//4 - RED, 5 - PURPLE, 6 - YELLOW, 7 - WHITE
//8 - GREY, 9 - MORE BLUE
//10 - LIGHT GREEN, 11 - WERY LIGHT BLUE
//12 - WERY RED, 13 - WERY PURPLE
void output(int textColor, double text) {
    SetConsoleTextAttribute(colors, textColor);
    std::cout << text;
    SetConsoleTextAttribute(colors, 7);
}
void output(int textColor, string text) {
    SetConsoleTextAttribute(colors, textColor);
    std::cout << text;
    SetConsoleTextAttribute(colors, 7);
}
void output(int textColor, int text) {
    SetConsoleTextAttribute(colors, textColor);
    std::cout << text;
    SetConsoleTextAttribute(colors, 7);
}
#pragma endregion

double F(double x) {

    //первообразная(для точного знач. интеграла
    double y = (sin(10000 * x) - 10000 * x * cos(10000 * x)) / 100000000;

    return y;
}

double f(double x) {

    //Функция.

    double y = x*sin(10000*x);

    return y;
}

double f2deriv(double x) {
    //2 производная.

    double y = -100000000*x*sin(10000*x) + 20000*cos(10000*x);

    return y;
}

double f2nderiv(double x) {
    //производная 2n порядка, где n - количество точек квадратуры гаусса

    double y = -100000000 * x * sin(10000 * x) + 20000 * cos(10000 * x);

    return y;
}

int main()
{

    double(*funct)(double) = f;
    double(*fderive)(double) = f2deriv;
    double(*f2nderive)(double) = f2nderiv;

    double a = 0;
    double b = 1;
    int n = 1; //разбиение
    double h = (b - a) / n;
    vector<Point> fpoints;

    for (int i = 0; i <= n; i++) {
       fpoints.push_back(Point(a + h*i, 0, 0));
    }

    Rect rec(fpoints, f);
    Newton ne(fpoints, f, h);
    Gauss ga1(1, h, fpoints, f);
    Gauss ga2(2, h, fpoints, f);
    Gauss ga3(3, h, fpoints, f);

    double I_true = F(b) - F(a);

    /*
    output(10, rec.Integral()); cout << "\t RECTANGLE \t"; output(10, rec.error(fderive)); cout<<"\tActual error: " << (abs(rec.Integral() - (F(b)-F(a)))); cout << "\n";
    output(11, ne.Integral()); cout << "\t NEWTON \t"; output(11, ne.error(fderive)); cout << "\tActual error: " << (abs(ne.Integral() - (F(b) - F(a)))); cout << "\n";
    output(12, ga1.Integral()); cout << "\t GAUSS \t"; output(12, ga1.error(f2nderive)); cout << "\tActual error: " << (abs(ga1.Integral() - (F(b) - F(a)))); cout << "\n";
    output(12, ga2.Integral()); cout << "\t GAUSS \t"; output(12, ga2.error(f2nderive)); cout << "\tActual error: " << (abs(ga2.Integral() - (F(b) - F(a)))); cout << "\n";
    output(12, ga3.Integral()); cout << "\t GAUSS \t"; output(12, ga3.error(f2nderive)); cout << "\tActual error: " << (abs(ga3.Integral() - (F(b) - F(a)))); cout << "\n";
    output(12, ga4.Integral()); cout << "\t GAUSS \t"; output(12, ga4.error(f2nderive)); cout << "\tActual error: " << (abs(ga4.Integral() - (F(b) - F(a)))); cout << "\n";


    double Istar = F(b) - F(a);
    double Ih = ga2.Integral();

    h = (b - a) / (2*n);
    fpoints.clear();
    for (int i = 0; i <= n; i++) {
        fpoints.push_back(Point(a + h * i, 0, 0));
    }

    ga2 = Gauss(2, fpoints, f);
    double Ih_2 = ga2.Integral();

    cout << "\n I* - Ih: " << (Istar - Ih);
    cout << "\n I* - Ih / I* - Ih_2: " << (Istar - Ih) / (Istar - Ih_2);
    cout << "\n Ih_2 - Ih: " << (Ih_2 - Ih);
    cout << "\n IR: " << Ih_2 - ((Ih_2 - Ih)/3);
    cout << "\n I* - IR: " << Istar - (Ih_2 - ((Ih_2 - Ih) / 3)) << "\n"; 
    */

    double res_rec = abs(rec.Integral() - I_true);
    double res_ne = abs(ne.Integral() - I_true);
    double res_ga1 = abs(ga1.Integral() - I_true);
    double res_ga2 = abs(ga2.Integral() - I_true);
    double res_ga3 = abs(ga3.Integral() - I_true);

    double Integ_ga2 = ga2.Integral();

    //cout << "I rec: " << scientific << res_rec << "\n";
    //cout << "I ne: " << scientific << res_ne << "\n";
    //cout << "I ga1: " << scientific << res_ga1 << "\n";
    cout << "I ga2: " << scientific << res_ga2 << "\n";
    //cout << "I ga3: " << scientific << res_ga3 << "\n";

    

    h = (b - a) / (2 * n);
    fpoints.clear();
    for (int i = 0; i <= 2*n; i++) {
        fpoints.push_back(Point(a + h * i, 0, 0));
    }

    rec = Rect(fpoints, f);
    ne = Newton(fpoints, f, h);
    ga1 = Gauss(1, h, fpoints, f);
    ga2 = Gauss(2, h, fpoints, f);
    ga3 = Gauss(3, h, fpoints, f);

    double res_rec_h2 = abs(rec.Integral() - I_true);
    double res_ne_h2 = abs(ne.Integral() - I_true);
    double res_ga1_h2 = abs(ga1.Integral() - I_true);
    double res_ga2_h2 = abs(ga2.Integral() - I_true);
    double res_ga3_h2 = abs(ga3.Integral() - I_true);

    double Integ_ga2_h2 = ga2.Integral();

    //cout << "I h/2 rec: " << scientific << res_rec_h2 << "\n";
    //cout << "I h/2 ne: " << scientific << res_ne_h2 << "\n";
    //cout << "I h/2 ga1: " << scientific << res_ga1_h2 << "\n";
    cout << "I h/2 ga2: " << scientific << res_ga2_h2 << "\n";
    //cout << "I h/2 ga3: " << scientific << res_ga3_h2 << "\n";

    cout << "\nIR (h) : " << scientific << Integ_ga2_h2 + ((Integ_ga2_h2 - Integ_ga2) / 3.0) << "\n";
    cout << "I* - IR (h): " << I_true - (Integ_ga2_h2 + ((Integ_ga2_h2 - Integ_ga2) / 3.0)) << "\n\n";

    h = (b - a) / (4 * n);
    fpoints.clear();
    for (int i = 0; i <= 4 * n; i++) {
        fpoints.push_back(Point(a + h * i, 0, 0));
    }

    rec = Rect(fpoints, f);
    ne = Newton(fpoints, f, h);
    ga1 = Gauss(1, h, fpoints, f);
    ga2 = Gauss(2, h, fpoints, f);
    ga3 = Gauss(3, h, fpoints, f);

    double res_rec_h4 = abs(rec.Integral() - I_true);
    double res_ne_h4 = abs(ne.Integral() - I_true);
    double res_ga1_h4 = abs(ga1.Integral() - I_true);
    double res_ga2_h4 = abs(ga2.Integral() - I_true);
    double res_ga3_h4 = abs(ga3.Integral() - I_true);

    double Integ_ga2_h4 = ga2.Integral();

    //cout << "I h/4 rec: " << scientific << res_rec_h4 << "\n";
    //cout << "I h/4 ne: " << scientific << res_ne_h4 << "\n";
    //cout << "I h/4 ga1: " << scientific << res_ga1_h4 << "\n";
    cout << "I h/4 ga2: " << scientific << res_ga2_h4 << "\n";
    //cout << "I h/4 ga3: " << scientific << res_ga3_h4 << "\n";

    cout << "\nIR (h/2) : " << scientific << Integ_ga2_h4 + ((Integ_ga2_h4 - Integ_ga2_h2) / 3.0) << "\n";
    cout << "I* - IR (h/2): " << I_true - (Integ_ga2_h4 + ((Integ_ga2_h4 - Integ_ga2_h2) / 3.0)) << "\n\n";

    h = (b - a) / (8 * n);
    fpoints.clear();
    for (int i = 0; i <= 8 * n; i++) {
        fpoints.push_back(Point(a + h * i, 0, 0));
    }

    rec = Rect(fpoints, f);
    ne = Newton(fpoints, f, h);
    ga1 = Gauss(1, h, fpoints, f);
    ga2 = Gauss(2, h, fpoints, f);
    ga3 = Gauss(3, h, fpoints, f);

    double res_rec_h8 = abs(rec.Integral() - I_true);
    double res_ne_h8 = abs(ne.Integral() - I_true);
    double res_ga1_h8 = abs(ga1.Integral() - I_true);
    double res_ga2_h8 = abs(ga2.Integral() - I_true);
    double res_ga3_h8 = abs(ga3.Integral() - I_true);

    double Integ_ga2_h8 = ga2.Integral();

    //cout << "I h/8 rec: " << scientific << res_rec_h8 << "\n";
    //cout << "I h/8 ne: " << scientific << res_ne_h8 << "\n";
    //cout << "I h/8 ga1: " << scientific << res_ga1_h8 << "\n";
    cout << "I h/8 ga2: " << scientific << res_ga2_h8 << "\n";
    //cout << "I h/8 ga3: " << scientific << res_ga3_h8 << "\n";

    cout << "\nIR (h/4) : " << scientific << Integ_ga2_h8 + ((Integ_ga2_h8 - Integ_ga2_h4) / 3.0) << "\n";
    cout << "I* - IR (h/4): " << I_true - (Integ_ga2_h8 + ((Integ_ga2_h8 - Integ_ga2_h4) / 3.0)) << "\n\n";

    cout << "formula 1 h: " << scientific << res_ga2 / res_ga2_h2 << "\n";
    cout << "formula 2 h: " << scientific << (Integ_ga2_h2 - Integ_ga2) / 3.0 << "\n";

    cout << "formula 1 h/2: " << scientific << res_ga2_h2 / res_ga2_h4 << "\n";
    cout << "formula 2 h/2: " << scientific << (Integ_ga2_h4 - Integ_ga2_h2) / 3.0 << "\n";

    cout << "formula 1 h/4: " << scientific << res_ga2_h4 / res_ga2_h8 << "\n";
    cout << "formula 2 h/4: " << scientific << (Integ_ga2_h8 - Integ_ga2_h4) / 3.0 << "\n";

    cout << "\nOtns: " << scientific << abs(res_ga1) / abs(Integ_ga2);
    cout << "\nOtns: " << scientific << abs(res_ga1_h2) / abs(Integ_ga2_h2);
    cout << "\nOtns: " << scientific << abs(res_ga1_h4) / abs(Integ_ga2_h4);

    cout << "\n Integ: " << scientific << Integ_ga2;
    cout << "\n Integ: " << scientific << Integ_ga2_h2;
    cout << "\n Integ: " << scientific << Integ_ga2_h4;

    cout << "\n" << scientific << 9.52124806820126 * pow(10, -5);

    std::cin;
}