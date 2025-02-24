#ifndef MEMTAG_H
#define MEMTAG_H

#include "util.h"

#ifdef HAS_ARM_MTE
#include "arm_mte.h"
#define MEMTAG 1
// Note that bionic libc always reserves tag 0 via PR_MTE_TAG_MASK prctl
#define RESERVED_TAG 0
#define TAG_WIDTH 4
#endif

static inline void *untag_pointer(void *ptr) {
#ifdef HAS_ARM_MTE
  const uintptr_t mask = UINTPTR_MAX >> 8;
  return (void *)((uintptr_t)ptr & mask);
#else
  return ptr;
#endif
}

static inline const void *untag_const_pointer(const void *ptr) {
#ifdef HAS_ARM_MTE
  const uintptr_t mask = UINTPTR_MAX >> 8;
  return (const void *)((uintptr_t)ptr & mask);
#else
  return ptr;
#endif
}

static inline void *set_pointer_tag(void *ptr, u8 tag) {
#ifdef HAS_ARM_MTE
  return (void *)(((uintptr_t)tag << 56) | (uintptr_t)untag_pointer(ptr));
#else
  (void)tag;
  return ptr;
#endif
}

static inline u8 get_pointer_tag(void *ptr) {
#ifdef HAS_ARM_MTE
  return (((uintptr_t)ptr) >> 56) & 0xf;
#else
  (void)ptr;
  return 0;
#endif
}

#endif
