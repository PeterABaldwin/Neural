/**
 * from a tutorial https://www.youtube.com/watch?v=KkwX7FkLfug
 * XOR training
 * TODO: Add error checking... everywhere.
**/

#include <iostream>
#include "TrainingData.h"
#include "NeuralNet.h"

using namespace std;

/*
* Param: 
*/
void showVectorVals(string label, vector<double> &v) {
	cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}

	cout << endl;
}

int main() {

	TrainingData trainData("trainingData.txt");

	vector<unsigned> topology;//array of values for amount of layers in the net
	trainData.getTopology(topology);

	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;

	while (!trainData.isEof()) {
		++trainingPass;
		cout << endl << "Pass " << trainingPass;

		//get new input data and feed it forward;
		if (trainData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		showVectorVals(": Inputs:", inputVals);
		myNet.feedForward(inputVals);

		//collect the net's actual results:
		myNet.getResults(resultVals);
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
	string useless;
	cin >> useless;


	//old
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
	return 1;
}
