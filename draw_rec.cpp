#include "DataStructure.h"

// Vẽ nét đơn
void DrawRectangleSingle(int x, int y, int width, int height){
    gotoXY(x,y);
    cout << char(218);
    for(int i = 0; i < width; ++i){
        cout <<  char(196);
    }
    cout << char(191);

    for (int i = 1; i <= height; ++i) {
        gotoXY(x, y + i);
        cout << char(179);
        for (int j = 0; j < width; ++j) {
            cout << char(32);
        }
        cout << char(179);
    }

    gotoXY(x, y + height);
    cout << char(192);
    for (int i = 0; i < width; ++i) {
        cout << char(196);
    }
    cout << char(217);

}

//vẽ nét đôi
void DrawRectangleDouble(int x, int y, int width, int height){
    gotoXY(x, y);
    cout << char(201);
    for (int i = 0; i < width; ++i) {
        cout << char(205);
    }
    cout << char(187);

    for (int i = 1; i <= height; ++i) {
        gotoXY(x, y + i);
        cout << char(186);
        for (int j = 0; j < width; ++j) {
            cout << char(32);
        }
        cout << char(186);
    }

    gotoXY(x, y + height);
    cout << char(200);
    for (int i = 0; i < width; ++i) {
        cout << char(205);
    }
    cout << char(188);

}
