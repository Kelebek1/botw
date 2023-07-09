#pragma once

#include <container/seadPtrArray.h>
#include <container/seadObjArray.h>
#include <math/seadMatrix.h>

#include "Game/AI/AI/aiFork2AI.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

// TODO inherits from something
class AirOctaDataMgr {
    SEAD_RTTI_BASE(AirOctaDataMgr)

public:
    struct MessageData {
        u32 unk_00;
        u64 unk_08;
    };

    // struct Unk28 {
    // };
    // KSYS_CHECK_SIZE_NX150(Unk28, 0xB3);

    void sub_71002FB1A8(u64 a1);
    void sub_71002FAF84(ksys::act::Actor* actor);

    /* 0x08 */ ksys::act::BaseProcLink mBaseProcLink1;
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink2;
    /* 0x28 */ void* unk_28{};
    /* 0x30 */ u32 unk_30{};
    /* 0x34 */ sead::Vector3f unk_34{sead::Vector3f::zero};
    /* 0x40 */ void* unk_40{};
    /* 0x40 */ u32 unk_48{};
    /* 0x4C */ sead::Vector3f unk_4C{sead::Vector3f::zero};
    sead::FixedObjArray<MessageData, 4> obj_arr;
    /* 0xD8 */ u16 unk_D8{};
    /* 0xDA */ bool unk_DA{};
    /* 0xDC */ u32 unk_DC;
    /* 0xE0 */ sead::Vector3f vec_E0{sead::Vector3f::zero};
    /* 0xEC */ sead::Vector3f vec_EC{sead::Vector3f::zero};
    /* 0xF8 */ sead::Vector3f vec_F8{sead::Vector3f::zero};
    /* 0x104 */ sead::Vector3f vec_104{sead::Vector3f::zero};
    /* 0x110 */ f32 unk_110{};
    /* 0x114 */ f32 unk_114{};
    /* 0x118 */ f32 unk_118{};
    /* 0x11C */ f32 unk_11C{};
    /* 0x120 */ u8 unk_120{};
};
KSYS_CHECK_SIZE_NX150(AirOctaDataMgr, 0x128);

class AirOctaRoot : public Fork2AI {
    SEAD_RTTI_OVERRIDE(AirOctaRoot, Fork2AI)
public:
    explicit AirOctaRoot(const InitArg& arg);
    ~AirOctaRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

protected:
    // aitree_variable at offset 0x38
    void* mAirOctaDataMgr_a{};
    AirOctaDataMgr* mAirOctaDataMgr;
};

}  // namespace uking::ai
