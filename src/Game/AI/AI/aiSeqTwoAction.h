#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTwoAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqTwoAction, ksys::act::ai::Ai)
public:
    explicit SeqTwoAction(const InitArg& arg);

    bool isFailed() const override;
    bool isFinished() const override;
    bool isChangeable() const override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

    void calc_() override;
    void handlePendingChildChange_() override;
    virtual bool _m34() const;
    virtual bool _m35() const;
    virtual bool _m36() const;

protected:
    // static_param at offset 0x38
    const bool* mIsFinishedByFailAction_s{};
    // static_param at offset 0x40
    const bool* mIsEndChangeable_s{};
    // static_param at offset 0x48
    const bool* mIsNoChangeable_s{};
};

}  // namespace uking::ai
