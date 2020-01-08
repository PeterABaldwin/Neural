#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

#include "BMP.h"
#include <set>

class RGB {
public:
    RGB(int px, int py);
    int rgb[4];//red, green, blue, alpha
    int pos[2];//position x, position y
private:
};

RGB::RGB (int px, int py) {
    srand(time(NULL)*(px + py));
    for (int i = 0; i < 4; i++) {
        rgb[i] = rand() / 255;
    }
    /*rgb[0] = rand() / 255;
    rgb[1] = rand() / 255;
    rgb[2] = rand() / 255;*/
    rgb[3] = 255;
    pos[0] = px;
    pos[1] = py;
}

set<RGB*> quadrent;

void generate() {
    string name = "rgb0";
    int xy[2] = { 0, 0 };

    for (int i = 0; i < 4; i++) {
        name.pop_back();
        name.append("" + i);

        if (i == 0) { xy[0] = 0; xy[1] = 50; }
        else if (i == 1) { xy[0] = 50; xy[1] = 50; }
        else if (i == 2) { xy[0] = 50; xy[1] = 0; }
        else if (i == 3) { xy[0] = 0; xy[1] = 0; }
        RGB* name = new RGB(xy[0], xy[1]);
        quadrent.insert(name);
    }
}

int main() {

    generate();
    
    //create BMP in memory
    BMP bmp2(100, 100, false);//width, height alpha(boolean)
    //modify bmp
    bmp2.fill_region(0, 0, 50, 50, 51, 102, 255, 255);//padding left, padding bottom, width, height, Red, Green, Blue, alpha 
    
    cout << "size: " << quadrent.size() << endl;
    


    for (set<RGB*>::iterator itr = quadrent.begin(); itr != quadrent.end(); itr++)
    {
        bmp2.fill_region((*itr)->pos[0], (*itr)->pos[1], 50, 50, (*itr)->rgb[0], (*itr)->rgb[1], (*itr)->rgb[2], 0);//padding left, padding bottom, width, height, Red, Green, Blue, alpha 

        //cout << itr << " | ";

        cout << (*itr)->rgb[0] << " | ";
        cout << (*itr)->rgb[1] << " | ";
        cout << (*itr)->rgb[2] << " | ";
        cout << (*itr)->rgb[3] << " | ";
        cout << endl;
    }



    //write bmp
    bmp2.write("img_test.bmp");
    /*
    //read bmp
    BMP bmp("/tmp/img_test.bmp");
    bmp.write("/tmp/img_copy");
    */
}