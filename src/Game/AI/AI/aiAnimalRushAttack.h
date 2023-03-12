#pragma once

#include <math/seadVector.h>

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class AnimalRushAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRushAttack, ksys::act::ai::Ai)
public:
    explicit AnimalRushAttack(const InitArg& arg);
    ~AnimalRushAttack() override;

    bool isFailed() const override;
    bool isFinished() const override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    bool sub_710030CB64(bool a2);
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mUpdateTargetPosTime_s{};
    // static_param at offset 0x40
    const float* mAttackPosOffsetLength_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer mTimer{};
    sead::Vector3f unk_5C;
    char pad[0x8];
};
KSYS_CHECK_SIZE_NX150(AnimalRushAttack, 0x70);

}  // namespace uking::ai
