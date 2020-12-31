#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroRelicBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroRelicBattleRoot, ksys::act::ai::Ai)
public:
    explicit ZoraHeroRelicBattleRoot(const InitArg& arg);
    ~ZoraHeroRelicBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mZoraHeroShowMsgUnit_a{};
};

}  // namespace uking::ai
