ARGS=-isystem ~/googletest/googletest/include \
	 -I ~/googletest/googletest \
	 ~/googletest/googletest/src/gtest-all.cc \
	 ~/googletest/googletest/src/gtest_main.cc

TESTS = hash_test.cc ext-gcd_test.cc

test: $(TESTS)
	g++ --std=c++11 -o test $(TESTS) $(ARGS)

run: test
	./test

clean:
	rm test
