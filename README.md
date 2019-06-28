# Call Assert Library
This library is intended to be used with other unit testing libraries. It servers as a helper to verify that callbacks or wrapped functions have been called in the correct order and with the correct arguments.

## Example
Here is a quick demonstration of how this library is used.
```C
void callback_a(int x,double y,char z){
  register(arg_gen("callback_a","idc",x,y,z));
}

void callback_b(int a){
  register(arg_gen("callback_b","i",a));
}

int unit_test_runnuer(){
  ...
  /*Verify that the callbacks were called with the correct order and argumetns*/
  assert(arg_gen("callback_a","idc",3,3.14,'x'))
  assert(arg_gen("callback_b","i",42));
  ...
}
```

## API

Allocate and populate an argument array
```C
void * arg_gen(const char * name,const char * arg_types,...)
```

### Supported Types
The following types can be passed to arg_gen's arg_types format string:
- d: double
- i: int
- c: char
