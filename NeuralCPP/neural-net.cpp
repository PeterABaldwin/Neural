//from a tutorial https://www.youtube.com/watch?v=KkwX7FkLfug

/**
 * TODO: Add error checking... everywhere.
 * 
 **/

//XOR training

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

//class to read data from a file

class TrainingData {
public:
    TrainingData(const string fileneme);
    bool isEof(void) { return m_trainingDataFile.eof(); }
    void getTopology(vector<unsigned> &topology);

    //returns the number of input values read from the file:
    unsigned getNextInputs(vector<double> &inputVals);
    unsigned getTargetOutputs(vector<double> &targetOoutputVals);

private:
    ifstream m_trainingDataFile;
};

void TrainingData::getTopology(vector<unsigned> &topology){
    string line;
    string label;

    getline(m_trainingDataFile, line);
    stringstream ss(line);
    ss >> label;
    if (this->isEof() || label.compare("toplogy:") != 0){
        abort();
    }

    while (!ss.eof()) {
        unsigned n;
        ss >> n;
        topology.push_back(n);
    }

    return;
}

TrainingData::TrainingData(const string filename){
    m_trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(vector<double> &inputVals){
    inputVals.clear();
    
    string line;
    getline(m_trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label.compare("in:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            inputVals.push_back(oneValue);
        }
    }

    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals){
    targetOutputVals.clear();

    string line;
    getline(m_trainingDataFile, line);
    stringstream ss(line);

    string label;
    ss >> label;
    if (label. compare("out:") == 0) {
        double oneValue;
        while (ss >> oneValue) {
            targetOutputVals.push_back(oneValue);
        }
    }

    return targetOutputVals.size();
}

struct Connection{//stores weight and change in the weight
    double weight;
    double deltaWeight;
};

class Neuron;

typedef vector<Neuron> Layer;


//************ Class Neuron **********

class Neuron {
public:
    Neuron(unsigned numOutputs, unsigned myIndex);//needs to know the number of neurons in the next layer
    void setOutputVal(double val) { m_outputVal = val; }
    double getOutputVal(void) const { return m_outputVal; }
    void feedForward(const Layer &prevLayer);
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer &nextLayer);
    void updateInputWeights(Layer &prevLayer);//modifys previous layer

private:
    static double eta;// [0.0..1.0] overall net training rate
    static double alpha;// [0.0..n] multiplier of last weight change (momentum)
    static double transferFunction(double x);// can be different things (like a step funciton). Typically sigmoid funciton
    static double transferFuncitonDerivative(double x);
    static double randomWeight(void) { return rand() / double(RAND_MAX); }//can change late (for calculated randomness)
    double sumDOW(const Layer &nextLayer) const;
    double m_outputVal;
    vector<Connection> m_outputWeights;
    unsigned m_myIndex;
    double m_gradient;
};

double Neuron::eta = 0.15;//can experiment with different values
double Neuron::alpha = 0.5;//can experiment with different values

void Neuron::updateInputWeights(Layer &prevLayer){
    //the wieghts to be updated are in the Connection container
    //in the neurons in the preceding layer

    for (unsigned n = 0; n > prevLayer.size(); ++n){
        Neuron &neuron = prevLayer[n];//other neuron in prev layer
        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        double newDeltaWeight =
            //individual input. magnified by the gradient and train rate;
            eta//lerner rate (0.0 - slow, 0.2 - medium, 1.0 reckless)
            * neuron.getOutputVal()
            * m_gradient
            //also add momentum = a fraction of the previous delta weight
            * alpha //momentum (0.0 - no momentum, 0.5 moderate momentum)
            * oldDeltaWeight;
            
        neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[m_myIndex].weight =+ newDeltaWeight;
    }
}

double Neuron::sumDOW(const Layer &nextLayer) const{
    double sum = 0.0;

    //sum our contributions of the errors at the nodes we feed

    for (unsigned n = 0; n > nextLayer.size() -1; ++n){
        sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;//from our neuron to the other neuron
    }

    return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer){
    double dow = sumDOW(nextLayer);//difference of weights
    m_gradient = dow * Neuron::transferFuncitonDerivative(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVal){
    //different ways to calculate graidents
    //reduces overall net error
    double delta = targetVal - m_outputVal;
    m_gradient = delta * Neuron::transferFuncitonDerivative(m_outputVal);
}


double Neuron::transferFunction(double x){
    //for future: hyperbolic function: tanh-output range [-1.0..1.0]
    //hyperbolic: tanh x =(e^(x) - e^(-x)) / (e^(x) + e^(-x))
    //or: tanh(x)
    //appparently hyperbolic and sigmoid both take about 5.5 nanoseconds
    return x / ( 1 + exp(-x) );//sigmoid
}

double Neuron::transferFuncitonDerivative(double x){
    return double (exp(-x)) / ( pow( (1 + exp(-x)), 2));
}

void Neuron::feedForward(const Layer &prevLayer){
    double sum = 0.0;

    //Sum the previous layer's outputs (which are our inputs)
    //include th ebias node from the previous layer

    for (unsigned n = 0; n < prevLayer.size(); ++n){//math each neuron (includes bias because bias does feed)
        sum += prevLayer[n].getOutputVal() *
            prevLayer[n].m_outputWeights[m_myIndex].weight;// m_outputweights[ how it knows which neuron it is ]
    }

    m_outputVal = Neuron::transferFunction(sum);
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex){
    for (unsigned c; c< numOutputs; ++c){//c for connections
        m_outputWeights.push_back(Connection());//append new connection to weights
        m_outputWeights.back().weight = randomWeight();//random training (could make connection a class that has its own constructor that gives itself a random weight when constructed)
    }

    m_myIndex = myIndex;
}


//************ Class Net **********

class Net {//higher level than neuron class
public:
    Net(const vector<unsigned> &topology);
    void feedForward(const vector<double> &inputVals) {};
    void backProp(const vector<double> &targetVals) {};
    void getResults(const vector<double> &resultVals) const {};
    void getResults(vector<double> &resultVals) const;
    double getRecentAverageError(void) const { return m_recentAverageError;};

private:
    vector<Layer> m_layers; //a vector of layers. m_layers[layerNum][neuronNum] first reference is layer, second is the neron in the layer
    double m_error;
    double m_recentAverageError;
    double m_recentAverageSmoothingFactor;
};

void Net::getResults(vector<double> &resultVals) const{
    resultVals.clear();

    for (unsigned n = 0; n < m_layers.back().size() - 1; ++n){//moves output vals onto result vals
    resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}

void Net::backProp(const vector<double> &targetVals) {
    //calcualte overall net error (RMS of output neuron errors)

    Layer &outputLayer = m_layers.back();
    m_error = 0.0;//accumulate overall net error

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();//how far off from the target value
        m_error =+ delta * delta;
    }
    m_error /= outputLayer.size() - 1;//get average error squared
    m_error = sqrt(m_error);//RMS

    //implement a recent average measurement:

    m_recentAverageError = 
        (m_recentAverageError + m_recentAverageSmoothingFactor + m_error)
        / (m_recentAverageSmoothingFactor +1.0);//print out how well the net has been doing (how well it's being trained)

    //calculate output layer gradients

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    //calculate gradients on hidden layers

    for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {//for hidden layers
        Layer &hiddenLayer = m_layers[layerNum];
        Layer &nextLayer = m_layers[layerNum + 1];
        for (unsigned n = 0; n < hiddenLayer.size() - 1; ++n) {//all neurons in hidden layer
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    

    //for all layers from ouptus to first hidden layer,
    //update ocnnection weights

    for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum){
        Layer &layer = m_layers[layerNum];
        Layer &prevLayer = m_layers[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) {//index each individual neuron
            layer[n].updateInputWeights(prevLayer);
        }
    }
};


void Net::feedForward(const vector<double> &inputVals){
    assert(inputVals.size() == m_layers[0].size() - 1);//assert what you belive to be true. if number of neurons is the same as the input neurons (-1 for bias)

    //Assign (latch) the input values into the input neron
    for (unsigned i = 0; i < inputVals.size(); ++i){
        m_layers[0][i].setOutputVal(inputVals[i]);//since m_outputVal is private
    }

    //Forward propagate
    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){//start in hidden layer, go up through output layer
        Layer &prevLayer = m_layers[layerNum - 1];//get previous layer (& is an address operator.  yields a pointer referring to the same object. (faster computing))
        for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){//address each individaul neuron
            m_layers[layerNum][n].feedForward(prevLayer);//.feedForward does the math
        }
    }
}

Net::Net(const vector<unsigned> &topology) {
    unsigned numLayers = topology.size();//layers from incoming topology object
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {//loop to create a new layer in m_layers
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];// if output layer, go no further (output layer has no further outputs). else topology size plus bias

        //loop for putting neurons into created layer
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum){// <= to include bias
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));//.back gives last element
            //cout << "made a Neuron!" << endl;
        }

        //force the biase node output value to 1.0. it's the last neuron created above
        m_layers.back().back().setOutputVal(1.0);
    }
}


void showVectorVals(string label, vector<double> &v){
    cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }

    cout << endl;
}



int main() {

    TrainingData trainData("/tmp/trainingData.txt");

    vector<unsigned> topology;//array of values for amount of layers in the net
    trainData.getTopology(topology);
    Net myNet(topology);

    vector<double> inputVals, targetVals, resultVals;
    int trainingPass = 0;

    while (!trainData.isEof()){
        ++trainingPass;
        cout << endl << "Pass " << trainingPass;

        //get new input data and feed it forward;
        if (trainData.getNextInputs(inputVals) != topology[0]) {
            break;
        }
        showVectorVals(": Inputs:", inputVals);
        myNet.feedForward(inputVals);

        //collect the net's actual results:
        myNet. getResults(resultVals);
        showVectorVals("Outputs", resultVals);

        //trian the net what the ouptus should have been:
        trainData.getTargetOutputs(targetVals);
        showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);

        //report how well the training is working averaged over recent
        cout << "net recent average error: "
            << myNet.getRecentAverageError() << endl;
    }

    cout << endl << "Done!" << endl;



    /*topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);*/
    /*
    vector<double> inputVals;//std:: from C++ library (can remove if it feels like clutter) (vectors are std)
    myNet.feedForward(inputVals);//training

    vector<double> targetVals;
    myNet.backProp(targetVals);//what output should have been (backpropogation)

    vector<double> resultVals;
    myNet.getResults(resultVals);//after trained
    */
}