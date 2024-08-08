#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCDrawNode.hpp>
#include <Geode/modify/HardStreak.hpp>

namespace eclipse::hacks::Player {

    class NoWavePulse : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("No Wave Pulse", "player.nowavepulse")
                ->setDescription("Removes the wave trail pulse")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "No Wave Pulse"; }
    };

    REGISTER_HACK(NoWavePulse)

   class $modify(HardStreak) {    // Yes this is copied from Prism Menu I'm stupid to write it myself
       void updateStroke(float dt) {
           //log::info("HardStreak\n---\nm_waveSize = {}\nm_pulseSize = {}\nm_isSolid = {}", m_waveSize, m_pulseSize, m_isSolid);
           if (!config::get<bool>("player.nowavepulse", true)) {
               m_pulseSize = 1.24F;
           }
           HardStreak::updateStroke(dt);
       }
   };
     
}
