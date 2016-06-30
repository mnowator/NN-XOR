#include "neuralnetwork.h"

#include <QDomDocument>
#include <QDebug>
#include <QFile>
#include <QTextStream>

NeuralNetwork::NeuralNetwork()
{

}

void NeuralNetwork::setInputLayerDimension(unsigned dimension)
{
    m_inputLayer = new NeuronsLayer;

    m_inputLayer->createNeurons(dimension);
    m_layers.front()->setupBackwardConnections(m_inputLayer);
}

void NeuralNetwork::setLayersDimensions(QVector<unsigned> dimensions)
{
    m_layers.clear();

    for ( unsigned i=0; i<dimensions.length(); ++i )
    {
        NeuronsLayer* layer = new NeuronsLayer();

        layer->createNeurons(dimensions[i]);
        
        if ( m_layers.length() > 0 )
        {
            layer->setupBackwardConnections(m_layers.back());
            m_layers.back()->setupForwardConnections(layer);
        }

        m_layers.append(layer);
    }
}

void NeuralNetwork::setTeachningFactor(double teachningFactor)
{
    foreach (NeuronsLayer* layer, m_layers)
        layer->setTeachingFactor(teachningFactor);
}

void NeuralNetwork::train(QVector<double> input, QVector<double> output)
{
    // Setup input layer
    m_inputLayer->setActivationValues(input);

    // Activate layers
    foreach ( NeuronsLayer* layer, m_layers )
        layer->activate();

    // Compute error
    for ( int i=m_layers.length()-1; i >= 0; --i )
    {
        if ( i == m_layers.length()-1)
            m_layers[i]->computeError(output);
        else
            m_layers[i]->computeError();
    }

    // Train
    for ( int i=m_layers.length()-1; i >= 0; --i )
        m_layers[i]->train();
}

QVector<double> NeuralNetwork::getResults(QVector<double> input)
{
    // Setup input layer
    m_inputLayer->setActivationValues(input);

    // Activate layers
    foreach ( NeuronsLayer* layer, m_layers )
        layer->activate();

    return m_layers.back()->getActivationValues();
}

void NeuralNetwork::saveNetwork(QString path)
{
    QDomDocument dom("NN");
    QFile file(path);

    QDomElement root = dom.createElement("NeuralNetwork");
    QDomElement element, layers;

    dom.appendChild(root);

    element = dom.createElement("LayersNumber");
    element.appendChild(dom.createTextNode(QString::number(m_layers.length())));
    root.appendChild(element);

    element = dom.createElement("InputLayerLength");
    element.appendChild(dom.createTextNode(QString::number(m_inputLayer->length())));
    root.appendChild(element);

    layers = dom.createElement("Layers");

    for ( unsigned i=0; i<m_layers.length(); ++i )
    {
        QDomElement layerElement = dom.createElement("Layer");
        QDomElement neurons = dom.createElement("Neurons");

        QDomElement neuronsNumber = dom.createElement("NeuronsNumber");
        neuronsNumber.appendChild(dom.createTextNode(QString::number(m_layers[i]->length())));
        layerElement.appendChild(neuronsNumber);

        for ( unsigned j=0; j<m_layers[i]->length(); ++j )
        {
            QDomElement neuronElement = dom.createElement("Neuron");
            QDomElement weightsElement = dom.createElement("Weights");
            QVector<double> weights;

            if ( i== 0 )
                weights = m_layers[i]->getNeurons()[j]->getWeights(m_inputLayer->getNeurons());
            else
                weights = m_layers[i]->getNeurons()[j]->getWeights(m_layers[i-1]->getNeurons());

            foreach( double weight, weights )
            {
                QDomElement weightElement = dom.createElement("Weight");

                weightElement.appendChild(dom.createTextNode(QString::number(weight)));
                weightsElement.appendChild(weightElement);
            }


            neuronElement.appendChild(weightsElement);
            neurons.appendChild(neuronElement);
        }

        layerElement.appendChild(neurons);
        layers.appendChild(layerElement);
    }

    root.appendChild(layers);

    if ( file.open( QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream textStream( &file );
        textStream << dom.toString();
    }
    file.close();
}





















