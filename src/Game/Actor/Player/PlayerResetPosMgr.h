#pragma once

#include <heap/seadDisposer.h>
#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <thread/seadSpinLock.h>
#include "KingSystem/ActorSystem/actActor.h"

class ResetPos {
    sead::Vector3<f32> pos;
    f32 rotation;
};

class PlayerResetPosMgr {
    SEAD_SINGLETON_DISPOSER(PlayerResetPosMgr)

    PlayerResetPosMgr() : 
        numResetPos{},
        resetPositions{}, 
        resetPosActor{},
        hasResetPosOverride{},
        resetPosOverride{},
        spinLock{},
        status{}
    {
    };

public:
    /* 0x020 */ s32 numResetPos;
    /* 0x024 */ ResetPos resetPositions[64];
    /* 0x428 */ ksys::act::Actor *resetPosActor;
    /* 0x430 */ bool hasResetPosOverride;
    /* 0x434 */ ResetPos resetPosOverride;
    /* 0x448 */ sead::SpinLock spinLock;
    /* 0x458 */ int status;
    /* 0x45C */ sead::Vector3<f32> field_45C;
    /* 0x468 */ sead::Vector3<f32> field_468;
};
