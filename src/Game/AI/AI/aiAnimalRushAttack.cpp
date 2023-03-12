
#include "Game/AI/AI/aiAnimalRushAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalRushAttack::AnimalRushAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRushAttack::~AnimalRushAttack() = default;

bool AnimalRushAttack::isFailed() const {
    if (mFlags.isOn(ActionBase::Flag::Failed)) {
        return true;
    }
    return getCurrentChild()->isFailed();
}

bool AnimalRushAttack::isFinished() const {
    if (mFlags.isOn(ActionBase::Flag::Finished)) {
        return true;
    }
    return getCurrentChild()->isFinished();
}

bool AnimalRushAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRushAttack::enter_(ksys::act::ai::InlineParamPack*) {
    const auto* characterController = mActor->sub_71011D7C00();
    mActor->m45();

    if (!characterController) {
        setFailed();
        return;
    }

    if (!sub_710030CB64(true)) {
        setFailed();
    }

    mTimer = ksys::Timer((*mUpdateTargetPosTime_s < 0) ? 1.0f : *mUpdateTargetPosTime_s,
                         (*mUpdateTargetPosTime_s < 0) ? 1.0f : *mUpdateTargetPosTime_s,
                         (*mUpdateTargetPosTime_s < 0) ? 0.0f : -1.0f);

    ksys::act::ai::InlineParamPack params;
    params.count = 0;
    params.addVec3(unk_5C, "TargetPos", -1);
    changeChild("突進", &params);
}

extern bool sub_710072FAB0(ksys::act::Actor*, sead::Vector3f&, sead::Vector3f&, s32, f32, f32);

bool AnimalRushAttack::sub_710030CB64(bool a2) {
    auto& matrix = mActor->getMtx();
    f32 matrix_x = matrix.m[0][3];
    f32 matrix_z = matrix.m[2][3];

    sead::Vector3f diff = {
        mTargetPos_d->x - matrix_x,
        0.0f,
        mTargetPos_d->z - matrix_z,
    };

    f32 sqrt = diff.length();
    if (sqrt > 0.0f) {
        diff *= 1.0f / sqrt;
    }

    sead::Vector3f out1 = (diff * *mAttackPosOffsetLength_s) + *mTargetPos_d;
    sead::Vector3f out2;

    if (sub_710072FAB0(mActor, out1, out2, -1, -1.0f, -1.0f)) {
        unk_5C = out1;
    } else {
        sead::Vector2f temp = {(matrix_x - out2.x) * (matrix_x - out2.x) +
                                   (matrix_z - out2.z) * (matrix_z - out2.z),
                               (matrix_x - mTargetPos_d->x) * (matrix_x - mTargetPos_d->x) +
                                   (matrix_z - mTargetPos_d->z) * (matrix_z - mTargetPos_d->z)};
        bool res = temp.x < temp.y;
        if (res && !a2) {
            return false;
        }
        unk_5C = out2;
        return !res;
    }
    return true;
}

void AnimalRushAttack::calc_() {
    if (isFinished() || isFailed()) {
        return;
    }

    if (mTimer.value > 1.19209289551e-07f) {
        sub_710030CB64(false);
        getCurrentChild()->setDynamicParam(unk_5C, "TargetPos");
        mTimer.update();
    }

    auto child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        child = getCurrentChild();
        if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else {
        child->isChangeable();
    }
}

void AnimalRushAttack::leave_() {}

void AnimalRushAttack::loadParams_() {
    getStaticParam(&mUpdateTargetPosTime_s, "UpdateTargetPosTime");
    getStaticParam(&mAttackPosOffsetLength_s, "AttackPosOffsetLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
