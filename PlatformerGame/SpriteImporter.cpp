#include "SpriteImporter.hpp"

using namespace std;

bool SpriteImporter::read_bmp24(string_view file_path) {
    ifstream bmp;
    bmp.open(file_path.data(), ios::binary);
    BitmapFileHeader fileheader;
    BitmapInfoHeader infoheader;
    bmp.read((char*)&fileheader, sizeof(fileheader));
    if (fileheader.type != 'MB') {
        bmp.close();
        throw "file extension is not bitmap";
        return false;
    }
    bmp.read((char*)&infoheader, sizeof(infoheader));
    if (infoheader.bit_count != 24) {
        bmp.close();
        throw "bitmap file bit_count is not 24";
        return false;
    }

    int size = infoheader.size_image;
    if (w == 0)
        w = infoheader.width;
    else if (w != infoheader.width) {
        throw "unexpected image size. fit image size to previous index image size.";
        return false;
    }
    if (h == 0)
        h = infoheader.height;
    else if (h != infoheader.height) {
        throw "unexpected image size. fit image size to previous index image size.";
        return false;
    }

    int padding = w % 4;
    if (size == 0) size = (w * 3 + padding) * h;

    char* image = (char*)malloc(size);

    bmp.seekg(fileheader.offBits);
    bmp.read(image, size);

    ++n;
    if (spr == NULL)
        spr = (int*)malloc(sizeof(int) * w * h);
    else
        spr = (int*)realloc(spr, sizeof(int) * w * h * n);
    if (spr == NULL) return false;

    int spridx = w * h * (n - 1);
    for (int i = h - 1; i >= 0; --i) {
        for (int j = 0; j < w; ++j) {
            int idx = j * 3 + i * (w * 3 + padding);
            RGB* pixel = (RGB*)&image[idx];
            int alpha = (pixel->r + pixel->g + pixel->b) / 3;
            spr[spridx++] = alpha;
        }
    }
    return true;
}

tuple<int*, int, int, int> SpriteImporter::get() {
    return { spr, w, h, n };
}