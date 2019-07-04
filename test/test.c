/* Malte Gruber 2019 */

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <callback_tester.h>

#define ASSERT(name, format, ...) if(new_assert(name,format,__VA_ARGS__)!=PASS) return ERROR; else return PASS;

int test(void) {
	callstate_generator("example_call_A", "llidl", 4, 123, 15, 3.14159, 9999);
	ASSERT("example_call_A", "llRiRdl", 4, 123, 9, 15, 3.14, 4.0, 99991);
	asssert_call_queue_size(0);
	return 0;
}

int main(int argc, char ** argv) {
	printf("Example file\n");

	int res = test();
	if (res != PASS) {
		printf("UNIT TEST FAILED!\r\n");
	} else {
		printf("UNIT TEST PASSED! :D\r\n");
	}
	return 0;
}
