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

TESTS = kmp_test \

BMS = \

run: $(TESTS)
	for t in $(TESTS); do ./$$t; done
test_%: %_test
	./$<
bm_%: %_bm
	./$<

%_test: tests/%_test.cc %.h
	g++ --std=c++11 -o $@ $< $(TEST_ARGS)

clean:
	rm -vf $(TESTS)
	rm -vf $(BMS)
