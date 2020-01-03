//from a tutorial https://www.youtube.com/watch?v=KkwX7FkLfug

#include <vector>

using namespace std;

class Net {
public:
    Net(topology);
    void feeForward(const vector<double> &inputVals);
    void backProp(const vector<double> &targetVals);
    void getResults(const vector<double> &resultVals) const;

private:
};

int main() {
    Net myNet(topology);
    
    std::vector<double> inputVals;//std from C++ library (can remove if it feels like clutter)
    myNet.feeForward(inputVals);//training

    vector<double> targetVals;
    myNet.backProp(targetVals);//what output should have been (backpropogation)

    vector<double> resultVals;
    myNet.getResults(resultVals);//after trained
}