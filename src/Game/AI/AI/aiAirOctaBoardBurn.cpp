#include "Game/AI/AI/aiAirOctaBoardBurn.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/AI/aiAirOctaRoot.h"

namespace uking::ai {

AirOctaBoardBurn::AirOctaBoardBurn(const InitArg& arg) : SeqTwoAction(arg) {}

AirOctaBoardBurn::~AirOctaBoardBurn() = default;

bool AirOctaBoardBurn::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void AirOctaBoardBurn::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* data_mgr = sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
    sead::Vector3f targetPos{sead::Vector3f::zero};
    ksys::act::ActorConstDataAccess accessor;
    if (data_mgr && ksys::act::acquireActor(&data_mgr->mBaseProcLink2, &accessor) &&
        accessor.hasProc()) {
        auto& mtx = accessor.getActorMtx();
        mtx.getBase(targetPos, 3);
    }
    ksys::act::ai::InlineParamPack paramPack;
    paramPack.addVec3(targetPos, "TargetPos", -1);
    SeqTwoAction::enter_(&paramPack);
}

void AirOctaBoardBurn::leave_() {
    SeqTwoAction::leave_();
}

void AirOctaBoardBurn::loadParams_() {
    SeqTwoAction::loadParams_();
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaBoardBurn::calc_() {
    SeqTwoAction::calc_();
    if (isCurrentChild("先行動")) {
        mActor->m93(4, 0.0f);
    } else {
        mActor->m93(0, 0.0f);
    }
}

}  // namespace uking::ai
