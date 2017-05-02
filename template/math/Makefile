ARGS=-isystem ~/googletest/googletest/include \
	 -isystem ~/googletest/googlemock/include \
	 -I ~/googletest/googletest \
	 -I ~/googletest/googlemock \
	 ~/googletest/googletest/src/gtest-all.cc \
	 ~/googletest/googletest/src/gtest_main.cc

TESTS = chinese-remainder_test \
		det-int_test \
		ext-gcd_test \
		fft_test \
		hash_test \

run: $(TESTS)
	for t in $(TESTS); do ./$$t; done

%_test: tests/%_test.cc %.h
	g++ --std=c++11 -o $@ $< $(ARGS)

fft_test: tests/fft_test.cc fft.h field-complex.h field-intmod.h
	g++ --std=c++11 -o $@ $< $(ARGS)

run_%: %_test
	./$<

clean:
	rm $(TESTS)
