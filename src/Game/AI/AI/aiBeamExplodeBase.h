#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeamExplodeBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BeamExplodeBase, ksys::act::ai::Ai)
public:
    explicit BeamExplodeBase(const InitArg& arg);
    ~BeamExplodeBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mMaxDistance_s{};
    // static_param at offset 0x40
    const bool* mIsDelete_s{};
};

}  // namespace uking::ai
