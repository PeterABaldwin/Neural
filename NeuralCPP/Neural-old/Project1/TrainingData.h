#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct TrainingData {
public:
	TrainingData(const string fileneme);
	bool isEof(void) { return m_trainingDataFile.eof(); }
	void getTopology(vector<unsigned>& topology);

	//returns the number of input values read from the file:
	unsigned getNextInputs(vector<double>& inputVals);
	unsigned getTargetOutputs(vector<double>& targetOoutputVals);

private:
	ifstream m_trainingDataFile;
};

void TrainingData::getTopology(vector<unsigned>& topology) {
	string line;
	string label;

	getline(m_trainingDataFile, line);
	//cout << "getline: " << getline(m_trainingDataFile, line) << endl;
	stringstream ss(line);
	ss >> label;
	if (this->isEof()) {
		cout << "topology error is isEof, label: " << label << endl;
		abort();
	}
	else if (label.compare("topology:") != 0) {
		cout << "topology error is compare, label: " << label << endl;
		abort();
	}

	while (!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	return;
}

TrainingData::TrainingData(const string filename) {
	m_trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(vector<double>& inputVals) {
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

unsigned TrainingData::getTargetOutputs(vector<double>& targetOutputVals) {
	targetOutputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	string label;
	ss >> label;
	if (label.compare("out:") == 0) {
		double oneValue;
		while (ss >> oneValue) {
			targetOutputVals.push_back(oneValue);
		}
	}

	return targetOutputVals.size();
}