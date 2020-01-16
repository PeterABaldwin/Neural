#include <iostream>
#include <sstream>

using namespace std;

unsigned char* ReadBMP(const char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for (i = 0; i < size; i += 3)
    {
        unsigned char tmp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = tmp;
        //cout << data[i] << data[i+2] << data[i+4] << " ";
    }

    return data;
}

void process(char const* name) {

    //1, 2, 4 (multiply R*1, B*2, G*4 and add together to get singular value (think RWX values for reason))
    unsigned char* data = ReadBMP(name);
    int x;
    int y;

    string s0 = "1";
    cout << "Locaiton x: ";
    cin >> s0;
    x = atoi(s0.c_str());

    cout << "Locaiton y: ";
    cin >> s0;
    y = atoi(s0.c_str());
    //R, G, B at pixel(j,i)

    cout << "R: " << data[3 * (y * 100 + x)] << " | G: " << data[3 * (y * 100 + x) + 1] << " | B: " << data[3 * (y * 100 + x) + 2] << endl;

    cout << "R: ";
    printf("%u", data[3 * (y * 100 + x)]);
    cout << " | G: ";
    printf("%u", data[3 * (y * 100 + x) + 1]);
    cout << " | B: ";
    printf("%u", data[3 * (y * 100 + x) + 2]);
    cout << endl;
    //converts to accurate decimal (%X for hex)

    //cout << ReadBMP("image1.bmp");//reads entire image

    //need to seperate the colors
}

int main() {

    cout << "Image number: ";
    string s0 = "1";
    cin >> s0;
    std::string s1 = "//img//image";
    s1.append(s0);
    s1.append(".bmp");

    for (int i = 100; i > 0; i--) {
        char const* name = s1.c_str();
        process(name);
    }
    return 0;
}