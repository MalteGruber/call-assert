//Copyright (c) 2019 Malte Gruber
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#include <callback_tester.h>

typedef uint8_t byte;
#define MAX_ARG_SIZE 8 //Bytes
enum {
	VALUE_CHECK, RANGE_CHECK
};

typedef int (*serializer_t)(byte*, byte**, int);
FILE * printer;
typedef struct {
	byte *data;
	struct queue_member_t * next;
} queue_member_t;

queue_member_t *queue_base = NULL;

static void log_error(const char *format, ...) {
	bool initialized = false;
	if (!initialized) {
		initialized = true;
		printer = stderr;
	}
	va_list vargs;
	va_start(vargs, format);
	vfprintf(printer, format, vargs);
	va_end(vargs);
}

static void enqueue(byte *data) {
	queue_member_t * new_member = malloc(sizeof(queue_member_t));
	new_member->data = data;
	new_member->next = NULL;
	if (queue_base != NULL) {
		queue_member_t * tmp = queue_base;
		while (tmp->next != NULL) {
			tmp = (queue_member_t*) tmp->next;
		}
		tmp->next = (struct queue_member_t*) new_member;
	} else {
		queue_base = new_member;
	}
}

static int queue_size() {
	int size = 0;
	queue_member_t * tmp = queue_base;
	if (queue_base != NULL) {
		size++;
		while (tmp->next != NULL) {
			size += 1;
			tmp = (queue_member_t*) tmp->next;
		}
	}
	return size;
}

static void dequeue(byte **data) {

	if (queue_base->next != NULL) {
		queue_member_t *new_oldest = (queue_member_t*) queue_base->next;
		*data = queue_base->data;
		free(queue_base);
		queue_base = new_oldest;
	} else {
		*data = queue_base->data;
		free(queue_base);
		queue_base = NULL;
	}

}

static int serializer_generic(byte * data, byte ** target, int size) {
	memcpy(*target, data, size);
	*target += size;
	return size;
}

#define CALL_CHECK(t,name,serializer) \
if(name==c){\
	t tmp=va_arg(args,t);\
	serializer((byte*)&tmp,&wptr,sizeof(t));\
	handled=true;\
}

#define LIB_TYPE_DECLARATIONS \
CALL_CHECK(double,'d',serializer_generic)\
CALL_CHECK(int,'i',serializer_generic)\
CALL_CHECK(long,'l',serializer_generic)\

static void align_ptr(byte ** ptr) {
	uintptr_t addr = (uintptr_t) *ptr;
	if (addr % 8 != 0) {
		addr += 8 - addr % 8;
	}
	*ptr = (byte*) addr;
}

void set_log_sink(FILE * dst) {
	printer = dst;
}

int callback_called(const char *name, const char *arg_str, ...) {

	char * arg_type_char = (char*) arg_str;
	va_list args;

	/*Allocate space for the packet, assume that every argument is of max length*/
	int argc = strlen(arg_str);
	int name_len = strlen(name);
	byte *data = malloc((argc + 1) * MAX_ARG_SIZE + name_len);
	byte *wptr = data;

	/*Save the name*/
	strcpy((char*) wptr, name);
	wptr += strlen(name);

	va_start(args, arg_str);

	do {
		char c = *arg_type_char;
		bool handled = false;

		align_ptr(&wptr);

		LIB_TYPE_DECLARATIONS

		if (!handled)
			log_error("'%c' - is not a valid type!\n", *(arg_type_char));

	} while (*(++arg_type_char) != '\0');
	va_end(args);
	enqueue(data);
	return PASS;
}

#define TESTER(T,TARGET_CHAR,FORMAT) \
if(c==TARGET_CHAR){ \
	T * x=(T*)rptr_real;\
	T a=va_arg(args,T);\
	if(state==RANGE_CHECK){\
		T b=va_arg(args,T);\
		if((*x<a) || (*x>b)){\
			log_error("ERROR: argument %d (type "#T") of %s with value "#FORMAT" not in range ["#FORMAT","#FORMAT"]\n", arg_counter,caller_name,*x,a,b);\
			free(base);va_end(args);\
			return ERROR;\
		}\
	}else{\
		if(a!=*x){log_error("ERROR: argument %d (type "#T") of %s with value "#FORMAT" not equal to "#FORMAT"\n",arg_counter,caller_name,*x,a);\
		free(base);va_end(args);return ERROR;}\
	}\
	rptr_real+=sizeof(int);\
	handled=true;\
}\

int callback_assert(const char *name, const char *arg_str, ...) {

	char * arg_type_char = (char*) arg_str;
	va_list args;

	/*Allocate space for the packet*/

	byte * rptr_real = NULL;
	dequeue(&rptr_real);
	byte *base = rptr_real;
	char * caller_name = (char*) rptr_real;
	rptr_real += strlen(caller_name);

	align_ptr(&rptr_real);

	va_start(args, arg_str);
	int state = VALUE_CHECK;
	int arg_counter = 0;
	do {
		char c = *arg_type_char;
		bool keyword = false;
		bool handled = false;

		if (c == 'R') {
			state = RANGE_CHECK;
			handled = true;
			keyword = true;
		}

		align_ptr(&rptr_real);

		TESTER(int, 'i', %d);
		TESTER(double, 'd', %f);
		TESTER(long, 'l', %ld);

		align_ptr(&rptr_real);

		if (!keyword && state != VALUE_CHECK) {
			state = VALUE_CHECK;
		}

		if (!keyword) {
			arg_counter++;
		}

		if (!handled)
			log_error("'%c' - is not a valid type!\n", *(arg_type_char));

	} while (*(++arg_type_char) != '\0');
	va_end(args);

	return PASS;
}

int asssert_call_queue_size(int size) {
	int actual_size = queue_size();
	if (size != actual_size) {
		log_error("Expected %d calls in call queue, found %d", size,
				actual_size);
		return ERROR;
	}
	return PASS;
}
