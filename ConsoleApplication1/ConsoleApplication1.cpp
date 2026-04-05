// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h> 
using namespace std;


struct Ball {
    int x, y; //позиция шара
    int vx, vy; //скорость шара
};

struct Paddle {
    int y; //позиция ракетки
    int height; //высота ракетки
    int score; //счёт ракетки
};

struct Game {
    int width, height;
    Ball ball;
    Paddle left, right;
    bool running;
};

Game init() {
    Game ppong;
    ppong.width = 80;
    ppong.height = 20;

    ppong.ball = { 20, 10, 1, 1 }; //struct Ball
    
    ppong.left = { 8,4,0 };
    ppong.right = { 8,4,0 };

    ppong.running = true;

    return ppong;
}

void draw(Game& ppong) {
        //очистка поля
        system("cls");

        //верхняя стена
        cout << "Г" << string(ppong.width, '-') << "7\n";
        
        //внутреннаяя стена
        for (int y = 1; y < ppong.height - 1; y++) {
            cout << "|";
            for (int x = 0; x < ppong.width; x++) {

                if (x == 1 && y >= ppong.left.y
                    && y < ppong.left.y + ppong.left.height)
                    cout << "#";   //левая ракетка

                else if (x == ppong.width - 2 && y >= ppong.right.y
                    && y < ppong.right.y + ppong.right.height)
                    cout << "#";   //правая ракетка

                else if (x == ppong.ball.x && y == ppong.ball.y)
                    cout << "O";   //мяч

                else
                    cout << " ";   //пустота
            }
            cout << "|\n";
        }


        //нижняя стена
        cout << "L" << string(ppong.width, '-') << "_|\n";

        //счёт
        cout << ppong.left.score << " : " << ppong.right.score << endl;
}

void input(Game& ppong) {
    //я
    if (_kbhit()) {
        char key = _getch();

        if (key == 'w' && ppong.left.y > 1)
            ppong.left.y--;
        if (key == 's' && ppong.left.y + ppong.left.height < ppong.height - 1)
            ppong.left.y++;
    }

    //бот
    int paddle_center = ppong.right.y + ppong.right.height / 2;

    if (paddle_center < ppong.ball.y && ppong.right.y + ppong.right.height < ppong.height - 1)
        ppong.right.y++;
    else if (paddle_center > ppong.ball.y && ppong.right.y > 1)
        ppong.right.y--;   
}


void update(Game& ppong) {
    //двигаем мяч
    ppong.ball.x += ppong.ball.vx;
    ppong.ball.y += ppong.ball.vy;

    //верх низ
    if (ppong.ball.y <= 1 || ppong.ball.y >= ppong.height - 2)
        ppong.ball.vy *= -1;

    //отскок от левой ракетки
    if (ppong.ball.x == 2
        && ppong.ball.y >= ppong.left.y
        && ppong.ball.y < ppong.left.y + ppong.left.height)
        ppong.ball.vx *= -1;

    //отскок от правой ракетки
    if (ppong.ball.x == ppong.width - 3
        && ppong.ball.y >= ppong.right.y
        && ppong.ball.y < ppong.right.y + ppong.right.height)
        ppong.ball.vx *= -1;

    //гол в левые волрота
    if (ppong.ball.x <= 0) {
        ppong.right.score++;
        ppong.ball = { ppong.width / 2, ppong.height / 2, 1, 1 };
    }

    //гол в правые ворота
    if (ppong.ball.x >= ppong.width - 1) {
        ppong.left.score++;
        ppong.ball = { ppong.width / 2, ppong.height / 2, -1, 1 };
    }
}

int main() {
    Game ppong = init();

    while (ppong.running) {
        draw(ppong);
        input(ppong);
        update(ppong);
        Sleep(50);
    }
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

