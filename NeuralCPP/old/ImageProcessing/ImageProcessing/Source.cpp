#include <iostream>
#include <sstream>
#include "Misc.h"

using namespace std;

int main() {
    /*
    cout << "Image number: ";
    string s0 = "1";
    cin >> s0;
    std::string s1 = "//img//image";
    s1.append(s0);
    s1.append(".bmp");
    std::string s1 = "2.bmp";
    */

    for (int i = 100; i > 0; i--) {


        cout << "Image number: ";
        string s0 = "1";
        cin >> s0;
        std::string s1 = s0;
        s1.append(".bmp");




        char const* name = s1.c_str();
        process(name);
    }
    return 0;
}