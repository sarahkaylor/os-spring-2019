cc_library(
    name = "maybe",
    hdrs = ["maybe.h"],
    deps = [],
)

cc_library(
    name = "map_impl",
    hdrs = ["map_impl.h"],
    deps = [
        ":maybe",
    ],
)

cc_library(
    name = "string_hashes",
    srcs = ["string_hashes.cpp"],
    hdrs = ["string_hashes.h"],
)

cc_test(
    name = "map_tests",
    srcs = ["map_tests.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":map_impl",
        ":string_hashes",
        "@gtest//:main",
    ],
)

cc_library(
    name = "cache_map",
    hdrs = ["cache_map.h"],
    deps = [
        ":maybe",
    ],
)

cc_test(
    name = "cache_map_tests",
    srcs = ["cache_map_tests.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":cache_map",
        ":string_hashes",
        "@gtest//:main",
    ],
)
