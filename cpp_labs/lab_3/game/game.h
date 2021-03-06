#pragma once

#include "gamemodel/gamemodel.h"
#include "gameview/gameview.h"
#include "gamecontroller/gamecontroller.h"
#include "gamestate.h"
#include "player.h"
#include <memory>

class Game {
public:
    // constructor
    Game(GameType gameType);
    // public methods
    void run();
private:
    GameType _gameType;
    // private methods
    void _switch_active_player();
    void _create_players();
    // private data
    std::unique_ptr<GameModel> _model;
    std::unique_ptr<GameView> _view;
    std::unique_ptr<GameController> _controller;
    std::unique_ptr<HumanPlayer> _UIuser;
    std::shared_ptr<Player> _player1, _player2;
    std::shared_ptr<Player> _activePlayer;
};

