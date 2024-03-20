#include "Game/AI/AI/aiAirOctaRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "prim/seadSafeString.h"

namespace act {
ksys::map::ObjectLink* findLinkReferenceObj(const ksys::act::Actor* actor,
                                                sead::SafeString& outName, const sead::SafeString& name,
                                                u32* linkRefIdx);
}

namespace uking::ai {

void AirOctaDataMgr::sub_71002FAF84(ksys::act::Actor* actor) {
    if (mFlags & 1) {
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
            const auto& actorMtx = actor->getMtx();
            sead::Vector3f actorW;
            actorMtx.getBase(actorW,3);

            sead::Matrix34f mtx;
            mtx.setInverse(accessor.getActorMtx());
            
            f32 x1 = mtx(0,0) * actorW.x;
            f32 x2 = mtx(1,0) * actorW.y;
            f32 x3 = mtx(2,0) * actorW.z;
            f32 y1 = mtx(0,1) * actorW.x;
            f32 y2 = mtx(1,1) * actorW.y;
            f32 y3 = mtx(2,1) * actorW.z;
            f32 z1 = mtx(0,2) * actorW.x;
            f32 z2 = mtx(1,2) * actorW.y;
            f32 z3 = mtx(2,2) * actorW.z;

            vec_E0.y = 0.0f;
            vec_E0.x = x1 + x2 + x3 + actorW.x;
            vec_E0.z = y1 + y2 + y3 + actorW.z;

            unk_110 = z1 + z2 + z3 + actorW.y;
        }
    }

    actor->getMtx().getBase(vec_F8, 3);
    vec_EC = vec_F8;
    vec_EC.y -= unk_110;
    sub_71002FB17C();
    mFlags |= 1;
}

void AirOctaDataMgr::sub_71002FB17C() {
    vec_F8.y = vec_EC.y + unk_110 + unk_114 + unk_118 + unk_11C;
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
