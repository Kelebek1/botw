#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class AirOctaDataMgr {
    SEAD_RTTI_BASE(AirOctaDataMgr)

public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }

private:
    /* 0x08 */ char unk_00[0x10];
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink;
};

class AirOctaBoardBurn : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(AirOctaBoardBurn, SeqTwoAction)
    friend AirOctaDataMgr;

public:
    explicit AirOctaBoardBurn(const InitArg& arg);
    ~AirOctaBoardBurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

protected:
    // aitree_variable at offset 0x50
    AirOctaDataMgr** mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
