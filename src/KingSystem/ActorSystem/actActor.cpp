#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"

namespace ksys::act {

namespace {
BaseProcLink sDummyBaseProcLink;
}  // namespace

BaseProcLink& getDummyBaseProcLink() {
    return sDummyBaseProcLink;
}

Actor::Actor(const CreateArg& arg) : BaseProc(arg) {
    mJobHandlers[BaseProcMgr::getConstant0()] = &mJob0;
    mJobHandlers[BaseProcMgr::getConstant1()] = &mJob1;
    mJobHandlers[BaseProcMgr::getConstant2()] = &mJob2;
    mJobHandlers[BaseProcMgr::getConstant4()] = &mJob4;

    mUnk1.actor = this;
    mUnk1._4 = 0;
}

Actor::~Actor() {
    // FIXME
}

void Actor::clearFlag(Actor::ActorFlag flag) {
    mActorFlags.resetBit(flag);
}

bool Actor::checkFlag(Actor::ActorFlag flag) const {
    return mActorFlags.isOnBit(flag);
}

void Actor::setFlag(Actor::ActorFlag flag) {
    setFlag(flag, true);
}

void Actor::setFlag(Actor::ActorFlag flag, bool on) {
    mActorFlags.changeBit(flag, on);
}

const sead::SafeString& Actor::getProfile() const {
    return mActorParam->getProfile();
}

const char* Actor::getUniqueName() const {
    const char* unique_name = nullptr;

    if (mMapObjIter.tryGetParamStringByKey(&unique_name, "UniqueName"))
        return unique_name;

    if (mUniqueName && mUniqueName->unique_name)
        unique_name = mUniqueName->unique_name->cstr();

    return unique_name;
}

s32 Actor::getMaxLife() {
    return getMaxLife_();
}

s32 Actor::getMaxLife_() {
    auto* paramList = getParam()->getRes().mGParamList;
    if (!paramList) {
        return 1;
    }
    auto general = paramList->get<ksys::res::GParamListObjType::General>();
    if (general) {
        return *general->mLife;
    }
    return 1;
}

Actor* Actor::m31() {
    if (mActorFlags.isOnBit(ActorFlag::_5) && mModelBindInfo) {
        return mModelBindInfo->sub_7100D3C5E0(this);
    }
    return nullptr;
}

Actor* Actor::m32() {
    return m31();
}

s32 Actor::m33() {
    return 0;
}

void Actor::handleAck(const MessageAck& ack) {
    if (m80())
        return;

    if (mRootAi)
        mRootAi->handleAck(ack);
}

int Actor::handleMessage(const Message& message) {
    const auto result = doHandleMessage_(message);
    switch (result) {
    default:
        return 0;
    case HandleMessageResult::_1:
        return 1;
    case HandleMessageResult::_2:
        m107();
        return 1;
    }
}

}  // namespace ksys::act
