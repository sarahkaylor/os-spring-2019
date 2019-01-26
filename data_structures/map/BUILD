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
