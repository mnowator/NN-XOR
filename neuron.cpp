#include "neuron.h"

#include <QtGlobal>
#include <QDebug>

Neuron::Neuron()
{

}

void Neuron::setTeachingFactor(double teachningFactor)
// Ustawianie wsp. uczenia
{
    m_teachingFactor = teachningFactor;
}

void Neuron::activate()
// Funkcja aktywacji
{
    double activatedValue = 0;

    // Aktywacja wszystkich neuronow z polaczen wstecznych, oraz akumulacja
    // aktywowanych wartosci przemnozonych przez wage polaczenia synaptycznego
    foreach ( Neuron* neuron, m_backwardConnections.keys() )
    {
        activatedValue += neuron->getActivateValue()*m_backwardConnections[neuron];
    }

    activatedValue += m_bias; // Dodanie biasu

    m_activatedValue = 1.0/(1.0+exp(-1.0*(activatedValue))); // Sigmoidalna funkcja aktywacji
}

void Neuron::computeError(double expectedValue)
// Funkcja obliczajaca blad
{
    double errorValue = 0;

    if ( m_forwardConnections.empty() ) // Jesli nie ma żadnych polaczen w "przod"
    {
        // Wtedy obliczamy blad na podstawie wartosci aktywacji i oczekiwanej wartosci
        errorValue = expectedValue - m_activatedValue;
    }
    else
    // Natomiast jesli neuron posiada polaczenia w "przod"
    {
        foreach ( Neuron* neuron, m_forwardConnections )
        // Wtedy sumujemy bledy ze wszystkich polaczen w "przod"
        {
            errorValue += neuron->getErrror(this);
        }
    }

    // Przypisanie wyliczonej wartosci bledu
    m_errorValue = errorValue;
}

double Neuron::getErrror(Neuron *neuron)
// Funkcja zwracajajaca blad na podstawie wskaznika
{
    return m_backwardConnections[neuron]*m_errorValue;
}

void Neuron::train()
// Funkcja przeprowadzajaca proces uczenia
{
    // Dla kazdego polaczenia w "tyl" liczyny korekcje wagi wg reguly Rosenblatta
    foreach ( Neuron* neuron, m_backwardConnections.keys() )
        m_backwardConnections[neuron] = m_backwardConnections[neuron]+ m_teachingFactor*m_errorValue*neuron->getActivateValue()*(m_activatedValue*(1.0-m_activatedValue));

    // Korekcja bias'u
    m_bias += m_teachingFactor*m_errorValue*(m_activatedValue*(1.0-m_activatedValue));
}

QVector<double> Neuron::getWeights(QVector<Neuron *> layer)
{
    QVector<double> weights;

    foreach( Neuron* neuron, layer )
        weights.append( m_backwardConnections[neuron] );

    return weights;
}

void Neuron::setActivateValue(double value)
// Funkcja ustawia wartosc aktywacji
{
    m_activatedValue = value;
}

double Neuron::getActivateValue() const
// Funkcja zwaraca wartosc aktywacji
{
    return m_activatedValue;
}

void Neuron::setState(STATE state)
// Funkcja ustawia stan neuronu
{
    m_state = state;
}

STATE Neuron::getState() const
// Funkcja zwraca stan neuronu
{
    return m_state;
}

void Neuron::setForwardConnection(Neuron *forwardNeuron)
// Funkcja dolacza polaczenie w "przod"
{
    m_forwardConnections.append(forwardNeuron);
}

void Neuron::setBackwardConnection(Neuron *backwardNeuron)
// Funkcja ustanawia polaczenie w "tyl" oraz losuje wage polaczenia
{
    m_backwardConnections[backwardNeuron] = (((qrand()%1000)-500.0)/1000.0);
}





