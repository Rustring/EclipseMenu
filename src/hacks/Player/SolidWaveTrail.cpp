#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCDrawNode.hpp>

namespace eclipse::hacks::Player {

    class NoDeathEffect : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("Solid Wave Trail", "player.solidwavetrail")
                ->setDescription("Makes the wave trail a solid color")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "Solid Wave Trail"; }
    }

class $modify(CCDrawNode) {
    bool drawPolygon(CCPoint *p0, unsigned int p1, const ccColor4F &p2, float p3, const ccColor4F &p4) {
        if (!Hacks::isHackEnabled("Solid Wave Trail")) return CCDrawNode::drawPolygon(p0,p1,p2,p3,p4);
        if (p2.r == 1.F && p2.g == 1.F && p2.b == 1.F && p2.a != 1.F) return true; // tried doing just p2.a != 1.F but uh
        this->setBlendFunc(CCSprite::create()->getBlendFunc());
        this->setZOrder(-1); // ok but why
        return CCDrawNode::drawPolygon(p0,p1,p2,p3,p4);
    }
};
