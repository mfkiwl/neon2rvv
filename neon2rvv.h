/*
 * This header file provides a simple API translation layer
 * between Arm/Aarch64 NEON to their corresponding RVV intrinsics versions.
 *
 * neon2rvv is freely redistributable under the MIT License.
 *
 * MIT License
 *
 * Copyright (c) 2023 Yang Hau <yuanyanghau@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NEON2RVV_H
#define NEON2RVV_H

#ifdef __cplusplus
extern "C" {
#endif

// TODO uncomment this and put all the implementation into `#elif defined(__riscv) || defined(__riscv__)`
// In this way the developers only need to include `neon2rvv.h`
// #if (defined(__aarch64__) || defined(_M_ARM64)) || defined(__arm__)
// #include <arm_neon.h>
// #elif (defined(__riscv) || defined(__riscv__))
#include <riscv_vector.h>

#include <stdint.h>
#include <stdlib.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma push_macro("FORCE_INLINE")
#pragma push_macro("ALIGN_STRUCT")
#define FORCE_INLINE static inline __attribute__((always_inline))
#define ALIGN_STRUCT(x) __attribute__((aligned(x)))
#define _neon2rvv_likely(x) __builtin_expect(!!(x), 1)
#define _neon2rvv_unlikely(x) __builtin_expect(!!(x), 0)
#endif

typedef float float32_t;

#if __riscv_v_min_vlen == 128
// 64bit width vector register
typedef vint8m1_t int8x8_t;
typedef vint16m1_t int16x4_t;
typedef vint32m1_t int32x2_t;
typedef vint64m1_t int64x1_t;
typedef vuint8m1_t uint8x8_t;
typedef vuint16m1_t uint16x4_t;
typedef vuint32m1_t uint32x2_t;
typedef vuint64m1_t uint64x1_t;
typedef vfloat32m1_t float32x2_t;
typedef vfloat64m1_t float64x1_t;
// 128bit width vector register
typedef vint8m1_t int8x16_t;
typedef vint16m1_t int16x8_t;
typedef vint32m1_t int32x4_t;
typedef vint64m1_t int64x2_t;
typedef vuint8m1_t uint8x16_t;
typedef vuint16m1_t uint16x8_t;
typedef vuint32m1_t uint32x4_t;
typedef vuint64m1_t uint64x2_t;
typedef vfloat32m1_t float32x4_t;
typedef vfloat64m1_t float64x2_t;

// FIXME wrong typedefs, just for passing compilation
typedef vint8m1x2_t int8x8x2_t;
typedef vuint8m1x2_t uint8x8x2_t;
typedef vint8m2_t int8x16x2_t;
typedef vuint8m2_t uint8x16x2_t;
typedef vint8m4_t int8x16x3_t;
typedef vuint8m4_t uint8x16x3_t;
typedef vint8m4_t int8x16x4_t;
typedef vuint8m4_t uint8x16x4_t;
typedef vint8m4_t int8x8x3_t;
typedef vuint8m4_t uint8x8x3_t;
typedef vint8m4_t int8x8x4_t;
typedef vuint8m4_t uint8x8x4_t;
typedef vint16m2_t int16x4x2_t;
typedef vuint16m2_t uint16x4x2_t;
typedef vint16m4_t int16x4x3_t;
typedef vuint16m4_t uint16x4x3_t;
typedef vint16m4_t int16x4x4_t;
typedef vuint16m4_t uint16x4x4_t;
typedef vint16m2_t int16x8x2_t;
typedef vuint16m2_t uint16x8x2_t;
typedef vint16m4_t int16x8x3_t;
typedef vuint16m4_t uint16x8x3_t;
typedef vint16m4_t int16x8x4_t;
typedef vuint16m4_t uint16x8x4_t;
typedef vint32m2_t int32x2x2_t;
typedef vuint32m2_t uint32x2x2_t;
typedef vint32m4_t int32x2x3_t;
typedef vuint32m4_t uint32x2x3_t;
typedef vint32m4_t int32x2x4_t;
typedef vuint32m4_t uint32x2x4_t;
typedef vint32m4_t int32x2x4_t;
typedef vuint32m4_t uint32x2x4_t;
typedef vint32m2_t int32x4x2_t;
typedef vuint32m2_t uint32x4x2_t;
typedef vint32m4_t int32x4x3_t;
typedef vuint32m4_t uint32x4x3_t;
typedef vint32m4_t int32x4x4_t;
typedef vuint32m4_t uint32x4x4_t;
typedef vfloat32m2_t float32x2x2_t;
typedef vfloat32m4_t float32x2x3_t;
typedef vfloat32m4_t float32x2x4_t;
typedef vfloat32m2_t float32x4x2_t;
typedef vfloat32m4_t float32x4x3_t;
typedef vfloat32m4_t float32x4x4_t;
typedef vint64m2_t int64x1x2_t;
typedef vuint64m2_t uint64x1x2_t;
typedef vint64m4_t int64x1x3_t;
typedef vuint64m4_t uint64x1x3_t;
typedef vint64m4_t int64x1x4_t;
typedef vuint64m4_t uint64x1x4_t;
#elif __riscv_v_min_vlen == 256
#elif __riscv_v_min_vlen == 512
#else
// typedef for other VLEN
#endif

#define NEON2RVV_ROUND_TYPE_RNU 0  // round-to-nearest-up (add +0.5 LSB)
#define NEON2RVV_ROUND_TYPE_RNE 1  // round-to-nearest-even
#define NEON2RVV_ROUND_TYPE_RDN 2  // round-down (truncate)
#define NEON2RVV_ROUND_TYPE_ROD 3  // round-to-odd (OR bits into LSB, aka "jam")

// forward declaration
FORCE_INLINE int8x8_t vdup_n_s8(int8_t __a);
FORCE_INLINE int16x4_t vdup_n_s16(int16_t __a);
FORCE_INLINE int32x2_t vdup_n_s32(int32_t __a);
FORCE_INLINE float32x2_t vdup_n_f32(float32_t __a);
FORCE_INLINE uint8x8_t vdup_n_u8(uint8_t __a);
FORCE_INLINE uint16x4_t vdup_n_u16(uint16_t __a);
FORCE_INLINE uint32x2_t vdup_n_u32(uint32_t __a);
FORCE_INLINE int64x1_t vdup_n_s64(int64_t __a);
FORCE_INLINE uint64x1_t vdup_n_u64(uint64_t __a);

FORCE_INLINE int8x8_t vcnt_s8(int8x8_t __a);
FORCE_INLINE uint8x8_t vcnt_u8(uint8x8_t __a);

/* vadd */
FORCE_INLINE int8x8_t vadd_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vadd_vv_i8m1(__a, __b, 8); }

FORCE_INLINE int16x4_t vadd_s16(int16x4_t __a, int16x4_t __b) { return __riscv_vadd_vv_i16m1(__a, __b, 4); }

FORCE_INLINE int32x2_t vadd_s32(int32x2_t __a, int32x2_t __b) { return __riscv_vadd_vv_i32m1(__a, __b, 2); }

FORCE_INLINE float32x2_t vadd_f32(float32x2_t __a, float32x2_t __b) { return __riscv_vfadd_vv_f32m1(__a, __b, 2); }

FORCE_INLINE uint8x8_t vadd_u8(uint8x8_t __a, uint8x8_t __b) { return __riscv_vadd_vv_u8m1(__a, __b, 8); }

FORCE_INLINE uint16x4_t vadd_u16(uint16x4_t __a, uint16x4_t __b) { return __riscv_vadd_vv_u16m1(__a, __b, 4); }

FORCE_INLINE uint32x2_t vadd_u32(uint32x2_t __a, uint32x2_t __b) { return __riscv_vadd_vv_u32m1(__a, __b, 2); }

FORCE_INLINE int64x1_t vadd_s64(int64x1_t __a, int64x1_t __b) { return __riscv_vadd_vv_i64m1(__a, __b, 2); }

FORCE_INLINE uint64x1_t vadd_u64(uint64x1_t __a, uint64x1_t __b) { return __riscv_vadd_vv_u64m1(__a, __b, 2); }

FORCE_INLINE int8x16_t vaddq_s8(int8x16_t __a, int8x16_t __b) { return __riscv_vadd_vv_i8m1(__a, __b, 16); }

FORCE_INLINE int16x8_t vaddq_s16(int16x8_t __a, int16x8_t __b) { return __riscv_vadd_vv_i16m1(__a, __b, 8); }

FORCE_INLINE int32x4_t vaddq_s32(int32x4_t __a, int32x4_t __b) { return __riscv_vadd_vv_i32m1(__a, __b, 4); }

FORCE_INLINE int64x2_t vaddq_s64(int64x2_t __a, int64x2_t __b) { return __riscv_vadd_vv_i64m1(__a, __b, 2); }

FORCE_INLINE float32x4_t vaddq_f32(float32x4_t __a, float32x4_t __b) { return __riscv_vfadd_vv_f32m1(__a, __b, 4); }

FORCE_INLINE uint8x16_t vaddq_u8(uint8x16_t __a, uint8x16_t __b) { return __riscv_vadd_vv_u8m1(__a, __b, 16); }

FORCE_INLINE uint16x8_t vaddq_u16(uint16x8_t __a, uint16x8_t __b) { return __riscv_vadd_vv_u16m1(__a, __b, 8); }

FORCE_INLINE uint32x4_t vaddq_u32(uint32x4_t __a, uint32x4_t __b) { return __riscv_vadd_vv_u32m1(__a, __b, 4); }

FORCE_INLINE uint64x2_t vaddq_u64(uint64x2_t __a, uint64x2_t __b) { return __riscv_vadd_vv_u64m1(__a, __b, 2); }

FORCE_INLINE int16x8_t vaddl_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwadd_vv_i16m2(__a, __b, 8));
}

FORCE_INLINE int32x4_t vaddl_s16(int16x4_t __a, int16x4_t __b) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwadd_vv_i32m2(__a, __b, 4));
}

FORCE_INLINE int64x2_t vaddl_s32(int32x2_t __a, int32x2_t __b) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwadd_vv_i64m2(__a, __b, 2));
}

FORCE_INLINE uint16x8_t vaddl_u8(uint8x8_t __a, uint8x8_t __b) {
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwaddu_vv_u16m2(__a, __b, 8));
}

FORCE_INLINE uint32x4_t vaddl_u16(uint16x4_t __a, uint16x4_t __b) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwaddu_vv_u32m2(__a, __b, 4));
}

FORCE_INLINE uint64x2_t vaddl_u32(uint32x2_t __a, uint32x2_t __b) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwaddu_vv_u64m2(__a, __b, 2));
}

FORCE_INLINE int16x8_t vaddw_s8(int16x8_t __a, int8x8_t __b) {
  vint16m1_t b_ext = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(__b, 8));
  return __riscv_vadd_vv_i16m1(__a, b_ext, 8);
}

// FORCE_INLINE int32x4_t vaddw_s16(int32x4_t __a, int16x4_t __b);

// FORCE_INLINE int64x2_t vaddw_s32(int64x2_t __a, int32x2_t __b);

// FORCE_INLINE uint16x8_t vaddw_u8(uint16x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint32x4_t vaddw_u16(uint32x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint64x2_t vaddw_u32(uint64x2_t __a, uint32x2_t __b);

FORCE_INLINE int8x8_t vhadd_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vaadd_vv_i8m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 8);
}

FORCE_INLINE int16x4_t vhadd_s16(int16x4_t __a, int16x4_t __b) {
  return __riscv_vaadd_vv_i16m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 4);
}

FORCE_INLINE int32x2_t vhadd_s32(int32x2_t __a, int32x2_t __b) {
  return __riscv_vaadd_vv_i32m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 2);
}

FORCE_INLINE uint8x8_t vhadd_u8(uint8x8_t __a, uint8x8_t __b) {
  return __riscv_vaaddu_vv_u8m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 8);
}

FORCE_INLINE uint16x4_t vhadd_u16(uint16x4_t __a, uint16x4_t __b) {
  return __riscv_vaaddu_vv_u16m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 4);
}

FORCE_INLINE uint32x2_t vhadd_u32(uint32x2_t __a, uint32x2_t __b) {
  return __riscv_vaaddu_vv_u32m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 2);
}

// FORCE_INLINE int8x16_t vhaddq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vhaddq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vhaddq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint8x16_t vhaddq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vhaddq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vhaddq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8_t vrhadd_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vaadd_vv_i8m1(__a, __b, NEON2RVV_ROUND_TYPE_RNU, 8);
}

// FORCE_INLINE int16x4_t vrhadd_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vrhadd_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vrhadd_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vrhadd_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vrhadd_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16_t vrhaddq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vrhaddq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vrhaddq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint8x16_t vrhaddq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vrhaddq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vrhaddq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8_t vqadd_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vsadd_vv_i8m1(__a, __b, 8); }

// FORCE_INLINE int16x4_t vqadd_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vqadd_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x1_t vqadd_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint8x8_t vqadd_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vqadd_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vqadd_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint64x1_t vqadd_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t vqaddq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vqaddq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vqaddq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vqaddq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vqaddq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vqaddq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vqaddq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vqaddq_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vaddhn_s16(int16x8_t __a, int16x8_t __b) {
  // 0xaa is 10101010 in binary
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(0xaa));
  int8x16_t add_res = __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vadd_vv_i16m1(__a, __b, 8));
  return __riscv_vcompress_vm_i8m1(add_res, mask, 16);
}

// FORCE_INLINE int16x4_t vaddhn_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int32x2_t vaddhn_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x8_t vaddhn_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint16x4_t vaddhn_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint32x2_t vaddhn_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vraddhn_s16(int16x8_t __a, int16x8_t __b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(0xaa));
  int16x8_t add_ab = __riscv_vadd_vv_i16m1(__a, __b, 8);
  int16x8_t add_round = __riscv_vadd_vx_i16m1(add_ab, 1 << 7, 8);
  return __riscv_vcompress_vm_i8m1(__riscv_vreinterpret_v_i16m1_i8m1(add_round), mask, 16);
}

// FORCE_INLINE int16x4_t vraddhn_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int32x2_t vraddhn_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x8_t vraddhn_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint16x4_t vraddhn_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint32x2_t vraddhn_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vmul_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vmul_vv_i8m1(__a, __b, 8); }

FORCE_INLINE int16x4_t vmul_s16(int16x4_t __a, int16x4_t __b) { return __riscv_vmul_vv_i16m1(__a, __b, 4); }

FORCE_INLINE int32x2_t vmul_s32(int32x2_t __a, int32x2_t __b) { return __riscv_vmul_vv_i32m1(__a, __b, 2); }

FORCE_INLINE float32x2_t vmul_f32(float32x2_t __a, float32x2_t __b) { return __riscv_vfmul_vv_f32m1(__a, __b, 2); }

FORCE_INLINE uint8x8_t vmul_u8(uint8x8_t __a, uint8x8_t __b) { return __riscv_vmul_vv_u8m1(__a, __b, 8); }

FORCE_INLINE uint16x4_t vmul_u16(uint16x4_t __a, uint16x4_t __b) { return __riscv_vmul_vv_u16m1(__a, __b, 4); }

FORCE_INLINE uint32x2_t vmul_u32(uint32x2_t __a, uint32x2_t __b) { return __riscv_vmul_vv_u32m1(__a, __b, 2); }

// FORCE_INLINE int8x16_t vmulq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vmulq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vmulq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4_t vmulq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vmulq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vmulq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vmulq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int16x4_t vqdmulh_s16(int16x4_t __a, int16x4_t __b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(0xaa));
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(__a, __b, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(
      __riscv_vcompress_vm_i16m2(__riscv_vreinterpret_v_i32m2_i16m2(ab_mulx2), mask, 8));
}

// FORCE_INLINE int32x2_t vqdmulh_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int16x8_t vqdmulhq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vqdmulhq_s32(int32x4_t __a, int32x4_t __b);

FORCE_INLINE int16x4_t vqrdmulh_s16(int16x4_t __a, int16x4_t __b) {
  uint8_t mask_arr[] = {0xaa};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 1);
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(__a, __b, 4);
  vint32m2_t ab_mulx2 = __riscv_vmul_vx_i32m2(ab_mul, 2, 4);
  vint32m2_t add_round = __riscv_vadd_vx_i32m2(ab_mulx2, 1 << 15, 4);
  return __riscv_vlmul_trunc_v_i16m2_i16m1(
      __riscv_vcompress_vm_i16m2(__riscv_vreinterpret_v_i32m2_i16m2(add_round), mask, 8));
}

// FORCE_INLINE int32x2_t vqrdmulh_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int16x8_t vqrdmulhq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vqrdmulhq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int16x4_t vqrdmlah_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int32x2_t vqrdmlah_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE int16x8_t vqrdmlahq_s16(int16x8_t __a, int16x8_t __b, int16x8_t __c);

// FORCE_INLINE int32x4_t vqrdmlahq_s32(int32x4_t __a, int32x4_t __b, int32x4_t __c);

// FORCE_INLINE int16x4_t vqrdmlsh_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int32x2_t vqrdmlsh_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE int16x8_t vqrdmlshq_s16(int16x8_t __a, int16x8_t __b, int16x8_t __c);

// FORCE_INLINE int32x4_t vqrdmlshq_s32(int32x4_t __a, int32x4_t __b, int32x4_t __c);

FORCE_INLINE int16x8_t vmull_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwmul_vv_i16m2(__a, __b, 8));
}

FORCE_INLINE int32x4_t vmull_s16(int16x4_t __a, int16x4_t __b) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(__a, __b, 8));
}

FORCE_INLINE int64x2_t vmull_s32(int32x2_t __a, int32x2_t __b) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmul_vv_i64m2(__a, __b, 8));
}

FORCE_INLINE uint16x8_t vmull_u8(uint8x8_t __a, uint8x8_t __b) {
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwmulu_vv_u16m2(__a, __b, 8));
}

FORCE_INLINE uint32x4_t vmull_u16(uint16x4_t __a, uint16x4_t __b) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmulu_vv_u32m2(__a, __b, 8));
}

FORCE_INLINE uint64x2_t vmull_u32(uint32x2_t __a, uint32x2_t __b) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmulu_vv_u64m2(__a, __b, 8));
}

FORCE_INLINE int32x4_t vqdmull_s16(int16x4_t __a, int16x4_t __b) {
  vint32m2_t ab_mul = __riscv_vwmul_vv_i32m2(__a, __b, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vmul_vx_i32m2(ab_mul, 2, 4));
}

// FORCE_INLINE int64x2_t vqdmull_s32(int32x2_t __a, int32x2_t __b);

FORCE_INLINE int8x8_t vmla_s8(int8x8_t __a, int8x8_t __b, int8x8_t __c) {
  return __riscv_vmacc_vv_i8m1(__a, __b, __c, 8);
}

// FORCE_INLINE int16x4_t vmla_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int32x2_t vmla_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE float32x2_t vmla_f32(float32x2_t __a, float32x2_t __b, float32x2_t __c);

// FORCE_INLINE uint8x8_t vmla_u8(uint8x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE uint16x4_t vmla_u16(uint16x4_t __a, uint16x4_t __b, uint16x4_t __c);

// FORCE_INLINE uint32x2_t vmla_u32(uint32x2_t __a, uint32x2_t __b, uint32x2_t __c);

// FORCE_INLINE int8x16_t vmlaq_s8(int8x16_t __a, int8x16_t __b, int8x16_t __c);

// FORCE_INLINE int16x8_t vmlaq_s16(int16x8_t __a, int16x8_t __b, int16x8_t __c);

// FORCE_INLINE int32x4_t vmlaq_s32(int32x4_t __a, int32x4_t __b, int32x4_t __c);

// FORCE_INLINE float32x4_t vmlaq_f32(float32x4_t __a, float32x4_t __b, float32x4_t __c);

// FORCE_INLINE uint8x16_t vmlaq_u8(uint8x16_t __a, uint8x16_t __b, uint8x16_t __c);

// FORCE_INLINE uint16x8_t vmlaq_u16(uint16x8_t __a, uint16x8_t __b, uint16x8_t __c);

// FORCE_INLINE uint32x4_t vmlaq_u32(uint32x4_t __a, uint32x4_t __b, uint32x4_t __c);

FORCE_INLINE int16x8_t vmlal_s8(int16x8_t __a, int8x8_t __b, int8x8_t __c) {
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwmacc_vv_i16m2(__riscv_vlmul_ext_v_i16m1_i16m2(__a), __b, __c, 8));
}

FORCE_INLINE int32x4_t vmlal_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c) {
  return __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmacc_vv_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(__a), __b, __c, 4));
}

FORCE_INLINE int64x2_t vmlal_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c) {
  return __riscv_vlmul_trunc_v_i64m2_i64m1(__riscv_vwmacc_vv_i64m2(__riscv_vlmul_ext_v_i64m1_i64m2(__a), __b, __c, 2));
}

FORCE_INLINE uint16x8_t vmlal_u8(uint16x8_t __a, uint8x8_t __b, uint8x8_t __c) {
  return __riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vwmaccu_vv_u16m2(__riscv_vlmul_ext_v_u16m1_u16m2(__a), __b, __c, 8));
}

FORCE_INLINE uint32x4_t vmlal_u16(uint32x4_t __a, uint16x4_t __b, uint16x4_t __c) {
  return __riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vwmaccu_vv_u32m2(__riscv_vlmul_ext_v_u32m1_u32m2(__a), __b, __c, 4));
}

FORCE_INLINE uint64x2_t vmlal_u32(uint64x2_t __a, uint32x2_t __b, uint32x2_t __c) {
  return __riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vwmaccu_vv_u64m2(__riscv_vlmul_ext_v_u64m1_u64m2(__a), __b, __c, 2));
}

FORCE_INLINE int32x4_t vqdmlal_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c) {
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(__b, __c, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vadd_vv_i32m1(__a, bc_mulx2, 4);
}

// FORCE_INLINE int64x2_t vqdmlal_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c);

FORCE_INLINE int8x8_t vmls_s8(int8x8_t __a, int8x8_t __b, int8x8_t __c) {
  return __riscv_vnmsac_vv_i8m1(__a, __b, __c, 8);
}

// FORCE_INLINE int16x4_t vmls_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int32x2_t vmls_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE float32x2_t vmls_f32(float32x2_t __a, float32x2_t __b, float32x2_t __c);

// FORCE_INLINE uint8x8_t vmls_u8(uint8x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE uint16x4_t vmls_u16(uint16x4_t __a, uint16x4_t __b, uint16x4_t __c);

// FORCE_INLINE uint32x2_t vmls_u32(uint32x2_t __a, uint32x2_t __b, uint32x2_t __c);

// FORCE_INLINE int8x16_t vmlsq_s8(int8x16_t __a, int8x16_t __b, int8x16_t __c);

// FORCE_INLINE int16x8_t vmlsq_s16(int16x8_t __a, int16x8_t __b, int16x8_t __c);

// FORCE_INLINE int32x4_t vmlsq_s32(int32x4_t __a, int32x4_t __b, int32x4_t __c);

// FORCE_INLINE float32x4_t vmlsq_f32(float32x4_t __a, float32x4_t __b, float32x4_t __c);

// FORCE_INLINE uint8x16_t vmlsq_u8(uint8x16_t __a, uint8x16_t __b, uint8x16_t __c);

// FORCE_INLINE uint16x8_t vmlsq_u16(uint16x8_t __a, uint16x8_t __b, uint16x8_t __c);

// FORCE_INLINE uint32x4_t vmlsq_u32(uint32x4_t __a, uint32x4_t __b, uint32x4_t __c);

FORCE_INLINE int16x8_t vmlsl_s8(int16x8_t __a, int8x8_t __b, int8x8_t __c) {
  return __riscv_vsub_vv_i16m1(__a, __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwmul_vv_i16m2(__b, __c, 8)), 8);
}

// FORCE_INLINE int32x4_t vmlsl_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int64x2_t vmlsl_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE uint16x8_t vmlsl_u8(uint16x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE uint32x4_t vmlsl_u16(uint32x4_t __a, uint16x4_t __b, uint16x4_t __c);

// FORCE_INLINE uint64x2_t vmlsl_u32(uint64x2_t __a, uint32x2_t __b, uint32x2_t __c);

FORCE_INLINE int32x4_t vqdmlsl_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c) {
  vint32m1_t bc_mul = __riscv_vlmul_trunc_v_i32m2_i32m1(__riscv_vwmul_vv_i32m2(__b, __c, 4));
  vint32m1_t bc_mulx2 = __riscv_vmul_vx_i32m1(bc_mul, 2, 4);
  return __riscv_vsub_vv_i32m1(__a, bc_mulx2, 4);
}

// FORCE_INLINE int64x2_t vqdmlsl_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c);

FORCE_INLINE float32x2_t vfma_f32(float32x2_t __a, float32x2_t __b, float32x2_t __c) {
  return __riscv_vfmacc_vv_f32m1(__a, __b, __c, 2);
}

// FORCE_INLINE float32x4_t vfmaq_f32(float32x4_t __a, float32x4_t __b, float32x4_t __c);

FORCE_INLINE float32x2_t vfms_f32(float32x2_t __a, float32x2_t __b, float32x2_t __c) {
  return __riscv_vfnmsac_vv_f32m1(__a, __b, __c, 2);
}

// FORCE_INLINE float32x4_t vfmsq_f32(float32x4_t __a, float32x4_t __b, float32x4_t __c);

// FORCE_INLINE float32x2_t vrndn_f32(float32x2_t __a);

// FORCE_INLINE float32x4_t vrndnq_f32(float32x4_t __a);

// FORCE_INLINE float32x2_t vrnda_f32(float32x2_t __a);

// FORCE_INLINE float32x4_t vrndaq_f32(float32x4_t __a);

// FORCE_INLINE float32x2_t vrndp_f32(float32x2_t __a);

// FORCE_INLINE float32x4_t vrndpq_f32(float32x4_t __a);

// FORCE_INLINE float32x2_t vrndm_f32(float32x2_t __a);

// FORCE_INLINE float32x4_t vrndmq_f32(float32x4_t __a);

// FORCE_INLINE float32x2_t vrndx_f32(float32x2_t __a);

// FORCE_INLINE float32x4_t vrndxq_f32(float32x4_t __a);

// FORCE_INLINE float32x2_t vrnd_f32(float32x2_t __a);

// FORCE_INLINE float32x4_t vrndq_f32(float32x4_t __a);

FORCE_INLINE int8x8_t vsub_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vsub_vv_i8m1(__a, __b, 8); }

FORCE_INLINE int16x4_t vsub_s16(int16x4_t __a, int16x4_t __b) { return __riscv_vsub_vv_i16m1(__a, __b, 4); }

FORCE_INLINE int32x2_t vsub_s32(int32x2_t __a, int32x2_t __b) { return __riscv_vsub_vv_i32m1(__a, __b, 2); }

FORCE_INLINE float32x2_t vsub_f32(float32x2_t __a, float32x2_t __b) { return __riscv_vfsub_vv_f32m1(__a, __b, 2); }

FORCE_INLINE uint8x8_t vsub_u8(uint8x8_t __a, uint8x8_t __b) { return __riscv_vsub_vv_u8m1(__a, __b, 8); }

FORCE_INLINE uint16x4_t vsub_u16(uint16x4_t __a, uint16x4_t __b) { return __riscv_vsub_vv_u16m1(__a, __b, 4); }

FORCE_INLINE uint32x2_t vsub_u32(uint32x2_t __a, uint32x2_t __b) { return __riscv_vsub_vv_u32m1(__a, __b, 2); }

FORCE_INLINE int64x1_t vsub_s64(int64x1_t __a, int64x1_t __b) { return __riscv_vsub_vv_i64m1(__a, __b, 2); }

FORCE_INLINE uint64x1_t vsub_u64(uint64x1_t __a, uint64x1_t __b) { return __riscv_vsub_vv_u64m1(__a, __b, 2); }

// FORCE_INLINE int8x16_t vsubq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vsubq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vsubq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vsubq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE float32x4_t vsubq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vsubq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vsubq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vsubq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vsubq_u64(uint64x2_t __a, uint64x2_t __b);

// FORCE_INLINE int16x8_t vsubl_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int32x4_t vsubl_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int64x2_t vsubl_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint16x8_t vsubl_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint32x4_t vsubl_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint64x2_t vsubl_u32(uint32x2_t __a, uint32x2_t __b);

FORCE_INLINE int16x8_t vsubw_s8(int16x8_t __a, int8x8_t __b) {
  vint16m1_t b_ext = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(__b, 8));
  return __riscv_vsub_vv_i16m1(__a, b_ext, 8);
}

// FORCE_INLINE int32x4_t vsubw_s16(int32x4_t __a, int16x4_t __b);

// FORCE_INLINE int64x2_t vsubw_s32(int64x2_t __a, int32x2_t __b);

// FORCE_INLINE uint16x8_t vsubw_u8(uint16x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint32x4_t vsubw_u16(uint32x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint64x2_t vsubw_u32(uint64x2_t __a, uint32x2_t __b);

FORCE_INLINE int8x8_t vhsub_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vasub_vv_i8m1(__a, __b, NEON2RVV_ROUND_TYPE_RDN, 8);
}

// FORCE_INLINE int16x4_t vhsub_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vhsub_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vhsub_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vhsub_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vhsub_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16_t vhsubq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vhsubq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vhsubq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint8x16_t vhsubq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vhsubq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vhsubq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8_t vqsub_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vssub_vv_i8m1(__a, __b, 8); }

// FORCE_INLINE int16x4_t vqsub_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vqsub_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x1_t vqsub_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint8x8_t vqsub_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vqsub_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vqsub_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint64x1_t vqsub_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t vqsubq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vqsubq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vqsubq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vqsubq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vqsubq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vqsubq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vqsubq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vqsubq_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vsubhn_s16(int16x8_t __a, int16x8_t __b) {
  // 0xaa is 10101010 in binary
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(0xaa));
  int8x16_t ab_sub = __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vsub_vv_i16m1(__a, __b, 8));
  return __riscv_vcompress_vm_i8m1(ab_sub, mask, 16);
}

// FORCE_INLINE int16x4_t vsubhn_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int32x2_t vsubhn_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x8_t vsubhn_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint16x4_t vsubhn_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint32x2_t vsubhn_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vrsubhn_s16(int16x8_t __a, int16x8_t __b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(0xaa));
  int16x8_t ab_sub = __riscv_vsub_vv_i16m1(__a, __b, 8);
  int16x8_t sub_round = __riscv_vadd_vx_i16m1(ab_sub, 1 << 7, 8);
  return __riscv_vcompress_vm_i8m1(__riscv_vreinterpret_v_i16m1_i8m1(sub_round), mask, 16);
}

FORCE_INLINE int16x4_t vrsubhn_s32(int32x4_t __a, int32x4_t __b) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16(0xaa));
  int32x4_t ab_sub = __riscv_vsub_vv_i32m1(__a, __b, 8);
  int32x4_t sub_round = __riscv_vadd_vx_i32m1(ab_sub, 1 << 15, 8);
  return __riscv_vcompress_vm_i16m1(__riscv_vreinterpret_v_i32m1_i16m1(sub_round), mask, 8);
}

// FORCE_INLINE int32x2_t vrsubhn_s64(int64x2_t __a, int64x2_t __b);

FORCE_INLINE uint8x8_t vrsubhn_u16(uint16x8_t __a, uint16x8_t __b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(0xaa));
  uint16x8_t ab_sub = __riscv_vsub_vv_u16m1(__a, __b, 8);
  uint16x8_t sub_round = __riscv_vadd_vx_u16m1(ab_sub, 1 << 7, 8);
  return __riscv_vcompress_vm_u8m1(__riscv_vreinterpret_v_u16m1_u8m1(sub_round), mask, 16);
}

FORCE_INLINE uint16x4_t vrsubhn_u32(uint32x4_t __a, uint32x4_t __b) {
  vbool16_t mask = __riscv_vreinterpret_v_u16m1_b16(vdup_n_u16(0xaa));
  uint32x4_t ab_sub = __riscv_vsub_vv_u32m1(__a, __b, 8);
  uint32x4_t sub_round = __riscv_vadd_vx_u32m1(ab_sub, 1 << 15, 8);
  return __riscv_vcompress_vm_u16m1(__riscv_vreinterpret_v_u32m1_u16m1(sub_round), mask, 8);
}

// FORCE_INLINE uint32x2_t vrsubhn_u64(uint64x2_t __a, uint64x2_t __b);

// FORCE_INLINE uint8x8_t vceq_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vceq_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vceq_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint32x2_t vceq_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vceq_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vceq_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vceq_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint8x16_t vceqq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vceqq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vceqq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint32x4_t vceqq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vceqq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vceqq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vceqq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint8x8_t vcge_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vcge_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vcge_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint32x2_t vcge_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vcge_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vcge_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vcge_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint8x16_t vcgeq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vcgeq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vcgeq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint32x4_t vcgeq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vcgeq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vcgeq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vcgeq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint8x8_t vcle_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vcle_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vcle_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint32x2_t vcle_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vcle_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vcle_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vcle_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint8x16_t vcleq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vcleq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vcleq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint32x4_t vcleq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vcleq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vcleq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vcleq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE uint8x8_t vcgt_s8(int8x8_t __a, int8x8_t __b) {
  // vbool8_t uses every bit to represent the boolean values of each elements of the comparison result
  vbool8_t cmp_res = __riscv_vmsgt_vv_i8m1_b8(__a, __b, 8);
  // FIXME __riscv_vmv_s_x_* has a bug. When calling with other funcs, only the first element will be set.
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(0xff), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcgt_s16(int16x4_t __a, int16x4_t __b) {
  vbool16_t cmp_res = __riscv_vmsgt_vv_i16m1_b16(__a, __b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(0xffff), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcgt_s32(int32x2_t __a, int32x2_t __b) {
  vbool32_t cmp_res = __riscv_vmsgt_vv_i32m1_b32(__a, __b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(0xffffffff), cmp_res, 2);
}

FORCE_INLINE uint32x2_t vcgt_f32(float32x2_t __a, float32x2_t __b) {
  vbool32_t cmp_res = __riscv_vmfgt_vv_f32m1_b32(__a, __b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(0xffffffff), cmp_res, 2);
}

FORCE_INLINE uint8x8_t vcgt_u8(uint8x8_t __a, uint8x8_t __b) {
  vbool8_t cmp_res = __riscv_vmsgtu_vv_u8m1_b8(__a, __b, 8);
  return __riscv_vmerge_vvm_u8m1(vdup_n_u8(0x0), vdup_n_u8(0xff), cmp_res, 8);
}

FORCE_INLINE uint16x4_t vcgt_u16(uint16x4_t __a, uint16x4_t __b) {
  vbool16_t cmp_res = __riscv_vmsgtu_vv_u16m1_b16(__a, __b, 4);
  return __riscv_vmerge_vvm_u16m1(vdup_n_u16(0x0), vdup_n_u16(0xffff), cmp_res, 4);
}

FORCE_INLINE uint32x2_t vcgt_u32(uint32x2_t __a, uint32x2_t __b) {
  vbool32_t cmp_res = __riscv_vmsgtu_vv_u32m1_b32(__a, __b, 2);
  return __riscv_vmerge_vvm_u32m1(vdup_n_u32(0x0), vdup_n_u32(0xffffffff), cmp_res, 2);
}

// FORCE_INLINE uint8x16_t vcgtq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vcgtq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vcgtq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint32x4_t vcgtq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vcgtq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vcgtq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vcgtq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint8x8_t vclt_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vclt_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vclt_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint32x2_t vclt_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vclt_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vclt_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vclt_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint8x16_t vcltq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vcltq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vcltq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint32x4_t vcltq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vcltq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vcltq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vcltq_u32(uint32x4_t __a, uint32x4_t __b);

// TODO RVV doesn't have abs?
FORCE_INLINE int8x8_t vabs_s8(int8x8_t __a) {
  // refer https://stackoverflow.com/questions/12041632/how-to-compute-the-integer-absolute-value
  vint8m1_t mask = __riscv_vsra_vx_i8m1(__a, 7, 8);
  vint8m1_t a_xor = __riscv_vxor_vv_i8m1(__a, mask, 8);
  return __riscv_vsub_vv_i8m1(a_xor, mask, 8);
}

FORCE_INLINE int16x4_t vabs_s16(int16x4_t __a) {
  vint16m1_t mask = __riscv_vsra_vx_i16m1(__a, 15, 4);
  vint16m1_t a_xor = __riscv_vxor_vv_i16m1(__a, mask, 4);
  return __riscv_vsub_vv_i16m1(a_xor, mask, 4);
}

FORCE_INLINE int32x2_t vabs_s32(int32x2_t __a) {
  vint32m1_t mask = __riscv_vsra_vx_i32m1(__a, 31, 2);
  vint32m1_t a_xor = __riscv_vxor_vv_i32m1(__a, mask, 2);
  return __riscv_vsub_vv_i32m1(a_xor, mask, 2);
}

FORCE_INLINE float32x2_t vabs_f32(float32x2_t __a) { return __riscv_vfabs_v_f32m1(__a, 2); }

// FORCE_INLINE int8x16_t vabsq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vabsq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vabsq_s32(int32x4_t __a);

// FORCE_INLINE float32x4_t vabsq_f32(float32x4_t __a);

FORCE_INLINE int8x8_t vqabs_s8(int8x8_t __a) {
  // refer https://stackoverflow.com/questions/12041632/how-to-compute-the-integer-absolute-value
  vint8m1_t mask = __riscv_vsra_vx_i8m1(__a, 7, 8);
  vint8m1_t a_xor = __riscv_vxor_vv_i8m1(__a, mask, 8);
  return __riscv_vssub_vv_i8m1(a_xor, mask, 8);
}

// FORCE_INLINE int16x4_t vqabs_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vqabs_s32(int32x2_t __a);

// FORCE_INLINE int8x16_t vqabsq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vqabsq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vqabsq_s32(int32x4_t __a);

// FORCE_INLINE uint32x2_t vcage_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint32x4_t vcageq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint32x2_t vcale_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint32x4_t vcaleq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint32x2_t vcagt_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint32x4_t vcagtq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint32x2_t vcalt_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint32x4_t vcaltq_f32(float32x4_t __a, float32x4_t __b);

FORCE_INLINE uint8x8_t vtst_s8(int8x8_t __a, int8x8_t __b) {
  vint8m1_t ab_and = __riscv_vand_vv_i8m1(__a, __b, 8);
  vbool8_t nonzero_mask = __riscv_vmsgtu_vx_u8m1_b8(__riscv_vreinterpret_v_i8m1_u8m1(ab_and), 0, 8);
  return __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vmerge_vxm_i8m1(vdup_n_s8(0), 0xff, nonzero_mask, 8));
}

// FORCE_INLINE uint16x4_t vtst_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vtst_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vtst_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vtst_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vtst_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint8x16_t vtstq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vtstq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vtstq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint8x16_t vtstq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vtstq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vtstq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8_t vabd_s8(int8x8_t __a, int8x8_t __b) {
  // extend to 16 bits then do abs()
  vint16m1_t ab_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(__a, __b, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(ab_sub, 15, 8);
  vint16m1_t ab_xor = __riscv_vxor_vv_i16m1(ab_sub, sign_bit_mask, 8);
  vint16m1_t ab_sub_16 = __riscv_vsub_vv_i16m1(ab_xor, sign_bit_mask, 8);

  // select the lower 8 bits
  vbool8_t compress_mask = __riscv_vreinterpret_v_i8m1_b8(vdup_n_s8(85));
  return __riscv_vcompress_vm_i8m1(__riscv_vreinterpret_v_i16m1_i8m1(ab_sub_16), compress_mask, 16);
}

// FORCE_INLINE int16x4_t vabd_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vabd_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2_t vabd_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vabd_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vabd_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vabd_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16_t vabdq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vabdq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vabdq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4_t vabdq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vabdq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vabdq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vabdq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int16x8_t vabdl_s8(int8x8_t __a, int8x8_t __b) {
  vint16m1_t ab_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(__a, __b, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(ab_sub, 15, 8);
  vint16m1_t ab_xor = __riscv_vxor_vv_i16m1(ab_sub, sign_bit_mask, 8);
  return __riscv_vsub_vv_i16m1(ab_xor, sign_bit_mask, 8);
}

// FORCE_INLINE int32x4_t vabdl_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int64x2_t vabdl_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint16x8_t vabdl_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint32x4_t vabdl_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint64x2_t vabdl_u32(uint32x2_t __a, uint32x2_t __b);

FORCE_INLINE int8x8_t vaba_s8(int8x8_t __a, int8x8_t __b, int8x8_t __c) {
  // extend to 16 bits then do abs()
  vint16m1_t bc_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(__b, __c, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(bc_sub, 15, 8);
  vint16m1_t bc_xor = __riscv_vxor_vv_i16m1(bc_sub, sign_bit_mask, 8);
  vint16m1_t bc_sub_16 = __riscv_vsub_vv_i16m1(bc_xor, sign_bit_mask, 8);
  // select the lower 8 bits
  vbool8_t compress_mask = __riscv_vreinterpret_v_i8m1_b8(vdup_n_s8(85));
  vint8m1_t abs_diff = __riscv_vcompress_vm_i8m1(__riscv_vreinterpret_v_i16m1_i8m1(bc_sub_16), compress_mask, 16);
  // accumulate
  return __riscv_vadd_vv_i8m1(__a, abs_diff, 8);
}

// FORCE_INLINE int16x4_t vaba_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int32x2_t vaba_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE uint8x8_t vaba_u8(uint8x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE uint16x4_t vaba_u16(uint16x4_t __a, uint16x4_t __b, uint16x4_t __c);

// FORCE_INLINE uint32x2_t vaba_u32(uint32x2_t __a, uint32x2_t __b, uint32x2_t __c);

// FORCE_INLINE int8x16_t vabaq_s8(int8x16_t __a, int8x16_t __b, int8x16_t __c);

// FORCE_INLINE int16x8_t vabaq_s16(int16x8_t __a, int16x8_t __b, int16x8_t __c);

// FORCE_INLINE int32x4_t vabaq_s32(int32x4_t __a, int32x4_t __b, int32x4_t __c);

// FORCE_INLINE uint8x16_t vabaq_u8(uint8x16_t __a, uint8x16_t __b, uint8x16_t __c);

// FORCE_INLINE uint16x8_t vabaq_u16(uint16x8_t __a, uint16x8_t __b, uint16x8_t __c);

// FORCE_INLINE uint32x4_t vabaq_u32(uint32x4_t __a, uint32x4_t __b, uint32x4_t __c);

FORCE_INLINE int16x8_t vabal_s8(int16x8_t __a, int8x8_t __b, int8x8_t __c) {
  vint16m1_t bc_sub = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwsub_vv_i16m2(__b, __c, 8));
  vint16m1_t sign_bit_mask = __riscv_vsra_vx_i16m1(bc_sub, 15, 8);
  vint16m1_t bc_xor = __riscv_vxor_vv_i16m1(bc_sub, sign_bit_mask, 8);
  vint16m1_t abs_diff = __riscv_vsub_vv_i16m1(bc_xor, sign_bit_mask, 8);
  return __riscv_vadd_vv_i16m1(__a, abs_diff, 8);
}

// FORCE_INLINE int32x4_t vabal_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int64x2_t vabal_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE uint16x8_t vabal_u8(uint16x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE uint32x4_t vabal_u16(uint32x4_t __a, uint16x4_t __b, uint16x4_t __c);

// FORCE_INLINE uint64x2_t vabal_u32(uint64x2_t __a, uint32x2_t __b, uint32x2_t __c);

FORCE_INLINE int8x8_t vmax_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vmax_vv_i8m1(__a, __b, 8); }

// FORCE_INLINE int16x4_t vmax_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vmax_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2_t vmax_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vmax_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vmax_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vmax_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16_t vmaxq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vmaxq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vmaxq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4_t vmaxq_f32(float32x4_t __a, float32x4_t __b);

FORCE_INLINE float32x2_t vmaxnm_f32(float32x2_t a, float32x2_t b) { return __riscv_vfmax_vv_f32m1(a, b, 2); }

// FORCE_INLINE float32x4_t vmaxnmq_f32(float32x4_t a, float32x4_t b);

FORCE_INLINE float32x2_t vminnm_f32(float32x2_t a, float32x2_t b) { return __riscv_vfmin_vv_f32m1(a, b, 2); }

// FORCE_INLINE float32x4_t vminnmq_f32(float32x4_t a, float32x4_t b);

// FORCE_INLINE uint8x16_t vmaxq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vmaxq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vmaxq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE int8x8_t vmin_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vmin_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vmin_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2_t vmin_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vmin_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vmin_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vmin_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16_t vminq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vminq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vminq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4_t vminq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16_t vminq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vminq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vminq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8_t vpadd_s8(int8x8_t __a, int8x8_t __b) {
  vbool8_t mask = __riscv_vreinterpret_v_u8m1_b8(vdup_n_u8(85));
  vint8m1_t ab = __riscv_vslideup_vx_i8m1(__a, __b, 8, 16);
  vint8m1_t ab_s = __riscv_vslidedown_vx_i8m1(ab, 1, 16);
  vint8m1_t ab_add = __riscv_vadd_vv_i8m1(ab, ab_s, 16);
  return __riscv_vcompress_vm_i8m1(ab_add, mask, 16);
}

// FORCE_INLINE int16x4_t vpadd_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vpadd_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2_t vpadd_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vpadd_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vpadd_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vpadd_u32(uint32x2_t __a, uint32x2_t __b);

FORCE_INLINE int16x4_t vpaddl_s8(int8x8_t __a) {
  uint8_t mask_arr[] = {85};
  vbool16_t mask = __riscv_vlm_v_b16(mask_arr, 1);
  vint8m1_t a_s = __riscv_vslidedown_vx_i8m1(__a, 1, 8);
  vint16m1_t a_add = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwadd_vv_i16m2(__a, a_s, 8));
  return __riscv_vcompress_vm_i16m1(a_add, mask, 8);
}

// FORCE_INLINE int32x2_t vpaddl_s16(int16x4_t __a);

// FORCE_INLINE int64x1_t vpaddl_s32(int32x2_t __a);

// FORCE_INLINE uint16x4_t vpaddl_u8(uint8x8_t __a);

// FORCE_INLINE uint32x2_t vpaddl_u16(uint16x4_t __a);

// FORCE_INLINE uint64x1_t vpaddl_u32(uint32x2_t __a);

// FORCE_INLINE int16x8_t vpaddlq_s8(int8x16_t __a);

// FORCE_INLINE int32x4_t vpaddlq_s16(int16x8_t __a);

// FORCE_INLINE int64x2_t vpaddlq_s32(int32x4_t __a);

// FORCE_INLINE uint16x8_t vpaddlq_u8(uint8x16_t __a);

// FORCE_INLINE uint32x4_t vpaddlq_u16(uint16x8_t __a);

// FORCE_INLINE uint64x2_t vpaddlq_u32(uint32x4_t __a);

FORCE_INLINE int16x4_t vpadal_s8(int16x4_t __a, int8x8_t __b) {
  uint8_t mask_arr[] = {85};
  vbool16_t mask = __riscv_vlm_v_b16(mask_arr, 1);
  vint8m1_t b_s = __riscv_vslidedown_vx_i8m1(__b, 1, 8);
  vint16m1_t b_add = __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vwadd_vv_i16m2(__b, b_s, 8));
  vint16m1_t padd = __riscv_vcompress_vm_i16m1(b_add, mask, 8);
  return __riscv_vadd_vv_i16m1(padd, __a, 8);
}

// FORCE_INLINE int32x2_t vpadal_s16(int32x2_t __a, int16x4_t __b);

// FORCE_INLINE int64x1_t vpadal_s32(int64x1_t __a, int32x2_t __b);

// FORCE_INLINE uint16x4_t vpadal_u8(uint16x4_t __a, uint8x8_t __b);

// FORCE_INLINE uint32x2_t vpadal_u16(uint32x2_t __a, uint16x4_t __b);

// FORCE_INLINE uint64x1_t vpadal_u32(uint64x1_t __a, uint32x2_t __b);

// FORCE_INLINE int16x8_t vpadalq_s8(int16x8_t __a, int8x16_t __b);

// FORCE_INLINE int32x4_t vpadalq_s16(int32x4_t __a, int16x8_t __b);

// FORCE_INLINE int64x2_t vpadalq_s32(int64x2_t __a, int32x4_t __b);

// FORCE_INLINE uint16x8_t vpadalq_u8(uint16x8_t __a, uint8x16_t __b);

// FORCE_INLINE uint32x4_t vpadalq_u16(uint32x4_t __a, uint16x8_t __b);

// FORCE_INLINE uint64x2_t vpadalq_u32(uint64x2_t __a, uint32x4_t __b);

// FORCE_INLINE int8x8_t vpmax_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vpmax_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vpmax_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2_t vpmax_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vpmax_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vpmax_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vpmax_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x8_t vpmin_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vpmin_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vpmin_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2_t vpmin_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8_t vpmin_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vpmin_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vpmin_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE float32x2_t vrecps_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vrecpsq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vrsqrts_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vrsqrtsq_f32(float32x4_t __a, float32x4_t __b);

FORCE_INLINE int8x8_t vshl_s8(int8x8_t __a, int8x8_t __b) {
  int8_t *_a = (int8_t *)&__a;
  int8_t *_b = (int8_t *)&__b;
  int8_t _c[8];
  for (int i = 0; i < 8; i++) {
    if (_b[i] < 0) {
      _c[i] = _a[i] >> -_b[i];
    } else {
      _c[i] = _a[i] << _b[i];
    }
  }
  return __riscv_vle8_v_i8m1(_c, 8);
  // FIXME the following is a working RVV impl, but I doubt its speed
  // vint8m1_t neg_mask = __riscv_vsra_vx_i8m1(__b, 7, 8);
  // vint8m1_t b_neg_mask = __riscv_vand_vv_i8m1(__b, neg_mask, 8);
  // vint8m1_t a_sll_mess = __riscv_vsll_vv_i8m1(__a, __riscv_vreinterpret_v_i8m1_u8m1(__b), 8);
  // vint8m1_t a_sll = __riscv_vand_vv_i8m1(a_sll_mess, __riscv_vnot_v_i8m1(neg_mask, 8), 8);
  // vint8m1_t b_neg = __riscv_vneg_v_i8m1(b_neg_mask, 8);
  // vbool8_t lt_mask = __riscv_vmsgt_vx_i8m1_b8(b_neg, 7, 8);
  // vuint8m1_t b_sra_bound = __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vmerge_vxm_i8m1(b_neg, 7, lt_mask, 8));
  // vint8m1_t a_sra = __riscv_vsra_vv_i8m1(__riscv_vand_vv_i8m1(__a, neg_mask, 8), b_sra_bound, 8);
  // vbool8_t gt_mask = __riscv_vmsgt_vx_i8m1_b8(__b, 7, 8);
  // vint8m1_t a_sll_sra = __riscv_vor_vv_i8m1(a_sll, a_sra, 8);
  // return __riscv_vmerge_vvm_i8m1(a_sll_sra, vdup_n_s8(0), gt_mask, 8);
}

// FORCE_INLINE int16x4_t vshl_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vshl_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x1_t vshl_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint8x8_t vshl_u8(uint8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vshl_u16(uint16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vshl_u32(uint32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint64x1_t vshl_u64(uint64x1_t __a, int64x1_t __b);

// FORCE_INLINE int8x16_t vshlq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vshlq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vshlq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vshlq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vshlq_u8(uint8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vshlq_u16(uint16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vshlq_u32(uint32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint64x2_t vshlq_u64(uint64x2_t __a, int64x2_t __b);

FORCE_INLINE int8x8_t vrshl_s8(int8x8_t __a, int8x8_t __b) {
  int8_t *_a = (int8_t *)&__a;
  int8_t *_b = (int8_t *)&__b;
  int8_t _c[8];
  for (int i = 0; i < 8; i++) {
    if (_b[i] < 0) {
      int8_t b_neg = -_b[i];
      _c[i] = (_a[i] + (1 << (b_neg - 1))) >> b_neg;
    } else {
      _c[i] = (_a[i]) << _b[i];
    }
  }
  return __riscv_vle8_v_i8m1(_c, 8);
}

// FORCE_INLINE int16x4_t vrshl_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vrshl_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x1_t vrshl_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint8x8_t vrshl_u8(uint8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vrshl_u16(uint16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vrshl_u32(uint32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint64x1_t vrshl_u64(uint64x1_t __a, int64x1_t __b);

// FORCE_INLINE int8x16_t vrshlq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vrshlq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vrshlq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vrshlq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vrshlq_u8(uint8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vrshlq_u16(uint16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vrshlq_u32(uint32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint64x2_t vrshlq_u64(uint64x2_t __a, int64x2_t __b);

// FORCE_INLINE int8x8_t vqshl_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vqshl_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vqshl_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x1_t vqshl_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint8x8_t vqshl_u8(uint8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vqshl_u16(uint16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vqshl_u32(uint32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint64x1_t vqshl_u64(uint64x1_t __a, int64x1_t __b);

// FORCE_INLINE int8x16_t vqshlq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vqshlq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vqshlq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vqshlq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vqshlq_u8(uint8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vqshlq_u16(uint16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vqshlq_u32(uint32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint64x2_t vqshlq_u64(uint64x2_t __a, int64x2_t __b);

// FORCE_INLINE int8x8_t vqrshl_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vqrshl_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vqrshl_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x1_t vqrshl_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint8x8_t vqrshl_u8(uint8x8_t __a, int8x8_t __b);

// FORCE_INLINE uint16x4_t vqrshl_u16(uint16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint32x2_t vqrshl_u32(uint32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint64x1_t vqrshl_u64(uint64x1_t __a, int64x1_t __b);

// FORCE_INLINE int8x16_t vqrshlq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vqrshlq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vqrshlq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vqrshlq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vqrshlq_u8(uint8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint16x8_t vqrshlq_u16(uint16x8_t __a, int16x8_t __b);

// FORCE_INLINE uint32x4_t vqrshlq_u32(uint32x4_t __a, int32x4_t __b);

// FORCE_INLINE uint64x2_t vqrshlq_u64(uint64x2_t __a, int64x2_t __b);

FORCE_INLINE int8x8_t vshr_n_s8(int8x8_t __a, const int __b) {
  const int imm = __b - (__b >> 3);
  return __riscv_vsra_vx_i8m1(__a, imm, 8);
}

// FORCE_INLINE int16x4_t vshr_n_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vshr_n_s32(int32x2_t __a, const int __b);

// FORCE_INLINE int64x1_t vshr_n_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint8x8_t vshr_n_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vshr_n_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vshr_n_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE uint64x1_t vshr_n_u64(uint64x1_t __a, const int __b);

// FORCE_INLINE int8x16_t vshrq_n_s8(int8x16_t __a, const int __b);

// FORCE_INLINE int16x8_t vshrq_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE int32x4_t vshrq_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int64x2_t vshrq_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x16_t vshrq_n_u8(uint8x16_t __a, const int __b);

// FORCE_INLINE uint16x8_t vshrq_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint32x4_t vshrq_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint64x2_t vshrq_n_u64(uint64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vrshr_n_s8(int8x8_t __a, const int __b) {
  vint16m2_t a_w = __riscv_vsext_vf2_i16m2(__a, 8);
  return __riscv_vnclip_wx_i8m1(a_w, __b, NEON2RVV_ROUND_TYPE_RNU, 8);
}

// FORCE_INLINE int16x4_t vrshr_n_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vrshr_n_s32(int32x2_t __a, const int __b);

// FORCE_INLINE int64x1_t vrshr_n_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint8x8_t vrshr_n_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vrshr_n_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vrshr_n_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE uint64x1_t vrshr_n_u64(uint64x1_t __a, const int __b);

// FORCE_INLINE int8x16_t vrshrq_n_s8(int8x16_t __a, const int __b);

// FORCE_INLINE int16x8_t vrshrq_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE int32x4_t vrshrq_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int64x2_t vrshrq_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x16_t vrshrq_n_u8(uint8x16_t __a, const int __b);

// FORCE_INLINE uint16x8_t vrshrq_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint32x4_t vrshrq_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint64x2_t vrshrq_n_u64(uint64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vshrn_n_s16(int16x8_t __a, const int __b) {
  return __riscv_vreinterpret_v_u8m1_i8m1(
      __riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(__riscv_vreinterpret_v_i16m1_u16m1(__a)), __b, 8));
}

// FORCE_INLINE int16x4_t vshrn_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vshrn_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vshrn_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vshrn_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vshrn_n_u64(uint64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vrshrn_n_s16(int16x8_t __a, const int __b) {
  vuint16m1_t a_round = __riscv_vadd_vx_u16m1(__riscv_vreinterpret_v_i16m1_u16m1(__a), 1 << (__b - 1), 8);
  return __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vnsrl_wx_u8m1(__riscv_vlmul_ext_v_u16m1_u16m2(a_round), __b, 8));
}

// FORCE_INLINE int16x4_t vrshrn_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vrshrn_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vrshrn_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vrshrn_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vrshrn_n_u64(uint64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vqshrn_n_s16(int16x8_t __a, const int __b) {
  vint16m1_t sra = __riscv_vsra_vx_i16m1(__a, __b, 8);
  vbool16_t positive_mask = __riscv_vmsgt_vx_i16m1_b16(sra, 0, 8);
  vbool16_t negative_mask = __riscv_vmnot_m_b16(positive_mask, 8);
  vint16m1_t sra_positive = __riscv_vmin_vx_i16m1_m(positive_mask, sra, INT8_MAX, 8);
  vint16m1_t sra_saturated = __riscv_vmax_vx_i16m1_m(negative_mask, sra_positive, INT8_MIN, 8);
  return __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vncvt_x_x_w_i8mf2(sra_saturated, 8));
}

// FORCE_INLINE int16x4_t vqshrn_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vqshrn_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vqshrn_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vqshrn_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vqshrn_n_u64(uint64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vqrshrn_n_s16(int16x8_t __a, const int __b) {
  return __riscv_vnclip_wx_i8m1(__riscv_vlmul_ext_v_i16m1_i16m2(__a), __b, NEON2RVV_ROUND_TYPE_RNU, 8);
}

// FORCE_INLINE int16x4_t vqrshrn_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vqrshrn_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vqrshrn_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vqrshrn_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vqrshrn_n_u64(uint64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vqshrun_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vqshrun_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vqshrun_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vqrshrun_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vqrshrun_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vqrshrun_n_s64(int64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vshl_n_s8(int8x8_t __a, const int __b) { return __riscv_vsll_vx_i8m1(__a, __b, 8); }

// FORCE_INLINE int16x4_t vshl_n_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vshl_n_s32(int32x2_t __a, const int __b);

// FORCE_INLINE int64x1_t vshl_n_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint8x8_t vshl_n_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vshl_n_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vshl_n_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE uint64x1_t vshl_n_u64(uint64x1_t __a, const int __b);

// FORCE_INLINE int8x16_t vshlq_n_s8(int8x16_t __a, const int __b);

// FORCE_INLINE int16x8_t vshlq_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE int32x4_t vshlq_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int64x2_t vshlq_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x16_t vshlq_n_u8(uint8x16_t __a, const int __b);

// FORCE_INLINE uint16x8_t vshlq_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint32x4_t vshlq_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint64x2_t vshlq_n_u64(uint64x2_t __a, const int __b);

// FORCE_INLINE int8x8_t vqshl_n_s8(int8x8_t __a, const int __b);

// FORCE_INLINE int16x4_t vqshl_n_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vqshl_n_s32(int32x2_t __a, const int __b);

// FORCE_INLINE int64x1_t vqshl_n_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint8x8_t vqshl_n_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vqshl_n_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vqshl_n_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE uint64x1_t vqshl_n_u64(uint64x1_t __a, const int __b);

// FORCE_INLINE int8x16_t vqshlq_n_s8(int8x16_t __a, const int __b);

// FORCE_INLINE int16x8_t vqshlq_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE int32x4_t vqshlq_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE int64x2_t vqshlq_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint8x16_t vqshlq_n_u8(uint8x16_t __a, const int __b);

// FORCE_INLINE uint16x8_t vqshlq_n_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint32x4_t vqshlq_n_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint64x2_t vqshlq_n_u64(uint64x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vqshlu_n_s8(int8x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vqshlu_n_s16(int16x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vqshlu_n_s32(int32x2_t __a, const int __b);

// FORCE_INLINE uint64x1_t vqshlu_n_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint8x16_t vqshluq_n_s8(int8x16_t __a, const int __b);

// FORCE_INLINE uint16x8_t vqshluq_n_s16(int16x8_t __a, const int __b);

// FORCE_INLINE uint32x4_t vqshluq_n_s32(int32x4_t __a, const int __b);

// FORCE_INLINE uint64x2_t vqshluq_n_s64(int64x2_t __a, const int __b);

// FORCE_INLINE int16x8_t vshll_n_s8(int8x8_t __a, const int __b);

// FORCE_INLINE int32x4_t vshll_n_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int64x2_t vshll_n_s32(int32x2_t __a, const int __b);

// FORCE_INLINE uint16x8_t vshll_n_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint32x4_t vshll_n_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint64x2_t vshll_n_u32(uint32x2_t __a, const int __b);

FORCE_INLINE int8x8_t vsra_n_s8(int8x8_t __a, int8x8_t __b, const int __c) {
  const int imm = __c - (__c >> 3);
  return __riscv_vadd_vv_i8m1(__a, __riscv_vsra_vx_i8m1(__b, imm, 8), 8);
}

// FORCE_INLINE int16x4_t vsra_n_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vsra_n_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int64x1_t vsra_n_s64(int64x1_t __a, int64x1_t __b, const int __c);

// FORCE_INLINE uint8x8_t vsra_n_u8(uint8x8_t __a, uint8x8_t __b, const int __c);

// FORCE_INLINE uint16x4_t vsra_n_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vsra_n_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE uint64x1_t vsra_n_u64(uint64x1_t __a, uint64x1_t __b, const int __c);

// FORCE_INLINE int8x16_t vsraq_n_s8(int8x16_t __a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vsraq_n_s16(int16x8_t __a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vsraq_n_s32(int32x4_t __a, int32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vsraq_n_s64(int64x2_t __a, int64x2_t __b, const int __c);

// FORCE_INLINE uint8x16_t vsraq_n_u8(uint8x16_t __a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vsraq_n_u16(uint16x8_t __a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vsraq_n_u32(uint32x4_t __a, uint32x4_t __b, const int __c);

// FORCE_INLINE uint64x2_t vsraq_n_u64(uint64x2_t __a, uint64x2_t __b, const int __c);

FORCE_INLINE int8x8_t vrsra_n_s8(int8x8_t __a, int8x8_t __b, const int __c) {
  vint16m2_t b_w = __riscv_vsext_vf2_i16m2(__b, 8);
  vint8m1_t b_rshr = __riscv_vnclip_wx_i8m1(b_w, __c, NEON2RVV_ROUND_TYPE_RNU, 8);
  return __riscv_vadd_vv_i8m1(__a, b_rshr, 8);
}

// FORCE_INLINE int16x4_t vrsra_n_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vrsra_n_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int64x1_t vrsra_n_s64(int64x1_t __a, int64x1_t __b, const int __c);

// FORCE_INLINE uint8x8_t vrsra_n_u8(uint8x8_t __a, uint8x8_t __b, const int __c);

// FORCE_INLINE uint16x4_t vrsra_n_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vrsra_n_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE uint64x1_t vrsra_n_u64(uint64x1_t __a, uint64x1_t __b, const int __c);

// FORCE_INLINE int8x16_t vrsraq_n_s8(int8x16_t __a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vrsraq_n_s16(int16x8_t __a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vrsraq_n_s32(int32x4_t __a, int32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vrsraq_n_s64(int64x2_t __a, int64x2_t __b, const int __c);

// FORCE_INLINE uint8x16_t vrsraq_n_u8(uint8x16_t __a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vrsraq_n_u16(uint16x8_t __a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vrsraq_n_u32(uint32x4_t __a, uint32x4_t __b, const int __c);

// FORCE_INLINE uint64x2_t vrsraq_n_u64(uint64x2_t __a, uint64x2_t __b, const int __c);

FORCE_INLINE int8x8_t vsri_n_s8(int8x8_t __a, int8x8_t __b, const int __c) {
  uint8_t mask = UINT8_MAX >> __c;
  vint8m1_t high = __riscv_vand_vx_i8m1(__a, ~mask, 8);
  vint8m1_t low_unmasked = __riscv_vsra_vx_i8m1(__b, __c, 8);
  vint8m1_t low = __riscv_vand_vx_i8m1(low_unmasked, mask, 8);
  return __riscv_vor_vv_i8m1(high, low, 8);
}

// FORCE_INLINE int16x4_t vsri_n_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vsri_n_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int64x1_t vsri_n_s64(int64x1_t __a, int64x1_t __b, const int __c);

// FORCE_INLINE uint8x8_t vsri_n_u8(uint8x8_t __a, uint8x8_t __b, const int __c);

// FORCE_INLINE uint16x4_t vsri_n_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vsri_n_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE uint64x1_t vsri_n_u64(uint64x1_t __a, uint64x1_t __b, const int __c);

// FORCE_INLINE int8x16_t vsriq_n_s8(int8x16_t __a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vsriq_n_s16(int16x8_t __a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vsriq_n_s32(int32x4_t __a, int32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vsriq_n_s64(int64x2_t __a, int64x2_t __b, const int __c);

// FORCE_INLINE uint8x16_t vsriq_n_u8(uint8x16_t __a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vsriq_n_u16(uint16x8_t __a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vsriq_n_u32(uint32x4_t __a, uint32x4_t __b, const int __c);

// FORCE_INLINE uint64x2_t vsriq_n_u64(uint64x2_t __a, uint64x2_t __b, const int __c);

// FORCE_INLINE int8x8_t vsli_n_s8(int8x8_t __a, int8x8_t __b, const int __c);

// FORCE_INLINE int16x4_t vsli_n_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vsli_n_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int64x1_t vsli_n_s64(int64x1_t __a, int64x1_t __b, const int __c);

// FORCE_INLINE uint8x8_t vsli_n_u8(uint8x8_t __a, uint8x8_t __b, const int __c);

// FORCE_INLINE uint16x4_t vsli_n_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vsli_n_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE uint64x1_t vsli_n_u64(uint64x1_t __a, uint64x1_t __b, const int __c);

// FORCE_INLINE int8x16_t vsliq_n_s8(int8x16_t __a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vsliq_n_s16(int16x8_t __a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vsliq_n_s32(int32x4_t __a, int32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vsliq_n_s64(int64x2_t __a, int64x2_t __b, const int __c);

// FORCE_INLINE uint8x16_t vsliq_n_u8(uint8x16_t __a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vsliq_n_u16(uint16x8_t __a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vsliq_n_u32(uint32x4_t __a, uint32x4_t __b, const int __c);

// FORCE_INLINE uint64x2_t vsliq_n_u64(uint64x2_t __a, uint64x2_t __b, const int __c);

// FORCE_INLINE int8x8_t vneg_s8(int8x8_t __a);

// FORCE_INLINE int16x4_t vneg_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vneg_s32(int32x2_t __a);

// FORCE_INLINE float32x2_t vneg_f32(float32x2_t __a);

// FORCE_INLINE int8x16_t vnegq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vnegq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vnegq_s32(int32x4_t __a);

// FORCE_INLINE float32x4_t vnegq_f32(float32x4_t __a);

// FORCE_INLINE int8x8_t vqneg_s8(int8x8_t __a);

// FORCE_INLINE int16x4_t vqneg_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vqneg_s32(int32x2_t __a);

// FORCE_INLINE int8x16_t vqnegq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vqnegq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vqnegq_s32(int32x4_t __a);

FORCE_INLINE int8x8_t vmvn_s8(int8x8_t __a) { return __riscv_vnot_v_i8m1(__a, 8); }

// FORCE_INLINE int16x4_t vmvn_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vmvn_s32(int32x2_t __a);

// FORCE_INLINE uint8x8_t vmvn_u8(uint8x8_t __a);

// FORCE_INLINE uint16x4_t vmvn_u16(uint16x4_t __a);

// FORCE_INLINE uint32x2_t vmvn_u32(uint32x2_t __a);

// FORCE_INLINE int8x16_t vmvnq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vmvnq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vmvnq_s32(int32x4_t __a);

// FORCE_INLINE uint8x16_t vmvnq_u8(uint8x16_t __a);

// FORCE_INLINE uint16x8_t vmvnq_u16(uint16x8_t __a);

// FORCE_INLINE uint32x4_t vmvnq_u32(uint32x4_t __a);

// FORCE_INLINE int8x8_t vcls_s8(int8x8_t __a);

// FORCE_INLINE int16x4_t vcls_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vcls_s32(int32x2_t __a);

// FORCE_INLINE int8x16_t vclsq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vclsq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vclsq_s32(int32x4_t __a);

FORCE_INLINE int8x8_t vclz_s8(int8x8_t __a) {
  // refer
  // https://stackoverflow.com/questions/23856596/how-to-count-leading-zeros-in-a-32-bit-unsigned-integer
  vuint8m1_t a_u = __riscv_vreinterpret_v_i8m1_u8m1(__a);
  a_u = __riscv_vor_vv_u8m1(__riscv_vsrl_vx_u8m1(a_u, 1, 8), a_u, 8);
  a_u = __riscv_vor_vv_u8m1(__riscv_vsrl_vx_u8m1(a_u, 2, 8), a_u, 8);
  a_u = __riscv_vor_vv_u8m1(__riscv_vsrl_vx_u8m1(a_u, 4, 8), a_u, 8);
  vuint8m1_t a_not = __riscv_vnot_v_u8m1(a_u, 8);
  return vcnt_s8(__riscv_vreinterpret_v_u8m1_i8m1(a_not));
}

// FORCE_INLINE int16x4_t vclz_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vclz_s32(int32x2_t __a);

// FORCE_INLINE uint8x8_t vclz_u8(uint8x8_t __a);

// FORCE_INLINE uint16x4_t vclz_u16(uint16x4_t __a);

// FORCE_INLINE uint32x2_t vclz_u32(uint32x2_t __a);

// FORCE_INLINE int8x16_t vclzq_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vclzq_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vclzq_s32(int32x4_t __a);

// FORCE_INLINE uint8x16_t vclzq_u8(uint8x16_t __a);

// FORCE_INLINE uint16x8_t vclzq_u16(uint16x8_t __a);

// FORCE_INLINE uint32x4_t vclzq_u32(uint32x4_t __a);

FORCE_INLINE int8x8_t vcnt_s8(int8x8_t __a) {
  const int8_t bit_population_lookup_arr[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
  vint8m1_t lookup = __riscv_vle8_v_i8m1(bit_population_lookup_arr, 16);
  vint8m1_t cnt_low =
      __riscv_vrgather_vv_i8m1(lookup, __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vand_vx_i8m1(__a, 0xf, 8)), 8);
  vint8m1_t a_high =
      __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vsrl_vx_u8m1(__riscv_vreinterpret_v_i8m1_u8m1(__a), 4, 8));
  vint8m1_t cnt_high = __riscv_vrgather_vv_i8m1(lookup, __riscv_vreinterpret_v_i8m1_u8m1(a_high), 8);
  return __riscv_vadd_vv_i8m1(cnt_low, cnt_high, 8);
}

// FORCE_INLINE uint8x8_t vcnt_u8(uint8x8_t __a);

// FORCE_INLINE int8x16_t vcntq_s8(int8x16_t __a);

// FORCE_INLINE uint8x16_t vcntq_u8(uint8x16_t __a);

FORCE_INLINE float32x2_t vrecpe_f32(float32x2_t __a) { return __riscv_vfrec7_v_f32m1(__a, 2); }

// FORCE_INLINE uint32x2_t vrecpe_u32(uint32x2_t __a);

// FORCE_INLINE float32x4_t vrecpeq_f32(float32x4_t __a);

// FORCE_INLINE uint32x4_t vrecpeq_u32(uint32x4_t __a);

FORCE_INLINE float32x2_t vrsqrte_f32(float32x2_t __a) { return __riscv_vfrsqrt7_v_f32m1(__a, 2); }

// FORCE_INLINE uint32x2_t vrsqrte_u32(uint32x2_t __a);

// FORCE_INLINE float32x4_t vrsqrteq_f32(float32x4_t __a);

// FORCE_INLINE uint32x4_t vrsqrteq_u32(uint32x4_t __a);

FORCE_INLINE int8_t vget_lane_s8(int8x8_t __a, const int __b) {
  return __riscv_vmv_x_s_i8m1_i8(__riscv_vslidedown_vx_i8m1(__a, __b, 8));
}

// FORCE_INLINE int16_t vget_lane_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32_t vget_lane_s32(int32x2_t __a, const int __b);

// FORCE_INLINE float32_t vget_lane_f32(float32x2_t __a, const int __b);

// FORCE_INLINE uint8_t vget_lane_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16_t vget_lane_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32_t vget_lane_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE int64_t vget_lane_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint64_t vget_lane_u64(uint64x1_t __a, const int __b);

// FORCE_INLINE int8_t vgetq_lane_s8(int8x16_t __a, const int __b);

// FORCE_INLINE int16_t vgetq_lane_s16(int16x8_t __a, const int __b);

// FORCE_INLINE int32_t vgetq_lane_s32(int32x4_t __a, const int __b);

// FORCE_INLINE float32_t vgetq_lane_f32(float32x4_t __a, const int __b);

// FORCE_INLINE uint8_t vgetq_lane_u8(uint8x16_t __a, const int __b);

// FORCE_INLINE uint16_t vgetq_lane_u16(uint16x8_t __a, const int __b);

// FORCE_INLINE uint32_t vgetq_lane_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE int64_t vgetq_lane_s64(int64x2_t __a, const int __b);

// FORCE_INLINE uint64_t vgetq_lane_u64(uint64x2_t __a, const int __b);

FORCE_INLINE int8x8_t vset_lane_s8(int8_t __a, int8x8_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 8);
  int8x8_t a_dup = vdup_n_s8(__a);
  return __riscv_vmerge_vvm_i8m1(__b, a_dup, mask, 8);
}

// FORCE_INLINE int16x4_t vset_lane_s16(int16_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vset_lane_s32(int32_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE float32x2_t vset_lane_f32(float32_t __a, float32x2_t __b, const int __c);

// FORCE_INLINE uint8x8_t vset_lane_u8(uint8_t __a, uint8x8_t __b, const int __c);

// FORCE_INLINE uint16x4_t vset_lane_u16(uint16_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vset_lane_u32(uint32_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE int64x1_t vset_lane_s64(int64_t __a, int64x1_t __b, const int __c);

// FORCE_INLINE uint64x1_t vset_lane_u64(uint64_t __a, uint64x1_t __b, const int __c);

// FORCE_INLINE int8x16_t vsetq_lane_s8(int8_t __a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vsetq_lane_s16(int16_t __a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vsetq_lane_s32(int32_t __a, int32x4_t __b, const int __c);

// FORCE_INLINE float32x4_t vsetq_lane_f32(float32_t __a, float32x4_t __b, const int __c);

// FORCE_INLINE uint8x16_t vsetq_lane_u8(uint8_t __a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vsetq_lane_u16(uint16_t __a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vsetq_lane_u32(uint32_t __a, uint32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vsetq_lane_s64(int64_t __a, int64x2_t __b, const int __c);

// FORCE_INLINE uint64x2_t vsetq_lane_u64(uint64_t __a, uint64x2_t __b, const int __c);

FORCE_INLINE int8x8_t vcreate_s8(uint64_t __a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_u64m1_i64m1(__riscv_vmv_v_x_u64m1(__a, 8)));
}

// FORCE_INLINE int16x4_t vcreate_s16(uint64_t __a);

// FORCE_INLINE int32x2_t vcreate_s32(uint64_t __a);

// FORCE_INLINE int64x1_t vcreate_s64(uint64_t __a);

// FORCE_INLINE float32x2_t vcreate_f32(uint64_t __a);

// FORCE_INLINE uint8x8_t vcreate_u8(uint64_t __a);

// FORCE_INLINE uint16x4_t vcreate_u16(uint64_t __a);

// FORCE_INLINE uint32x2_t vcreate_u32(uint64_t __a);

// FORCE_INLINE uint64x1_t vcreate_u64(uint64_t __a);

FORCE_INLINE int8x8_t vdup_n_s8(int8_t __a) { return __riscv_vmv_s_x_i8m1(__a, 8); }

FORCE_INLINE int16x4_t vdup_n_s16(int16_t __a) { return __riscv_vmv_s_x_i16m1(__a, 4); }

FORCE_INLINE int32x2_t vdup_n_s32(int32_t __a) { return __riscv_vmv_s_x_i32m1(__a, 2); }

FORCE_INLINE float32x2_t vdup_n_f32(float32_t __a) { return __riscv_vfmv_v_f_f32m1(__a, 2); }

FORCE_INLINE uint8x8_t vdup_n_u8(uint8_t __a) { return __riscv_vmv_s_x_u8m1(__a, 8); }

FORCE_INLINE uint16x4_t vdup_n_u16(uint16_t __a) { return __riscv_vmv_s_x_u16m1(__a, 4); }

FORCE_INLINE uint32x2_t vdup_n_u32(uint32_t __a) { return __riscv_vmv_s_x_u32m1(__a, 2); }

FORCE_INLINE int64x1_t vdup_n_s64(int64_t __a) { return __riscv_vmv_s_x_i64m1(__a, 1); }

FORCE_INLINE uint64x1_t vdup_n_u64(uint64_t __a) { return __riscv_vmv_s_x_u64m1(__a, 1); }

// FORCE_INLINE int8x16_t vdupq_n_s8(int8_t __a);

// FORCE_INLINE int16x8_t vdupq_n_s16(int16_t __a);

// FORCE_INLINE int32x4_t vdupq_n_s32(int32_t __a);

// FORCE_INLINE float32x4_t vdupq_n_f32(float32_t __a);

// FORCE_INLINE uint8x16_t vdupq_n_u8(uint8_t __a);

// FORCE_INLINE uint16x8_t vdupq_n_u16(uint16_t __a);

// FORCE_INLINE uint32x4_t vdupq_n_u32(uint32_t __a);

// FORCE_INLINE int64x2_t vdupq_n_s64(int64_t __a);

// FORCE_INLINE uint64x2_t vdupq_n_u64(uint64_t __a);

FORCE_INLINE int8x8_t vmov_n_s8(int8_t __a) { return vdup_n_s8(__a); }

// FORCE_INLINE int16x4_t vmov_n_s16(int16_t __a);

// FORCE_INLINE int32x2_t vmov_n_s32(int32_t __a);

// FORCE_INLINE float32x2_t vmov_n_f32(float32_t __a);

// FORCE_INLINE uint8x8_t vmov_n_u8(uint8_t __a);

// FORCE_INLINE uint16x4_t vmov_n_u16(uint16_t __a);

// FORCE_INLINE uint32x2_t vmov_n_u32(uint32_t __a);

// FORCE_INLINE int64x1_t vmov_n_s64(int64_t __a);

// FORCE_INLINE uint64x1_t vmov_n_u64(uint64_t __a);

// FORCE_INLINE int8x16_t vmovq_n_s8(int8_t __a);

// FORCE_INLINE int16x8_t vmovq_n_s16(int16_t __a);

// FORCE_INLINE int32x4_t vmovq_n_s32(int32_t __a);

// FORCE_INLINE float32x4_t vmovq_n_f32(float32_t __a);

// FORCE_INLINE uint8x16_t vmovq_n_u8(uint8_t __a);

// FORCE_INLINE uint16x8_t vmovq_n_u16(uint16_t __a);

// FORCE_INLINE uint32x4_t vmovq_n_u32(uint32_t __a);

// FORCE_INLINE int64x2_t vmovq_n_s64(int64_t __a);

// FORCE_INLINE uint64x2_t vmovq_n_u64(uint64_t __a);

FORCE_INLINE int8x8_t vdup_lane_s8(int8x8_t __a, const int __b) { return __riscv_vrgather_vx_i8m1(__a, __b, 8); }

// FORCE_INLINE int16x4_t vdup_lane_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32x2_t vdup_lane_s32(int32x2_t __a, const int __b);

// FORCE_INLINE float32x2_t vdup_lane_f32(float32x2_t __a, const int __b);

// FORCE_INLINE uint8x8_t vdup_lane_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16x4_t vdup_lane_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32x2_t vdup_lane_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE int64x1_t vdup_lane_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint64x1_t vdup_lane_u64(uint64x1_t __a, const int __b);

// FORCE_INLINE int8x16_t vdupq_lane_s8(int8x8_t __a, const int __b);

// FORCE_INLINE int16x8_t vdupq_lane_s16(int16x4_t __a, const int __b);

// FORCE_INLINE int32x4_t vdupq_lane_s32(int32x2_t __a, const int __b);

// FORCE_INLINE float32x4_t vdupq_lane_f32(float32x2_t __a, const int __b);

// FORCE_INLINE uint8x16_t vdupq_lane_u8(uint8x8_t __a, const int __b);

// FORCE_INLINE uint16x8_t vdupq_lane_u16(uint16x4_t __a, const int __b);

// FORCE_INLINE uint32x4_t vdupq_lane_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE int64x2_t vdupq_lane_s64(int64x1_t __a, const int __b);

// FORCE_INLINE uint64x2_t vdupq_lane_u64(uint64x1_t __a, const int __b);

FORCE_INLINE int8x16_t vcombine_s8(int8x8_t __a, int8x8_t __b) { return __riscv_vslideup_vx_i8m1(__a, __b, 8, 16); }

// FORCE_INLINE int16x8_t vcombine_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x4_t vcombine_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE int64x2_t vcombine_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE float32x4_t vcombine_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x16_t vcombine_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x8_t vcombine_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x4_t vcombine_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE uint64x2_t vcombine_u64(uint64x1_t __a, uint64x1_t __b);

FORCE_INLINE int8x8_t vget_high_s8(int8x16_t __a) { return __riscv_vslidedown_vx_i8m1(__a, 8, 16); }

// FORCE_INLINE int16x4_t vget_high_s16(int16x8_t __a);

// FORCE_INLINE int32x2_t vget_high_s32(int32x4_t __a);

// FORCE_INLINE int64x1_t vget_high_s64(int64x2_t __a);

// FORCE_INLINE float32x2_t vget_high_f32(float32x4_t __a);

// FORCE_INLINE uint8x8_t vget_high_u8(uint8x16_t __a);

// FORCE_INLINE uint16x4_t vget_high_u16(uint16x8_t __a);

// FORCE_INLINE uint32x2_t vget_high_u32(uint32x4_t __a);

// FORCE_INLINE uint64x1_t vget_high_u64(uint64x2_t __a);

FORCE_INLINE int8x8_t vget_low_s8(int8x16_t __a) { return __a; }

// FORCE_INLINE int16x4_t vget_low_s16(int16x8_t __a);

// FORCE_INLINE int32x2_t vget_low_s32(int32x4_t __a);

// FORCE_INLINE float32x2_t vget_low_f32(float32x4_t __a);

// FORCE_INLINE uint8x8_t vget_low_u8(uint8x16_t __a);

// FORCE_INLINE uint16x4_t vget_low_u16(uint16x8_t __a);

// FORCE_INLINE uint32x2_t vget_low_u32(uint32x4_t __a);

// FORCE_INLINE int64x1_t vget_low_s64(int64x2_t __a);

// FORCE_INLINE uint64x1_t vget_low_u64(uint64x2_t __a);

FORCE_INLINE int32x2_t vcvt_s32_f32(float32x2_t __a) { return __riscv_vfcvt_rtz_x_f_v_i32m1(__a, 8); }

FORCE_INLINE float32x2_t vcvt_f32_s32(int32x2_t __a) { return __riscv_vfcvt_f_x_v_f32m1(__a, 8); }

FORCE_INLINE float32x2_t vcvt_f32_u32(uint32x2_t __a) { return __riscv_vfcvt_f_xu_v_f32m1(__a, 8); }

FORCE_INLINE uint32x2_t vcvt_u32_f32(float32x2_t __a) { return __riscv_vfcvt_rtz_xu_f_v_u32m1(__a, 8); }

// FORCE_INLINE int32x4_t vcvtq_s32_f32(float32x4_t __a);

// FORCE_INLINE float32x4_t vcvtq_f32_s32(int32x4_t __a);

// FORCE_INLINE float32x4_t vcvtq_f32_u32(uint32x4_t __a);

// FORCE_INLINE uint32x4_t vcvtq_u32_f32(float32x4_t __a);

FORCE_INLINE int32x2_t vcvt_n_s32_f32(float32x2_t __a, const int __b) {
  vfloat32m1_t a_mul_pow2_b = __riscv_vfmul_vf_f32m1(__a, (uint64_t)1 << __b, 2);
  return __riscv_vfcvt_rtz_x_f_v_i32m1(a_mul_pow2_b, 2);
}

// FORCE_INLINE float32x2_t vcvt_n_f32_s32(int32x2_t __a, const int __b);

// FORCE_INLINE float32x2_t vcvt_n_f32_u32(uint32x2_t __a, const int __b);

// FORCE_INLINE uint32x2_t vcvt_n_u32_f32(float32x2_t __a, const int __b);

// FORCE_INLINE int32x4_t vcvtq_n_s32_f32(float32x4_t __a, const int __b);

// FORCE_INLINE float32x4_t vcvtq_n_f32_s32(int32x4_t __a, const int __b);

// FORCE_INLINE float32x4_t vcvtq_n_f32_u32(uint32x4_t __a, const int __b);

// FORCE_INLINE uint32x4_t vcvtq_n_u32_f32(float32x4_t __a, const int __b);

FORCE_INLINE int8x8_t vmovn_s16(int16x8_t __a) {
  uint8_t mask_arr[] = {85, 85};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 16);
  return __riscv_vcompress_vm_i8m1(__riscv_vreinterpret_v_i16m1_i8m1(__a), mask, 16);
}

// FORCE_INLINE int16x4_t vmovn_s32(int32x4_t __a);

// FORCE_INLINE int32x2_t vmovn_s64(int64x2_t __a);

// FORCE_INLINE uint8x8_t vmovn_u16(uint16x8_t __a);

// FORCE_INLINE uint16x4_t vmovn_u32(uint32x4_t __a);

// FORCE_INLINE uint32x2_t vmovn_u64(uint64x2_t __a);

FORCE_INLINE int8x8_t vqmovn_s16(int16x8_t __a) {
  return __riscv_vlmul_ext_v_i8mf2_i8m1(__riscv_vnclip_wx_i8mf2(__a, 0, NEON2RVV_ROUND_TYPE_RDN, 8));
}

// FORCE_INLINE int16x4_t vqmovn_s32(int32x4_t __a);

// FORCE_INLINE int32x2_t vqmovn_s64(int64x2_t __a);

// FORCE_INLINE uint8x8_t vqmovn_u16(uint16x8_t __a);

// FORCE_INLINE uint16x4_t vqmovn_u32(uint32x4_t __a);

// FORCE_INLINE uint32x2_t vqmovn_u64(uint64x2_t __a);

// FORCE_INLINE uint8x8_t vqmovun_s16(int16x8_t __a);

// FORCE_INLINE uint16x4_t vqmovun_s32(int32x4_t __a);

// FORCE_INLINE uint32x2_t vqmovun_s64(int64x2_t __a);

FORCE_INLINE int16x8_t vmovl_s8(int8x8_t __a) {
  return __riscv_vlmul_trunc_v_i16m2_i16m1(__riscv_vsext_vf2_i16m2(__a, 8));
}

// FORCE_INLINE int32x4_t vmovl_s16(int16x4_t __a);

// FORCE_INLINE int64x2_t vmovl_s32(int32x2_t __a);

// FORCE_INLINE uint16x8_t vmovl_u8(uint8x8_t __a);

// FORCE_INLINE uint32x4_t vmovl_u16(uint16x4_t __a);

// FORCE_INLINE uint64x2_t vmovl_u32(uint32x2_t __a);

FORCE_INLINE int8x8_t vtbl1_s8(int8x8_t __a, int8x8_t __b) {
  // TODO a better way to set the high half into zeros
  vint8m1_t a_s = __riscv_vslidedown_vx_i8m1(__riscv_vslideup_vx_i8m1(__a, __a, 8, 16), 8, 16);
  return __riscv_vrgather_vv_i8m1(a_s, __riscv_vreinterpret_v_i8m1_u8m1(__b), 8);
}

// FORCE_INLINE uint8x8_t vtbl1_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE int8x8_t vtbl2_s8(int8x8x2_t __a, int8x8_t __b);

// FORCE_INLINE uint8x8_t vtbl2_u8(uint8x8x2_t __a, uint8x8_t __b);

// FORCE_INLINE int8x8_t vtbl3_s8(int8x8x3_t __a, int8x8_t __b);

// FORCE_INLINE uint8x8_t vtbl3_u8(uint8x8x3_t __a, uint8x8_t __b);

// FORCE_INLINE int8x8_t vtbl4_s8(int8x8x4_t __a, int8x8_t __b);

// FORCE_INLINE uint8x8_t vtbl4_u8(uint8x8x4_t __a, uint8x8_t __b);

FORCE_INLINE int8x8_t vtbx1_s8(int8x8_t __a, int8x8_t __b, int8x8_t __c) {
  // TODO a better way to set the high half into zeros
  vint8m1_t b_s = __riscv_vslidedown_vx_i8m1(__riscv_vslideup_vx_i8m1(__b, __b, 8, 16), 8, 16);
  vint8m1_t b_unbound = __riscv_vrgather_vv_i8m1(b_s, __riscv_vreinterpret_v_i8m1_u8m1(__c), 8);
  vbool8_t gt_mask = __riscv_vmsgt_vx_i8m1_b8(__c, 7, 8);
  vbool8_t lt_mask = __riscv_vmslt_vx_i8m1_b8(__c, 0, 8);
  vbool8_t out_range_mask = __riscv_vmor_mm_b8(gt_mask, lt_mask, 8);
  return __riscv_vmerge_vvm_i8m1(b_unbound, __a, out_range_mask, 8);
}

// FORCE_INLINE uint8x8_t vtbx1_u8(uint8x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE int8x8_t vtbx2_s8(int8x8_t __a, int8x8x2_t __b, int8x8_t __c);

// FORCE_INLINE uint8x8_t vtbx2_u8(uint8x8_t __a, uint8x8x2_t __b, uint8x8_t __c);

// FORCE_INLINE int8x8_t vtbx3_s8(int8x8_t __a, int8x8x3_t __b, int8x8_t __c);

// FORCE_INLINE uint8x8_t vtbx3_u8(uint8x8_t __a, uint8x8x3_t __b, uint8x8_t __c);

// FORCE_INLINE int8x8_t vtbx4_s8(int8x8_t __a, int8x8x4_t __b, int8x8_t __c);

// FORCE_INLINE uint8x8_t vtbx4_u8(uint8x8_t __a, uint8x8x4_t __b, uint8x8_t __c);

FORCE_INLINE int16x4_t vmul_lane_s16(int16x4_t __a, int16x4_t __b, const int __c) {
  vint16m1_t b_dup_lane = __riscv_vrgather_vx_i16m1(__b, __c, 4);
  return __riscv_vmul_vv_i16m1(__a, b_dup_lane, 4);
}

// FORCE_INLINE int32x2_t vmul_lane_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE float32x2_t vmul_lane_f32(float32x2_t __a, float32x2_t __b, const int __c);

// FORCE_INLINE uint16x4_t vmul_lane_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vmul_lane_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE int16x8_t vmulq_lane_s16(int16x8_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x4_t vmulq_lane_s32(int32x4_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE float32x4_t vmulq_lane_f32(float32x4_t __a, float32x2_t __b, const int __c);

// FORCE_INLINE uint16x8_t vmulq_lane_u16(uint16x8_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x4_t vmulq_lane_u32(uint32x4_t __a, uint32x2_t __b, const int __c);

FORCE_INLINE int16x4_t vmla_lane_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c, const int __d) {
  vint16m1_t c_dup_lane = __riscv_vrgather_vx_i16m1(__c, __d, 4);
  return __riscv_vmacc_vv_i16m1(__a, __b, c_dup_lane, 8);
}

// FORCE_INLINE int32x2_t vmla_lane_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE float32x2_t vmla_lane_f32(float32x2_t __a, float32x2_t __b, float32x2_t __c, const int __d);

// FORCE_INLINE uint16x4_t vmla_lane_u16(uint16x4_t __a, uint16x4_t __b, uint16x4_t __c, const int __d);

// FORCE_INLINE uint32x2_t vmla_lane_u32(uint32x2_t __a, uint32x2_t __b, uint32x2_t __c, const int __d);

// FORCE_INLINE int16x8_t vmlaq_lane_s16(int16x8_t __a, int16x8_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x4_t vmlaq_lane_s32(int32x4_t __a, int32x4_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE float32x4_t vmlaq_lane_f32(float32x4_t __a, float32x4_t __b, float32x2_t __c, const int __d);

// FORCE_INLINE uint16x8_t vmlaq_lane_u16(uint16x8_t __a, uint16x8_t __b, uint16x4_t __c, const int __d);

// FORCE_INLINE uint32x4_t vmlaq_lane_u32(uint32x4_t __a, uint32x4_t __b, uint32x2_t __c, const int __d);

FORCE_INLINE int32x4_t vmlal_lane_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c, const int __d) {
  vint16m1_t c_dup = __riscv_vrgather_vx_i16m1(__c, __d, 4);
  return __riscv_vlmul_trunc_v_i32m2_i32m1(
      __riscv_vwmacc_vv_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(__a), __b, c_dup, 4));
}

// FORCE_INLINE int64x2_t vmlal_lane_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE uint32x4_t vmlal_lane_u16(uint32x4_t __a, uint16x4_t __b, uint16x4_t __c, const int __d);

// FORCE_INLINE uint64x2_t vmlal_lane_u32(uint64x2_t __a, uint32x2_t __b, uint32x2_t __c, const int __d);

// FORCE_INLINE int32x4_t vqdmlal_lane_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int64x2_t vqdmlal_lane_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE int16x4_t vmls_lane_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x2_t vmls_lane_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE float32x2_t vmls_lane_f32(float32x2_t __a, float32x2_t __b, float32x2_t __c, const int __d);

// FORCE_INLINE uint16x4_t vmls_lane_u16(uint16x4_t __a, uint16x4_t __b, uint16x4_t __c, const int __d);

// FORCE_INLINE uint32x2_t vmls_lane_u32(uint32x2_t __a, uint32x2_t __b, uint32x2_t __c, const int __d);

// FORCE_INLINE int16x8_t vmlsq_lane_s16(int16x8_t __a, int16x8_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x4_t vmlsq_lane_s32(int32x4_t __a, int32x4_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE float32x4_t vmlsq_lane_f32(float32x4_t __a, float32x4_t __b, float32x2_t __c, const int __d);

// FORCE_INLINE uint16x8_t vmlsq_lane_u16(uint16x8_t __a, uint16x8_t __b, uint16x4_t __c, const int __d);

// FORCE_INLINE uint32x4_t vmlsq_lane_u32(uint32x4_t __a, uint32x4_t __b, uint32x2_t __c, const int __d);

// FORCE_INLINE int32x4_t vmlsl_lane_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int64x2_t vmlsl_lane_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE uint32x4_t vmlsl_lane_u16(uint32x4_t __a, uint16x4_t __b, uint16x4_t __c, const int __d);

// FORCE_INLINE uint64x2_t vmlsl_lane_u32(uint64x2_t __a, uint32x2_t __b, uint32x2_t __c, const int __d);

// FORCE_INLINE int32x4_t vqdmlsl_lane_s16(int32x4_t __a, int16x4_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int64x2_t vqdmlsl_lane_s32(int64x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE int32x4_t vmull_lane_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vmull_lane_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE uint32x4_t vmull_lane_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint64x2_t vmull_lane_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE int32x4_t vqdmull_lane_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vqdmull_lane_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int16x8_t vqdmulhq_lane_s16(int16x8_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x4_t vqdmulhq_lane_s32(int32x4_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int16x4_t vqdmulh_lane_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vqdmulh_lane_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int16x8_t vqrdmulhq_lane_s16(int16x8_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x4_t vqrdmulhq_lane_s32(int32x4_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int16x4_t vqrdmulh_lane_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vqrdmulh_lane_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int16x8_t vqrdmlahq_lane_s16(int16x8_t __a, int16x8_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x4_t vqrdmlahq_lane_s32(int32x4_t __a, int32x4_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE int16x4_t vqrdmlah_lane_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x2_t vqrdmlah_lane_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE int16x8_t vqrdmlshq_lane_s16(int16x8_t __a, int16x8_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x4_t vqrdmlshq_lane_s32(int32x4_t __a, int32x4_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE int16x4_t vqrdmlsh_lane_s16(int16x4_t __a, int16x4_t __b, int16x4_t __c, const int __d);

// FORCE_INLINE int32x2_t vqrdmlsh_lane_s32(int32x2_t __a, int32x2_t __b, int32x2_t __c, const int __d);

// FORCE_INLINE int16x4_t vmul_n_s16(int16x4_t __a, int16_t __b);

// FORCE_INLINE int32x2_t vmul_n_s32(int32x2_t __a, int32_t __b);

// FORCE_INLINE float32x2_t vmul_n_f32(float32x2_t __a, float32_t __b);

// FORCE_INLINE uint16x4_t vmul_n_u16(uint16x4_t __a, uint16_t __b);

// FORCE_INLINE uint32x2_t vmul_n_u32(uint32x2_t __a, uint32_t __b);

// FORCE_INLINE int16x8_t vmulq_n_s16(int16x8_t __a, int16_t __b);

// FORCE_INLINE int32x4_t vmulq_n_s32(int32x4_t __a, int32_t __b);

// FORCE_INLINE float32x4_t vmulq_n_f32(float32x4_t __a, float32_t __b);

// FORCE_INLINE uint16x8_t vmulq_n_u16(uint16x8_t __a, uint16_t __b);

// FORCE_INLINE uint32x4_t vmulq_n_u32(uint32x4_t __a, uint32_t __b);

// FORCE_INLINE int32x4_t vmull_n_s16(int16x4_t __a, int16_t __b);

// FORCE_INLINE int64x2_t vmull_n_s32(int32x2_t __a, int32_t __b);

// FORCE_INLINE uint32x4_t vmull_n_u16(uint16x4_t __a, uint16_t __b);

// FORCE_INLINE uint64x2_t vmull_n_u32(uint32x2_t __a, uint32_t __b);

// FORCE_INLINE int32x4_t vqdmull_n_s16(int16x4_t __a, int16_t __b);

// FORCE_INLINE int64x2_t vqdmull_n_s32(int32x2_t __a, int32_t __b);

// FORCE_INLINE int16x8_t vqdmulhq_n_s16(int16x8_t __a, int16_t __b);

// FORCE_INLINE int32x4_t vqdmulhq_n_s32(int32x4_t __a, int32_t __b);

// FORCE_INLINE int16x4_t vqdmulh_n_s16(int16x4_t __a, int16_t __b);

// FORCE_INLINE int32x2_t vqdmulh_n_s32(int32x2_t __a, int32_t __b);

// FORCE_INLINE int16x8_t vqrdmulhq_n_s16(int16x8_t __a, int16_t __b);

// FORCE_INLINE int32x4_t vqrdmulhq_n_s32(int32x4_t __a, int32_t __b);

// FORCE_INLINE int16x4_t vqrdmulh_n_s16(int16x4_t __a, int16_t __b);

// FORCE_INLINE int32x2_t vqrdmulh_n_s32(int32x2_t __a, int32_t __b);

FORCE_INLINE int16x4_t vmla_n_s16(int16x4_t __a, int16x4_t __b, int16_t __c) {
  return __riscv_vmacc_vx_i16m1(__a, __c, __b, 4);
}

// FORCE_INLINE int32x2_t vmla_n_s32(int32x2_t __a, int32x2_t __b, int32_t __c);

// FORCE_INLINE float32x2_t vmla_n_f32(float32x2_t __a, float32x2_t __b, float32_t __c);

// FORCE_INLINE uint16x4_t vmla_n_u16(uint16x4_t __a, uint16x4_t __b, uint16_t __c);

// FORCE_INLINE uint32x2_t vmla_n_u32(uint32x2_t __a, uint32x2_t __b, uint32_t __c);

// FORCE_INLINE int16x8_t vmlaq_n_s16(int16x8_t __a, int16x8_t __b, int16_t __c);

// FORCE_INLINE int32x4_t vmlaq_n_s32(int32x4_t __a, int32x4_t __b, int32_t __c);

// FORCE_INLINE float32x4_t vmlaq_n_f32(float32x4_t __a, float32x4_t __b, float32_t __c);

// FORCE_INLINE uint16x8_t vmlaq_n_u16(uint16x8_t __a, uint16x8_t __b, uint16_t __c);

// FORCE_INLINE uint32x4_t vmlaq_n_u32(uint32x4_t __a, uint32x4_t __b, uint32_t __c);

// FORCE_INLINE int32x4_t vmlal_n_s16(int32x4_t __a, int16x4_t __b, int16_t __c);

// FORCE_INLINE int64x2_t vmlal_n_s32(int64x2_t __a, int32x2_t __b, int32_t __c);

// FORCE_INLINE uint32x4_t vmlal_n_u16(uint32x4_t __a, uint16x4_t __b, uint16_t __c);

// FORCE_INLINE uint64x2_t vmlal_n_u32(uint64x2_t __a, uint32x2_t __b, uint32_t __c);

// FORCE_INLINE int32x4_t vqdmlal_n_s16(int32x4_t __a, int16x4_t __b, int16_t __c);

// FORCE_INLINE int64x2_t vqdmlal_n_s32(int64x2_t __a, int32x2_t __b, int32_t __c);

// FORCE_INLINE int16x4_t vmls_n_s16(int16x4_t __a, int16x4_t __b, int16_t __c);

// FORCE_INLINE int32x2_t vmls_n_s32(int32x2_t __a, int32x2_t __b, int32_t __c);

// FORCE_INLINE float32x2_t vmls_n_f32(float32x2_t __a, float32x2_t __b, float32_t __c);

// FORCE_INLINE uint16x4_t vmls_n_u16(uint16x4_t __a, uint16x4_t __b, uint16_t __c);

// FORCE_INLINE uint32x2_t vmls_n_u32(uint32x2_t __a, uint32x2_t __b, uint32_t __c);

// FORCE_INLINE int16x8_t vmlsq_n_s16(int16x8_t __a, int16x8_t __b, int16_t __c);

// FORCE_INLINE int32x4_t vmlsq_n_s32(int32x4_t __a, int32x4_t __b, int32_t __c);

// FORCE_INLINE float32x4_t vmlsq_n_f32(float32x4_t __a, float32x4_t __b, float32_t __c);

// FORCE_INLINE uint16x8_t vmlsq_n_u16(uint16x8_t __a, uint16x8_t __b, uint16_t __c);

// FORCE_INLINE uint32x4_t vmlsq_n_u32(uint32x4_t __a, uint32x4_t __b, uint32_t __c);

// FORCE_INLINE int32x4_t vmlsl_n_s16(int32x4_t __a, int16x4_t __b, int16_t __c);

// FORCE_INLINE int64x2_t vmlsl_n_s32(int64x2_t __a, int32x2_t __b, int32_t __c);

// FORCE_INLINE uint32x4_t vmlsl_n_u16(uint32x4_t __a, uint16x4_t __b, uint16_t __c);

// FORCE_INLINE uint64x2_t vmlsl_n_u32(uint64x2_t __a, uint32x2_t __b, uint32_t __c);

// FORCE_INLINE int32x4_t vqdmlsl_n_s16(int32x4_t __a, int16x4_t __b, int16_t __c);

// FORCE_INLINE int64x2_t vqdmlsl_n_s32(int64x2_t __a, int32x2_t __b, int32_t __c);

FORCE_INLINE int8x8_t vext_s8(int8x8_t __a, int8x8_t __b, const int __c) {
  vint8m1_t a_slidedown = __riscv_vslidedown_vx_i8m1(__a, __c, 8);
  return __riscv_vslideup_vx_i8m1(a_slidedown, __b, 8 - __c, 8);
}

// FORCE_INLINE int16x4_t vext_s16(int16x4_t __a, int16x4_t __b, const int __c);

// FORCE_INLINE int32x2_t vext_s32(int32x2_t __a, int32x2_t __b, const int __c);

// FORCE_INLINE int64x1_t vext_s64(int64x1_t __a, int64x1_t __b, const int __c);

// FORCE_INLINE float32x2_t vext_f32(float32x2_t __a, float32x2_t __b, const int __c);

// FORCE_INLINE uint8x8_t vext_u8(uint8x8_t __a, uint8x8_t __b, const int __c);

// FORCE_INLINE uint16x4_t vext_u16(uint16x4_t __a, uint16x4_t __b, const int __c);

// FORCE_INLINE uint32x2_t vext_u32(uint32x2_t __a, uint32x2_t __b, const int __c);

// FORCE_INLINE uint64x1_t vext_u64(uint64x1_t __a, uint64x1_t __b, const int __c);

// FORCE_INLINE int8x16_t vextq_s8(int8x16_t __a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vextq_s16(int16x8_t __a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vextq_s32(int32x4_t __a, int32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vextq_s64(int64x2_t __a, int64x2_t __b, const int __c);

// FORCE_INLINE float32x4_t vextq_f32(float32x4_t __a, float32x4_t __b, const int __c);

// FORCE_INLINE uint8x16_t vextq_u8(uint8x16_t __a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vextq_u16(uint16x8_t __a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vextq_u32(uint32x4_t __a, uint32x4_t __b, const int __c);

// FORCE_INLINE uint64x2_t vextq_u64(uint64x2_t __a, uint64x2_t __b, const int __c);

FORCE_INLINE int8x8_t vrev64_s8(int8x8_t __a) {
  uint8_t shuffle_indices_arr[] = {7, 6, 5, 4, 3, 2, 1, 0};
  vuint8m1_t shuffle_indices = __riscv_vle8_v_u8m1(shuffle_indices_arr, 8);
  return __riscv_vrgather_vv_i8m1(__a, shuffle_indices, 8);
}

// FORCE_INLINE int16x4_t vrev64_s16(int16x4_t __a);

// FORCE_INLINE int32x2_t vrev64_s32(int32x2_t __a);

// FORCE_INLINE float32x2_t vrev64_f32(float32x2_t __a);

// FORCE_INLINE uint8x8_t vrev64_u8(uint8x8_t __a);

// FORCE_INLINE uint16x4_t vrev64_u16(uint16x4_t __a);

// FORCE_INLINE uint32x2_t vrev64_u32(uint32x2_t __a);

// FORCE_INLINE int8x16_t vrev64q_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vrev64q_s16(int16x8_t __a);

// FORCE_INLINE int32x4_t vrev64q_s32(int32x4_t __a);

// FORCE_INLINE float32x4_t vrev64q_f32(float32x4_t __a);

// FORCE_INLINE uint8x16_t vrev64q_u8(uint8x16_t __a);

// FORCE_INLINE uint16x8_t vrev64q_u16(uint16x8_t __a);

// FORCE_INLINE uint32x4_t vrev64q_u32(uint32x4_t __a);

// FORCE_INLINE int8x8_t vrev32_s8(int8x8_t __a);

// FORCE_INLINE int16x4_t vrev32_s16(int16x4_t __a);

// FORCE_INLINE uint8x8_t vrev32_u8(uint8x8_t __a);

// FORCE_INLINE uint16x4_t vrev32_u16(uint16x4_t __a);

// FORCE_INLINE int8x16_t vrev32q_s8(int8x16_t __a);

// FORCE_INLINE int16x8_t vrev32q_s16(int16x8_t __a);

// FORCE_INLINE uint8x16_t vrev32q_u8(uint8x16_t __a);

// FORCE_INLINE uint16x8_t vrev32q_u16(uint16x8_t __a);

// FORCE_INLINE int8x8_t vrev16_s8(int8x8_t __a);

// FORCE_INLINE uint8x8_t vrev16_u8(uint8x8_t __a);

// FORCE_INLINE int8x16_t vrev16q_s8(int8x16_t __a);

// FORCE_INLINE uint8x16_t vrev16q_u8(uint8x16_t __a);

FORCE_INLINE int8x8_t vbsl_s8(uint8x8_t __a, int8x8_t __b, int8x8_t __c) {
  return __riscv_vxor_vv_i8m1(
      __riscv_vand_vv_i8m1(__riscv_vxor_vv_i8m1(__c, __b, 8), __riscv_vreinterpret_v_u8m1_i8m1(__a), 8), __c, 8);
}

// FORCE_INLINE int16x4_t vbsl_s16(uint16x4_t __a, int16x4_t __b, int16x4_t __c);

// FORCE_INLINE int32x2_t vbsl_s32(uint32x2_t __a, int32x2_t __b, int32x2_t __c);

// FORCE_INLINE int64x1_t vbsl_s64(uint64x1_t __a, int64x1_t __b, int64x1_t __c);

// FORCE_INLINE float32x2_t vbsl_f32(uint32x2_t __a, float32x2_t __b, float32x2_t __c);

// FORCE_INLINE uint8x8_t vbsl_u8(uint8x8_t __a, uint8x8_t __b, uint8x8_t __c);

// FORCE_INLINE uint16x4_t vbsl_u16(uint16x4_t __a, uint16x4_t __b, uint16x4_t __c);

// FORCE_INLINE uint32x2_t vbsl_u32(uint32x2_t __a, uint32x2_t __b, uint32x2_t __c);

// FORCE_INLINE uint64x1_t vbsl_u64(uint64x1_t __a, uint64x1_t __b, uint64x1_t __c);

// FORCE_INLINE int8x16_t vbslq_s8(uint8x16_t __a, int8x16_t __b, int8x16_t __c);

// FORCE_INLINE int16x8_t vbslq_s16(uint16x8_t __a, int16x8_t __b, int16x8_t __c);

// FORCE_INLINE int32x4_t vbslq_s32(uint32x4_t __a, int32x4_t __b, int32x4_t __c);

// FORCE_INLINE int64x2_t vbslq_s64(uint64x2_t __a, int64x2_t __b, int64x2_t __c);

// FORCE_INLINE float32x4_t vbslq_f32(uint32x4_t __a, float32x4_t __b, float32x4_t __c);

// FORCE_INLINE uint8x16_t vbslq_u8(uint8x16_t __a, uint8x16_t __b, uint8x16_t __c);

// FORCE_INLINE uint16x8_t vbslq_u16(uint16x8_t __a, uint16x8_t __b, uint16x8_t __c);

// FORCE_INLINE uint32x4_t vbslq_u32(uint32x4_t __a, uint32x4_t __b, uint32x4_t __c);

// FORCE_INLINE uint64x2_t vbslq_u64(uint64x2_t __a, uint64x2_t __b, uint64x2_t __c);

FORCE_INLINE int8x8x2_t vtrn_s8(int8x8_t __a, int8x8_t __b) {
  vuint16m1_t a_u16 = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vreinterpret_v_i8m1_i16m1(__a));
  vuint16m1_t b_u16 = __riscv_vreinterpret_v_i16m1_u16m1(__riscv_vreinterpret_v_i8m1_i16m1(__b));

  vuint8m1_t a1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(__riscv_vsll_vx_u16m1(a_u16, 8, 4), 8, 4));
  vuint8m1_t b1 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(b_u16, 8, 4));
  vint8m1_t trn1 = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vor_vv_u8m1(a1, b1, 8));

  vuint8m1_t a2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsrl_vx_u16m1(a_u16, 8, 4));
  vuint8m1_t b2 = __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vsll_vx_u16m1(__riscv_vsrl_vx_u16m1(b_u16, 8, 4), 8, 4));
  vint8m1_t trn2 = __riscv_vreinterpret_v_u8m1_i8m1(__riscv_vor_vv_u8m1(a2, b2, 8));
  return __riscv_vcreate_v_i8m1x2(trn1, trn2);
}

// FORCE_INLINE int16x4x2_t vtrn_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint8x8x2_t vtrn_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4x2_t vtrn_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE int32x2x2_t vtrn_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2x2_t vtrn_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint32x2x2_t vtrn_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16x2_t vtrnq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8x2_t vtrnq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4x2_t vtrnq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4x2_t vtrnq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16x2_t vtrnq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8x2_t vtrnq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4x2_t vtrnq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8x2_t vzip_s8(int8x8_t __a, int8x8_t __b) {
  // TODO add explaination. source:
  // https://github.com/riscv-non-isa/rvv-intrinsic-doc/issues/289#issuecomment-1781385001
  uint8x8_t a_u8 = __riscv_vreinterpret_v_i8m1_u8m1(__a);
  uint8x8_t b_u8 = __riscv_vreinterpret_v_i8m1_u8m1(__b);
  vuint16m2_t ab_waddu = __riscv_vwaddu_vv_u16m2(a_u8, b_u8, 8);
  vuint16m2_t res_m2 = __riscv_vwmaccu_vx_u16m2(ab_waddu, 0xff, b_u8, 8);
  vint8m1_t res =
      __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vreinterpret_v_u16m1_i16m1(__riscv_vlmul_trunc_v_u16m2_u16m1(res_m2)));
  return __riscv_vcreate_v_i8m1x2(res, __riscv_vslidedown_vx_i8m1(res, 8, 16));
}

// FORCE_INLINE int16x4x2_t vzip_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE uint8x8x2_t vzip_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4x2_t vzip_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE int32x2x2_t vzip_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2x2_t vzip_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint32x2x2_t vzip_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16x2_t vzipq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8x2_t vzipq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4x2_t vzipq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4x2_t vzipq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16x2_t vzipq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8x2_t vzipq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4x2_t vzipq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8x2_t vuzp_s8(int8x8_t __a, int8x8_t __b) {
  uint8_t mask_arr[] = {85, 85};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 16);
  vint8m1_t ab = __riscv_vslideup_vx_i8m1(__a, __b, 8, 16);
  vint8m1_t ab_s_down = __riscv_vslide1down_vx_i8m1(ab, 0, 16);
  vint8m1_t res_low = __riscv_vcompress_vm_i8m1(ab, mask, 16);
  vint8m1_t res_high = __riscv_vcompress_vm_i8m1(ab_s_down, mask, 16);
  return __riscv_vcreate_v_i8m1x2(res_low, res_high);
}

// FORCE_INLINE int16x4x2_t vuzp_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2x2_t vuzp_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE float32x2x2_t vuzp_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE uint8x8x2_t vuzp_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4x2_t vuzp_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2x2_t vuzp_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int8x16x2_t vuzpq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8x2_t vuzpq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4x2_t vuzpq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE float32x4x2_t vuzpq_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE uint8x16x2_t vuzpq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8x2_t vuzpq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4x2_t vuzpq_u32(uint32x4_t __a, uint32x4_t __b);

FORCE_INLINE int8x8_t vld1_s8(const int8_t *__a) { return __riscv_vle8_v_i8m1(__a, 8); }

FORCE_INLINE int16x4_t vld1_s16(const int16_t *__a) { return __riscv_vle16_v_i16m1(__a, 4); }

FORCE_INLINE int32x2_t vld1_s32(const int32_t *__a) { return __riscv_vle32_v_i32m1(__a, 2); }

FORCE_INLINE int64x1_t vld1_s64(const int64_t *__a) { return __riscv_vle64_v_i64m1(__a, 1); }

FORCE_INLINE float32x2_t vld1_f32(const float32_t *__a) { return __riscv_vle32_v_f32m1(__a, 2); }

FORCE_INLINE uint8x8_t vld1_u8(const uint8_t *__a) { return __riscv_vle8_v_u8m1(__a, 8); }

FORCE_INLINE uint16x4_t vld1_u16(const uint16_t *__a) { return __riscv_vle16_v_u16m1(__a, 4); }

FORCE_INLINE uint32x2_t vld1_u32(const uint32_t *__a) { return __riscv_vle32_v_u32m1(__a, 2); }

FORCE_INLINE uint64x1_t vld1_u64(const uint64_t *__a) { return __riscv_vle64_v_u64m1(__a, 1); }

FORCE_INLINE int8x16_t vld1q_s8(const int8_t *__a) { return __riscv_vle8_v_i8m1(__a, 16); }

FORCE_INLINE int16x8_t vld1q_s16(const int16_t *__a) { return __riscv_vle16_v_i16m1(__a, 8); }

FORCE_INLINE int32x4_t vld1q_s32(const int32_t *__a) { return __riscv_vle32_v_i32m1(__a, 4); }

FORCE_INLINE int64x2_t vld1q_s64(const int64_t *__a) { return __riscv_vle64_v_i64m1(__a, 2); }

FORCE_INLINE float32x4_t vld1q_f32(const float32_t *__a) { return __riscv_vle32_v_f32m1(__a, 4); }

FORCE_INLINE uint8x16_t vld1q_u8(const uint8_t *__a) { return __riscv_vle8_v_u8m1(__a, 16); }

FORCE_INLINE uint16x8_t vld1q_u16(const uint16_t *__a) { return __riscv_vle16_v_u16m1(__a, 8); }

FORCE_INLINE uint32x4_t vld1q_u32(const uint32_t *__a) { return __riscv_vle32_v_u32m1(__a, 4); }

FORCE_INLINE uint64x2_t vld1q_u64(const uint64_t *__a) { return __riscv_vle64_v_u64m1(__a, 2); }

FORCE_INLINE int8x8_t vld1_lane_s8(const int8_t *__a, int8x8_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 1);
  vint8m1_t a_dup = vdup_n_s8(__a[0]);
  return __riscv_vmerge_vvm_i8m1(__b, a_dup, mask, 8);
}

FORCE_INLINE int16x4_t vld1_lane_s16(const int16_t *__a, int16x4_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool16_t mask = __riscv_vlm_v_b16(mask_arr, 1);
  vint16m1_t a_dup = vdup_n_s16(__a[0]);
  return __riscv_vmerge_vvm_i16m1(__b, a_dup, mask, 8);
}

FORCE_INLINE int32x2_t vld1_lane_s32(const int32_t *__a, int32x2_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool32_t mask = __riscv_vlm_v_b32(mask_arr, 1);
  vint32m1_t a_dup = vdup_n_s32(__a[0]);
  return __riscv_vmerge_vvm_i32m1(__b, a_dup, mask, 8);
}

FORCE_INLINE float32x2_t vld1_lane_f32(const float32_t *__a, float32x2_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool32_t mask = __riscv_vlm_v_b32(mask_arr, 1);
  vfloat32m1_t a_dup = vdup_n_f32(__a[0]);
  return __riscv_vmerge_vvm_f32m1(__b, a_dup, mask, 8);
}

FORCE_INLINE uint8x8_t vld1_lane_u8(const uint8_t *__a, uint8x8_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 1);
  vuint8m1_t a_dup = vdup_n_u8(__a[0]);
  return __riscv_vmerge_vvm_u8m1(__b, a_dup, mask, 8);
}

FORCE_INLINE uint16x4_t vld1_lane_u16(const uint16_t *__a, uint16x4_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool16_t mask = __riscv_vlm_v_b16(mask_arr, 1);
  vuint16m1_t a_dup = vdup_n_u16(__a[0]);
  return __riscv_vmerge_vvm_u16m1(__b, a_dup, mask, 8);
}

FORCE_INLINE uint32x2_t vld1_lane_u32(const uint32_t *__a, uint32x2_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool32_t mask = __riscv_vlm_v_b32(mask_arr, 1);
  vuint32m1_t a_dup = vdup_n_u32(__a[0]);
  return __riscv_vmerge_vvm_u32m1(__b, a_dup, mask, 8);
}

FORCE_INLINE int64x1_t vld1_lane_s64(const int64_t *__a, int64x1_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool64_t mask = __riscv_vlm_v_b64(mask_arr, 1);
  vint64m1_t a_dup = vdup_n_s64(__a[0]);
  return __riscv_vmerge_vvm_i64m1(__b, a_dup, mask, 8);
}

FORCE_INLINE uint64x1_t vld1_lane_u64(const uint64_t *__a, uint64x1_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool64_t mask = __riscv_vlm_v_b64(mask_arr, 1);
  vuint64m1_t a_dup = vdup_n_u64(__a[0]);
  return __riscv_vmerge_vvm_u64m1(__b, a_dup, mask, 8);
}

// FORCE_INLINE int8x16_t vld1q_lane_s8(const int8_t *__a, int8x16_t __b, const int __c);

// FORCE_INLINE int16x8_t vld1q_lane_s16(const int16_t *__a, int16x8_t __b, const int __c);

// FORCE_INLINE int32x4_t vld1q_lane_s32(const int32_t *__a, int32x4_t __b, const int __c);

// FORCE_INLINE float32x4_t vld1q_lane_f32(const float32_t *__a, float32x4_t __b, const int __c);

// FORCE_INLINE uint8x16_t vld1q_lane_u8(const uint8_t *__a, uint8x16_t __b, const int __c);

// FORCE_INLINE uint16x8_t vld1q_lane_u16(const uint16_t *__a, uint16x8_t __b, const int __c);

// FORCE_INLINE uint32x4_t vld1q_lane_u32(const uint32_t *__a, uint32x4_t __b, const int __c);

// FORCE_INLINE int64x2_t vld1q_lane_s64(const int64_t *__a, int64x2_t __b, const int __c);

// FORCE_INLINE uint64x2_t vld1q_lane_u64(const uint64_t *__a, uint64x2_t __b, const int __c);

FORCE_INLINE int8x8_t vld1_dup_s8(const int8_t *__a) { return vdup_n_s8(__a[0]); }

// FORCE_INLINE int16x4_t vld1_dup_s16(const int16_t *__a);

// FORCE_INLINE int32x2_t vld1_dup_s32(const int32_t *__a);

// FORCE_INLINE float32x2_t vld1_dup_f32(const float32_t *__a);

// FORCE_INLINE uint8x8_t vld1_dup_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4_t vld1_dup_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2_t vld1_dup_u32(const uint32_t *__a);

// FORCE_INLINE int64x1_t vld1_dup_s64(const int64_t *__a);

// FORCE_INLINE uint64x1_t vld1_dup_u64(const uint64_t *__a);

// FORCE_INLINE int8x16_t vld1q_dup_s8(const int8_t *__a);

// FORCE_INLINE int16x8_t vld1q_dup_s16(const int16_t *__a);

// FORCE_INLINE int32x4_t vld1q_dup_s32(const int32_t *__a);

// FORCE_INLINE float32x4_t vld1q_dup_f32(const float32_t *__a);

// FORCE_INLINE uint8x16_t vld1q_dup_u8(const uint8_t *__a);

// FORCE_INLINE uint16x8_t vld1q_dup_u16(const uint16_t *__a);

// FORCE_INLINE uint32x4_t vld1q_dup_u32(const uint32_t *__a);

// FORCE_INLINE int64x2_t vld1q_dup_s64(const int64_t *__a);

// FORCE_INLINE uint64x2_t vld1q_dup_u64(const uint64_t *__a);

FORCE_INLINE void vst1_s8(int8_t *__a, int8x8_t __b) { return __riscv_vse8_v_i8m1(__a, __b, 8); }

// FORCE_INLINE void vst1_s16(int16_t *__a, int16x4_t __b);

// FORCE_INLINE void vst1_s32(int32_t *__a, int32x2_t __b);

// FORCE_INLINE void vst1_s64(int64_t *__a, int64x1_t __b);

// FORCE_INLINE void vst1_f32(float32_t *__a, float32x2_t __b);

// FORCE_INLINE void vst1_u8(uint8_t *__a, uint8x8_t __b);

// FORCE_INLINE void vst1_u16(uint16_t *__a, uint16x4_t __b);

// FORCE_INLINE void vst1_u32(uint32_t *__a, uint32x2_t __b);

// FORCE_INLINE void vst1_u64(uint64_t *__a, uint64x1_t __b);

// FORCE_INLINE void vst1q_s8(int8_t *__a, int8x16_t __b);

// FORCE_INLINE void vst1q_s16(int16_t *__a, int16x8_t __b);

// FORCE_INLINE void vst1q_s32(int32_t *__a, int32x4_t __b);

// FORCE_INLINE void vst1q_s64(int64_t *__a, int64x2_t __b);

// FORCE_INLINE void vst1q_f32(float32_t *__a, float32x4_t __b);

// FORCE_INLINE void vst1q_u8(uint8_t *__a, uint8x16_t __b);

// FORCE_INLINE void vst1q_u16(uint16_t *__a, uint16x8_t __b);

// FORCE_INLINE void vst1q_u32(uint32_t *__a, uint32x4_t __b);

// FORCE_INLINE void vst1q_u64(uint64_t *__a, uint64x2_t __b);

FORCE_INLINE void vst1_lane_s8(int8_t *__a, int8x8_t __b, const int __c) {
  const uint8_t mask_arr[] = {1};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 2);
  int8x8_t b_s = __riscv_vslidedown_vx_i8m1(__b, __c, 8);
  __riscv_vse8_v_i8m1_m(mask, __a, b_s, 8);
}

// FORCE_INLINE void vst1_lane_s16(int16_t *__a, int16x4_t __b, const int __c);

// FORCE_INLINE void vst1_lane_s32(int32_t *__a, int32x2_t __b, const int __c);

// FORCE_INLINE void vst1_lane_f32(float32_t *__a, float32x2_t __b, const int __c);

// FORCE_INLINE void vst1_lane_u8(uint8_t *__a, uint8x8_t __b, const int __c);

// FORCE_INLINE void vst1_lane_u16(uint16_t *__a, uint16x4_t __b, const int __c);

// FORCE_INLINE void vst1_lane_u32(uint32_t *__a, uint32x2_t __b, const int __c);

// FORCE_INLINE void vst1_lane_s64(int64_t *__a, int64x1_t __b, const int __c);

// FORCE_INLINE void vst1_lane_u64(uint64_t *__a, uint64x1_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_s8(int8_t *__a, int8x16_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_s16(int16_t *__a, int16x8_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_s32(int32_t *__a, int32x4_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_f32(float32_t *__a, float32x4_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_u8(uint8_t *__a, uint8x16_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_u16(uint16_t *__a, uint16x8_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_u32(uint32_t *__a, uint32x4_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_s64(int64_t *__a, int64x2_t __b, const int __c);

// FORCE_INLINE void vst1q_lane_u64(uint64_t *__a, uint64x2_t __b, const int __c);

FORCE_INLINE int8x8x2_t vld2_s8(const int8_t *__a) { return __riscv_vlseg2e8_v_i8m1x2(__a, 8); }

// FORCE_INLINE int16x4x2_t vld2_s16(const int16_t *__a);

// FORCE_INLINE int32x2x2_t vld2_s32(const int32_t *__a);

// FORCE_INLINE float32x2x2_t vld2_f32(const float32_t *__a);

// FORCE_INLINE uint8x8x2_t vld2_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4x2_t vld2_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2x2_t vld2_u32(const uint32_t *__a);

// FORCE_INLINE int64x1x2_t vld2_s64(const int64_t *__a);

// FORCE_INLINE uint64x1x2_t vld2_u64(const uint64_t *__a);

// FORCE_INLINE int8x16x2_t vld2q_s8(const int8_t *__a);

// FORCE_INLINE int16x8x2_t vld2q_s16(const int16_t *__a);

// FORCE_INLINE int32x4x2_t vld2q_s32(const int32_t *__a);

// FORCE_INLINE float32x4x2_t vld2q_f32(const float32_t *__a);

// FORCE_INLINE uint8x16x2_t vld2q_u8(const uint8_t *__a);

// FORCE_INLINE uint16x8x2_t vld2q_u16(const uint16_t *__a);

// FORCE_INLINE uint32x4x2_t vld2q_u32(const uint32_t *__a);

FORCE_INLINE int8x8x2_t vld2_lane_s8(const int8_t *__a, int8x8x2_t __b, const int __c) {
  const uint8_t mask_arr[] = {(uint8_t)(1 << __c)};
  vbool8_t mask = __riscv_vlm_v_b8(mask_arr, 1);
  vint8m1_t a_dup0 = vdup_n_s8(__a[0]);
  vint8m1_t a_dup1 = vdup_n_s8(__a[1]);
  vint8m1_t c0 = __riscv_vmerge_vvm_i8m1(__riscv_vget_v_i8m1x2_i8m1(__b, 0), a_dup0, mask, 8);
  vint8m1_t c1 = __riscv_vmerge_vvm_i8m1(__riscv_vget_v_i8m1x2_i8m1(__b, 1), a_dup1, mask, 8);
  return __riscv_vcreate_v_i8m1x2(c0, c1);
}

// FORCE_INLINE int16x4x2_t vld2_lane_s16(const int16_t *__a, int16x4x2_t __b, const int __c);

// FORCE_INLINE int32x2x2_t vld2_lane_s32(const int32_t *__a, int32x2x2_t __b, const int __c);

// FORCE_INLINE float32x2x2_t vld2_lane_f32(const float32_t *__a, float32x2x2_t __b, const int __c);

// FORCE_INLINE uint8x8x2_t vld2_lane_u8(const uint8_t *__a, uint8x8x2_t __b, const int __c);

// FORCE_INLINE uint16x4x2_t vld2_lane_u16(const uint16_t *__a, uint16x4x2_t __b, const int __c);

// FORCE_INLINE uint32x2x2_t vld2_lane_u32(const uint32_t *__a, uint32x2x2_t __b, const int __c);

// FORCE_INLINE int16x8x2_t vld2q_lane_s16(const int16_t *__a, int16x8x2_t __b, const int __c);

// FORCE_INLINE int32x4x2_t vld2q_lane_s32(const int32_t *__a, int32x4x2_t __b, const int __c);

// FORCE_INLINE float32x4x2_t vld2q_lane_f32(const float32_t *__a, float32x4x2_t __b, const int __c);

// FORCE_INLINE uint16x8x2_t vld2q_lane_u16(const uint16_t *__a, uint16x8x2_t __b, const int __c);

// FORCE_INLINE uint32x4x2_t vld2q_lane_u32(const uint32_t *__a, uint32x4x2_t __b, const int __c);

// FORCE_INLINE int8x8x2_t vld2_dup_s8(const int8_t *__a);

// FORCE_INLINE int16x4x2_t vld2_dup_s16(const int16_t *__a);

// FORCE_INLINE int32x2x2_t vld2_dup_s32(const int32_t *__a);

// FORCE_INLINE float32x2x2_t vld2_dup_f32(const float32_t *__a);

// FORCE_INLINE uint8x8x2_t vld2_dup_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4x2_t vld2_dup_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2x2_t vld2_dup_u32(const uint32_t *__a);

// FORCE_INLINE int64x1x2_t vld2_dup_s64(const int64_t *__a);

// FORCE_INLINE uint64x1x2_t vld2_dup_u64(const uint64_t *__a);

FORCE_INLINE void vst2_s8(int8_t *__a, int8x8x2_t __b) { return __riscv_vsseg2e8_v_i8m1x2(__a, __b, 8); }

// FORCE_INLINE void vst2_s16(int16_t *__a, int16x4x2_t __b);

// FORCE_INLINE void vst2_s32(int32_t *__a, int32x2x2_t __b);

// FORCE_INLINE void vst2_f32(float32_t *__a, float32x2x2_t __b);

// FORCE_INLINE void vst2_u8(uint8_t *__a, uint8x8x2_t __b);

// FORCE_INLINE void vst2_u16(uint16_t *__a, uint16x4x2_t __b);

// FORCE_INLINE void vst2_u32(uint32_t *__a, uint32x2x2_t __b);

// FORCE_INLINE void vst2_s64(int64_t *__a, int64x1x2_t __b);

// FORCE_INLINE void vst2_u64(uint64_t *__a, uint64x1x2_t __b);

// FORCE_INLINE void vst2q_s8(int8_t *__a, int8x16x2_t __b);

// FORCE_INLINE void vst2q_s16(int16_t *__a, int16x8x2_t __b);

// FORCE_INLINE void vst2q_s32(int32_t *__a, int32x4x2_t __b);

// FORCE_INLINE void vst2q_f32(float32_t *__a, float32x4x2_t __b);

// FORCE_INLINE void vst2q_u8(uint8_t *__a, uint8x16x2_t __b);

// FORCE_INLINE void vst2q_u16(uint16_t *__a, uint16x8x2_t __b);

// FORCE_INLINE void vst2q_u32(uint32_t *__a, uint32x4x2_t __b);

// FORCE_INLINE void vst2_lane_s8(int8_t *__a, int8x8x2_t __b, const int __c);

// FORCE_INLINE void vst2_lane_s16(int16_t *__a, int16x4x2_t __b, const int __c);

// FORCE_INLINE void vst2_lane_s32(int32_t *__a, int32x2x2_t __b, const int __c);

// FORCE_INLINE void vst2_lane_f32(float32_t *__a, float32x2x2_t __b, const int __c);

// FORCE_INLINE void vst2_lane_u8(uint8_t *__a, uint8x8x2_t __b, const int __c);

// FORCE_INLINE void vst2_lane_u16(uint16_t *__a, uint16x4x2_t __b, const int __c);

// FORCE_INLINE void vst2_lane_u32(uint32_t *__a, uint32x2x2_t __b, const int __c);

// FORCE_INLINE void vst2q_lane_s16(int16_t *__a, int16x8x2_t __b, const int __c);

// FORCE_INLINE void vst2q_lane_s32(int32_t *__a, int32x4x2_t __b, const int __c);

// FORCE_INLINE void vst2q_lane_f32(float32_t *__a, float32x4x2_t __b, const int __c);

// FORCE_INLINE void vst2q_lane_u16(uint16_t *__a, uint16x8x2_t __b, const int __c);

// FORCE_INLINE void vst2q_lane_u32(uint32_t *__a, uint32x4x2_t __b, const int __c);

// FORCE_INLINE int8x8x3_t vld3_s8(const int8_t *__a);

// FORCE_INLINE int16x4x3_t vld3_s16(const int16_t *__a);

// FORCE_INLINE int32x2x3_t vld3_s32(const int32_t *__a);

// FORCE_INLINE float32x2x3_t vld3_f32(const float32_t *__a);

// FORCE_INLINE uint8x8x3_t vld3_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4x3_t vld3_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2x3_t vld3_u32(const uint32_t *__a);

// FORCE_INLINE int64x1x3_t vld3_s64(const int64_t *__a);

// FORCE_INLINE uint64x1x3_t vld3_u64(const uint64_t *__a);

// FORCE_INLINE int8x16x3_t vld3q_s8(const int8_t *__a);

// FORCE_INLINE int16x8x3_t vld3q_s16(const int16_t *__a);

// FORCE_INLINE int32x4x3_t vld3q_s32(const int32_t *__a);

// FORCE_INLINE float32x4x3_t vld3q_f32(const float32_t *__a);

// FORCE_INLINE uint8x16x3_t vld3q_u8(const uint8_t *__a);

// FORCE_INLINE uint16x8x3_t vld3q_u16(const uint16_t *__a);

// FORCE_INLINE uint32x4x3_t vld3q_u32(const uint32_t *__a);

// FORCE_INLINE int8x8x3_t vld3_lane_s8(const int8_t *__a, int8x8x3_t __b, const int __c);

// FORCE_INLINE int16x4x3_t vld3_lane_s16(const int16_t *__a, int16x4x3_t __b, const int __c);

// FORCE_INLINE int32x2x3_t vld3_lane_s32(const int32_t *__a, int32x2x3_t __b, const int __c);

// FORCE_INLINE float32x2x3_t vld3_lane_f32(const float32_t *__a, float32x2x3_t __b, const int __c);

// FORCE_INLINE uint8x8x3_t vld3_lane_u8(const uint8_t *__a, uint8x8x3_t __b, const int __c);

// FORCE_INLINE uint16x4x3_t vld3_lane_u16(const uint16_t *__a, uint16x4x3_t __b, const int __c);

// FORCE_INLINE uint32x2x3_t vld3_lane_u32(const uint32_t *__a, uint32x2x3_t __b, const int __c);

// FORCE_INLINE int16x8x3_t vld3q_lane_s16(const int16_t *__a, int16x8x3_t __b, const int __c);

// FORCE_INLINE int32x4x3_t vld3q_lane_s32(const int32_t *__a, int32x4x3_t __b, const int __c);

// FORCE_INLINE float32x4x3_t vld3q_lane_f32(const float32_t *__a, float32x4x3_t __b, const int __c);

// FORCE_INLINE uint16x8x3_t vld3q_lane_u16(const uint16_t *__a, uint16x8x3_t __b, const int __c);

// FORCE_INLINE uint32x4x3_t vld3q_lane_u32(const uint32_t *__a, uint32x4x3_t __b, const int __c);

// FORCE_INLINE int8x8x3_t vld3_dup_s8(const int8_t *__a);

// FORCE_INLINE int16x4x3_t vld3_dup_s16(const int16_t *__a);

// FORCE_INLINE int32x2x3_t vld3_dup_s32(const int32_t *__a);

// FORCE_INLINE float32x2x3_t vld3_dup_f32(const float32_t *__a);

// FORCE_INLINE uint8x8x3_t vld3_dup_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4x3_t vld3_dup_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2x3_t vld3_dup_u32(const uint32_t *__a);

// FORCE_INLINE int64x1x3_t vld3_dup_s64(const int64_t *__a);

// FORCE_INLINE uint64x1x3_t vld3_dup_u64(const uint64_t *__a);

// FORCE_INLINE void vst3_s8(int8_t *__a, int8x8x3_t __b);

// FORCE_INLINE void vst3_s16(int16_t *__a, int16x4x3_t __b);

// FORCE_INLINE void vst3_s32(int32_t *__a, int32x2x3_t __b);

// FORCE_INLINE void vst3_f32(float32_t *__a, float32x2x3_t __b);

// FORCE_INLINE void vst3_u8(uint8_t *__a, uint8x8x3_t __b);

// FORCE_INLINE void vst3_u16(uint16_t *__a, uint16x4x3_t __b);

// FORCE_INLINE void vst3_u32(uint32_t *__a, uint32x2x3_t __b);

// FORCE_INLINE void vst3_s64(int64_t *__a, int64x1x3_t __b);

// FORCE_INLINE void vst3_u64(uint64_t *__a, uint64x1x3_t __b);

// FORCE_INLINE void vst3q_s8(int8_t *__a, int8x16x3_t __b);

// FORCE_INLINE void vst3q_s16(int16_t *__a, int16x8x3_t __b);

// FORCE_INLINE void vst3q_s32(int32_t *__a, int32x4x3_t __b);

// FORCE_INLINE void vst3q_f32(float32_t *__a, float32x4x3_t __b);

// FORCE_INLINE void vst3q_u8(uint8_t *__a, uint8x16x3_t __b);

// FORCE_INLINE void vst3q_u16(uint16_t *__a, uint16x8x3_t __b);

// FORCE_INLINE void vst3q_u32(uint32_t *__a, uint32x4x3_t __b);

// FORCE_INLINE void vst3_lane_s8(int8_t *__a, int8x8x3_t __b, const int __c);

// FORCE_INLINE void vst3_lane_s16(int16_t *__a, int16x4x3_t __b, const int __c);

// FORCE_INLINE void vst3_lane_s32(int32_t *__a, int32x2x3_t __b, const int __c);

// FORCE_INLINE void vst3_lane_f32(float32_t *__a, float32x2x3_t __b, const int __c);

// FORCE_INLINE void vst3_lane_u8(uint8_t *__a, uint8x8x3_t __b, const int __c);

// FORCE_INLINE void vst3_lane_u16(uint16_t *__a, uint16x4x3_t __b, const int __c);

// FORCE_INLINE void vst3_lane_u32(uint32_t *__a, uint32x2x3_t __b, const int __c);

// FORCE_INLINE void vst3q_lane_s16(int16_t *__a, int16x8x3_t __b, const int __c);

// FORCE_INLINE void vst3q_lane_s32(int32_t *__a, int32x4x3_t __b, const int __c);

// FORCE_INLINE void vst3q_lane_f32(float32_t *__a, float32x4x3_t __b, const int __c);

// FORCE_INLINE void vst3q_lane_u16(uint16_t *__a, uint16x8x3_t __b, const int __c);

// FORCE_INLINE void vst3q_lane_u32(uint32_t *__a, uint32x4x3_t __b, const int __c);

// FORCE_INLINE int8x8x4_t vld4_s8(const int8_t *__a);

// FORCE_INLINE int16x4x4_t vld4_s16(const int16_t *__a);

// FORCE_INLINE int32x2x4_t vld4_s32(const int32_t *__a);

// FORCE_INLINE float32x2x4_t vld4_f32(const float32_t *__a);

// FORCE_INLINE uint8x8x4_t vld4_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4x4_t vld4_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2x4_t vld4_u32(const uint32_t *__a);

// FORCE_INLINE int64x1x4_t vld4_s64(const int64_t *__a);

// FORCE_INLINE uint64x1x4_t vld4_u64(const uint64_t *__a);

// FORCE_INLINE int8x16x4_t vld4q_s8(const int8_t *__a);

// FORCE_INLINE int16x8x4_t vld4q_s16(const int16_t *__a);

// FORCE_INLINE int32x4x4_t vld4q_s32(const int32_t *__a);

// FORCE_INLINE float32x4x4_t vld4q_f32(const float32_t *__a);

// FORCE_INLINE uint8x16x4_t vld4q_u8(const uint8_t *__a);

// FORCE_INLINE uint16x8x4_t vld4q_u16(const uint16_t *__a);

// FORCE_INLINE uint32x4x4_t vld4q_u32(const uint32_t *__a);

// FORCE_INLINE int8x8x4_t vld4_lane_s8(const int8_t *__a, int8x8x4_t __b, const int __c);

// FORCE_INLINE int16x4x4_t vld4_lane_s16(const int16_t *__a, int16x4x4_t __b, const int __c);

// FORCE_INLINE int32x2x4_t vld4_lane_s32(const int32_t *__a, int32x2x4_t __b, const int __c);

// FORCE_INLINE float32x2x4_t vld4_lane_f32(const float32_t *__a, float32x2x4_t __b, const int __c);

// FORCE_INLINE uint8x8x4_t vld4_lane_u8(const uint8_t *__a, uint8x8x4_t __b, const int __c);

// FORCE_INLINE uint16x4x4_t vld4_lane_u16(const uint16_t *__a, uint16x4x4_t __b, const int __c);

// FORCE_INLINE uint32x2x4_t vld4_lane_u32(const uint32_t *__a, uint32x2x4_t __b, const int __c);

// FORCE_INLINE int16x8x4_t vld4q_lane_s16(const int16_t *__a, int16x8x4_t __b, const int __c);

// FORCE_INLINE int32x4x4_t vld4q_lane_s32(const int32_t *__a, int32x4x4_t __b, const int __c);

// FORCE_INLINE float32x4x4_t vld4q_lane_f32(const float32_t *__a, float32x4x4_t __b, const int __c);

// FORCE_INLINE uint16x8x4_t vld4q_lane_u16(const uint16_t *__a, uint16x8x4_t __b, const int __c);

// FORCE_INLINE uint32x4x4_t vld4q_lane_u32(const uint32_t *__a, uint32x4x4_t __b, const int __c);

// FORCE_INLINE int8x8x4_t vld4_dup_s8(const int8_t *__a);

// FORCE_INLINE int16x4x4_t vld4_dup_s16(const int16_t *__a);

// FORCE_INLINE int32x2x4_t vld4_dup_s32(const int32_t *__a);

// FORCE_INLINE float32x2x4_t vld4_dup_f32(const float32_t *__a);

// FORCE_INLINE uint8x8x4_t vld4_dup_u8(const uint8_t *__a);

// FORCE_INLINE uint16x4x4_t vld4_dup_u16(const uint16_t *__a);

// FORCE_INLINE uint32x2x4_t vld4_dup_u32(const uint32_t *__a);

// FORCE_INLINE int64x1x4_t vld4_dup_s64(const int64_t *__a);

// FORCE_INLINE uint64x1x4_t vld4_dup_u64(const uint64_t *__a);

// FORCE_INLINE void vst4_s8(int8_t *__a, int8x8x4_t __b);

// FORCE_INLINE void vst4_s16(int16_t *__a, int16x4x4_t __b);

// FORCE_INLINE void vst4_s32(int32_t *__a, int32x2x4_t __b);

// FORCE_INLINE void vst4_f32(float32_t *__a, float32x2x4_t __b);

// FORCE_INLINE void vst4_u8(uint8_t *__a, uint8x8x4_t __b);

// FORCE_INLINE void vst4_u16(uint16_t *__a, uint16x4x4_t __b);

// FORCE_INLINE void vst4_u32(uint32_t *__a, uint32x2x4_t __b);

// FORCE_INLINE void vst4_s64(int64_t *__a, int64x1x4_t __b);

// FORCE_INLINE void vst4_u64(uint64_t *__a, uint64x1x4_t __b);

// FORCE_INLINE void vst4q_s8(int8_t *__a, int8x16x4_t __b);

// FORCE_INLINE void vst4q_s16(int16_t *__a, int16x8x4_t __b);

// FORCE_INLINE void vst4q_s32(int32_t *__a, int32x4x4_t __b);

// FORCE_INLINE void vst4q_f32(float32_t *__a, float32x4x4_t __b);

// FORCE_INLINE void vst4q_u8(uint8_t *__a, uint8x16x4_t __b);

// FORCE_INLINE void vst4q_u16(uint16_t *__a, uint16x8x4_t __b);

// FORCE_INLINE void vst4q_u32(uint32_t *__a, uint32x4x4_t __b);

// FORCE_INLINE void vst4_lane_s8(int8_t *__a, int8x8x4_t __b, const int __c);

// FORCE_INLINE void vst4_lane_s16(int16_t *__a, int16x4x4_t __b, const int __c);

// FORCE_INLINE void vst4_lane_s32(int32_t *__a, int32x2x4_t __b, const int __c);

// FORCE_INLINE void vst4_lane_f32(float32_t *__a, float32x2x4_t __b, const int __c);

// FORCE_INLINE void vst4_lane_u8(uint8_t *__a, uint8x8x4_t __b, const int __c);

// FORCE_INLINE void vst4_lane_u16(uint16_t *__a, uint16x4x4_t __b, const int __c);

// FORCE_INLINE void vst4_lane_u32(uint32_t *__a, uint32x2x4_t __b, const int __c);

// FORCE_INLINE void vst4q_lane_s16(int16_t *__a, int16x8x4_t __b, const int __c);

// FORCE_INLINE void vst4q_lane_s32(int32_t *__a, int32x4x4_t __b, const int __c);

// FORCE_INLINE void vst4q_lane_f32(float32_t *__a, float32x4x4_t __b, const int __c);

// FORCE_INLINE void vst4q_lane_u16(uint16_t *__a, uint16x8x4_t __b, const int __c);

// FORCE_INLINE void vst4q_lane_u32(uint32_t *__a, uint32x4x4_t __b, const int __c);

// FORCE_INLINE int8x8_t vand_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vand_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vand_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vand_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vand_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vand_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int64x1_t vand_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint64x1_t vand_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t vandq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vandq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vandq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vandq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vandq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vandq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vandq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vandq_u64(uint64x2_t __a, uint64x2_t __b);

// FORCE_INLINE int8x8_t vorr_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t vorr_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vorr_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vorr_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vorr_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vorr_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int64x1_t vorr_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint64x1_t vorr_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t vorrq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vorrq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vorrq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vorrq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vorrq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vorrq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vorrq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vorrq_u64(uint64x2_t __a, uint64x2_t __b);

// FORCE_INLINE int8x8_t veor_s8(int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int16x4_t veor_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t veor_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t veor_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t veor_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t veor_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int64x1_t veor_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint64x1_t veor_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t veorq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t veorq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t veorq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t veorq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t veorq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t veorq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t veorq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t veorq_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vbic_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vand_vv_i8m1(__a, __riscv_vnot_v_i8m1(__b, 8), 8);
}

// FORCE_INLINE int16x4_t vbic_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vbic_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vbic_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vbic_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vbic_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int64x1_t vbic_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint64x1_t vbic_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t vbicq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vbicq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vbicq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vbicq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vbicq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vbicq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vbicq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vbicq_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE int8x8_t vorn_s8(int8x8_t __a, int8x8_t __b) {
  return __riscv_vor_vv_i8m1(__a, __riscv_vnot_v_i8m1(__b, 8), 8);
}

// FORCE_INLINE int16x4_t vorn_s16(int16x4_t __a, int16x4_t __b);

// FORCE_INLINE int32x2_t vorn_s32(int32x2_t __a, int32x2_t __b);

// FORCE_INLINE uint8x8_t vorn_u8(uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint16x4_t vorn_u16(uint16x4_t __a, uint16x4_t __b);

// FORCE_INLINE uint32x2_t vorn_u32(uint32x2_t __a, uint32x2_t __b);

// FORCE_INLINE int64x1_t vorn_s64(int64x1_t __a, int64x1_t __b);

// FORCE_INLINE uint64x1_t vorn_u64(uint64x1_t __a, uint64x1_t __b);

// FORCE_INLINE int8x16_t vornq_s8(int8x16_t __a, int8x16_t __b);

// FORCE_INLINE int16x8_t vornq_s16(int16x8_t __a, int16x8_t __b);

// FORCE_INLINE int32x4_t vornq_s32(int32x4_t __a, int32x4_t __b);

// FORCE_INLINE int64x2_t vornq_s64(int64x2_t __a, int64x2_t __b);

// FORCE_INLINE uint8x16_t vornq_u8(uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE uint16x8_t vornq_u16(uint16x8_t __a, uint16x8_t __b);

// FORCE_INLINE uint32x4_t vornq_u32(uint32x4_t __a, uint32x4_t __b);

// FORCE_INLINE uint64x2_t vornq_u64(uint64x2_t __a, uint64x2_t __b);

FORCE_INLINE float32x2_t vreinterpret_f32_s64(int64x1_t __a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i64m1_i32m1(__a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_u64(uint64x1_t __a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(__a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_s8(int8x8_t __a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i8m1_i32m1(__a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_s16(int16x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i16m1_i32m1(__a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_s32(int32x2_t __a) { return __riscv_vreinterpret_v_i32m1_f32m1(__a); }

FORCE_INLINE float32x2_t vreinterpret_f32_u8(uint8x8_t __a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u8m1_u32m1(__a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_u16(uint16x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u16m1_u32m1(__a));
}

FORCE_INLINE float32x2_t vreinterpret_f32_u32(uint32x2_t __a) { return __riscv_vreinterpret_v_u32m1_f32m1(__a); }

FORCE_INLINE int64x1_t vreinterpret_s64_f32(float32x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(__a));
}

FORCE_INLINE int64x1_t vreinterpret_s64_u64(uint64x1_t __a) { return __riscv_vreinterpret_v_u64m1_i64m1(__a); }

FORCE_INLINE int64x1_t vreinterpret_s64_s8(int8x8_t __a) { return __riscv_vreinterpret_v_i8m1_i64m1(__a); }

FORCE_INLINE int64x1_t vreinterpret_s64_s16(int16x4_t __a) { return __riscv_vreinterpret_v_i16m1_i64m1(__a); }

FORCE_INLINE int64x1_t vreinterpret_s64_s32(int32x2_t __a) { return __riscv_vreinterpret_v_i32m1_i64m1(__a); }

FORCE_INLINE int64x1_t vreinterpret_s64_u8(uint8x8_t __a) {
  return __riscv_vreinterpret_v_i8m1_i64m1(__riscv_vreinterpret_v_u8m1_i8m1(__a));
}

FORCE_INLINE int64x1_t vreinterpret_s64_u16(uint16x4_t __a) {
  return __riscv_vreinterpret_v_i16m1_i64m1(__riscv_vreinterpret_v_u16m1_i16m1(__a));
}

FORCE_INLINE int64x1_t vreinterpret_s64_u32(uint32x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_u32m1_i32m1(__a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_f32(float32x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_f32m1_u32m1(__a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_s64(int64x1_t __a) { return __riscv_vreinterpret_v_i64m1_u64m1(__a); }

FORCE_INLINE uint64x1_t vreinterpret_u64_s8(int8x8_t __a) {
  return __riscv_vreinterpret_v_u8m1_u64m1(__riscv_vreinterpret_v_i8m1_u8m1(__a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_s16(int16x4_t __a) {
  return __riscv_vreinterpret_v_u16m1_u64m1(__riscv_vreinterpret_v_i16m1_u16m1(__a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_s32(int32x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_i32m1_u32m1(__a));
}

FORCE_INLINE uint64x1_t vreinterpret_u64_u8(uint8x8_t __a) { return __riscv_vreinterpret_v_u8m1_u64m1(__a); }

FORCE_INLINE uint64x1_t vreinterpret_u64_u16(uint16x4_t __a) { return __riscv_vreinterpret_v_u16m1_u64m1(__a); }

FORCE_INLINE uint64x1_t vreinterpret_u64_u32(uint32x2_t __a) { return __riscv_vreinterpret_v_u32m1_u64m1(__a); }

FORCE_INLINE int8x8_t vreinterpret_s8_f32(float32x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_f32m1_i32m1(__a));
}

FORCE_INLINE int8x8_t vreinterpret_s8_s64(int64x1_t __a) { return __riscv_vreinterpret_v_i64m1_i8m1(__a); }

FORCE_INLINE int8x8_t vreinterpret_s8_u64(uint64x1_t __a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_u64m1_i64m1(__a));
}

FORCE_INLINE int8x8_t vreinterpret_s8_s16(int16x4_t __a) { return __riscv_vreinterpret_v_i16m1_i8m1(__a); }

FORCE_INLINE int8x8_t vreinterpret_s8_s32(int32x2_t __a) { return __riscv_vreinterpret_v_i32m1_i8m1(__a); }

FORCE_INLINE int8x8_t vreinterpret_s8_u8(uint8x8_t __a) { return __riscv_vreinterpret_v_u8m1_i8m1(__a); }

FORCE_INLINE int8x8_t vreinterpret_s8_u16(uint16x4_t __a) {
  return __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vreinterpret_v_u16m1_i16m1(__a));
}

FORCE_INLINE int8x8_t vreinterpret_s8_u32(uint32x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_u32m1_i32m1(__a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_f32(float32x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_f32m1_i32m1(__a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_s64(int64x1_t __a) { return __riscv_vreinterpret_v_i64m1_i16m1(__a); }

FORCE_INLINE int16x4_t vreinterpret_s16_u64(uint64x1_t __a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_u64m1_i64m1(__a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_s8(int8x8_t __a) { return __riscv_vreinterpret_v_i8m1_i16m1(__a); }

FORCE_INLINE int16x4_t vreinterpret_s16_s32(int32x2_t __a) { return __riscv_vreinterpret_v_i32m1_i16m1(__a); }

FORCE_INLINE int16x4_t vreinterpret_s16_u8(uint8x8_t __a) {
  return __riscv_vreinterpret_v_i8m1_i16m1(__riscv_vreinterpret_v_u8m1_i8m1(__a));
}

FORCE_INLINE int16x4_t vreinterpret_s16_u16(uint16x4_t __a) { return __riscv_vreinterpret_v_u16m1_i16m1(__a); }

FORCE_INLINE int16x4_t vreinterpret_s16_u32(uint32x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_u32m1_i32m1(__a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_f32(float32x2_t __a) { return __riscv_vreinterpret_v_f32m1_i32m1(__a); }

FORCE_INLINE int32x2_t vreinterpret_s32_s64(int64x1_t __a) { return __riscv_vreinterpret_v_i64m1_i32m1(__a); }

FORCE_INLINE int32x2_t vreinterpret_s32_u64(uint64x1_t __a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(__a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_s8(int8x8_t __a) { return __riscv_vreinterpret_v_i8m1_i32m1(__a); }

FORCE_INLINE int32x2_t vreinterpret_s32_s16(int16x4_t __a) { return __riscv_vreinterpret_v_i16m1_i32m1(__a); }

FORCE_INLINE int32x2_t vreinterpret_s32_u8(uint8x8_t __a) {
  return __riscv_vreinterpret_v_i8m1_i32m1(__riscv_vreinterpret_v_u8m1_i8m1(__a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_u16(uint16x4_t __a) {
  return __riscv_vreinterpret_v_i16m1_i32m1(__riscv_vreinterpret_v_u16m1_i16m1(__a));
}

FORCE_INLINE int32x2_t vreinterpret_s32_u32(uint32x2_t __a) { return __riscv_vreinterpret_v_u32m1_i32m1(__a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_f32(float32x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_f32m1_u32m1(__a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_s64(int64x1_t __a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(__riscv_vreinterpret_v_i64m1_u64m1(__a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_u64(uint64x1_t __a) { return __riscv_vreinterpret_v_u64m1_u8m1(__a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_s8(int8x8_t __a) { return __riscv_vreinterpret_v_i8m1_u8m1(__a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_s16(int16x4_t __a) {
  return __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vreinterpret_v_i16m1_u16m1(__a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_s32(int32x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_i32m1_u32m1(__a));
}

FORCE_INLINE uint8x8_t vreinterpret_u8_u16(uint16x4_t __a) { return __riscv_vreinterpret_v_u16m1_u8m1(__a); }

FORCE_INLINE uint8x8_t vreinterpret_u8_u32(uint32x2_t __a) { return __riscv_vreinterpret_v_u32m1_u8m1(__a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_f32(float32x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_f32m1_u32m1(__a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_s64(int64x1_t __a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(__riscv_vreinterpret_v_i64m1_u64m1(__a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_u64(uint64x1_t __a) { return __riscv_vreinterpret_v_u64m1_u16m1(__a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_s8(int8x8_t __a) {
  return __riscv_vreinterpret_v_u8m1_u16m1(__riscv_vreinterpret_v_i8m1_u8m1(__a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_s16(int16x4_t __a) { return __riscv_vreinterpret_v_i16m1_u16m1(__a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_s32(int32x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_i32m1_u32m1(__a));
}

FORCE_INLINE uint16x4_t vreinterpret_u16_u8(uint8x8_t __a) { return __riscv_vreinterpret_v_u8m1_u16m1(__a); }

FORCE_INLINE uint16x4_t vreinterpret_u16_u32(uint32x2_t __a) { return __riscv_vreinterpret_v_u32m1_u16m1(__a); }

FORCE_INLINE uint32x2_t vreinterpret_u32_f32(float32x2_t __a) { return __riscv_vreinterpret_v_f32m1_u32m1(__a); }

FORCE_INLINE uint32x2_t vreinterpret_u32_s64(int64x1_t __a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_i64m1_u64m1(__a));
}

FORCE_INLINE uint32x2_t vreinterpret_u32_u64(uint64x1_t __a) { return __riscv_vreinterpret_v_u64m1_u32m1(__a); }

FORCE_INLINE uint32x2_t vreinterpret_u32_s8(int8x8_t __a) {
  return __riscv_vreinterpret_v_u8m1_u32m1(__riscv_vreinterpret_v_i8m1_u8m1(__a));
}

FORCE_INLINE uint32x2_t vreinterpret_u32_s16(int16x4_t __a) {
  return __riscv_vreinterpret_v_u16m1_u32m1(__riscv_vreinterpret_v_i16m1_u16m1(__a));
}

FORCE_INLINE uint32x2_t vreinterpret_u32_s32(int32x2_t __a) { return __riscv_vreinterpret_v_i32m1_u32m1(__a); }

FORCE_INLINE uint32x2_t vreinterpret_u32_u8(uint8x8_t __a) { return __riscv_vreinterpret_v_u8m1_u32m1(__a); }

FORCE_INLINE uint32x2_t vreinterpret_u32_u16(uint16x4_t __a) { return __riscv_vreinterpret_v_u16m1_u32m1(__a); }

FORCE_INLINE float32x4_t vreinterpretq_f32_s64(int64x2_t __a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i64m1_i32m1(__a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_u64(uint64x2_t __a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u64m1_u32m1(__a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_s8(int8x16_t __a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i8m1_i32m1(__a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_s16(int16x8_t __a) {
  return __riscv_vreinterpret_v_i32m1_f32m1(__riscv_vreinterpret_v_i16m1_i32m1(__a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_s32(int32x4_t __a) { return __riscv_vreinterpret_v_i32m1_f32m1(__a); }

FORCE_INLINE float32x4_t vreinterpretq_f32_u8(uint8x16_t __a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u8m1_u32m1(__a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_u16(uint16x8_t __a) {
  return __riscv_vreinterpret_v_u32m1_f32m1(__riscv_vreinterpret_v_u16m1_u32m1(__a));
}

FORCE_INLINE float32x4_t vreinterpretq_f32_u32(uint32x4_t __a) { return __riscv_vreinterpret_v_u32m1_f32m1(__a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_f32(float32x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_f32m1_i32m1(__a));
}

FORCE_INLINE int64x2_t vreinterpretq_s64_u64(uint64x2_t __a) { return __riscv_vreinterpret_v_u64m1_i64m1(__a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_s8(int8x16_t __a) { return __riscv_vreinterpret_v_i8m1_i64m1(__a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_s16(int16x8_t __a) { return __riscv_vreinterpret_v_i16m1_i64m1(__a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_s32(int32x4_t __a) { return __riscv_vreinterpret_v_i32m1_i64m1(__a); }

FORCE_INLINE int64x2_t vreinterpretq_s64_u8(uint8x16_t __a) {
  return __riscv_vreinterpret_v_i8m1_i64m1(__riscv_vreinterpret_v_u8m1_i8m1(__a));
}

FORCE_INLINE int64x2_t vreinterpretq_s64_u16(uint16x8_t __a) {
  return __riscv_vreinterpret_v_i16m1_i64m1(__riscv_vreinterpret_v_u16m1_i16m1(__a));
}

FORCE_INLINE int64x2_t vreinterpretq_s64_u32(uint32x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_i64m1(__riscv_vreinterpret_v_u32m1_i32m1(__a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_f32(float32x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_f32m1_u32m1(__a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_s64(int64x2_t __a) { return __riscv_vreinterpret_v_i64m1_u64m1(__a); }

FORCE_INLINE uint64x2_t vreinterpretq_u64_s8(int8x16_t __a) {
  return __riscv_vreinterpret_v_u8m1_u64m1(__riscv_vreinterpret_v_i8m1_u8m1(__a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_s16(int16x8_t __a) {
  return __riscv_vreinterpret_v_u16m1_u64m1(__riscv_vreinterpret_v_i16m1_u16m1(__a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_s32(int32x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_i32m1_u32m1(__a));
}

FORCE_INLINE uint64x2_t vreinterpretq_u64_u8(uint8x16_t __a) { return __riscv_vreinterpret_v_u8m1_u64m1(__a); }

FORCE_INLINE uint64x2_t vreinterpretq_u64_u16(uint16x8_t __a) { return __riscv_vreinterpret_v_u16m1_u64m1(__a); }

FORCE_INLINE uint64x2_t vreinterpretq_u64_u32(uint32x4_t __a) { return __riscv_vreinterpret_v_u32m1_u64m1(__a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_f32(float32x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_f32m1_i32m1(__a));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_s64(int64x2_t __a) { return __riscv_vreinterpret_v_i64m1_i8m1(__a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_u64(uint64x2_t __a) {
  return __riscv_vreinterpret_v_i64m1_i8m1(__riscv_vreinterpret_v_u64m1_i64m1(__a));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_s16(int16x8_t __a) { return __riscv_vreinterpret_v_i16m1_i8m1(__a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_s32(int32x4_t __a) { return __riscv_vreinterpret_v_i32m1_i8m1(__a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_u8(uint8x16_t __a) { return __riscv_vreinterpret_v_u8m1_i8m1(__a); }

FORCE_INLINE int8x16_t vreinterpretq_s8_u16(uint16x8_t __a) {
  return __riscv_vreinterpret_v_i16m1_i8m1(__riscv_vreinterpret_v_u16m1_i16m1(__a));
}

FORCE_INLINE int8x16_t vreinterpretq_s8_u32(uint32x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_i8m1(__riscv_vreinterpret_v_u32m1_i32m1(__a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_f32(float32x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_f32m1_i32m1(__a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_s64(int64x2_t __a) { return __riscv_vreinterpret_v_i64m1_i16m1(__a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_u64(uint64x2_t __a) {
  return __riscv_vreinterpret_v_i64m1_i16m1(__riscv_vreinterpret_v_u64m1_i64m1(__a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_s8(int8x16_t __a) { return __riscv_vreinterpret_v_i8m1_i16m1(__a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_s32(int32x4_t __a) { return __riscv_vreinterpret_v_i32m1_i16m1(__a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_u8(uint8x16_t __a) {
  return __riscv_vreinterpret_v_i8m1_i16m1(__riscv_vreinterpret_v_u8m1_i8m1(__a));
}

FORCE_INLINE int16x8_t vreinterpretq_s16_u16(uint16x8_t __a) { return __riscv_vreinterpret_v_u16m1_i16m1(__a); }

FORCE_INLINE int16x8_t vreinterpretq_s16_u32(uint32x4_t __a) {
  return __riscv_vreinterpret_v_i32m1_i16m1(__riscv_vreinterpret_v_u32m1_i32m1(__a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_f32(float32x4_t __a) { return __riscv_vreinterpret_v_f32m1_i32m1(__a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_s64(int64x2_t __a) { return __riscv_vreinterpret_v_i64m1_i32m1(__a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_u64(uint64x2_t __a) {
  return __riscv_vreinterpret_v_i64m1_i32m1(__riscv_vreinterpret_v_u64m1_i64m1(__a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_s8(int8x16_t __a) { return __riscv_vreinterpret_v_i8m1_i32m1(__a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_s16(int16x8_t __a) { return __riscv_vreinterpret_v_i16m1_i32m1(__a); }

FORCE_INLINE int32x4_t vreinterpretq_s32_u8(uint8x16_t __a) {
  return __riscv_vreinterpret_v_i8m1_i32m1(__riscv_vreinterpret_v_u8m1_i8m1(__a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_u16(uint16x8_t __a) {
  return __riscv_vreinterpret_v_i16m1_i32m1(__riscv_vreinterpret_v_u16m1_i16m1(__a));
}

FORCE_INLINE int32x4_t vreinterpretq_s32_u32(uint32x4_t __a) { return __riscv_vreinterpret_v_u32m1_i32m1(__a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_f32(float32x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_f32m1_u32m1(__a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_s64(int64x2_t __a) {
  return __riscv_vreinterpret_v_u64m1_u8m1(__riscv_vreinterpret_v_i64m1_u64m1(__a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_u64(uint64x2_t __a) { return __riscv_vreinterpret_v_u64m1_u8m1(__a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_s8(int8x16_t __a) { return __riscv_vreinterpret_v_i8m1_u8m1(__a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_s16(int16x8_t __a) {
  return __riscv_vreinterpret_v_u16m1_u8m1(__riscv_vreinterpret_v_i16m1_u16m1(__a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_s32(int32x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_u8m1(__riscv_vreinterpret_v_i32m1_u32m1(__a));
}

FORCE_INLINE uint8x16_t vreinterpretq_u8_u16(uint16x8_t __a) { return __riscv_vreinterpret_v_u16m1_u8m1(__a); }

FORCE_INLINE uint8x16_t vreinterpretq_u8_u32(uint32x4_t __a) { return __riscv_vreinterpret_v_u32m1_u8m1(__a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_f32(float32x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_f32m1_u32m1(__a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_s64(int64x2_t __a) {
  return __riscv_vreinterpret_v_u64m1_u16m1(__riscv_vreinterpret_v_i64m1_u64m1(__a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_u64(uint64x2_t __a) { return __riscv_vreinterpret_v_u64m1_u16m1(__a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_s8(int8x16_t __a) {
  return __riscv_vreinterpret_v_u8m1_u16m1(__riscv_vreinterpret_v_i8m1_u8m1(__a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_s16(int16x8_t __a) { return __riscv_vreinterpret_v_i16m1_u16m1(__a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_s32(int32x4_t __a) {
  return __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_i32m1_u32m1(__a));
}

FORCE_INLINE uint16x8_t vreinterpretq_u16_u8(uint8x16_t __a) { return __riscv_vreinterpret_v_u8m1_u16m1(__a); }

FORCE_INLINE uint16x8_t vreinterpretq_u16_u32(uint32x4_t __a) { return __riscv_vreinterpret_v_u32m1_u16m1(__a); }

FORCE_INLINE uint32x4_t vreinterpretq_u32_f32(float32x4_t __a) { return __riscv_vreinterpret_v_f32m1_u32m1(__a); }

FORCE_INLINE uint32x4_t vreinterpretq_u32_s64(int64x2_t __a) {
  return __riscv_vreinterpret_v_u64m1_u32m1(__riscv_vreinterpret_v_i64m1_u64m1(__a));
}

FORCE_INLINE uint32x4_t vreinterpretq_u32_u64(uint64x2_t __a) { return __riscv_vreinterpret_v_u64m1_u32m1(__a); }

FORCE_INLINE uint32x4_t vreinterpretq_u32_s8(int8x16_t __a) {
  return __riscv_vreinterpret_v_u8m1_u32m1(__riscv_vreinterpret_v_i8m1_u8m1(__a));
}

FORCE_INLINE uint32x4_t vreinterpretq_u32_s16(int16x8_t __a) {
  return __riscv_vreinterpret_v_u16m1_u32m1(__riscv_vreinterpret_v_i16m1_u16m1(__a));
}

FORCE_INLINE uint32x4_t vreinterpretq_u32_s32(int32x4_t __a) { return __riscv_vreinterpret_v_i32m1_u32m1(__a); }

FORCE_INLINE uint32x4_t vreinterpretq_u32_u8(uint8x16_t __a) { return __riscv_vreinterpret_v_u8m1_u32m1(__a); }

FORCE_INLINE uint32x4_t vreinterpretq_u32_u16(uint16x8_t __a) { return __riscv_vreinterpret_v_u16m1_u32m1(__a); }

// FORCE_INLINE uint8x16_t vaeseq_u8(uint8x16_t __data, uint8x16_t __key);

// FORCE_INLINE uint8x16_t vaesdq_u8(uint8x16_t __data, uint8x16_t __key);

// FORCE_INLINE uint8x16_t vaesmcq_u8(uint8x16_t __data);

// FORCE_INLINE uint8x16_t vaesimcq_u8(uint8x16_t __data);

// FORCE_INLINE uint32_t vsha1h_u32(uint32_t __hash_e);

// FORCE_INLINE uint32x4_t vsha1cq_u32(uint32x4_t __hash_abcd, uint32_t __hash_e, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha1pq_u32(uint32x4_t __hash_abcd, uint32_t __hash_e, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha1mq_u32(uint32x4_t __hash_abcd, uint32_t __hash_e, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha1su0q_u32(uint32x4_t __w0_3, uint32x4_t __w4_7, uint32x4_t __w8_11);

// FORCE_INLINE uint32x4_t vsha1su1q_u32(uint32x4_t __tw0_3, uint32x4_t __w12_15);

// FORCE_INLINE uint32x4_t vsha256hq_u32(uint32x4_t __hash_abcd, uint32x4_t __hash_efgh, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha256h2q_u32(uint32x4_t __hash_abcd, uint32x4_t __hash_efgh, uint32x4_t __wk);

// FORCE_INLINE uint32x4_t vsha256su0q_u32(uint32x4_t __w0_3, uint32x4_t __w4_7);

// FORCE_INLINE uint32x4_t vsha256su1q_u32(uint32x4_t __tw0_3, uint32x4_t __w8_11, uint32x4_t __w12_15);

// /* AdvSIMD Dot Product intrinsics. */

// FORCE_INLINE uint32x2_t vdot_u32(uint32x2_t __r, uint8x8_t __a, uint8x8_t __b);

// FORCE_INLINE uint32x4_t vdotq_u32(uint32x4_t __r, uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE int32x2_t vdot_s32(int32x2_t __r, int8x8_t __a, int8x8_t __b);

// FORCE_INLINE int32x4_t vdotq_s32(int32x4_t __r, int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint32x2_t vdot_lane_u32(uint32x2_t __r, uint8x8_t __a, uint8x8_t __b, const int __index);

// FORCE_INLINE uint32x4_t vdotq_lane_u32(uint32x4_t __r, uint8x16_t __a, uint8x8_t __b, const int __index);

// FORCE_INLINE int32x2_t vdot_lane_s32(int32x2_t __r, int8x8_t __a, int8x8_t __b, const int __index);

// FORCE_INLINE int32x4_t vdotq_lane_s32(int32x4_t __r, int8x16_t __a, int8x8_t __b, const int __index);

// FORCE_INLINE uint32x2_t vdot_laneq_u32(uint32x2_t __r, uint8x8_t __a, uint8x16_t __b, const int __index);

// FORCE_INLINE uint32x4_t vdotq_laneq_u32(uint32x4_t __r, uint8x16_t __a, uint8x16_t __b, const int __index);

// FORCE_INLINE int32x2_t vdot_laneq_s32(int32x2_t __r, int8x8_t __a, int8x16_t __b, const int __index);

// FORCE_INLINE int32x4_t vdotq_laneq_s32(int32x4_t __r, int8x16_t __a, int8x16_t __b, const int __index);

// /* AdvSIMD Complex numbers intrinsics. */

// FORCE_INLINE float32x2_t vcadd_rot90_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vcaddq_rot90_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vcadd_rot270_f32(float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vcaddq_rot270_f32(float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vcmla_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vcmlaq_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vcmla_lane_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b, const int __index);

// FORCE_INLINE float32x2_t vcmla_laneq_f32(float32x2_t __r, float32x2_t __a, float32x4_t __b, const int __index);

// FORCE_INLINE float32x4_t vcmlaq_lane_f32(float32x4_t __r, float32x4_t __a, float32x2_t __b, const int __index);

// FORCE_INLINE float32x4_t vcmlaq_laneq_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b, const int __index);

// FORCE_INLINE float32x2_t vcmla_rot90_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vcmlaq_rot90_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vcmla_rot90_lane_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b, const int __index);

// FORCE_INLINE float32x2_t vcmla_rot90_laneq_f32(float32x2_t __r, float32x2_t __a, float32x4_t __b, const int __index);

// FORCE_INLINE float32x4_t vcmlaq_rot90_lane_f32(float32x4_t __r, float32x4_t __a, float32x2_t __b, const int __index);

// FORCE_INLINE float32x4_t vcmlaq_rot90_laneq_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b, const int
// __index);

// FORCE_INLINE float32x2_t vcmla_rot180_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vcmlaq_rot180_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vcmla_rot180_lane_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b, const int __index);

// FORCE_INLINE float32x2_t vcmla_rot180_laneq_f32(float32x2_t __r, float32x2_t __a, float32x4_t __b, const int
// __index);

// FORCE_INLINE float32x4_t vcmlaq_rot180_lane_f32(float32x4_t __r, float32x4_t __a, float32x2_t __b, const int
// __index);

// FORCE_INLINE float32x4_t vcmlaq_rot180_laneq_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b, const int
// __index);

// FORCE_INLINE float32x2_t vcmla_rot270_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b);

// FORCE_INLINE float32x4_t vcmlaq_rot270_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b);

// FORCE_INLINE float32x2_t vcmla_rot270_lane_f32(float32x2_t __r, float32x2_t __a, float32x2_t __b, const int __index);

// FORCE_INLINE float32x2_t vcmla_rot270_laneq_f32(float32x2_t __r, float32x2_t __a, float32x4_t __b, const int
// __index);

// FORCE_INLINE float32x4_t vcmlaq_rot270_lane_f32(float32x4_t __r, float32x4_t __a, float32x2_t __b, const int
// __index);

// FORCE_INLINE float32x4_t vcmlaq_rot270_laneq_f32(float32x4_t __r, float32x4_t __a, float32x4_t __b, const int
// __index);

// /* AdvSIMD Matrix Multiply-Accumulate and Dot Product intrinsics. */

// FORCE_INLINE int32x2_t vusdot_s32(int32x2_t __r, uint8x8_t __a, int8x8_t __b);

// FORCE_INLINE int32x4_t vusdotq_s32(int32x4_t __r, uint8x16_t __a, int8x16_t __b);

// FORCE_INLINE int32x2_t vusdot_lane_s32(int32x2_t __r, uint8x8_t __a, int8x8_t __b, const int __index);

// FORCE_INLINE int32x4_t vusdotq_lane_s32(int32x4_t __r, uint8x16_t __a, int8x8_t __b, const int __index);

// FORCE_INLINE int32x2_t vsudot_lane_s32(int32x2_t __r, int8x8_t __a, uint8x8_t __b, const int __index);

// FORCE_INLINE int32x4_t vsudotq_lane_s32(int32x4_t __r, int8x16_t __a, uint8x8_t __b, const int __index);

// FORCE_INLINE int32x2_t vusdot_laneq_s32(int32x2_t __r, uint8x8_t __a, int8x16_t __b, const int __index);

// FORCE_INLINE int32x4_t vusdotq_laneq_s32(int32x4_t __r, uint8x16_t __a, int8x16_t __b, const int __index);

// FORCE_INLINE int32x2_t vsudot_laneq_s32(int32x2_t __r, int8x8_t __a, uint8x16_t __b, const int __index);

// FORCE_INLINE int32x4_t vsudotq_laneq_s32(int32x4_t __r, int8x16_t __a, uint8x16_t __b, const int __index);

// /* AdvSIMD 8-bit Integer Matrix Multiply (I8MM); intrinsics. */

// FORCE_INLINE int32x4_t vmmlaq_s32(int32x4_t __r, int8x16_t __a, int8x16_t __b);

// FORCE_INLINE uint32x4_t vmmlaq_u32(uint32x4_t __r, uint8x16_t __a, uint8x16_t __b);

// FORCE_INLINE int32x4_t vusmmlaq_s32(int32x4_t __r, uint8x16_t __a, int8x16_t __b);

#ifdef __cplusplus
}
#endif

#if defined(__GNUC__) || defined(__clang__)
#pragma pop_macro("ALIGN_STRUCT")
#pragma pop_macro("FORCE_INLINE")
#endif

// TODO uncomment this and put all the implementation into `#elif defined(__riscv) || defined(__riscv__)`
// #endif /* #elif (defined(__riscv) || defined(__riscv__)) */

#endif /* NEON2RVV_H */
