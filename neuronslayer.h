#ifndef NAURONSLAYER_H
#define NAURONSLAYER_H

#include <QVector>
#include "neuron.h"


class NeuronsLayer
{
private:
    QVector<Neuron*> m_neurons;

public:
    NeuronsLayer();

    unsigned getNeuronsNumber();

    void createNeurons( unsigned numOfNurons );
    void setTeachingFactor(double teachningFactor );

    void setupForwardConnections( NeuronsLayer* layer );
    void setupBackwardConnections( NeuronsLayer* layer );

    void setActivationValues(QVector<double> activationValues);
    QVector<double> getActivationValues();
    QVector<Neuron*> getNeurons();

    unsigned length();

    void activate();
    void computeError(QVector<double> expectedValues = QVector<double>() );
    void train();
    void relaxAllNeurons();

    Neuron* at ( unsigned id );
};

#endif // NAURONSLAYER_H
