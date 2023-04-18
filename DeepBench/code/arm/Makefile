all: sparse gemm conv

BIN_DIR?=bin
EIGEN_PATH?=/usr/include/eigen3
MKDIR=mkdir -p
ARM_COMPUTE_INCLUDE_PATH?=./ARMComputeLib
ARM_COMPUTE_LIB_PATH?=./ARMComputeLib/
ARM_COMPUTE_LIB=$(ARM_COMPUTE_LIB_PATH)lib/arm64-v8a-neon
KERNELS_DIR=../kernels/

gemm: gemm_bench.cc
	$(MKDIR) $(BIN_DIR)
	g++ -O3 --std=c++11 -I $(KERNELS_DIR) -pthread -o bin/gemm_bench $<

sparse: sparse_bench.cpp
	$(MKDIR) $(BIN_DIR)
	g++ -O3 -std=c++11 -o bin/sparse_bench $< \
		-I $(EIGEN_PATH) -I $(KERNELS_DIR)

conv: convolution.cpp
	$(MKDIR) $(BIN_DIR)
	g++ -O3 -I$(ARM_COMPUTE_INCLUDE_PATH) -I $(ARM_COMPUTE_INCLUDE_PATH)/include -I $(KERNELS_DIR) -std=c++17 -L /home/odroid/Desktop/SHREC_DL_Embedded_Benchmarks/DeepBench/code/arm/ARMComputeLib/lib/arm64-v8a-neon-cl/libarm_compute_core-static.a $< -o bin/conv_bench

clean:
	rm -rf $(BIN_DIR)
