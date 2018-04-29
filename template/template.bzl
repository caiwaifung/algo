def template_test(name):
    return native.cc_test(name=name + "_test",
                          srcs = [name + ".h",
                                  "tests/" + name + "_test.cc"],
                          deps = ["//template/base",
                                  "@gtest//:gtest_main"])

