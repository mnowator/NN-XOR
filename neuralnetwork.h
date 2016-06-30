#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QVector>
#include "neuronslayer.h"


class NeuralNetwork
{
private:
    QVector<NeuronsLayer*> m_layers;
    NeuronsLayer* m_inputLayer;


public:
    NeuralNetwork();

    void setInputLayerDimension(unsigned dimension);
    void setLayersDimensions(QVector<unsigned> dimensions);
    void setTeachningFactor(double teachningFactor);
    void train(QVector<double> input, QVector<double> output);

    QVector<double> getResults(QVector<double> input);

    void saveNetwork(QString path);
    void loadNetwork(QString path);

};

#endif // NEURALNETWORK_H
