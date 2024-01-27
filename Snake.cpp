#include "constc.h"
#include <cstdlib>

class Snake{
private:
    std::vector<snake> snPieces;
    const size_t size;
    char dir = ' ';
    void bodyLogic(snake* tempF,snake* tempB, board B) {
        if (B[snPieces.front().y][snPieces.front().x] == FOOD) {
            if (snPieces.size() >= 2) {
                snPieces.back().state = SNAKE_BODY;
                for(size_t i = snPieces.size()-1; i >= 2; i--)
                    snPieces.at(i) = snPieces.at(i-1);
                snPieces.at(1) = *tempF;
            }
            snPieces.insert(snPieces.end(), *tempB);
        } else if (snPieces.size() >= 2) {
            for(size_t i = snPieces.size()-1; i >= 2; i--)
                snPieces.at(i) = snPieces.at(i-1);
            snPieces.at(1) = *tempF;
            snPieces.back().state = SNAKE_TAIL;
        }
    }

public:
    Snake(size_t size): size(size) {
        snPieces.reserve(size * size / 2);
        snPieces.insert(snPieces.begin(), {size / 2, size / 2, SNAKE_HEAD});
    }

    ~Snake(){snPieces.clear();}

    void changeDir(char c){
              if(c == UP && dir != DOWN) { dir = UP;
        }else if(c == DOWN && dir != UP) { dir = DOWN;
        }else if(c == LEFT && dir != RIGHT) { dir = LEFT;
        }else if(c == RIGHT && dir != LEFT) { dir = RIGHT;}
    }
    void clearBoard(board B){
        for(size_t i = 0; i < snPieces.size(); i++)
            if (B[snPieces.at(i).y][snPieces.at(i).x] != FOOD)
                B[snPieces.at(i).y][snPieces.at(i).x] = BOARD_CHAR;
    }
    void placePieces(board B){
        for(size_t i = 0; i < snPieces.size(); i++)
            B[snPieces.at(i).y][snPieces.at(i).x] = snPieces.at(i).state;
    }

    bool Die(board B){
        system("stty cooked");
        if (
            snPieces.front().x == 0      ||
            snPieces.front().y == 0      ||
            snPieces.front().x == size-1 ||
            snPieces.front().y == size-1 ||
            B[snPieces.front().y][snPieces.front().x] == SNAKE_BODY ||
            B[snPieces.front().y][snPieces.front().x] == SNAKE_TAIL 
        ) {return true;}
        return false;
    }

    void move(board B) {
        snake tempFront = snPieces.front(); tempFront.state = SNAKE_BODY;
        snake tempBack  = snPieces.back();  tempBack.state  = SNAKE_TAIL; 
        switch (dir) {
            case UP:
                snPieces.front().y--;
                bodyLogic(&tempFront, &tempBack, B);
            break;
            case DOWN:
                snPieces.front().y++;
                bodyLogic(&tempFront, &tempBack, B);
            break;
            case LEFT:
                snPieces.front().x--;
                bodyLogic(&tempFront, &tempBack, B);
            break;
            case RIGHT:
                snPieces.front().x++;
                bodyLogic(&tempFront, &tempBack, B);
            break;
        }
    }
};