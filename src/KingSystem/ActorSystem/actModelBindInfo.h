#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
class Actor;

class ActorBind {
    SEAD_RTTI_BASE(ActorBind)

public:
    virtual void _m0() = 0;
    virtual s64 _m1() = 0;
    virtual bool _m2() = 0;
    virtual bool _m3() = 0;
    virtual void* _m5(void* a2) = 0;
    virtual void _m6() {}

    /* 0x08 */ BaseProcLink mBaseProcLink;
    /* 0x18 */ bool unk_18{true};
    /* 0x20 */ BaseProc* unk_20{nullptr};
};

class ModelBindInfo : ActorBind {
    SEAD_RTTI_OVERRIDE(ModelBindInfo, ActorBind)

public:
    Actor* sub_7100D3C5E0(BaseProc* proc);

private:
    const char* mNode{nullptr};
    gsys::BoneAccessKeyEx mBoneAccessKey;
    sead::Matrix34f mMtx{sead::Matrix34f::ident};
    signed int unk_98{0};
};
// KSYS_CHECK_SIZE_NX150(ModelBindInfo, 0xA0);

}  // namespace ksys::act
