all: memoryTestReadMallocSharedMemory memoryTestReadMallocIntimateSharedMemory 

memoryTestReadMallocSharedMemory:  memoryTestReadMallocSharedMemory.c
	gcc -Wimplicit-function-declaration  memoryTestReadMallocSharedMemory.c -o  memoryTestReadMallocSharedMemory
	chmod uog+rx memoryTestReadMallocSharedMemory

memoryTestReadMallocIntimateSharedMemory:  memoryTestReadMallocIntimateSharedMemory.c
	gcc -Wimplicit-function-declaration  memoryTestReadMallocIntimateSharedMemory.c -o  memoryTestReadMallocIntimateSharedMemory
	chmod uog+rx memoryTestReadMallocIntimateSharedMemory
