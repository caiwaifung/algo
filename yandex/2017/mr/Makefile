TESTS = 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24
SMALL = 0 1 10 11 20

run: a out/score
	$(foreach i,$(TESTS),echo running: $i; ./a <in/$i.in >out/$i.out;)
	out/score

small: a out/score
	$(foreach i,$(SMALL),echo running: $i; ./a <in/$i.in >out/$i.out;)
	out/score $(SMALL)

gen: in/gen
	in/gen

a: a.cc
	g++ a.cc -o a -O2 --std=c++11 -fsanitize=address

out/score: out/score.cc
	g++ out/score.cc -o out/score --std=c++11

in/gen: in/gen.cc
	g++ in/gen.cc -o in/gen --std=c++11

clean:
	rm a in/gen out/score out/*.out out/*.ppm
