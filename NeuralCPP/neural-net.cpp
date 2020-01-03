//from a tutorial https://www.youtube.com/watch?v=KkwX7FkLfug

#include <vector>
#include <iostream>

using namespace std;

class Neuron {};

typedef vector<Neuron> Layer;

class Net {
public:
    Net(const vector<unsigned> &topology);
    void feeForward(const vector<double> &inputVals) {};
    void backProp(const vector<double> &targetVals) {};
    void getResults(const vector<double> &resultVals) const {};

private:
    vector<Layer> m_layers; //a vector of layers. m_layers[layerNum][neuronNum] first reference is layer, second is the neron in the layer
};

Net::Net(const vector<unsigned> &topology) {
    unsigned numLayers = topology.size();//layers from incoming topology object
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {//loop to create a new layer in m_layers
        m_layers.push_back(Layer());

        //loop for putting neurons into created layer
        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum){// <= to include bias
            m_layers.back().push_back(Neuron());//.back gives last element
            cout << "made a Neuron!" << endl;
        }
    }
}


int main() {

    vector<unsigned> topology;//array of values for amount of layers in the net
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);
    Net myNet(topology);


    //Net myNet(topology);
    
    vector<double> inputVals;//std:: from C++ library (can remove if it feels like clutter) (vectors are std)
    myNet.feeForward(inputVals);//training

    vector<double> targetVals;
    myNet.backProp(targetVals);//what output should have been (backpropogation)

    vector<double> resultVals;
    myNet.getResults(resultVals);//after trained
}