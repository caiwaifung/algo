TESTS = 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

run: a out/score
	$(foreach i,$(TESTS),echo running: $i; ./a <in/$i.in >out/$i.out;)
	out/score

gen: in/gen
	in/gen

a: a.cc
	g++ a.cc -o a -O2 --std=c++11

out/score: out/score.cc
	g++ out/score.cc -o out/score --std=c++11

in/gen: in/gen.cc
	g++ in/gen.cc -o in/gen --std=c++11

clean:
	rm a in/gen out/score out/*.out out/*.ppm
