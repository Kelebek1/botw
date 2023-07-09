#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "Game/AI/AI/aiAirOctaBoardBurn.h"

namespace uking::ai {

class AirOctaBurnReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaBurnReaction, ksys::act::ai::Ai)
public:
    explicit AirOctaBurnReaction(const InitArg& arg);
    ~AirOctaBurnReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    bool sub_71002FAA64();

protected:
    // static_param at offset 0x38
    const float* mDisconnectTime_s{};
    // static_param at offset 0x40
    const float* mDisconnectRandTime_s{};
    // static_param at offset 0x48
    const float* mSingleBurnTime_s{};
    // static_param at offset 0x50
    const float* mChangeRandTime_s{};
    // aitree_variable at offset 0x58
    void* mAirOctaDataMgr_a{};
    s64 unk_60{false};
    f32 unk_68{0.0f};
    f32 unk_6C{0.0f};
};

}  // namespace uking::ai
