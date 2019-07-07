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
ASSERT_PASS(asssert_call_queue_size(0));\
ASSERT_PASS(callback_called("A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_called("B", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_called("type_test_"#T, "idl"FORMAT,100,3.14,9999999, VAL));\
ASSERT_PASS(callback_called("C", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_assert("A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_assert("B", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_assert("type_test_"#T, "iRdRl"FORMAT,100,3.13,3.15,9999998,9999999, VAL));\
ASSERT_PASS(callback_assert("C", "id", INT_MIN,DBL_MIN));\
	;\
ASSERT_PASS(callback_called("012345A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_called("0123456B", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_called("type_test_"#T, "idl"FORMAT,424,3.14,9999999, VAL));\
ASSERT_PASS(callback_called("01234C", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_assert("012345A", "id", INT_MAX,DBL_MAX));\
ASSERT_PASS(callback_assert("0123456B", "id", INT_MIN,DBL_MIN));\
ASSERT_ERROR(callback_assert("type_test_"#T, "iRdRl"FORMAT,424,3.13,3.15,9999998,9999999, VAL-1));\
ASSERT_PASS(callback_assert("01234C", "id", INT_MIN,DBL_MIN));\
ASSERT_PASS(callback_called("type_test_"#T, "idl"FORMAT,425,3.14,9999999, VAL));\
ASSERT_ERROR(callback_assert("type_test_"#T, "iRdRl"FORMAT,425,3.13,3.15,9999998,9999999, VAL-1));\
ASSERT_PASS(callback_called("1xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("1xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("12xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("12xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("123xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("123xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("1234xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("1234xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("12345xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("12345xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("123456xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("123456xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("1234567xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("1234567xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("12345678xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("12345678ype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("123456789xype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("123456789xype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("12aaaaaaaaxype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(callback_assert("12aaaaaaaaxype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(callback_called("12bbbbbbbbbxype_test_"#T, "idl"FORMAT"iiidl",101,3.14,9999999, VAL,312,1,2,3,1.1,LONG_MAX));\
ASSERT_PASS(asssert_call_queue_size(1));\
ASSERT_PASS(callback_assert("12bbbbbbbbbxype_test_"#T, "RiRdRl"FORMAT"iiiRdl",100,105,3.13,3.15,9999998,9999999, VAL,312,1,2,3,1.0,1.2,LONG_MAX));\
ASSERT_PASS(asssert_call_queue_size(0));\

int test_types(void) {
	for (int i = 0; i < 100; i++) {
		TEST_CALL_TYPE(int, "i", 4123);TEST_CALL_TYPE(long, "l", 12324123);TEST_CALL_TYPE(
				double, "d", 1337.0);
	}
	return PASS;
}

int main(int argc, char ** argv) {
	FILE * meh = fopen("test_logs.txt", "w");
	set_log_sink(meh);
	int res = test_types();
	if (res != PASS) {
		printf("TEST FAILED!\r\n");
	} else {
		printf("TEST PASSED!\r\n");
	}
	return 0;
}
