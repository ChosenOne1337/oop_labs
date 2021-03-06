#include "gamemodel/gamemodel.h"
#include "gamecontroller/eventlistener.h"

namespace  {

class SplashScreenListener: public EventListener {
public:
    void key_event_occurred(const KeyEvent&) override {
        _get_model()->main_menu();
    }
private:
};

bool register_listener() {
    ListenerFactory::instance().register_listener<SplashScreenListener>(GameState::SplashScreen);
    return true;
}

bool regHandlers = register_listener();

}
