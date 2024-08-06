#include <modules/gui/gui.hpp>
#include <modules/hack/hack.hpp>
#include <modules/config/config.hpp>

#include <Geode/modify/CCDrawNode.hpp>
#include <Geode/modify/HardStreak.hpp>

namespace eclipse::hacks::Player {

    class SolidWaveTrail : public hack::Hack {
        void init() override {
            auto tab = gui::MenuTab::find("Player");
            tab->addToggle("Solid Wave Trail", "player.solidwavetrail")
                ->setDescription("Makes the wave trail a solid color")
                ->handleKeybinds();
        }

        [[nodiscard]] const char* getId() const override { return "Solid Wave Trail"; }
    }:

    REGISTER_HACK(SolidWaveTrail)

class $modify (CCDrawNode)
{
    bool drawPolygon(CCPoint *verts, unsigned int count, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor)
    {
        if (typeinfo_cast<HardStreak*>(this))
        {
            if (!noWave)
                noWave = Client::GetModule("no-wave");

            if (!solidWave)
                solidWave = Client::GetModule("solid-wave");

            if (noWave->enabled)
                return true;

            if (solidWave->enabled)
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
