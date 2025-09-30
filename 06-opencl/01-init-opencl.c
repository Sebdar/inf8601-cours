#define CL_TARGET_OPENCL_VERSION 200

#include <CL/cl.h>
#include <stdio.h>

int main() {
    cl_int result;
    cl_platform_id platform;
    
    result = clGetPlatformIDs(1, &platform, NULL);
    if(result != CL_SUCCESS) {
        return -1;
    }
    printf("Platform obtained\n");
    
    cl_device_id device;
    result = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    if(result != CL_SUCCESS) {
        return -1;
    }
    printf("Device obtained\n");

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &result);
    if(result != CL_SUCCESS) {
        return -1;
    }
    printf("Context created\n");


    size_t buf_size = 4096u;
    cl_mem buf_input = clCreateBuffer(context, CL_MEM_READ_ONLY, buf_size, NULL, &result);
    if(result != CL_SUCCESS) {
        return -1;
    }

    cl_mem buf_output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, buf_size, NULL, &result);
    if(result != CL_SUCCESS) {
        return -1;
    }


    // Do your computations here ..



    result = clReleaseMemObject(buf_input);
    if(result != CL_SUCCESS) {
        return -1;
    }

    result = clReleaseMemObject(buf_output);
    if(result != CL_SUCCESS) {
        return -1;
    }

    result = clReleaseContext(context);
    if(result != CL_SUCCESS) {
        return -1;
    }
    printf("Context destroyed\n");

    clReleaseDevice(device);
    if(result != CL_SUCCESS) {
        return -1;
    }
    printf("Device deleted, exiting ..");
    return 0;
}
