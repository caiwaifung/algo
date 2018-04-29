cc_library(
    name = "ext-gcd",
    hdrs = ["ext-gcd.h"],
)

cc_test(
    name = "chinese-remainder_test",
    srcs = [
        "chinese-remainder.h",
        "tests/chinese-remainder_test.cc",
    ],
    deps = [
        ":ext-gcd",
        "//template/base",
        "@gtest//:gtest_main",
    ],
)
