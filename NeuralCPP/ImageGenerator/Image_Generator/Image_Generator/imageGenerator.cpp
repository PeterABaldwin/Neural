#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <set>
#include "BMP.h"

using namespace std;

void delay(int seconds)
{
    time_t start, current;

    time(&start);

    do
    {
        time(&current);
    } while ((current - start) < seconds);
}

class RGB {
public:
    RGB(int px, int py, int s, int d);//s is seed
    int rgb[4];//red, green, blue, alpha
    int pos[2];//position x, position y
private:
};

RGB::RGB(int px, int py, int s, int d) {
    srand(time(NULL) + (s*d));
    for (int i = 0; i < 4; i++) {
        rgb[i] = rand() % 255;
    }
    rgb[3] = 255;
    pos[0] = px;
    pos[1] = py;
}

RGB generate(int xy[2], int i, int s) {// c = create, g = generate
    delay(1);
    return RGB(xy[0], xy[1], i, s);
}

typedef vector<RGB> img;

class Image {
public:
    vector<img> i_img;
    Image(const int g);
    void MakeImage(int im, const char * name);
};

Image::Image(const int gen) {

    for (int g = 0; g < gen; g++) {
        i_img.push_back(img());
        for (int c = 0; c < 4; c++) {

            int xy[2] = { 0, 0 };

            if (c == 0) { xy[0] = 0; xy[1] = 50; }
            else if (c == 1) { xy[0] = 50; xy[1] = 50; }
            else if (c == 2) { xy[0] = 50; xy[1] = 0; }
            else if (c == 3) { xy[0] = 0; xy[1] = 0; }

            i_img.back().push_back(generate(xy, gen*g, c));
        }
        cout << "Image: " << g << " | part's made: " << i_img[g].size() << endl;


        for (int c = 0; c < 4; c++) {
            cout << "red: " << i_img[g][c].rgb[0] << " | ";
            cout << "green: " << i_img[g][c].rgb[1] << " | ";
            cout << "blue: " << i_img[g][c].rgb[2] << " | ";
            cout << "position: x " << i_img[g][c].pos[0] << " y " << i_img[g][c].pos[1] << " | ";
            cout << endl;
        }

        std::string s = "image";

        s.append(std::to_string(g));
        s.append(".jpg");

        char const* name = s.c_str();

        //const char * name = ch + "img_test.jpg";

        cout << name << endl;

        MakeImage(g, name);
    
    }

    cout << "# of images: " << i_img.size() << endl;

    for (int i = 0; i < i_img.size(); i++) {

    }
        
}

void Image::MakeImage(int im, const char * name) {


    //create BMP in memory
    BMP bmp2(100, 100, false);//width, height alpha(boolean)
    //modify bmp
    //bmp.fill_region(0, 0, 50, 50, 51, 102, 255, 255);//padding left, padding bottom, width, height, Red, Green, Blue, alpha 
    for (int rgb = 0; rgb < 4; rgb++) {

        bmp2.fill_region(i_img[im][rgb].pos[0], i_img[im][rgb].pos[1], 50, 50, i_img[im][rgb].rgb[0], i_img[im][rgb].rgb[1], i_img[im][rgb].rgb[2], 0);//padding left, padding bottom, width, height, Red, Green, Blue, alpha
    }


    //write bmp
    bmp2.write(name);
    /*
    //read bmp
    BMP bmp("/images/img_test.bmp");
    bmp.write("/images/img_copy");
    */
}

int main() {

    cout << "how many itterations? ";
    string input = "1";
    cin >> input;
    int gen = 1;

    stringstream ss(input);
    if ((ss >> gen).fail())
    {
        cout << "input an integer.";
        return 2;
    }

    Image Img(gen);
}