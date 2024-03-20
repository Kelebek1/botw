#include "Game/AI/AI/aiActorWaterDepthSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

ActorWaterDepthSelect::ActorWaterDepthSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ActorWaterDepthSelect::~ActorWaterDepthSelect() = default;

bool ActorWaterDepthSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ActorWaterDepthSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool ActorWaterDepthSelect::isChangeable() const {
    return getCurrentChild()->isChangeable();
}

bool ActorWaterDepthSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ActorWaterDepthSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (isUnderwater() && isDeep()) {
        changeChild("深瀬", params);
    } else {
        changeChild("浅瀬", params);
    }
}

void ActorWaterDepthSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ActorWaterDepthSelect::loadParams_() {
    getStaticParam(&mDeepDepth_s, "DeepDepth");
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
    getStaticParam(&mForceDeepChange_s, "ForceDeepChange");
}

void ActorWaterDepthSelect::calc_() {
    if (*mOnEnterOnly_s) {
        return;
    }

    auto is_deep = isUnderwater() && isDeep();
    if (*mForceDeepChange_s && is_deep) {
        if (!isCurrentChild("深瀬")) {
            return changeChild("深瀬");
        }
    }

    if (getCurrentChild()->isChangeable()) {
        if (is_deep) {
            if (!isCurrentChild("深瀬")) {
                changeChild("深瀬");
            }
        } else if (!isCurrentChild("浅瀬")) {
            changeChild("浅瀬");
        }
    }
}

bool ActorWaterDepthSelect::isUnderwater() const {
    return *mDeepDepth_s > 0.0f && mActor->get68f();
}

bool ActorWaterDepthSelect::isDeep() const {
    auto y_w = mActor->getMtx()(1, 3);
    return mActor->get6f0() - y_w > *mDeepDepth_s;
}

}  // namespace uking::ai
