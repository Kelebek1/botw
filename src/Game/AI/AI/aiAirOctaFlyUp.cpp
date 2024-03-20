#include "Game/AI/AI/aiAirOctaFlyUp.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

AirOctaFlyUp::AirOctaFlyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaFlyUp::~AirOctaFlyUp() = default;

bool AirOctaFlyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AirOctaFlyUp::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* dataMgr = sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
    if (dataMgr) {
        dataMgr->unk_114 = 0.0f;
        dataMgr->sub_71002FB17C();
    }
    unk_50 = getActor()->getMtx()(1, 3);
    changeChild("開始", nullptr);
}

void AirOctaFlyUp::calc_() {
    auto* dataMgr = sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
    if (!dataMgr) {
        return;
    }

    unk_54 += ksys::VFR::instance()->getDeltaTime();

    auto fly_up_turning_pts = std::min(unk_54 / *mFlyUpDuration_s, 1.0f) * 2.0f;
    auto fly_up_multiplier = fly_up_turning_pts < 1.0f ?
                                 sead::Mathf::exp((fly_up_turning_pts - 1.0f) * 10.f) :
                                 2.0f - sead::Mathf::exp((fly_up_turning_pts - 1.0f) * -10.f);
    fly_up_multiplier *= 0.5;
    dataMgr->unk_114 = fly_up_multiplier * *mTargetDistance_d;
    dataMgr->sub_71002FB17C();
    auto& actorMtx = getActor()->getMtx();

    if (isCurrentChild("終了")) {
        if (!unk_5C) {
            auto currentChild = getCurrentChild();
            if (currentChild->isFinished() || currentChild->isFailed()) {
                auto* asList = getActor()->getASList();
                if (asList) {
                    asList->startAnimationMaybe(-1.0f, -1.0f, "Wait", 0, 0, true);
                }
                unk_5C = true;
            } else if (!unk_5C) {
                return;
            }
        }

        if ((fly_up_multiplier >= 1.0f && actorMtx(1, 3) >= getDataMgr()->vec_F8.y) || unk_54 >= *mFlyUpDuration_s * 3.0f) {
            ksys::act::ActorConstDataAccess accessor;
            if (ksys::act::acquireActor(&getDataMgr()->mBaseProcLink1, &accessor)) {
                unk_58 = 3;
                getActor()->sendMessage(*accessor.getMessageTransceiverId(), 0x80000C8, &unk_58,
                                        false);
            }
        }
    } else if ((actorMtx(1, 3) - unk_50) >= (*mTargetDistance_d * 0.9f) ||
               unk_54 >= (*mFlyUpDuration_s * 3.0f)) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&getDataMgr()->mBaseProcLink1, &accessor)) {
            unk_58 = 2;
            getActor()->sendMessage(*accessor.getMessageTransceiverId(), 0x80000C8, &unk_58,
                                    false);
        }
    }
}

void AirOctaFlyUp::leave_() {
    auto* dataMgr = sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
    if (dataMgr) {
        dataMgr->unk_118 += *mTargetDistance_d;
        dataMgr->unk_114 = 0.0f;
        dataMgr->sub_71002FB17C();
    }
}

void AirOctaFlyUp::loadParams_() {
    getStaticParam(&mFlyUpDuration_s, "FlyUpDuration");
    getDynamicParam(&mTargetDistance_d, "TargetDistance");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

bool AirOctaFlyUp::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x80000C8) {
        auto* userData = reinterpret_cast<AirOctaDataMgr::MessageData*>(message.getUserData());
        auto* dataMgr = sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
        if (!dataMgr) {
            return true;
        }

        if (userData) {
            if (userData->unk_00 == 3) {
                changeChild("終了", nullptr);
            } else if (userData->unk_00 == 4) {
                setFinished();
            }
        }
        return true;
    }
    return false;
}

AirOctaDataMgr* AirOctaFlyUp::getDataMgr() const {
    return sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
}

}  // namespace uking::ai
