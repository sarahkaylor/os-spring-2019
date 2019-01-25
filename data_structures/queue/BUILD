
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
		"@gtest//:main"
	],
)
