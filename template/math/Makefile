TEST_ARGS=-isystem ~/googletest/googletest/include \
	 -isystem ~/googletest/googlemock/include \
	 -I ~/googletest/googletest \
	 -I ~/googletest/googlemock \
	 ~/googletest/googletest/src/gtest-all.cc \
	 ~/googletest/googletest/src/gtest_main.cc \
	 -Wall -Wconversion -Wno-sign-conversion -Wextra -Wshadow \
	 -fsanitize=address

BM_ARGS=-isystem ~/benchmark/include \
	 -I ~/benchmark \
	 ~/benchmark/src/*.cc \
	 -DHAVE_STD_REGEX \
	 -DNDEBUG

TESTS = chinese-remainder_test \
		det-int_test \
		ext-gcd_test \
		fft_test \
		hash_test \
		mu_test \
		online-convolution_test \
		phi_test \

BMS = fft_bm \

run: $(TESTS)
	for t in $(TESTS); do ./$$t; done
test_%: %_test
	./$<
bm_%: %_bm
	./$<

%_test: tests/%_test.cc %.h
	g++ --std=c++11 -o $@ $< $(TEST_ARGS)
fft_test: tests/fft_test.cc fft.h field-complex.h field-intmod.h
	g++ --std=c++11 -o $@ $< $(TEST_ARGS)
online-convolution_test: tests/online-convolution_test.cc online-convolution.h fft.h field-complex.h field-intmod.h
	g++ --std=c++11 -o $@ $< $(TEST_ARGS)

fft_bm: tests/fft_bm.cc fft.h field-complex.h field-intmod.h
	g++ -O2 --std=c++11 -o $@ $< $(BM_ARGS)

clean:
	rm -vf $(TESTS)
	rm -vf $(BMS)
