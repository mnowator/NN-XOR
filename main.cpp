#include <QCoreApplication>
#include <QtGlobal>
#include <QTime>
#include <iostream>
#include <QDebug>

#include "neuron.h"

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());

    QCoreApplication a(argc, argv);
    QList<Neuron*> neurons;

    neurons.append(new Neuron());
    neurons.append(new Neuron());

    neurons.append(new Neuron());
    neurons.append(new Neuron());

    neurons.append(new Neuron());

    neurons[0]->setTeachingFactor(0.5);
    neurons[1]->setTeachingFactor(0.5);
    neurons[2]->setTeachingFactor(0.5);
    neurons[3]->setTeachingFactor(0.5);
    neurons[4]->setTeachingFactor(0.5);

    neurons[0]->setState(ACTIVATED);
    neurons[1]->setState(ACTIVATED);

    neurons[2]->setBackwardConnection(neurons[0]);
    neurons[2]->setBackwardConnection(neurons[1]);
    neurons[3]->setBackwardConnection(neurons[0]);
    neurons[3]->setBackwardConnection(neurons[1]);

    neurons[2]->setForwardConnection(neurons[4]);
    neurons[3]->setForwardConnection(neurons[4]);
    neurons[4]->setBackwardConnection(neurons[2]);
    neurons[4]->setBackwardConnection(neurons[3]);

    QList<QList<double> > patterns;

    QList<double> pattern1 = { 0, 0, 0 };
    QList<double> pattern2 = { 0, 1, 1 };
    QList<double> pattern3 = { 1, 0, 1 };
    QList<double> pattern4 = { 1, 1, 0 };

    patterns.append(pattern1);
    patterns.append(pattern2);
    patterns.append(pattern3);
    patterns.append(pattern4);

    for ( unsigned i=0; i<10000; ++i )
    {
        unsigned idx = qrand() % 4;

        neurons[0]->setActivateValue(patterns[idx][0]);
        neurons[1]->setActivateValue(patterns[idx][1]);

        neurons[2]->activate();
        neurons[3]->activate();
        neurons[2]->setState(ACTIVATED);
        neurons[3]->setState(ACTIVATED);

        neurons[4]->activate();
        neurons[4]->setState(ACTIVATED);


        neurons[4]->computeError(patterns[idx][2]);
        neurons[2]->computeError();
        neurons[3]->computeError();
        neurons[4]->setState(ERROR_COMPUTED);
        neurons[3]->setState(ERROR_COMPUTED);
        neurons[2]->setState(ERROR_COMPUTED);


        neurons[4]->train();       
        neurons[2]->train();  
        neurons[3]->train();

        neurons[2]->setState(RELAXED);
        neurons[3]->setState(RELAXED);
        neurons[4]->setState(RELAXED);
    }

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

