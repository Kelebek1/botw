#pragma once

#include <heap/seadDisposer.h>
#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <container/seadSafeArray.h>
#include <thread/seadSpinLock.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actCamera.h"

class Root6 {
    SEAD_SINGLETON_DISPOSER(Root6)

    public:
        Root6() = default;

        auto sub_71009287CC(ksys::act::ActorLinkConstDataAccess* accessor) -> void;
        auto getCameraActor() -> ksys::act::Actor*;

        ksys::act::Actor* mSomeActor{};
};

class ResetPos {
public:
    inline auto setPos(const sead::Vector3<f32>& pos_) { pos = pos_; }
    inline auto setRot(f32 rot) { rotation = rot; }

private:
    sead::Vector3<f32> pos;
    f32 rotation;
};

class PlayerResetPosMgr {
    SEAD_SINGLETON_DISPOSER(PlayerResetPosMgr)

public:
    PlayerResetPosMgr() = default;

    auto isNotResetting() -> bool;
    auto callCameraM151IfStatus4() -> void;
    auto addResetPos(const sead::Vector3<f32>& pos, f32 rotation) -> void;
    auto setResetPos(const sead::Vector3<f32>& pos, f32 rotation, ksys::act::Actor* actor) -> void;
    auto clearResetPos() -> void;

private:
    s32 mNumResetPos{};
    sead::SafeArray<ResetPos, 64> mResetPositions{};
    ksys::act::Actor* mResetPosActor{};
    bool mHasResetPosOverride{};
    ResetPos mResetPosOverride{};
    sead::SpinLock mSpinLock;
    int mStatus{};
    sead::Vector3<f32> mUnk_45C;
    sead::Vector3<f32> mUnk_468;
};
