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
              if(c == 'w' && dir != 's') { dir = 'w';
        }else if(c == 's' && dir != 'w') { dir = 's';
        }else if(c == 'a' && dir != 'd') { dir = 'a';
        }else if(c == 'd' && dir != 'a') { dir = 'd';}
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

    bool snakeLose(board B){
        system("stty cooked");
        if (
            snPieces.front().x == 0      ||
            snPieces.front().y == 0      ||
            snPieces.front().x == size-1 ||
            snPieces.front().y == size-1 
        ) {
            printf("\n%s\n", "Змійка зайшла за межі :(");
            // std::exit(EXIT_SUCCESS);
            return true;
        }else if (
            B[snPieces.front().y][snPieces.front().x] == SNAKE_BODY ||
            B[snPieces.front().y][snPieces.front().x] == SNAKE_TAIL 
        ) {
            printf("\n%s\n", "Змійка вкусила сама себе :(");
            // std::exit(EXIT_SUCCESS);
            return true;
        }
        return false;
    }

    void move(board B) {
        snake tempFront = snPieces.front(); tempFront.state = SNAKE_BODY;
        snake tempBack  = snPieces.back();  tempBack.state  = SNAKE_TAIL; 
        switch (dir) {
            case 'w':
                snPieces.front().y--;
                bodyLogic(&tempFront, &tempBack, B);
            break;
            case 's':
                snPieces.front().y++;
                bodyLogic(&tempFront, &tempBack, B);
            break;
            case 'a':
                snPieces.front().x--;
                bodyLogic(&tempFront, &tempBack, B);
            break;
            case 'd':
                snPieces.front().x++;
                bodyLogic(&tempFront, &tempBack, B);
            break;
        }
    }
};