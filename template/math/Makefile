ARGS=-isystem ~/googletest/googletest/include \
	 -isystem ~/googletest/googlemock/include \
	 -I ~/googletest/googletest \
	 -I ~/googletest/googlemock \
	 ~/googletest/googletest/src/gtest-all.cc \
	 ~/googletest/googletest/src/gtest_main.cc

TESTS = tests/hash_test.cc \
		tests/ext-gcd_test.cc \
		tests/fft_test.cc \
		tests/fft-int_test.cc \

all_tests: $(TESTS)
	g++ --std=c++11 -o all_tests $(TESTS) $(ARGS)

run: all_tests
	./all_tests

clean:
	rm all_tests
