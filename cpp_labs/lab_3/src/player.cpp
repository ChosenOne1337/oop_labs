#include <ncurses.h>
#include <stdexcept>
#include "player.h"
#include "event.h"

namespace  {

KeyCode int_to_keycode(int code) {
    switch (code) {
    case KEY_UP:
        return KeyCode::KeyUP;
    case KEY_DOWN:
        return KeyCode::KeyDOWN;
    case KEY_LEFT:
        return KeyCode::KeyLEFT;
    case KEY_RIGHT:
        return KeyCode::KeyRIGHT;
    case KEY_STAB:
        return KeyCode::KeySTAB;
    case '\n':
        return KeyCode::KeyENTER;
    default:
        return KeyCode::KeyUNKNOWN;
    }
}

} // anonymous namespace

// human player

void HumanPlayer::wait_event() {
    if (_get_listener() == nullptr) {
        throw std::runtime_error("HumanPlayer::wait_event(): listener is NULL");
    }
    int code = getch();
    if (code == KEY_MOUSE) {
        MouseEvent event;
        // filling event...
        // ...
        _get_listener()->mouse_event_occurred(event);
    }
    else {
        KeyCode keyCode = int_to_keycode(code);
        KeyEvent event(keyCode);
        _get_listener()->key_event_occurred(event);
    }
}

// bot player

void BotPlayer::wait_event() {
    if (_get_listener() == nullptr) {
        throw std::runtime_error("BotPlayer::wait_event(): listener is NULL");
    }
}