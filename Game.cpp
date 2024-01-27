#include "Food.cpp"
#include "Snake.cpp"
#include "constc.h"

class Game {
private:
    const size_t size;
    board BOARD;
    Food food;
    bool gameRuning = true;
    void createBoard() {
        BOARD = new char *[size];
        for (size_t i = 0; i < size; i++)
            BOARD[i] = new char[size];
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++)
                BOARD[j][i] = BOARD_CHAR;
    }

    void deleteBoard() {
        for (size_t i = 0; i < size; i++)
            delete[] BOARD[i];
        delete[] BOARD;
    }

public:
    Snake snake;
    Game(size_t size) : size(size) , food(size), snake(size) {
        createBoard();
        food.fPlace(BOARD);
    }

    ~Game() { deleteBoard(); }

    void showBoard() {
        system("clear");
        for (size_t y = 0; y < size; y++) {
            for (size_t x = 0; x < size; x++) {
                if (
                (!x          &&          !y) ||
                (!x          && y == size-1) ||
                (x == size-1 &&          !y) ||
                (x == size-1 && y == size-1)
                ) /* -> */ printf("%c",      BOARD_CORNER);
                else if(!x || x == size-1)
                    printf("%c",BOARD_VER_SIDE);
                else if(!y || y == size-1)
                    printf("%c%c%c",BOARD_HOR_SIDE,BOARD_HOR_SIDE,BOARD_HOR_SIDE);
                else
                    printf(" %c ",BOARD[y][x]);
            }
            printf("\n");
        }
    }
    void mainLoop();
    void endGame(){gameRuning = false;}
    bool snakeDie(){return snake.Die(BOARD);}
};