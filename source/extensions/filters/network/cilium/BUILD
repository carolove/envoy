load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

# Cilium proxy L4 network filter.

envoy_extension_package()

envoy_cc_library(
    name = "tls_wrapper_lib",
    srcs = ["tls_wrapper.cc"],
    hdrs = ["tls_wrapper.h"],
    deps = [
        ":network_policy_lib",
        ":socket_option_lib",
        "//include/envoy/network:transport_socket_interface",
        "//include/envoy/registry",
        "//include/envoy/server:transport_socket_config_interface",
        "//source/extensions/transport_sockets/tls:ssl_socket_lib",
        "//source/server:transport_socket_config_lib",
    ],
)

envoy_cc_library(
    name = "network_policy_lib",
    srcs = [
        "network_policy.cc",
    ],
    hdrs = [
        "network_policy.h",
    ],
    deps = [
        ":accesslog_lib",
        ":conntrack_lib",
        ":grpc_subscription_lib",
        "@envoy_api//envoy/extensions/filters/network/cilium/v3:pkg_cc_proto",
        "//include/envoy/config:subscription_interface",
        "//include/envoy/singleton:manager_interface",
        "//source/common/common:logger_lib",
        "//source/common/local_info:local_info_lib",
        "//source/common/network:address_lib",
        "//source/common/router:config_utility_lib",
        "//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "socket_option_lib",
    hdrs = [
        "socket_option.h",
    ],
    repository = "@envoy",
    deps = [
        ":conntrack_lib",
        "//include/envoy/network:listen_socket_interface",
        "//source/common/common:logger_lib",
    ],
)

envoy_cc_library(
    name = "grpc_subscription_lib",
    srcs = [
        "grpc_subscription.cc",
    ],
    hdrs = [
        "grpc_subscription.h",
    ],
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        "//source/common/config:grpc_subscription_lib",
        "//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "l7policy_lib",
    srcs = [
        "l7policy.cc",
    ],
    hdrs = [
        "l7policy.h",
    ],
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        ":accesslog_lib",
        ":network_policy_lib",
        ":socket_option_lib",
        "//cilium/api:l7policy_cc_proto",
        "//include/envoy/config:subscription_interface",
        "//source/common/http:utility_lib",
        "//source/common/network:upstream_server_name_lib",
        "//source/common/network:upstream_subject_alt_names_lib",
    ],
)

envoy_cc_library(
    name = "accesslog_lib",
    srcs = [
        "accesslog.cc",
    ],
    hdrs = [
        "accesslog.h",
    ],
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        ":socket_option_lib",
        "//cilium/api:accesslog_proto_cc_proto",
        "//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "bpf_lib",
    srcs = [
        "bpf.cc",
    ],
    hdrs = [
        "bpf.h",
        "//:linux/bpf.h",
        "//:linux/bpf_common.h",
        "//:linux/type_mapper.h",
    ],
    repository = "@envoy",
    deps = [
        "//source/common/common:logger_lib",
        "//source/common/common:utility_lib",
    ],
)

envoy_cc_library(
    name = "ipcache_lib",
    srcs = [
        "ipcache.cc",
    ],
    hdrs = [
        "ipcache.h",
    ],
    repository = "@envoy",
    deps = [
        ":bpf_lib",
        "//include/envoy/singleton:manager_interface",
        "//source/common/common:assert_lib",
        "//source/common/common:logger_lib",
        "//source/common/network:address_lib",
    ],
)

envoy_cc_library(
    name = "conntrack_lib",
    srcs = [
        "conntrack.cc",
    ],
    hdrs = [
        "conntrack.h",
    ],
    repository = "@envoy",
    deps = [
        ":bpf_lib",
        "//include/envoy/network:connection_interface",
        "//include/envoy/network:listen_socket_interface",
        "//include/envoy/singleton:manager_interface",
        "//source/common/common:assert_lib",
        "//source/common/common:logger_lib",
        "//source/common/network:address_lib",
    ],
)

envoy_cc_library(
    name = "proxylib_lib",
    srcs = [
        "proxylib.cc",
    ],
    hdrs = [
        "proxylib.h",
        "//proxylib:libcilium.h",
        "//proxylib:types.h",
    ],
    repository = "@envoy",
    deps = [
        "//include/envoy/network:connection_interface",
        "//include/envoy/singleton:manager_interface",
        "//source/common/buffer:buffer_lib",
        "//source/common/common:assert_lib",
        "//source/common/common:logger_lib",
    ],
)

envoy_cc_extension(
    name = "config",
    srcs = [
        "config.cc",
    ],
    hdrs = [
        "config.h",
    ],
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        ":conntrack_lib",
        ":network_policy_lib",
        ":proxylib_lib",
        ":socket_option_lib",
        "//cilium/api:network_filter_cc_proto",
        "//include/envoy/buffer:buffer_interface",
        "//include/envoy/network:connection_interface",
        "//include/envoy/network:filter_interface",
        "//include/envoy/registry",
        "//include/envoy/server:filter_config_interface",
        "//source/common/common:assert_lib",
        "//source/common/common:logger_lib",
        "//source/common/network:address_lib",
        "//source/common/network:upstream_server_name_lib",
        "//source/common/network:upstream_subject_alt_names_lib",
    ],
)
