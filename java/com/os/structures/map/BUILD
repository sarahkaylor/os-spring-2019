java_library(
    name = "IMap",
    srcs = ["IMap.java"],
)

java_library(
    name = "IKeyHasher",
    srcs = ["IKeyHasher.java"],
    deps = [],
)

java_library(
    name = "MapImpl",
    srcs = ["MapImpl.java"],
    deps = [
        ":IKeyHasher",
        ":IMap",
    ],
)
