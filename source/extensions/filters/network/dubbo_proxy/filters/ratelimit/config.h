#pragma once

#include "envoy/extensions/filters/network/dubbo_proxy/filters/ratelimit/v3/rate_limit.pb.h"
#include "envoy/extensions/filters/network/dubbo_proxy/filters/ratelimit/v3/rate_limit.pb.validate.h"

#include "extensions/filters/common/ratelimit/ratelimit.h"
#include "extensions/filters/network/dubbo_proxy/filters/factory_base.h"
#include "extensions/filters/network/dubbo_proxy/filters/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace DubboFilters {
namespace RateLimitFilter {

using namespace Envoy::Extensions::NetworkFilters;

/**
 * Config registration for the rate limit filter. @see NamedDubboFilterConfigFactory.
 */
class RateLimitFilterConfig
    : public DubboProxy::DubboFilters::FactoryBase<
          envoy::extensions::filters::network::dubbo_proxy::filters::ratelimit::v3::RateLimit> {
public:
  RateLimitFilterConfig()
      : FactoryBase(DubboProxy::DubboFilters::DubboFilterNames::get().RATE_LIMIT) {}

private:
  DubboProxy::DubboFilters::FilterFactoryCb createFilterFactoryFromProtoTyped(
      const envoy::extensions::filters::network::dubbo_proxy::filters::ratelimit::v3::RateLimit&
          proto_config,
      const std::string& stats_prefix, Server::Configuration::FactoryContext& context) override;
};

} // namespace RateLimitFilter
} // namespace DubboFilters
} // namespace Extensions
} // namespace Envoy
