// adt_memory_node.c
// Escuela Superior de Arte y Tecnologia
// Algoritmos & Inteligencia Artificial
// ESAT 2020-2021
//

#include <stdio.h>
#include <stdlib.h>

#include "common_def.h"
#include "adt_memory_node.h"

#include "EDK_MemoryManager/edk_memory_manager.h"

// Memory Node Declarations
static s16 MEMNODE_initWithoutCheck(MemoryNode *node); // inits a MN with no checks
static void *MEMNODE_data(MemoryNode *node);           // returns a reference to data_
static u16 MEMNODE_size(MemoryNode *node);             // returns data size

// Memory Node's API Definitions
struct memory_node_ops_s memory_node_ops = {
    .data = MEMNODE_data,
    .size = MEMNODE_size,
};

// Memory Node Definitions
MemoryNode *MEMNODE_create()
{
  MemoryNode *node = MM->malloc(sizeof(MemoryNode));
  if (NULL == node)
  {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return NULL;
  }
  MEMNODE_initWithoutCheck(node);
  return node;
}

s16 MEMNODE_createFromRef(MemoryNode **node)
{
  *node = MEMNODE_create();
  if (NULL == *node)
  {
#ifdef VERBOSE_
    printf("Error: [%s] not enough memory available\n", __FUNCTION__);
#endif
    return kErrorCode_Memory;
  }
  return kErrorCode_Ok;
}

s16 MEMNODE_initWithoutCheck(MemoryNode *node)
{
  node->data_ = NULL;
  node->size_ = 0;
  node->ops_ = &memory_node_ops;
  return kErrorCode_Ok;
}

void *MEMNODE_data(MemoryNode *node)
{ // returns a reference to data_
  return node->data_;
}

u16 MEMNODE_size(MemoryNode *node)
{ // returns data size
  return node->size_;
}

s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes)
{
  if (NULL == node)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] node not found", __FUNCTION__);
    // #endif
  }
  else
  {
    node->data_ = src;
    node->size_ = bytes;
  }
}

s16 MEMNODE_reset(MemoryNode *node)
{
  if (NULL == node)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] node not found", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  if (NULL == node->data_)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] pointer data_ is NULL", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  free(node->data_);
  node->data_ = NULL;
  node->size_ = 0;
  return kErrorCode_Ok;
}

s16 MEMNODE_softReset(MemoryNode *node)
{
  if (NULL == node)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] node not found", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  if (NULL == node->data_)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] pointer data_ is NULL", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  node->data_ = NULL;
  node->size_ = 0;
  return kErrorCode_Ok;
}

s16 MEMNODE_free(MemoryNode *node)
{
  if (NULL == node)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] node not found", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  if (NULL == node->data_)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] pointer data_ is NULL", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  free(node->data_);
  free(node);
  return kErrorCode_Ok;
}

s16 MEMNODE_softFree(MemoryNode *node)
{
  if (NULL == node)
  {
    // #ifdef VERBOSE_
    // printf("Error: [%s] node not found", __FUNCTION__);
    // #endif
    return kErrorCode_Null;
  }
  free(node);
}

s16 MEMNODE_memSet(MemoryNode *node, u8 value)
{
  if (NULL == node)
  {
    return kErrorCode_Null;
  }
  if (NULL == node->data_)
  {
    return kErrorCode_Null;
  }
  u8* aux = (u8*)node->data_;
  for(int i = 0; i < node->size_; i++)
  {
    aux[i] = value;
  }
  free(aux);
  // memset(node->data_, value, node->size_);
}

s16 MEMNODE_memCopy(MemoryNode *node, void *src, u16 bytes)
{
  if (NULL == node)
  {
    return kErrorCode_Null;
  }
  if (NULL == node->data_)
  {
    return kErrorCode_Null;
  }

   
  return kErrorCode_Ok;
}

s16 MEMNODE_memConcat(MemoryNode *node, void *src, u16 bytes)
{
  if (NULL == node)
  {
    return kErrorCode_Null;
  }
  if (NULL == node->data_)
  {
    return kErrorCode_Null;
  }

  u16 total_size = node->size_ + bytes;

  void *aux_pointer = MM->malloc(total_size);
int i = 0;
  for(int i = 0; i < node->size_; i++<){
    aux_pointer[i] = node->data_[i];
  }
  for(i; i < total_size; i++){
    aux_pointer[i] = src[i-node->size_];
  }

  free(node->data_);
  node->data_ = aux_pointer;
  node->size_ = bytes;
}

s16 MEMNODE_memMask(MemoryNode *node, u8 mask)
{
}