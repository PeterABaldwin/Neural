//from a tutorial https://www.youtube.com/watch?v=KkwX7FkLfug

class Net {
public:
    Net(topology);
    void feeForward(inputVals);
    void backProp(targetVals);
    void getResults(resultVals) const;

private:
};

int main() {
    Net myNet(topology);
    

    myNet.feeForward(inputVals);//training
    myNet.backProp(targetVals);//what output should have been (backpropogation)
    myNet.getResults(resultVals);//after trained
}
//a test