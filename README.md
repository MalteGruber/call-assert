
# Call Assert Library
This library is intended to be used with other unit testing libraries. It servers as a helper to verify that callbacks or wrapped functions have been called in the correct order and with the correct arguments. This library also supports range checking of arguments.

## Example
Here is a quick demonstration of how this library is used.
```C
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
```

## API

Function called by callback to register the function call and its arguments.
-- `name`: *function name, must match that provided to `callback_assert`*
-- `arg_str`:  *Type format string, must describe type of arguments passed after `arg_str`*
```C
int callback_called(const char *name, const char *arg_str, ...);
```
Verify that the function `name` was called with the specified arguments.
-- `name`: *function name, must match that provided to `callback_called`*
-- `arg_str`: *Type format string, must describe type of arguments passed after `arg_str`*
```C
int callback_assert(const char *name, const char *arg_str, ...);
```
Verify the size of the call queue.
-- `size`:  *Number of calls expected in the call queue*
```C
int asssert_call_queue_size(int size);```
```

### Supported Types
The following types can be passed to arg_gen's arg_types format string:
- d: double
- i: int
- c: char
