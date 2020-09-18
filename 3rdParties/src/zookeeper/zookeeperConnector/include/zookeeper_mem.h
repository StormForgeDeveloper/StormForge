////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StormForge
// 
// Author : KyungKun Ko
//
// Description : zookeeper memory implementation
//
////////////////////////////////////////////////////////////////////////////////


#ifndef ZOOKEEPER_MEM_H_
#define ZOOKEEPER_MEM_H_

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*zoo_mem_malloc_t)(size_t size);
typedef void* (*zoo_mem_calloc_t)(size_t count, size_t size);
typedef void (*zoo_mem_free_t)(void* pPtr);


typedef struct zoo_mem_handler {
	
    zoo_mem_malloc_t malloc_func;
	zoo_mem_malloc_t calloc_func;
    zoo_mem_free_t free_func;

} zoo_mem_handler_t;


#ifdef __cplusplus
}
#endif

#endif /*ZOOKEEPER_MEM_H_*/
