#include <iostream>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    int left = 10, top = 8, right = 70, bottom = 18;
    float scrollSpeed = 0.7;
    int colorAttribute = 2;

    setTextColor(colorAttribute);

    for (int x = left; x <= right; x++) {
        gotoxy(x, top);
        cout << "-";
        gotoxy(x, bottom);
        cout << "-";
    }
    for (int y = top; y <= bottom; y++) {
        gotoxy(left, y);
        cout << "|";
        gotoxy(right, y);
        cout << "|";
    }

    gotoxy(left + 2, top + 2);
    cout << "Текст внутри окна";

    for (int y = bottom - 1; y > top; y--) {
        gotoxy(left + 2, y);
        cout << "                ";
        gotoxy(left + 2, y - 1);
        cout << "Текст прокрутки";
        Sleep(static_cast<int>(1000 * scrollSpeed));
    }

    setTextColor(7);

    return 0;
}
