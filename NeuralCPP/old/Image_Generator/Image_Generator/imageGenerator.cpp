#include <iostream>
#include "Image.h"

using namespace std;

int main() {
    cout << "how many itterations? ";
    string input = "1";
    cin >> input;
    int gen = 1;//default make one image

    //check if user input is an integer
    stringstream ss(input);
    if ((ss >> gen).fail())
    {
        cout << "input an integer.";
        return 2;
    }

    Image Img(gen);
}

