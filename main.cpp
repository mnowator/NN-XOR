#include <QCoreApplication>
#include <QtGlobal>
#include <QTime>
#include <QPair>
#include <iostream>
#include <QDebug>
#include <random>
#include <QFile>
#include <vector>

#include "neuralnetwork.h"
#include "mnist_reader.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Generator licz pseudolosowych
    qsrand(QTime::currentTime().msec());

    auto dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>();

    QVector<QVector<double> > trainingImages;
    QVector<QVector<double> > trainingOutputs;
    QVector<unsigned> trainingLabels;

    double startTeachningFactor = 0.5;
    double finishTeachingFactor = 0.02;
    unsigned numOfEpoach = 50;

    NeuralNetwork nn;


    for ( unsigned i=0; i<dataset.training_images.size(); ++i )
    {
        QVector<double> image;

        for ( unsigned j=0; j<dataset.training_images[i].size(); ++j )
            image.append(dataset.training_images[i][j]/255.0f);

        trainingImages.append(image);
        trainingLabels.append(dataset.training_labels[i]);
    }

    for ( unsigned i=0; i<10; ++i )
    {
        QVector<double> output;

        for ( unsigned j=0; j<10; ++j )
            if ( i == j )
                output.append(1.0f);
            else
                output.append(0.0f);

        trainingOutputs.append(output);
    }

    nn.setLayersDimensions(QVector<unsigned>({300,10}));
    nn.setInputLayerDimension(784);

    // Proces uczenia
    for ( unsigned i=0; i<numOfEpoach; ++i )
    {
        qDebug() << "Epoach = " << i+1;
        double teachingFactor = startTeachningFactor - (((startTeachningFactor-finishTeachingFactor)/(float)numOfEpoach)*i);
        double mean = 0;
        unsigned idx = qrand() % 60000;
        QVector<double> testedOutput;

        nn.setTeachningFactor(teachingFactor);

        for ( unsigned j=0; j<trainingImages.length(); ++j)
            nn.train(trainingImages[j], trainingOutputs[trainingLabels[j]]);

        qDebug() << "Testing network with randomized image.";
        qDebug() << "Label: " << trainingLabels[idx];

        testedOutput = nn.getResults(trainingImages[idx]);

        for ( unsigned j=0; j<testedOutput.length(); ++j)
        {
            qDebug() << j << " -- " << testedOutput[j] * 100.0 << "%";
        }
    }


    nn.saveNetwork("neuralnetwork.xml");

    return a.exec();
}













