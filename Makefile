

demo:
	gcc -pedantic-errors -Wall -g -Werror -I. callback_tester.c demo.c -o demo_executable
	./demo_executable
	