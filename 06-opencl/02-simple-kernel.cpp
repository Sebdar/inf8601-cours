#define CL_TARGET_OPENCL_VERSION 200

#include <CL/cl.h>
#include <iostream>
#include "utils.h"

int main() {
    ClErrorChecker check_err;
    cl_platform_id platform;
    
    check_err = clGetPlatformIDs(1, &platform, NULL);
    check_err();
    printf("Platform obtained\n");
    
    cl_device_id device;
    check_err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    check_err();
    printf("Device obtained\n");

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, check_err.get());
    check_err();
    printf("Context created\n");

    // Create buffer

    size_t buf_size = sizeof(cl_int);
    cl_mem buf_io = clCreateBuffer(context, CL_MEM_READ_WRITE, buf_size, NULL, check_err.get());
    check_err();
    printf("Buffer created\n");


    // Prepare kernel
    std::string kernel_code = load_file("02-simple-kernel.cl");
    const char* code = kernel_code.c_str();
    size_t size = kernel_code.size();
    cl_program prog = clCreateProgramWithSource(context, 1, &code, &size, check_err.get());
    check_err();
    printf("Program created\n");

    check_err = clBuildProgram(prog, 1, &device, NULL, NULL, NULL);
    opencl_print_build_log(prog, device);
    check_err();


    printf("Program built\n");

    cl_kernel kernel = clCreateKernel(prog, "simple_kernel", check_err.get());
    check_err();

    // Prepare queue
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, NULL, check_err.get());
    check_err();

    check_err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &buf_io);
    check_err();

    size_t wg_size = 1;
    size_t wg_num = 1;
    check_err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &wg_num, &wg_size, 0, NULL, NULL);
    check_err();
    printf("Kernel launched!");

    cl_int result;
    check_err = clEnqueueReadBuffer(queue, buf_io, CL_TRUE, 0, sizeof(cl_int), &result, 0, NULL, NULL);
    check_err();

    std::cout << "Result is " << result << '\n';

    check_err = clReleaseProgram(prog);
    check_err();
    check_err = clReleaseMemObject(buf_io);
    check_err();

    check_err = clReleaseContext(context);
    check_err();
    printf("Context destroyed\n");

    clReleaseDevice(device);
    check_err();
    printf("Device deleted, exiting ..");
    return 0;
}
