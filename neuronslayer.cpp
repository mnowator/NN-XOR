#include "neuronslayer.h"

NeuronsLayer::NeuronsLayer()
{

}

unsigned NeuronsLayer::getNeuronsNumber()
{
    return m_neurons.length();
}

void NeuronsLayer::createNeurons(unsigned numOfNurons)
{
    m_neurons.clear();

    for ( unsigned i=0; i<numOfNurons; ++i)
    {
        Neuron* neuron = new Neuron();

        m_neurons.push_back(neuron);
    }
}

void NeuronsLayer::setTeachingFactor(double teachningFactor)
{
    foreach( Neuron* neuron, m_neurons )
        neuron->setTeachingFactor(teachningFactor);
}

void NeuronsLayer::setupForwardConnections(NeuronsLayer *layer)
{
    foreach( Neuron* neuron, m_neurons )
        for ( unsigned i=0; i<layer->getNeuronsNumber(); ++i )
            neuron->setForwardConnection(layer->at(i));
}

void NeuronsLayer::setupBackwardConnections(NeuronsLayer *layer)
{
    foreach( Neuron* neuron, m_neurons )
        for ( unsigned i=0; i<layer->getNeuronsNumber(); ++i )
            neuron->setBackwardConnection(layer->at(i));
}

void NeuronsLayer::setActivationValues(QVector<double> activationValues)
{
    for ( unsigned i=0; i<activationValues.length(); ++i )
        m_neurons[i]->setActivateValue(activationValues[i]);
}

QVector<double> NeuronsLayer::getActivationValues()
{
    QVector<double> output;

    foreach( Neuron* neuron, m_neurons )
        output.append(neuron->getActivateValue());

    return output;
}

QVector<Neuron *> NeuronsLayer::getNeurons()
{
    return m_neurons;
}

unsigned NeuronsLayer::length()
{
    return m_neurons.length();
}

void NeuronsLayer::activate()
{
    foreach ( Neuron* neuron, m_neurons)
    {
        neuron->activate();
    }
}

void NeuronsLayer::computeError(QVector<double> expectedValues)
{
    if ( expectedValues.length() == m_neurons.length() )
        for ( unsigned i=0; i<m_neurons.length(); ++i)
        {
            m_neurons.at(i)->computeError(expectedValues[i]);
        }
    else
        foreach ( Neuron* neuron, m_neurons)
        {
            neuron->computeError();
        }
}

void NeuronsLayer::train()
{
    foreach ( Neuron* neuron, m_neurons)
        neuron->train();
}

void NeuronsLayer::relaxAllNeurons()
{
    foreach ( Neuron* neuron, m_neurons)
        neuron->setState(RELAXED);
}

Neuron *NeuronsLayer::at(unsigned id)
{
    return m_neurons[id];
}
