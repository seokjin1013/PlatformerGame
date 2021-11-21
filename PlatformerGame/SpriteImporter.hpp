#pragma once
#include <tuple>
#include <string>
#include <string_view>
#include <fstream>

#pragma pack(push, 1)                // 구조체를 1바이트 크기로 정렬

struct BitmapFileHeader     // BMP 비트맵 파일 헤더 구조체
{
    unsigned short type;           // BMP 파일 매직 넘버
    unsigned int   size;           // 파일 크기
    unsigned short reserved1;      // 예약
    unsigned short reserved2;      // 예약
    unsigned int   offBits;        // 비트맵 데이터의 시작 위치
};

struct BitmapInfoHeader     // BMP 비트맵 정보 헤더 구조체(DIB 헤더)
{
    unsigned int   size;           // 현재 구조체의 크기
    int            width;          // 비트맵 이미지의 가로 크기
    int            height;         // 비트맵 이미지의 세로 크기
    unsigned short planes;         // 사용하는 색상판의 수
    unsigned short bit_count;       // 픽셀 하나를 표현하는 비트 수
    unsigned int   compression;    // 압축 방식
    unsigned int   size_image;     // 비트맵 이미지의 픽셀 데이터 크기
    int            x_pels_per_meter;  // 그림의 가로 해상도(미터당 픽셀)
    int            y_pels_per_meter;  // 그림의 세로 해상도(미터당 픽셀)
    unsigned int   clr_used;        // 색상 테이블에서 실제 사용되는 색상 수
    unsigned int   clr_important;   // 비트맵을 표현하기 위해 필요한 색상 인덱스 수
};

struct RGB            // 24비트 비트맵 이미지의 픽셀 구조체
{
    unsigned char b;          // 파랑
    unsigned char g;         // 초록
    unsigned char r;           // 빨강
};

#pragma pack(pop)

class SpriteImporter {
public:
    bool read_bmp24(std::string_view file_path);
    std::tuple<int*, int, int, int> get();
private:
    int* spr = NULL;
    int w = 0, h = 0, n = 0;
};