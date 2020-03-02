/**
 * from a tutorial https://www.youtube.com/watch?v=KkwX7FkLfug
 * XOR training
 * TODO: Add error checking... everywhere.
 * get random files from trainign data
**/

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TrainingData.h"
#include "NeuralNet.h"
#include "Misc.h"

//using namespace std;

TrainingData top;
TrainingData TDExpectedOut;
TrainingData TDIn;
vector<double> inputVals, targetVals, resultVals;
vector<unsigned> topology;//array of values for amount of layers in the net
Net myNet;

void train() {
	int trainingPass = 0;
	for (int j = 0; j < 10; j++) {
		cout << "td?: " << TDIn.isEof() << endl;
		//while (!TDIn.isEof()) {
		++trainingPass;
		cout << endl << "Pass " << trainingPass << endl;

		//get new input data and feed it forward;
		if (TDIn.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		//showVectorVals(": Inputs:", inputVals);//displays input values
		myNet.feedForward(inputVals);

		//collect the net's actual results:
		myNet.getResults(resultVals);
		showVectorVals("Outputs", resultVals);

		//trian the net what the ouptus should have been:
		TDExpectedOut.getTargetOutputs(targetVals);
		showVectorVals("Targets:", targetVals);

		//change to new function that gets output based on image name from other file
		//depending on which itme it is, make 1 through 10 all zeroes excet for the place designated for the image type as 1

		assert(targetVals.size() == topology.back());//make sure topology is correct

		myNet.backProp(targetVals);

		//report how well the training is working averaged over recent
		cout << "net recent average error: "
			<< myNet.getRecentAverageError() << endl;
	}
}
void predict() {
	int trainingPass = 0;
	++trainingPass;
	cout << endl << "Pass " << trainingPass << endl;

	if (TDIn.getNextInputs(inputVals) != topology[0]) {
		abort();
	}
	myNet.feedForward(inputVals);

	myNet.getResults(resultVals);
	showVectorVals("Outputs", resultVals);

	//not needed here but included for testing
	TDExpectedOut.getTargetOutputs(targetVals);
	showVectorVals("Targets:", targetVals);
}

int main() {
	string imgName = "4";

	//int topo[4] = { 1765000, 16, 16, 10 };//using 4 as length
	int topo[4] = { 10000, 16, 16, 10 };//using 4 as length
	topologyGen(topo, 4);//makes topology to use
	//needs a gig or memory for the 353x500 image?!

	string in = "image";
	in.append(".txt");
	string expOut = "expected - Copy";
	expOut.append(".txt");

	top.open("topology.txt");
	top.getTopology(topology);
	myNet.genNet(topology);

	cout << endl << "Done setting up NN" << endl;

	bool i = true;
	do {

		TDExpectedOut.open(expOut);
		TDIn.open(in);

		cout << endl << "2 for image, 1 for trian, 0 for predict" << endl;
		int inp;
		cin >> inp;
		switch (inp) {
		case 0:
			predict();
			break;
		case 1:
			train();
			myNet.writeWeight();//writes created weights to file
		case 2:
			image(imgName);
			break;
		default:
			i = false;
			break;
		}

		TDIn.close();
		TDExpectedOut.close();
	} while (i);

	//compare output vals and depending on which one is highest depends on what program outputs

	//Input layer should be array size of largest image from dataset (will be one size as allimages will be the same size from true training)
}
