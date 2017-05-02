ARGS=-isystem ~/googletest/googletest/include \
	 -isystem ~/googletest/googlemock/include \
	 -I ~/googletest/googletest \
	 -I ~/googletest/googlemock \
	 ~/googletest/googletest/src/gtest-all.cc \
	 ~/googletest/googletest/src/gtest_main.cc

TESTS = hash_test \
		ext-gcd_test \
		fft_test \
		fft-int_test \
		chinese-remainder_test

%_test: tests/%_test.cc %.h
	g++ --std=c++11 -o $@ $< $(ARGS)

run: $(TESTS)
	for t in $(TESTS); do ./$$t; done

clean:
	rm $(TESTS)
