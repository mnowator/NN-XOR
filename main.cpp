#include <QCoreApplication>
#include <QtGlobal>
#include <QTime>
#include <iostream>
#include <QDebug>

#include "neuralnetwork.h"

int main(int argc, char *argv[])
{
    // Generator licz pseudolosowych
    qsrand(QTime::currentTime().msec());

    QCoreApplication a(argc, argv);

    NeuralNetwork nn;
    nn.setLayersDimensions(QList<double>({2,1}));

    nn.setTeachningFactor(0.5);

    QList<QList<double> > patterns;

    // Wzorce
    QList<double> pattern1 = { 0, 0, 0 };
    QList<double> pattern2 = { 0, 1, 1 };
    QList<double> pattern3 = { 1, 0, 1 };
    QList<double> pattern4 = { 1, 1, 0 };

    patterns.append(pattern1);
    patterns.append(pattern2);
    patterns.append(pattern3);
    patterns.append(pattern4);

    // Proces uczenia
    for ( unsigned i=0; i<100000; ++i )
    {
        unsigned idx = qrand() % 4; // Losowany numer wzorca

        // Ustawienie wartosci z wzorcow na sztucznej warstwie stanwiacej wejscia do sieci
        neurons[0]->setActivateValue(patterns[idx][0]);
        neurons[1]->setActivateValue(patterns[idx][1]);

        // Aktywacja kolejnych warstw sieci
        neurons[2]->activate();
        neurons[3]->activate();
        neurons[2]->setState(ACTIVATED);
        neurons[3]->setState(ACTIVATED);

        neurons[4]->activate();
        neurons[4]->setState(ACTIVATED);

        // Obliczenie bledu zgodnie ze wsteczna propagacja bledu
        neurons[4]->computeError(patterns[idx][2]);
        neurons[2]->computeError();
        neurons[3]->computeError();
        neurons[4]->setState(ERROR_COMPUTED);
        neurons[3]->setState(ERROR_COMPUTED);
        neurons[2]->setState(ERROR_COMPUTED);

        // Przeprowadzenie procesu uczenia
        neurons[4]->train();
        neurons[2]->train();
        neurons[3]->train();

        neurons[2]->setState(RELAXED);
        neurons[3]->setState(RELAXED);
        neurons[4]->setState(RELAXED);
    }

    // Testowanie nauczonej sieci
    forever
    {
        double x1,x2;

        std::cout << "x1: ";
        std::cin >> x1;

        std::cout << "x2: ";
        std::cin >> x2;

        neurons[0]->setActivateValue(x1);
        neurons[1]->setActivateValue(x2);
        neurons[2]->activate();
        neurons[3]->activate();
        neurons[2]->setState(ACTIVATED);
        neurons[3]->setState(ACTIVATED);

        neurons[4]->activate();
        neurons[4]->setState(ACTIVATED);

        std::cout << "Output: " << neurons[4]->getActivateValue() << "\n";

        neurons[2]->setState(RELAXED);
        neurons[3]->setState(RELAXED);
        neurons[4]->setState(RELAXED);
    }



    return a.exec();
}

