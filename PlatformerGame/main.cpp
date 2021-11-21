#include <iostream>
#include "PlayManager.hpp"

using namespace std;

int main() {
    try {
        PlayManager::instance().play();
    } catch (const char* str) {
        cout << str;
    }
    getchar();
    return 0;
}