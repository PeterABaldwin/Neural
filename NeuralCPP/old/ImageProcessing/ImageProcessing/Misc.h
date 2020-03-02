#pragma once

using namespace std;

unsigned char* ReadBMP(const char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    long width = *(int*)&info[18];
    long height = *(int*)&info[22];

    long size = 3 * width * height;
    cout << "Size: " << size / 3 << " width: " << width << " height: " << height << endl;
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
    //cout << data << endl;
 //   int x;
    int x = 1;
    //    int y;
    int y = 1;

    string s0 = "1";
    //cout << "Locaiton x: ";
    //cin >> s0;
    //x = atoi(s0.c_str());

    //cout << "Locaiton y: ";
    //cin >> s0;
    //y = atoi(s0.c_str());
    //R, G, B at pixel(j,i)

    cout << data[0] << data[1] << data[2] << endl;
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
