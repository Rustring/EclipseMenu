#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/CCDrawNode.hpp>
#include <Geode/modify/HardStreak.hpp>

namespace eclipse::hacks::Player {

    class SolidWaveTrail : public hack::Hack {    // Hack name and desciption
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("Solid Wave Trail", "player.solidwavetrail")
                ->setDescription("Makes the player wave trail a solid color")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "Solid Wave Trail"; }
    };

   REGISTER_HACK(SolidWaveTrail)


   class $modify(cocos2d::CCDrawNode) {    // The actual code behind the hack
       
        bool drawPolygon(CCPoint *verts, unsigned int count, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor)    
       
           if (!config::get<bool>("player.solidwavetrail", true))
            {
                if (fillColor.r >= 1.0f && fillColor.g >= 1.0f && fillColor.b >= 1.0f && this->getColor() != ccc3(255, 255, 255))
                    return true;

                if (this->getTag() != 1)
                {
                    this->setTag(1);
                    this->setBlendFunc(CCSprite::create()->getBlendFunc());
                }

                this->setZOrder(-1);
            }
        }

        return CCDrawNode::drawPolygon(verts, count, fillColor, borderWidth, borderColor);
     }
   };

}
