#include "Game/Actor/Player/PlayerResetPosMgr.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

SEAD_SINGLETON_DISPOSER_IMPL(Root6)

auto Root6::sub_71009287CC(ksys::act::ActorLinkConstDataAccess* accessor) -> void {
    if (accessor != nullptr) {
        accessor->acquire(mSomeActor);
    }
}

auto Root6::getCameraActor() -> ksys::act::Actor* {
    if (mSomeActor && ksys::act::BaseProcMgr::instance() && ksys::act::BaseProcMgr::instance()->isAccessingProcSafe(mSomeActor, nullptr)) {
        return mSomeActor;
    }
    return nullptr;
}

SEAD_SINGLETON_DISPOSER_IMPL(PlayerResetPosMgr)

auto PlayerResetPosMgr::isNotResetting() -> bool {
    return mStatus == 0;
}

auto PlayerResetPosMgr::callCameraM151IfStatus4() -> void {
    if (mStatus == 4) {

    }
}

auto PlayerResetPosMgr::addResetPos(const sead::Vector3<f32>& pos, f32 rotation) -> void {
    mSpinLock.lock();
    if (mNumResetPos < 64) {
        mResetPositions[mNumResetPos].setPos(pos);
        mResetPositions[mNumResetPos].setRot(rotation);
        mNumResetPos++;
    }
    mSpinLock.unlock();
}

auto PlayerResetPosMgr::setResetPos(const sead::Vector3<f32>& pos, f32 rotation, ksys::act::Actor* actor) -> void {
    mSpinLock.lock();
    mResetPosActor = actor;
    mHasResetPosOverride = true;
    mResetPosOverride.setPos(pos);
    mResetPosOverride.setRot(rotation);
    mSpinLock.unlock();
}

auto PlayerResetPosMgr::clearResetPos() -> void {
    mSpinLock.lock();
    if (mResetPosActor == nullptr) {
        mHasResetPosOverride = false;
    }
    mSpinLock.unlock();
    mNumResetPos = 0;
}
