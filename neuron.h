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
    // Lista polaczen w "przod"
    QList<Neuron* > m_forwardConnections;
    // Tablica asocjacyjna laczaca wskaznik do neuronu z waga
    QHash<Neuron*, double > m_backwardConnections;

    double m_bias=0;
    double m_activatedValue=0;
    double m_errorValue=0;
    double m_teachingFactor=0;

    STATE m_state = RELAXED;

public:
    Neuron();

    // Funkcja ustawiajace wsp. uczenia
    void setTeachingFactor(double teachningFactor);

    // Funkcja aktywujaca neuron
    void activate();
    // Funkcja obliczajaca blad
    void computeError(double expectedValue=0);

    // Funkcja zwarcajaca wartosc bledu bazujac na wskazniku Neuronu w polaczeniach
    double getErrror(Neuron* neuron);

    // Funkcja modyfikujaca wagi polaczen synaptycznych oraz bias
    void train();

    // Funkcja szytwno ustawiajaca wartosc aktywacji neuronu
    // Uzywana do sztucznego imitowania wektorow wejsciowych
    void setActivateValue(double value);
    // Funckja zwarajaca wartosc aktywacji neuronu
    double getActivateValue() const;

    // Funkcja sluzaca do ustawienia stanu neuronu
    void setState(STATE state);
    // Funckja zwracajaca aktualny stan neuronu
    STATE getState() const;

    // Funkcja ustawiajaca polaczenie z innym neuronem w "przod"
    void setForwardConnection(Neuron* forwardNeuron);
    // Funkcja ustawiacja polaczenie z innym neuronemw w "tyl"
    void setBackwardConnection(Neuron* backwardNeuron);
};

#endif // NEURON_H
