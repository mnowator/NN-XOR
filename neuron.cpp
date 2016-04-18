#include "neuron.h"

#include <QtGlobal>
#include <QDebug>

Neuron::Neuron()
{

}

void Neuron::setTeachingFactor(double teachningFactor)
{
    m_teachingFactor = teachningFactor;
}

void Neuron::activate()
{
    double activatedValue = 0;

    foreach ( Neuron* neuron, m_backwardConnections.keys() )
    {
        if ( neuron->getState() == RELAXED )
            neuron->activate();

        activatedValue += neuron->getActivateValue()*m_backwardConnections[neuron];
    }

    activatedValue += m_bias;

    m_activatedValue = 1.0/(1.0+exp(-1*(activatedValue)));
}

void Neuron::computeError(double expectedValue)
{
    double errorValue = 0;

    if ( m_forwardConnections.empty() )
    {
        errorValue = expectedValue - m_activatedValue;
    }
    else
    {
        foreach ( Neuron* neuron, m_forwardConnections )
        {
            errorValue += neuron->getErrror(this);
        }
    }

    m_errorValue = errorValue;
}

double Neuron::getErrror(Neuron *neuron)
{
    return m_backwardConnections[neuron]*m_errorValue;
}

void Neuron::train()
{
    foreach ( Neuron* neuron, m_backwardConnections.keys() )
        m_backwardConnections[neuron] = m_backwardConnections[neuron]+m_teachingFactor*m_errorValue*neuron->getActivateValue()*(m_activatedValue*(1.0-m_activatedValue));

    m_bias += m_teachingFactor*m_errorValue*(m_activatedValue*(1.0-m_activatedValue));
}

void Neuron::setActivateValue(double value)
{
    m_activatedValue = value;
}

double Neuron::getActivateValue() const
{
    return m_activatedValue;
}

void Neuron::setState(STATE state)
{
    m_state = state;
}

STATE Neuron::getState() const
{
    return m_state;
}

void Neuron::setForwardConnection(Neuron *forwardNeuron)
{
    m_forwardConnections.append(forwardNeuron);
}

void Neuron::setBackwardConnection(Neuron *backwardNeuron)
{
    m_backwardConnections[backwardNeuron] = (((qrand()%1000)-500.0)/1000.0);
}





