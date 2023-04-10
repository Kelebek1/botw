#include "Game/AI/AI/aiSeqTwoAction.h"

namespace uking::ai {

SeqTwoAction::SeqTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool SeqTwoAction::isFailed() const {
    if (mFlags.isOn(Flag::Failed)) {
        return true;
    }
    if (*mIsFinishedByFailAction_s) {
        return false;
    }
    if (!*mIsFinishedByFailAction_s && isCurrentChild("後行動")) {
        return getCurrentChild()->isFailed();
    }
    return false;
}

bool SeqTwoAction::isFinished() const {
    if (mFlags.isOn(Flag::Finished) || _m34()) {
        return true;
    }
    if (isCurrentChild("後行動")) {
        return getCurrentChild()->isFinished();
    }
    return false;
}

bool SeqTwoAction::isChangeable() const {
    if (*mIsNoChangeable_s) {
        return false;
    }
    auto* child = getCurrentChild();
    if (child->isChangeable()) {
        return true;
    }
    if (!*mIsEndChangeable_s) {
        return false;
    }
    return child->isFinished() || child->isFailed();
}

void SeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!handlePendingChildChange()) {
        if (_m36()) {
            changeChild("後行動", params);
        } else {
            changeChild("先行動", params);
        }
    }
}

void SeqTwoAction::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getStaticParam(&mIsEndChangeable_s, "IsEndChangeable");
    getStaticParam(&mIsNoChangeable_s, "IsNoChangeable");
}

void SeqTwoAction::calc_() {
    auto* child = getCurrentChild();
    if (_m35() && isCurrentChild("先行動")) {
        changeChild("後行動", nullptr);
    } else if (_m34()) {
        setFinished();
    } else if (child->isFinished() || child->isFailed()) {
        if (!child->isFailed() || !*mIsFinishedByFailAction_s) {
            if (isCurrentChild("先行動")) {
                changeChild("後行動", nullptr);
                return;
            }
            if (child->isFinished()) {
                setFinished();
                return;
            }
        }
        setFailed();
    }
}

void SeqTwoAction::handlePendingChildChange_() {
    changeChild(mPendingChildIdx);
}

bool SeqTwoAction::_m34() const {
    return false;
}

bool SeqTwoAction::_m35() const {
    return false;
}

bool SeqTwoAction::_m36() const {
    return false;
}

}  // namespace uking::ai
