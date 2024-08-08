CC = c++ -std=c++17
TESTFLAGS = -pthread -lgmock -lgmock_main -lgtest_main -lgtest -I/Users/caroylns/.brew/include -L/Users/caroylns/.brew/lib
GCCFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: test

test: clean
	$(CC) $(GCCFLAGS) $(TESTFLAGS) -g tests/*.cpp -o containers_test
	./containers_test

clang:
	
	clang-format -i include/*.h templates/*.tpp tests/*.cpp tests/*.h s21_containers.h

clean:
	rm -rf containers_test
