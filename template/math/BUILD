cc_library(
    name = "gcd",
    hdrs = ["gcd.h"],
    deps = ["//template/base"],
)

cc_test(
    name = "gcd_test",
    srcs = ["tests/gcd_test.cc"],
    deps = [
        ":gcd",
        "@gtest//:gtest_main",
    ],
)
