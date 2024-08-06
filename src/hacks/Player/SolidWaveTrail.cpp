#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCDrawNode.hpp>

namespace eclipse::hacks::Player {

    class CCDrawNode : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("Solid Wave Trail", "player.solidwavetrail")
                ->setDescription("Makes the wave trail a solid color")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "Solid Wave Trail"; }
    }

    class $modify(CCDrawNode) {
    public:
        bool drawPolygon(CCPoint *p0, unsigned int p1, const ccColor4F &p2, float p3, const ccColor4F &p4) override {
          return CCDrawNode::drawPolygon(p0, p1, p2, p3, p4);
            }
            // Custom condition for drawing
            if (std::abs(p2.r - 1.0f) < 0.01f && std::abs(p2.g - 1.0f) < 0.01f && std::abs(p2.b - 1.0f) < 0.01f && p2.a != 1.0f) {
                return true; // Skip default draw if the condition is met
            }
            this->setBlendFunc(CCSprite::create()->getBlendFunc());
            this->setZOrder(-1); // Adjust ZOrder as needed
            return CCDrawNode::drawPolygon(p0, p1, p2, p3, p4);
        }
    };

}
