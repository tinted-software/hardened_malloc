cmake_minimum_required(VERSION 3.29)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

project(hardened_malloc C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(H_MALLOC_SEAL_METADATA OFF CACHE BOOL "")
set(H_MALLOC_ZERO_ON_FREE ON CACHE BOOL "")
set(H_MALLOC_WRITE_AFTER_FREE_CHECK ON CACHE BOOL "")
set(H_MALLOC_SLOT_RANDOMIZE ON CACHE BOOL "")
set(H_MALLOC_SLAB_CANARY ON CACHE BOOL "")
set(H_MALLOC_SLAB_QUARANTINE_RANDOM_LENGTH 1 CACHE STRING "")
set(H_MALLOC_SLAB_QUARANTINE_QUEUE_LENGTH 1 CACHE STRING "")
set(H_MALLOC_EXTENDED_SIZE_CLASSES ON CACHE BOOL "")
set(H_MALLOC_LARGE_SIZE_CLASSES ON CACHE BOOL "")
set(H_MALLOC_GUARD_SLABS_INTERVAL 1 ON CACHE STRING "")
set(H_MALLOC_GUARD_SIZE_DIVISOR 2 ON CACHE STRING "")
set(H_MALLOC_REGION_QUARANTINE_RANDOM_LENGTH 256 ON CACHE STRING "")
set(H_MALLOC_REGION_QUARANTINE_QUEUE_LENGTH 1024 ON CACHE STRING "")
set(H_MALLOC_REGION_QUARANTINE_SKIP_THRESHOLD 33554432 CACHE STRING "")
set(H_MALLOC_FREE_SLABS_QUARANTINE_RANDOM_LENGTH 32 CACHE STRING "")
set(H_MALLOC_CLASS_REGION_SIZE 34359738368 CACHE STRING "")
set(H_MALLOC_N_ARENA 4 CACHE STRING "")
set(H_MALLOC_STATS OFF CACHE BOOL "")
set(H_MALLOC_SELF_INIT ON CACHE BOOL "")

add_library(
	hardened_malloc
	./chacha.c
	./h_malloc.c
	./memory.c
	./pages.c
	./random.c
	./util.c
)
target_include_directories(
	hardened_malloc
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)
target_compile_definitions(
	hardened_malloc
	PRIVATE
	H_MALLOC_SEAL_METADATA=${H_MALLOC_SEAL_METADATA}
	H_MALLOC_ZERO_ON_FREE=${H_MALLOC_ZERO_ON_FREE}
	H_MALLOC_WRITE_AFTER_FREE_CHECK=${H_MALLOC_WRITE_AFTER_FREE_CHECK}
	H_MALLOC_SLOT_RANDOMIZE=${H_MALLOC_SLOT_RANDOMIZE}
	H_MALLOC_SLAB_CANARY=${H_MALLOC_SLAB_CANARY}
	H_MALLOC_SLAB_QUARANTINE_RANDOM_LENGTH=${H_MALLOC_SLAB_QUARANTINE_RANDOM_LENGTH}
	H_MALLOC_SLAB_QUARANTINE_QUEUE_LENGTH=${H_MALLOC_SLAB_QUARANTINE_QUEUE_LENGTH}
	H_MALLOC_EXTENDED_SIZE_CLASSES=${H_MALLOC_EXTENDED_SIZE_CLASSES}
	H_MALLOC_LARGE_SIZE_CLASSES=${H_MALLOC_LARGE_SIZE_CLASSES}
	H_MALLOC_GUARD_SLABS_INTERVAL=${H_MALLOC_GUARD_SLABS_INTERVAL}
	H_MALLOC_GUARD_SIZE_DIVISOR=${H_MALLOC_GUARD_SIZE_DIVISOR}
	H_MALLOC_REGION_QUARANTINE_RANDOM_LENGTH=${H_MALLOC_REGION_QUARANTINE_RANDOM_LENGTH}
	H_MALLOC_REGION_QUARANTINE_QUEUE_LENGTH=${H_MALLOC_REGION_QUARANTINE_QUEUE_LENGTH}
	H_MALLOC_REGION_QUARANTINE_SKIP_THRESHOLD=${H_MALLOC_REGION_QUARANTINE_SKIP_THRESHOLD}
	H_MALLOC_FREE_SLABS_QUARANTINE_RANDOM_LENGTH=${H_MALLOC_REGION_QUARANTINE_RANDOM_LENGTH}
	H_MALLOC_CLASS_REGION_SIZE=${H_MALLOC_CLASS_REGION_SIZE}
	H_MALLOC_N_ARENA=${H_MALLOC_N_ARENA}
	H_MALLOC_STATS=${H_MALLOC_STATS}
	H_MALLOC_SELF_INIT=${H_MALLOC_SELF_INIT}
	_DEFAULT_SOURCE
)

install(TARGETS hardened_malloc)

set(CPACK_SOURCE_GENERATOR "TZST")
set(CPACK_SOURCE_IGNORE_FILES
	\\.git/
	build/
	out/
	.cache/
	".*~$"
)
set(CPACK_THREADS 0)
set(CPACK_VERBATIM_VARIABLES YES)
include(CPack)
