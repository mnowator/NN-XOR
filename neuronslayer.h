#ifndef NAURONSLAYER_H
#define NAURONSLAYER_H

#include <QList>
#include "neuron.h"


class NeuronsLayer
{
private:
    QList<Neuron*> m_neurons;

public:
    NeuronsLayer();

    unsigned getNeuronsNumber();

    void createNeurons( unsigned numOfNurons );
    void setTeachingFactor(double teachningFactor );

    void setupForwardConnections( NeuronsLayer* layer );
    void setupBackwardConnections( NeuronsLayer* layer );

    void setActivationValues(QList<double> activationValues);
    QList<double> getActivationValues();

    void activate();
    void computeError(QList<double> expectedValues = QList<double>() );
    void train();
    void relaxAllNeurons();

    Neuron* at ( unsigned id );
};

#endif // NAURONSLAYER_H
