#include "Game/AI/AI/aiAnimalRoamBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AnimalRoamBase::AnimalRoamBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRoamBase::~AnimalRoamBase() = default;

bool AnimalRoamBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

extern void sub_7100F7604C(ksys::phys::CharacterFormSet*, f32);

void AnimalRoamBase::enter_(ksys::act::ai::InlineParamPack* params) {
    unk_A0 = 0;
    unk_A4 = true;
    auto form_set = mActor->getCharacterFormSet();
    if (form_set) {
        sub_7100F7604C(form_set, 0.5f);
    }
}

void AnimalRoamBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRoamBase::loadParams_() {
    getStaticParam(&mSearchNextPathRadius_s, "SearchNextPathRadius");
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mForwardDirDistCoefficient_s, "ForwardDirDistCoefficient");
    getStaticParam(&mDirRandomMinRatio_s, "DirRandomMinRatio");
    getStaticParam(&mDirRangeAngle_s, "DirRangeAngle");
    getStaticParam(&mRejectDistRatio_s, "RejectDistRatio");
    getStaticParam(&mContinueAddSearchAngle_s, "ContinueAddSearchAngle");
    getStaticParam(&mContinueReduceDistRatio_s, "ContinueReduceDistRatio");
    getStaticParam(&mContinueReduceRejectDistRatio_s, "ContinueReduceRejectDistRatio");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getMapUnitParam(&mEnableNoEntryAreaCheck_m, "EnableNoEntryAreaCheck");
    getAITreeVariable(&mFramesStuckOnTerrain_a, "FramesStuckOnTerrain");
    getAITreeVariable(&mIsStuckOnTerrain_a, "IsStuckOnTerrain");
}

void AnimalRoamBase::calc_() {
    ksys::act::ai::Ai::calc_();
}

bool AnimalRoamBase::m34(f32& a2) {
    auto form_set = mActor->getCharacterFormSet();
    if (form_set == nullptr) {
        return false;
    }

    return true;
}


}  // namespace uking::ai
