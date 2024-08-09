#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/Geode.hpp>
#include <Geode/modify/HardStreak.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>

using namespace geode::prelude;

namespace eclipse::hacks::Player {

    class NoWavePulse : public hack::Hack {   /// Hack name and description
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("No Wave Pulse", "player.nowavepulse")
                ->setDescription("Removes the wave trail pulsing effect")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "No Wave Pulse"; }
    };

    REGISTER_HACK(NoWavePulse)

   class $modify(HardStreak) {    // The actual code
       void updateStroke(float dt) {
           if (!config::get<bool>("player.nowavepulse", true)) {
               m_pulseSize = 1.24F;
           }
           HardStreak::updateStroke(dt);
       }
   };
     
}
