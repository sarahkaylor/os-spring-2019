java_library(
    name = "IMap",
    srcs = ["IMap.java"],
    visibility = ["//visibility:public"],
)

java_library(
    name = "IKeyHasher",
    srcs = ["IKeyHasher.java"],
    visibility = ["//visibility:public"],
    deps = [],
)

java_library(
    name = "MapImpl",
    srcs = ["MapImpl.java"],
    visibility = ["//visibility:public"],
    deps = [
        ":IKeyHasher",
        ":IMap",
    ],
)
