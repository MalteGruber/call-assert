/* Malte Gruber 2019 */
#include <callback_tester.h>
#define ASSERT_PASS(V) if(V!=PASS) return ERROR;

static void callback_A(int a, double b) {
	callback_called("callback_a", "id", a, b);
}

static void callback_B(long a, double b) {
	callback_called("callback_b", "ld", a, b);
}

void dummy_code_under_test(void) {
	callback_A(42, 3.14);
	callback_B(9000, 42.0);
}

static int demo_test() {
	dummy_code_under_test();
	/*Long and double assert*/
	ASSERT_PASS(callback_assert("callback_a", "id", 42, 3.14));
	/*Long assert and double range check*/
	ASSERT_PASS(callback_assert("callback_b", "lRd", 9000, 41.5, 42.4));
	return PASS;
}

int main(int argc, char ** argv) {
	int res = demo_test();
	if (res != PASS) {
		printf("Test failed!\r\n");
		return -1;
	}
	return 0;
}
