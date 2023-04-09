#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"

namespace ksys::act {

Actor* ModelBindInfo::sub_7100D3C5E0(BaseProc* proc) {
    if (unk_20) {
        proc = unk_20;
    }

    Actor* actor = sead::DynamicCast<Actor>(mBaseProcLink.getProc(nullptr, proc));
    if (!actor) {
        return nullptr;
    }

    auto& baseProc = actor->getfield738();
    if (baseProc.hasProc()) {
        ksys::act::ActorConstDataAccess acc;
        ksys::act::acquireActor(&baseProc, &acc);
        if (acc.isStateCalc()) {
            mBaseProcLink = baseProc;
            actor = sead::DynamicCast<Actor>(mBaseProcLink.getProc(nullptr, proc));
        }
        if (!actor) {
            return nullptr;
        }
    }

    if (actor->isCalc() && actor->isSpecialJobTypesMaskOverrideForThisActor(JobType::Calc1)) {
        return actor;
    }

    return nullptr;
}

}  // namespace ksys::act
