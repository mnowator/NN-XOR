#include "neuralnetwork.h"

NeuralNetwork::NeuralNetwork()
{

}

void NeuralNetwork::setLayersDimensions(QList<unsigned> dimensions)
{
    m_layers.clear();

    for ( unsigned i=0; i<dimensions.length(); ++i )
    {
        NeuronsLayer* layer = new NeuronsLayer();

        layer->createNeurons(dimensions[i]);

        if ( i == 0 )
        {
            m_inputLayer = new NeuronsLayer();

            m_inputLayer->createNeurons(dimensions[i]);
            layer->setupBackwardConnections(m_inputLayer);
        }
        else
        {
            layer->setupBackwardConnections(m_layers.front());
            m_layers.front()->setupForwardConnections(layer);
        }

        m_layers.append(layer);
    }
}

void NeuralNetwork::setTeachningFactor(double teachningFactor)
{
    foreach (NeuronsLayer* layer, m_layers)
        layer->setTeachingFactor(teachningFactor);
}

void NeuralNetwork::train(QList<double> input, QList<double> output)
{
    // Setup input layer
    m_inputLayer->setActivationValues(input);

    // Activate layers
    foreach ( NeuronsLayer* layer, m_layers )
        layer->activate();

    // Compute error
    for ( unsigned i=m_layers.length()-1; i >= 0; --i )
    {
        if ( i == m_layers.length()-1)
            m_layers[i]->computeError(output);
        else
            m_layers[i]->computeError();
    }

    // Train
    for ( unsigned i=m_layers.length()-1; i >= 0; --i )
        m_layers[i]->train();
}

QList<double> NeuralNetwork::getResults(QList<double> input)
{
    // Setup input layer
    m_inputLayer->setActivationValues(input);

    // Activate layers
    foreach ( NeuronsLayer* layer, m_layers )
        layer->activate();

    return m_layers.back()->getActivationValues();
}





















