#include <iostream>
#include "engine/Game.h"
#include "ui/GameWindow/GameWindow.h"
#include "resources/ResourcesManager.h"
#include "utils/SfmlUtils.h"

#include <iostream>
#include <thread>

#ifdef _WIN32 /// chcemy ukryc konsole
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main() {
    srand(time(0));
    ResourcesManager::singleton().load_all_sfml();
    GameWindow window;
    window.run();


    /// mozna zmienic Agenta na innego np. z UserConsoleAgent na MinMaxAgent aby grały dwa boty lub odwrotnie aby grali ludzie
//    MinMaxAgent player1(8); /// im wieksza glebokosc tym dluzej mysli (szczegolnie gdy pojawiaja sie damki ktore maja duzo ruchow)
//    MinMaxAgent player2(4);
//    aby gral czlowiek z komputerem
//    UserConsoleAgent player1; /// ja z poziom 5 już nie mam szans
//    UserConsoleAgent player2;
//    Game game(&player1, &player2, false); /// pierwszy gracz to ten na gorze
//
//    while(!game.is_finished()){
//        game.board.print();
//
//        std::cout << "Kliknij ENTER aby kontynuwac..." << std::flush;
//        getchar();
//        std::cout << "\n";
//
//        auto state = game.play_next_move();
//        switch (state) {
//            case IN_PROGRESS:
//                break;
//            case WIN_1:
//                game.board.print();
//                std::cout << "Wygrywa player 1";
//                break;
//            case WIN_2:
//                game.board.print();
//                std::cout << "Wygrywa player 2";
//                break;
//        }
//    }

    return 0;
}
