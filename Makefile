compile:
	ninja -C build
run:
	./build/main
valgrind:
	valgrind --leak-check=yes -s ./build/main
test:
	./build/list_tests
multitest:
	./build/list_tests --gtest_repeat=100
filtered_tests:
	./build/list_tests --gtest_filter=*
build_again:
	rm -r build/*
	cmake -G "Ninja" -B build/ -S .