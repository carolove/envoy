#pragma once

#include "extensions/filters/network/dubbo_proxy/filters/filter.h"

#include "absl/strings/string_view.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace DubboProxy {
namespace DubboFilters {

/**
 * Pass through Dubbo decoder filter. Continue at each decoding state within the series of
 * transitions.
 */
class PassThroughDecoderFilter : public DecoderFilter {
public:
  // DubboDecoderFilter
  void onDestroy() override {}

  void setDecoderFilterCallbacks(DecoderFilterCallbacks& callbacks) override {
    decoder_callbacks_ = &callbacks;
  };

  // Dubbo Decoder State Machine
  DubboProxy::FilterStatus transportBegin(DubboProxy::MessageMetadataSharedPtr) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus transportEnd() override { return DubboProxy::FilterStatus::Continue; }

  bool passthroughSupported() const override { return true; }

  DubboProxy::FilterStatus passthroughData(Buffer::Instance&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus messageBegin(DubboProxy::MessageMetadataSharedPtr) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus messageEnd() override { return DubboProxy::FilterStatus::Continue; }

  DubboProxy::FilterStatus structBegin(absl::string_view) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus structEnd() override { return DubboProxy::FilterStatus::Continue; }

  DubboProxy::FilterStatus fieldBegin(absl::string_view, DubboProxy::FieldType&,
                                       int16_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus fieldEnd() override { return DubboProxy::FilterStatus::Continue; }

  DubboProxy::FilterStatus boolValue(bool&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus byteValue(uint8_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus int16Value(int16_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus int32Value(int32_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus int64Value(int64_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus doubleValue(double&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus stringValue(absl::string_view) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus mapBegin(DubboProxy::FieldType&, DubboProxy::FieldType&,
                                     uint32_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus mapEnd() override { return DubboProxy::FilterStatus::Continue; }

  DubboProxy::FilterStatus listBegin(DubboProxy::FieldType&, uint32_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus listEnd() override { return DubboProxy::FilterStatus::Continue; }

  DubboProxy::FilterStatus setBegin(DubboProxy::FieldType&, uint32_t&) override {
    return DubboProxy::FilterStatus::Continue;
  }

  DubboProxy::FilterStatus setEnd() override { return DubboProxy::FilterStatus::Continue; }

protected:
  DecoderFilterCallbacks* decoder_callbacks_{};
};

} // namespace DubboFilters
} // namespace DubboProxy
} // namespace NetworkFilters
} // namespace Extensions
} // namespace Envoy
