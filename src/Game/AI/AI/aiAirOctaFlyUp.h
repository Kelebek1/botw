#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "Game/AI/AI/aiAirOctaRoot.h"

namespace uking::ai {

class AirOctaFlyUp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaFlyUp, ksys::act::ai::Ai)
public:
    explicit AirOctaFlyUp(const InitArg& arg);
    ~AirOctaFlyUp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    AirOctaDataMgr* getDataMgr() const;

protected:
    // static_param at offset 0x38
    const f32* mFlyUpDuration_s{};
    // dynamic_param at offset 0x40
    f32* mTargetDistance_d{};
    // aitree_variable at offset 0x48
    void* mAirOctaDataMgr_a{};
    f32 unk_50;
    f32 unk_54;
    s32 unk_58;
    bool unk_5C;
};

}  // namespace uking::ai
