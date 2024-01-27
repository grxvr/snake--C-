#include "Game.cpp"

int main() {
    char c;
    Game* game = new Game ( 10 );
    std::thread gameloop(&Game::mainLoop, game);
    while (1){
        std::cin >> c;
        game->snake.changeDir(c);
        if (game->snakeDie()) {
            gameloop.join();
            game->endGame();
            delete game;
            system("stty cooked; clear");
            printf("Ти програв!\n");
            sleep(3);
            game = new Game( 10 );
        }
    }
}
void Game::mainLoop(){
    while(gameRuning){
        snake.clearBoard(BOARD);
        snake.move(BOARD);
        food.fPlace(BOARD);
        snake.placePieces(BOARD);
        system("stty cooked");
        showBoard();
        system("stty raw");
        std::this_thread::sleep_for(std::chrono::milliseconds(144));
    }
}