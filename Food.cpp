#include "constc.h"
class Food {
    size_t x, y;
    const size_t size;
    
public:
    Food(size_t size) : size(size) { setRand(); }
    void setRand() {
        srand(static_cast<unsigned>(time(nullptr)));
        x = rand() % (size - 2) + 1;
        y = rand() % (size - 2) + 1;
    }
    void fPlace(board B) {
        while (B[y][x] != FOOD) {
        setRand();
        B[y][x] = FOOD;
        }
    }
};
