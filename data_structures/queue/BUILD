cc_library(
    name = "queue",
    hdrs = ["queue.h"],
    deps = [],
)

cc_test(
    name = "queue_tests",
    srcs = ["queue_tests.cc"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":queue",
        "@gtest//:main",
    ],
)

cc_library(
    name = "bound_buffer",
    hdrs = ["bound_buffer.h"],
    deps = [],
)

cc_test(
    name = "bound_buffer_tests",
    srcs = ["bound_buffer_tests.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":bound_buffer",
        "@gtest//:main",
    ],
)
