#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QList>
#include "neuronslayer.h"


class NeuralNetwork
{
private:
    QList<NeuronsLayer*> m_layers;
    NeuronsLayer* m_inputLayer;


public:
    NeuralNetwork();

    void setLayersDimensions(QList<unsigned> dimensions);
    void setTeachningFactor(double teachningFactor);
    void train(QList<double> input, QList<double> output);

    QList<double> getResults(QList<double> input);

};

#endif // NEURALNETWORK_H
