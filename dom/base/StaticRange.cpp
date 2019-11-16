/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "mozilla/dom/StaticRange.h"
#include "mozilla/dom/StaticRangeBinding.h"
#include "nsINode.h"

namespace mozilla {
namespace dom {

template already_AddRefed<StaticRange> StaticRange::Create(
    const RangeBoundary& aStartBoundary, const RangeBoundary& aEndBoundary,
    ErrorResult& aRv);
template already_AddRefed<StaticRange> StaticRange::Create(
    const RangeBoundary& aStartBoundary, const RawRangeBoundary& aEndBoundary,
    ErrorResult& aRv);
template already_AddRefed<StaticRange> StaticRange::Create(
    const RawRangeBoundary& aStartBoundary, const RangeBoundary& aEndBoundary,
    ErrorResult& aRv);
template already_AddRefed<StaticRange> StaticRange::Create(
    const RawRangeBoundary& aStartBoundary,
    const RawRangeBoundary& aEndBoundary, ErrorResult& aRv);
template nsresult StaticRange::SetStartAndEnd(
    const RangeBoundary& aStartBoundary, const RangeBoundary& aEndBoundary);
template nsresult StaticRange::SetStartAndEnd(
    const RangeBoundary& aStartBoundary, const RawRangeBoundary& aEndBoundary);
template nsresult StaticRange::SetStartAndEnd(
    const RawRangeBoundary& aStartBoundary, const RangeBoundary& aEndBoundary);
template nsresult StaticRange::SetStartAndEnd(
    const RawRangeBoundary& aStartBoundary,
    const RawRangeBoundary& aEndBoundary);
template void StaticRange::DoSetRange(const RangeBoundary& aStartBoundary,
                                      const RangeBoundary& aEndBoundary,
                                      nsINode* aRootNode);
template void StaticRange::DoSetRange(const RangeBoundary& aStartBoundary,
                                      const RawRangeBoundary& aEndBoundary,
                                      nsINode* aRootNode);
template void StaticRange::DoSetRange(const RawRangeBoundary& aStartBoundary,
                                      const RangeBoundary& aEndBoundary,
                                      nsINode* aRootNode);
template void StaticRange::DoSetRange(const RawRangeBoundary& aStartBoundary,
                                      const RawRangeBoundary& aEndBoundary,
                                      nsINode* aRootNode);

NS_IMPL_MAIN_THREAD_ONLY_CYCLE_COLLECTING_ADDREF(StaticRange)
NS_IMPL_MAIN_THREAD_ONLY_CYCLE_COLLECTING_RELEASE_WITH_LAST_RELEASE(
    StaticRange, DoSetRange(RawRangeBoundary(), RawRangeBoundary(), nullptr))

NS_INTERFACE_MAP_BEGIN_CYCLE_COLLECTION(StaticRange)
NS_INTERFACE_MAP_END_INHERITING(AbstractRange)

NS_IMPL_CYCLE_COLLECTION_CLASS(StaticRange)

NS_IMPL_CYCLE_COLLECTION_UNLINK_BEGIN_INHERITED(StaticRange, AbstractRange)
  NS_IMPL_CYCLE_COLLECTION_UNLINK(mStart)
  NS_IMPL_CYCLE_COLLECTION_UNLINK(mEnd)
NS_IMPL_CYCLE_COLLECTION_UNLINK_END

NS_IMPL_CYCLE_COLLECTION_TRAVERSE_BEGIN_INHERITED(StaticRange, AbstractRange)
NS_IMPL_CYCLE_COLLECTION_TRAVERSE_END

NS_IMPL_CYCLE_COLLECTION_TRACE_BEGIN_INHERITED(StaticRange, AbstractRange)
NS_IMPL_CYCLE_COLLECTION_TRACE_END

// static
template <typename SPT, typename SRT, typename EPT, typename ERT>
already_AddRefed<StaticRange> StaticRange::Create(
    const RangeBoundaryBase<SPT, SRT>& aStartBoundary,
    const RangeBoundaryBase<EPT, ERT>& aEndBoundary, ErrorResult& aRv) {
  RefPtr<StaticRange> staticRange = new StaticRange(aStartBoundary.Container());
  aRv = staticRange->SetStartAndEnd(aStartBoundary, aEndBoundary);
  if (NS_WARN_IF(aRv.Failed())) {
    return nullptr;
  }
  return staticRange.forget();
}

template <typename SPT, typename SRT, typename EPT, typename ERT>
void StaticRange::DoSetRange(const RangeBoundaryBase<SPT, SRT>& aStartBoundary,
                             const RangeBoundaryBase<EPT, ERT>& aEndBoundary,
                             nsINode* aRootNode) {
  mStart = aStartBoundary;
  mEnd = aEndBoundary;
  mIsPositioned = mStart.IsSet();
}

JSObject* StaticRange::WrapObject(JSContext* aCx,
                                  JS::Handle<JSObject*> aGivenProto) {
  return StaticRange_Binding::Wrap(aCx, this, aGivenProto);
}

}  // namespace dom
}  // namespace mozilla