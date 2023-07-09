#include "Game/AI/AI/aiAirOctaRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace act {
ksys::map::ObjectLink* findLinkReferenceObj(const ksys::act::Actor* actor,
                                                sead::SafeString& outName, const sead::SafeString& name,
                                                u32* linkRefIdx);
}

namespace uking::ai {

void AirOctaDataMgr::sub_71002FAF84(ksys::act::Actor* actor) {
    if (unk_120) {
        return;
    }

    sead::SafeString outManagerName{};
    auto managerLink = act::findLinkReferenceObj(actor, outManagerName, "Manager", nullptr);

    if (managerLink) { 
        ksys::act::ActorConstDataAccess accessor;
        managerLink->getObjectProcWithAccessor(accessor);
        accessor.linkAcquire(&mBaseProcLink1);
    }

    sead::SafeString outBoardName{};
    auto boardLink = act::findLinkReferenceObj(actor, outBoardName, "Board", nullptr);
    if (boardLink) { 
        ksys::act::ActorConstDataAccess accessor;
        boardLink->getObjectProcWithAccessor(accessor);
        if (accessor.linkAcquire(&mBaseProcLink2)) {
            auto& actorMtx = actor->getMtx();
            auto& accessMtx = accessor.getActorMtx();
            sead::Matrix34<f32> mtx;
            mtx.setInverse(accessMtx);

            // f32 x = mtx(0,0) * actorMtx(0,3) + mtx(1,0) * actorMtx(1,3) + mtx(2,0) * actorMtx(2,3) + accessMtx(0,3);
            // f32 y = mtx(0,1) * actorMtx(0,3) + mtx(1,1) * actorMtx(1,3) + mtx(2,1) * actorMtx(2,3) + accessMtx(1,3);
            // f32 z = mtx(0,2) * actorMtx(0,3) + mtx(1,2) * actorMtx(1,3) + mtx(2,2) * actorMtx(2,3) + accessMtx(2,3);
            vec_E0.x = mtx(0,0) * actorMtx(0,3) + mtx(1,0) * actorMtx(1,3) + mtx(2,0) * actorMtx(2,3) + mtx(0,3);
            vec_E0.y = 0.0f;
            vec_E0.z = mtx(0,2) * actorMtx(0,3) + mtx(1,2) * actorMtx(1,3) + mtx(2,2) * actorMtx(2,3) + mtx(2,3);
            unk_110 =  mtx(0,1) * actorMtx(0,3) + mtx(1,1) * actorMtx(1,3) + mtx(2,1) * actorMtx(2,3) + mtx(1,3);
            unk_110 += mtx(1, 3);
        }
    }

    auto& actorMtx = actor->getMtx();
    actorMtx.getBase(vec_F8, 3);
    f32 y_tmp = actorMtx(1, 3) - unk_110;

    vec_F8.y = y_tmp;
    // vec_F8.x = actorMtx(0, 3);
    // vec_F8.y = actorMtx(1, 3) - unk_110;
    // vec_F8.z = actorMtx(2, 3);
    actorMtx.getBase(vec_EC, 3);

    //vec_EC.x = actorMtx(0, 3);
    vec_EC.y = y_tmp + unk_110 + unk_114 + unk_118 + unk_11C;
    //vec_EC.z = actorMtx(2, 3);

    unk_120 |= 1;
}

AirOctaRoot::AirOctaRoot(const InitArg& arg) : Fork2AI(arg) {}

AirOctaRoot::~AirOctaRoot() = default;

bool AirOctaRoot::init_(sead::Heap* heap) {
    auto actor = getActor();
    actor->setDrawDistanceFlag(ksys::act::Actor::DrawDistanceFlag::_1);
    if (!Fork2AI::init_(heap)) {
        return false;
    }
    mAirOctaDataMgr = new (heap) AirOctaDataMgr;
    *(void**)mAirOctaDataMgr_a = (void*)mAirOctaDataMgr;
    return mAirOctaDataMgr != nullptr;
}

void AirOctaRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* dataMgr = sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
    if (dataMgr) {
        dataMgr->sub_71002FAF84(getActor());
    }
    Fork2AI::enter_(params);
}

void AirOctaRoot::leave_() {
    Fork2AI::leave_();
}

void AirOctaRoot::loadParams_() {
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

bool AirOctaRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x80000C8) {
        auto* userData = reinterpret_cast<AirOctaDataMgr::MessageData*>(message.getUserData());
        if (userData) {
            if (userData->unk_00 == 1) {
                auto* dataMgr =
                    sead::DynamicCast<AirOctaDataMgr>(*(AirOctaDataMgr**)mAirOctaDataMgr_a);
                if (dataMgr) {
                    dataMgr->sub_71002FB1A8(userData->unk_08);
                }
            }
        }
    }
    return Fork2AI::handleMessage_(message);
}

}  // namespace uking::ai
