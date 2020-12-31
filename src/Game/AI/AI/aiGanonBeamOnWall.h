#pragma once

#include "Game/AI/AI/aiLastBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeamOnWall : public LastBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(GanonBeamOnWall, LastBossShootNormalArrowRoot)
public:
    explicit GanonBeamOnWall(const InitArg& arg);
    ~GanonBeamOnWall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
