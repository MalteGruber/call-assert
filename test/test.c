/* Malte Gruber 2019 */

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <callback_tester.h>

#include <limits.h>
#include <float.h>
#define ASSERT_ERROR(V) if(V!=ERROR) return ERROR;
#define ASSERT_PASS(V) if(V!=PASS) return ERROR;

#define TEST_CALL_TYPE(T,FORMAT,VAL); \
ASSERT_PASS(callback_called("A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_called("B", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_called("type_test_"#T, "idl"FORMAT,42,3.14,9999999, VAL));\
ASSERT_PASS(callback_called("C", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_assert("A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_assert("B", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_assert("type_test_"#T, "iRdRl"FORMAT,42,3.13,3.15,9999998,9999999, VAL));\
ASSERT_PASS(callback_assert("C", "id", INT_MIN,DBL_MIN));\
	;\
ASSERT_PASS(callback_called("A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_called("B", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_called("type_test_"#T, "idl"FORMAT,42,3.14,9999999, VAL));\
ASSERT_PASS(callback_called("C", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_assert("A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_assert("B", "id", INT_MIN,DBL_MIN));\
ASSERT_ERROR(callback_assert("type_test_"#T, "iRdRl"FORMAT,42,3.13,3.15,9999998,9999999, VAL-1));\
ASSERT_PASS(callback_assert("C", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_called("type_test_"#T, "idl"FORMAT,42,3.14,9999999, VAL));\
ASSERT_ERROR(callback_assert("type_test_"#T, "iRdRl"FORMAT,42,3.13,3.15,9999998,9999999, VAL-1));\



int test_types(void) {

	TEST_CALL_TYPE(int,"i",4123);
	TEST_CALL_TYPE(long,"l",12324123);
	TEST_CALL_TYPE(double,"d",100.000);
	ASSERT_PASS(asssert_call_queue_size(0));
	return PASS;
}



int main(int argc, char ** argv) {
	printf("Example file\n");

	int res = test_types();
	if (res != PASS) {
		printf("TEST FAILED!\r\n");
	} else {
		printf("TEST PASSED!\r\n");
	}
	return 0;
}
