#include "Game/Game.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, // a handle to the current application instance
    _In_opt_ HINSTANCE hPrevInstance, // always Null
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow) {

    Game game;

    return game.Start();
}