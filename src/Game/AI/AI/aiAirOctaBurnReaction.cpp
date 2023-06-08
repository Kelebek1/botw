
#include <random/seadGlobalRandom.h>
#include "Game/AI/AI/aiAirOctaBurnReaction.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "Game/AI/AI/aiAirOctaBoardBurn.h"

namespace uking::ai {

AirOctaBurnReaction::AirOctaBurnReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaBurnReaction::~AirOctaBurnReaction() = default;

bool AirOctaBurnReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

//bool AirOctaBurnReaction::sub_71002FAA64() {}

void AirOctaBurnReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    bool acquired;
    bool has_proc;
    {
        ksys::act::ActorConstDataAccess accessor;
        auto* data_manager = sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
        acquired = ksys::act::acquireActor(&data_manager->getProc(), &accessor);
        has_proc = accessor.hasProc();
    }
    if (acquired && has_proc && sub_71002FAA64()) {
        unk_60 = true;
        changeChild("先行動", nullptr);
    } else {
        unk_60 = false;
        changeChild("後行動", nullptr);
    }
    f32 randTime = *mChangeRandTime_s;
    unk_68 = randTime * (1 + sead::GlobalRandom::instance()->getU32() - 1.0f);
    f32 disconnectTime = *mDisconnectTime_s;
    f32 disconnectRandTime = *mDisconnectRandTime_s;
    unk_6C = disconnectTime + ((1 + sead::GlobalRandom::instance()->getU32() - 1.0f) * disconnectRandTime);
}

void AirOctaBurnReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AirOctaBurnReaction::loadParams_() {
    getStaticParam(&mDisconnectTime_s, "DisconnectTime");
    getStaticParam(&mDisconnectRandTime_s, "DisconnectRandTime");
    getStaticParam(&mSingleBurnTime_s, "SingleBurnTime");
    getStaticParam(&mChangeRandTime_s, "ChangeRandTime");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
