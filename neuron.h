#ifndef NEURON_H
#define NEURON_H

#include <QHash>

enum STATE
{
    ACTIVATED,
    ERROR_COMPUTED,
    RELAXED,
};

class Neuron
{
private:
    QList<Neuron* > m_forwardConnections;
    QHash<Neuron*, double > m_backwardConnections;

    double m_bias=0;
    double m_activatedValue=0;
    double m_errorValue=0;
    double m_teachingFactor=0;

    STATE m_state = RELAXED;

public:
    Neuron();

    void setTeachingFactor(double teachningFactor);

    void activate();
    void computeError(double expectedValue=0);

    double getErrror(Neuron* neuron);

    void train();

    void setActivateValue(double value);
    double getActivateValue() const;

    void setState(STATE state);
    STATE getState() const;

    void setForwardConnection(Neuron* forwardNeuron);
    void setBackwardConnection(Neuron* backwardNeuron);
};

#endif // NEURON_H
