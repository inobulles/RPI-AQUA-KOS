
#ifndef __AQUA__LIB_CUDA_ROOT_H
	#define __AQUA__LIB_CUDA_ROOT_H
	
	// kernel stuff
	
	#define cuda_kernel    __global__
	#define thread         threadIdx.x
	#define block_dimension blockDim.x
	#define block           blockIdx.x
	
	// memory
	
	#define cuda_malloc cudaMallocManaged
	#define cuda_free   cudaFree
	
	// compiler macros
	
	typedef uvar*       cuda_bytecode_t;
	typedef const char* cuda_code_t;
	
	#define CUDA_PROGRAM(__CUDA_INCLUDE_code) #__CUDA_INCLUDE_code
	
	#define CUDA_COMPILE(__CUDA_COMPILE_code, __CUDA_COMPILE_bytecode) __CUDA_COMPILE_bytecode = nullptr; \
	{ \
		device __nvcc_device = is_device_supported("nvcc"); \
		if (!__nvcc_device) print("WARNING Your KOS does not support NVCC. You can thus not compile your CUDA code\n"); \
		else __CUDA_COMPILE_bytecode = get_device(__nvcc_device, __CUDA_COMPILE_code); \
	}
	
	#define CUDA_FREE { \
		device __nvcc_device = is_device_supported("nvcc"); \
		if (!__nvcc_device) print("WARNING Your KOS does not support NVCC. You can thus not compile your CUDA code\n"); \
		else get_device(__nvcc_device, "__FREE__"); \
	}
	
	#define CUDA_EXECUTE(__CUDA_EXCECUTE_bytecode, __CUDA_EXCECUTE_result) __CUDA_EXCECUTE_result = 1; \
	{ \
		device __cuda_device = is_device_supported("cuda"); \
		if (!__cuda_device) print("WARNING Your KOS does not support CUDA bytecode execution\n"); \
		else __CUDA_EXCECUTE_result = *get_device(__cuda_device, (const char*) __CUDA_EXCECUTE_bytecode); \
	}
	
#endif
