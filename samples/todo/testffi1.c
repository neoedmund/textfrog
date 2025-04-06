#include <ffi.h>
#include <stdio.h>

unsigned char
foo(unsigned int, float);

// The target function.
unsigned char
foo(unsigned int x, float y)
{
    unsigned char result = x - y;
    return result;
}

int
main(int argc, const char **argv)
{
    ffi_cif cif;
    ffi_type *arg_types[2];
    void *arg_values[2];
    ffi_status status;

    // Because the return value from foo() is smaller than sizeof(long), it
    // must be passed as ffi_arg or ffi_sarg.
    ffi_arg result;

    // Specify the data type of each argument. Available types are defined
    // in <ffi/ffi.h>.
    arg_types[0] = &ffi_type_uint;
    arg_types[1] = &ffi_type_float;

    // Prepare the ffi_cif structure.
    if ((status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI,
        2, &ffi_type_uint8, arg_types)) != FFI_OK)
    {
        // Handle the ffi_status error.
    }

    // Specify the values of each argument.
    unsigned int arg1 = 42;
    float arg2 = 5.1;

    arg_values[0] = &arg1;
    arg_values[1] = &arg2;

    // Invoke the function.
    ffi_call(&cif, FFI_FN(foo), &result, arg_values);

    // The ffi_arg 'result' now contains the unsigned char returned from foo(),
    // which can be accessed by a typecast.
    printf("result is %hhu\nFFI_DEFAULT_ABI=%d\n", (unsigned char)result,// 
    FFI_DEFAULT_ABI);// seem FFI_UNIX64==2

    return 0;
}




