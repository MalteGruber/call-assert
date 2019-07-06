
test:
	cppcheck ../
	gcc -pedantic-errors -Wall -g -Werror -I../ ../callback_tester.c test.c -o demo
	valgrind --track-origins=yes valgrind --leak-check=full -q ./demo
	./demo

quick:
	gcc -pedantic-errors -Wall -g -Werror -I../ ../callback_tester.c test.c -o demo
	./demo
	