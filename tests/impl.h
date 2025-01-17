#ifndef NEON2RVV_TEST_H
#define NEON2RVV_TEST_H

#include "common.h"
#include "debug_tools.h"

#define INTRIN_LIST                                                         \
  /* vadd */                                                                \
  _(vadd_s8)                                                                \
  _(vadd_s16)                                                               \
  _(vadd_s32)                                                               \
  _(vadd_f32)                                                               \
  _(vadd_u8)                                                                \
  _(vadd_u16)                                                               \
  _(vadd_u32)                                                               \
  _(vadd_s64)                                                               \
  _(vadd_u64)                                                               \
  _(vaddq_s8)                                                               \
  _(vaddq_s16)                                                              \
  _(vaddq_s32)                                                              \
  _(vaddq_s64)                                                              \
  _(vaddq_f32)                                                              \
  _(vaddq_u8)                                                               \
  _(vaddq_u16)                                                              \
  _(vaddq_u32)                                                              \
  _(vaddq_u64)                                                              \
  _(vaddl_s8)                                                               \
  _(vaddl_s16)                                                              \
  _(vaddl_s32)                                                              \
  _(vaddl_u8)                                                               \
  _(vaddl_u16)                                                              \
  _(vaddl_u32)                                                              \
  _(vaddw_s8)                                                               \
  _(vaddw_s16)                                                              \
  _(vaddw_s32)                                                              \
  _(vaddw_u8)                                                               \
  _(vaddw_u16)                                                              \
  _(vaddw_u32)                                                              \
  _(vhadd_s8)                                                               \
  _(vhadd_s16)                                                              \
  _(vhadd_s32)                                                              \
  _(vhadd_u8)                                                               \
  _(vhadd_u16)                                                              \
  _(vhadd_u32)                                                              \
  _(vhaddq_s8)                                                              \
  _(vhaddq_s16)                                                             \
  _(vhaddq_s32)                                                             \
  _(vhaddq_u8)                                                              \
  _(vhaddq_u16)                                                             \
  _(vhaddq_u32)                                                             \
  _(vrhadd_s8)                                                              \
  _(vrhadd_s16)                                                             \
  _(vrhadd_s32)                                                             \
  _(vrhadd_u8)                                                              \
  _(vrhadd_u16)                                                             \
  _(vrhadd_u32)                                                             \
  _(vrhaddq_s8)                                                             \
  _(vrhaddq_s16)                                                            \
  _(vrhaddq_s32)                                                            \
  _(vrhaddq_u8)                                                             \
  _(vrhaddq_u16)                                                            \
  _(vrhaddq_u32)                                                            \
  _(vqadd_s8)                                                               \
  _(vqadd_s16)                                                              \
  _(vqadd_s32)                                                              \
  _(vqadd_s64)                                                              \
  _(vqadd_u8)                                                               \
  _(vqadd_u16)                                                              \
  _(vqadd_u32)                                                              \
  _(vqadd_u64)                                                              \
  _(vqaddq_s8)                                                              \
  _(vqaddq_s16)                                                             \
  _(vqaddq_s32)                                                             \
  _(vqaddq_s64)                                                             \
  _(vqaddq_u8)                                                              \
  _(vqaddq_u16)                                                             \
  _(vqaddq_u32)                                                             \
  _(vqaddq_u64)                                                             \
  _(vaddhn_s16)                                                             \
  _(vaddhn_s32)                                                             \
  _(vaddhn_s64)                                                             \
  _(vaddhn_u16)                                                             \
  _(vaddhn_u32)                                                             \
  _(vaddhn_u64)                                                             \
  _(vraddhn_s16)                                                            \
  _(vraddhn_s32)                                                            \
  _(vraddhn_s64)                                                            \
  _(vraddhn_u16)                                                            \
  _(vraddhn_u32)                                                            \
  _(vraddhn_u64)                                                            \
  _(vmul_s8)                                                                \
  _(vmul_s16)                                                               \
  _(vmul_s32)                                                               \
  _(vmul_f32)                                                               \
  _(vmul_u8)                                                                \
  _(vmul_u16)                                                               \
  _(vmul_u32)                                                               \
  _(vmulq_s8)                                                               \
  _(vmulq_s16)                                                              \
  _(vmulq_s32)                                                              \
  _(vmulq_f32)                                                              \
  _(vmulq_u8)                                                               \
  _(vmulq_u16)                                                              \
  _(vmulq_u32)                                                              \
  /*_(vmul_p8)                                                           */ \
  /*_(vmulq_p8)                                                          */ \
  _(vqdmulh_s16)                                                            \
  _(vqdmulh_s32)                                                            \
  _(vqdmulhq_s16)                                                           \
  _(vqdmulhq_s32)                                                           \
  _(vqrdmulh_s16)                                                           \
  _(vqrdmulh_s32)                                                           \
  _(vqrdmulhq_s16)                                                          \
  _(vqrdmulhq_s32)                                                          \
  _(vqrdmlah_s16)                                                           \
  _(vqrdmlah_s32)                                                           \
  _(vqrdmlahq_s16)                                                          \
  _(vqrdmlahq_s32)                                                          \
  _(vqrdmlsh_s16)                                                           \
  _(vqrdmlsh_s32)                                                           \
  _(vqrdmlshq_s16)                                                          \
  _(vqrdmlshq_s32)                                                          \
  _(vmull_s8)                                                               \
  _(vmull_s16)                                                              \
  _(vmull_s32)                                                              \
  _(vmull_u8)                                                               \
  _(vmull_u16)                                                              \
  _(vmull_u32)                                                              \
  /*_(vmull_p8)                                                          */ \
  _(vqdmull_s16)                                                            \
  _(vqdmull_s32)                                                            \
  _(vmla_s8)                                                                \
  _(vmla_s16)                                                               \
  _(vmla_s32)                                                               \
  _(vmla_f32)                                                               \
  _(vmla_u8)                                                                \
  _(vmla_u16)                                                               \
  _(vmla_u32)                                                               \
  _(vmlaq_s8)                                                               \
  _(vmlaq_s16)                                                              \
  _(vmlaq_s32)                                                              \
  _(vmlaq_f32)                                                              \
  _(vmlaq_u8)                                                               \
  _(vmlaq_u16)                                                              \
  _(vmlaq_u32)                                                              \
  _(vmlal_s8)                                                               \
  _(vmlal_s16)                                                              \
  _(vmlal_s32)                                                              \
  _(vmlal_u8)                                                               \
  _(vmlal_u16)                                                              \
  _(vmlal_u32)                                                              \
  _(vqdmlal_s16)                                                            \
  _(vqdmlal_s32)                                                            \
  _(vmls_s8)                                                                \
  _(vmls_s16)                                                               \
  _(vmls_s32)                                                               \
  _(vmls_f32)                                                               \
  _(vmls_u8)                                                                \
  _(vmls_u16)                                                               \
  _(vmls_u32)                                                               \
  _(vmlsq_s8)                                                               \
  _(vmlsq_s16)                                                              \
  _(vmlsq_s32)                                                              \
  _(vmlsq_f32)                                                              \
  _(vmlsq_u8)                                                               \
  _(vmlsq_u16)                                                              \
  _(vmlsq_u32)                                                              \
  _(vmlsl_s8)                                                               \
  _(vmlsl_s16)                                                              \
  _(vmlsl_s32)                                                              \
  _(vmlsl_u8)                                                               \
  _(vmlsl_u16)                                                              \
  _(vmlsl_u32)                                                              \
  _(vqdmlsl_s16)                                                            \
  _(vqdmlsl_s32)                                                            \
  _(vfma_f32)                                                               \
  _(vfmaq_f32)                                                              \
  _(vfms_f32)                                                               \
  _(vfmsq_f32)                                                              \
  _(vrndn_f32)                                                              \
  _(vrndnq_f32)                                                             \
  _(vrnda_f32)                                                              \
  _(vrndaq_f32)                                                             \
  _(vrndp_f32)                                                              \
  _(vrndpq_f32)                                                             \
  _(vrndm_f32)                                                              \
  _(vrndmq_f32)                                                             \
  _(vrndx_f32)                                                              \
  _(vrndxq_f32)                                                             \
  _(vrnd_f32)                                                               \
  _(vrndq_f32)                                                              \
  _(vsub_s8)                                                                \
  _(vsub_s16)                                                               \
  _(vsub_s32)                                                               \
  _(vsub_f32)                                                               \
  _(vsub_u8)                                                                \
  _(vsub_u16)                                                               \
  _(vsub_u32)                                                               \
  _(vsub_s64)                                                               \
  _(vsub_u64)                                                               \
  _(vsubq_s8)                                                               \
  _(vsubq_s16)                                                              \
  _(vsubq_s32)                                                              \
  _(vsubq_s64)                                                              \
  _(vsubq_f32)                                                              \
  _(vsubq_u8)                                                               \
  _(vsubq_u16)                                                              \
  _(vsubq_u32)                                                              \
  _(vsubq_u64)                                                              \
  _(vsubl_s8)                                                               \
  _(vsubl_s16)                                                              \
  _(vsubl_s32)                                                              \
  _(vsubl_u8)                                                               \
  _(vsubl_u16)                                                              \
  _(vsubl_u32)                                                              \
  _(vsubw_s8)                                                               \
  _(vsubw_s16)                                                              \
  _(vsubw_s32)                                                              \
  _(vsubw_u8)                                                               \
  _(vsubw_u16)                                                              \
  _(vsubw_u32)                                                              \
  _(vhsub_s8)                                                               \
  _(vhsub_s16)                                                              \
  _(vhsub_s32)                                                              \
  _(vhsub_u8)                                                               \
  _(vhsub_u16)                                                              \
  _(vhsub_u32)                                                              \
  _(vhsubq_s8)                                                              \
  _(vhsubq_s16)                                                             \
  _(vhsubq_s32)                                                             \
  _(vhsubq_u8)                                                              \
  _(vhsubq_u16)                                                             \
  _(vhsubq_u32)                                                             \
  _(vqsub_s8)                                                               \
  _(vqsub_s16)                                                              \
  _(vqsub_s32)                                                              \
  _(vqsub_s64)                                                              \
  _(vqsub_u8)                                                               \
  _(vqsub_u16)                                                              \
  _(vqsub_u32)                                                              \
  _(vqsub_u64)                                                              \
  _(vqsubq_s8)                                                              \
  _(vqsubq_s16)                                                             \
  _(vqsubq_s32)                                                             \
  _(vqsubq_s64)                                                             \
  _(vqsubq_u8)                                                              \
  _(vqsubq_u16)                                                             \
  _(vqsubq_u32)                                                             \
  _(vqsubq_u64)                                                             \
  _(vsubhn_s16)                                                             \
  _(vsubhn_s32)                                                             \
  _(vsubhn_s64)                                                             \
  _(vsubhn_u16)                                                             \
  _(vsubhn_u32)                                                             \
  _(vsubhn_u64)                                                             \
  _(vrsubhn_s16)                                                            \
  _(vrsubhn_s32)                                                            \
  _(vrsubhn_s64)                                                            \
  _(vrsubhn_u16)                                                            \
  _(vrsubhn_u32)                                                            \
  _(vrsubhn_u64)                                                            \
  _(vceq_s8)                                                                \
  _(vceq_s16)                                                               \
  _(vceq_s32)                                                               \
  _(vceq_f32)                                                               \
  _(vceq_u8)                                                                \
  _(vceq_u16)                                                               \
  _(vceq_u32)                                                               \
  /*_(vceq_p8)                                                           */ \
  _(vceqq_s8)                                                               \
  _(vceqq_s16)                                                              \
  _(vceqq_s32)                                                              \
  _(vceqq_f32)                                                              \
  _(vceqq_u8)                                                               \
  _(vceqq_u16)                                                              \
  _(vceqq_u32)                                                              \
  /*_(vceqq_p8)                                                          */ \
  _(vcge_s8)                                                                \
  _(vcge_s16)                                                               \
  _(vcge_s32)                                                               \
  _(vcge_f32)                                                               \
  _(vcge_u8)                                                                \
  _(vcge_u16)                                                               \
  _(vcge_u32)                                                               \
  _(vcgeq_s8)                                                               \
  _(vcgeq_s16)                                                              \
  _(vcgeq_s32)                                                              \
  _(vcgeq_f32)                                                              \
  _(vcgeq_u8)                                                               \
  _(vcgeq_u16)                                                              \
  _(vcgeq_u32)                                                              \
  _(vcle_s8)                                                                \
  _(vcle_s16)                                                               \
  _(vcle_s32)                                                               \
  _(vcle_f32)                                                               \
  _(vcle_u8)                                                                \
  _(vcle_u16)                                                               \
  _(vcle_u32)                                                               \
  _(vcleq_s8)                                                               \
  _(vcleq_s16)                                                              \
  _(vcleq_s32)                                                              \
  _(vcleq_f32)                                                              \
  _(vcleq_u8)                                                               \
  _(vcleq_u16)                                                              \
  _(vcleq_u32)                                                              \
  _(vcgt_s8)                                                                \
  _(vcgt_s16)                                                               \
  _(vcgt_s32)                                                               \
  _(vcgt_f32)                                                               \
  _(vcgt_u8)                                                                \
  _(vcgt_u16)                                                               \
  _(vcgt_u32)                                                               \
  _(vcgtq_s8)                                                               \
  _(vcgtq_s16)                                                              \
  _(vcgtq_s32)                                                              \
  _(vcgtq_f32)                                                              \
  _(vcgtq_u8)                                                               \
  _(vcgtq_u16)                                                              \
  _(vcgtq_u32)                                                              \
  _(vclt_s8)                                                                \
  _(vclt_s16)                                                               \
  _(vclt_s32)                                                               \
  _(vclt_f32)                                                               \
  _(vclt_u8)                                                                \
  _(vclt_u16)                                                               \
  _(vclt_u32)                                                               \
  _(vcltq_s8)                                                               \
  _(vcltq_s16)                                                              \
  _(vcltq_s32)                                                              \
  _(vcltq_f32)                                                              \
  _(vcltq_u8)                                                               \
  _(vcltq_u16)                                                              \
  _(vcltq_u32)                                                              \
  _(vabs_s8)                                                                \
  _(vabs_s16)                                                               \
  _(vabs_s32)                                                               \
  _(vabs_f32)                                                               \
  _(vabsq_s8)                                                               \
  _(vabsq_s16)                                                              \
  _(vabsq_s32)                                                              \
  _(vabsq_f32)                                                              \
  _(vqabs_s8)                                                               \
  _(vqabs_s16)                                                              \
  _(vqabs_s32)                                                              \
  _(vqabsq_s8)                                                              \
  _(vqabsq_s16)                                                             \
  _(vqabsq_s32)                                                             \
  _(vcage_f32)                                                              \
  _(vcageq_f32)                                                             \
  _(vcale_f32)                                                              \
  _(vcaleq_f32)                                                             \
  _(vcagt_f32)                                                              \
  _(vcagtq_f32)                                                             \
  _(vcalt_f32)                                                              \
  _(vcaltq_f32)                                                             \
  _(vtst_s8)                                                                \
  _(vtst_s16)                                                               \
  _(vtst_s32)                                                               \
  _(vtst_u8)                                                                \
  _(vtst_u16)                                                               \
  _(vtst_u32)                                                               \
  /*_(vtst_p8)                                                           */ \
  /*_(vtst_p16)                                                          */ \
  _(vtstq_s8)                                                               \
  _(vtstq_s16)                                                              \
  _(vtstq_s32)                                                              \
  _(vtstq_u8)                                                               \
  _(vtstq_u16)                                                              \
  _(vtstq_u32)                                                              \
  /*_(vtstq_p8)                                                          */ \
  /*_(vtstq_p16)                                                         */ \
  _(vabd_s8)                                                                \
  _(vabd_s16)                                                               \
  _(vabd_s32)                                                               \
  _(vabd_f32)                                                               \
  _(vabd_u8)                                                                \
  _(vabd_u16)                                                               \
  _(vabd_u32)                                                               \
  _(vabdq_s8)                                                               \
  _(vabdq_s16)                                                              \
  _(vabdq_s32)                                                              \
  _(vabdq_f32)                                                              \
  _(vabdq_u8)                                                               \
  _(vabdq_u16)                                                              \
  _(vabdq_u32)                                                              \
  _(vabdl_s8)                                                               \
  _(vabdl_s16)                                                              \
  _(vabdl_s32)                                                              \
  _(vabdl_u8)                                                               \
  _(vabdl_u16)                                                              \
  _(vabdl_u32)                                                              \
  _(vaba_s8)                                                                \
  _(vaba_s16)                                                               \
  _(vaba_s32)                                                               \
  _(vaba_u8)                                                                \
  _(vaba_u16)                                                               \
  _(vaba_u32)                                                               \
  _(vabaq_s8)                                                               \
  _(vabaq_s16)                                                              \
  _(vabaq_s32)                                                              \
  _(vabaq_u8)                                                               \
  _(vabaq_u16)                                                              \
  _(vabaq_u32)                                                              \
  _(vabal_s8)                                                               \
  _(vabal_s16)                                                              \
  _(vabal_s32)                                                              \
  _(vabal_u8)                                                               \
  _(vabal_u16)                                                              \
  _(vabal_u32)                                                              \
  _(vmax_s8)                                                                \
  _(vmax_s16)                                                               \
  _(vmax_s32)                                                               \
  _(vmax_f32)                                                               \
  _(vmax_u8)                                                                \
  _(vmax_u16)                                                               \
  _(vmax_u32)                                                               \
  _(vmaxq_s8)                                                               \
  _(vmaxq_s16)                                                              \
  _(vmaxq_s32)                                                              \
  _(vmaxq_f32)                                                              \
  _(vmaxnm_f32)                                                             \
  _(vmaxnmq_f32)                                                            \
  _(vminnm_f32)                                                             \
  _(vminnmq_f32)                                                            \
  _(vmaxq_u8)                                                               \
  _(vmaxq_u16)                                                              \
  _(vmaxq_u32)                                                              \
  _(vmin_s8)                                                                \
  _(vmin_s16)                                                               \
  _(vmin_s32)                                                               \
  _(vmin_f32)                                                               \
  _(vmin_u8)                                                                \
  _(vmin_u16)                                                               \
  _(vmin_u32)                                                               \
  _(vminq_s8)                                                               \
  _(vminq_s16)                                                              \
  _(vminq_s32)                                                              \
  _(vminq_f32)                                                              \
  _(vminq_u8)                                                               \
  _(vminq_u16)                                                              \
  _(vminq_u32)                                                              \
  _(vpadd_s8)                                                               \
  _(vpadd_s16)                                                              \
  _(vpadd_s32)                                                              \
  _(vpadd_f32)                                                              \
  _(vpadd_u8)                                                               \
  _(vpadd_u16)                                                              \
  _(vpadd_u32)                                                              \
  _(vpaddl_s8)                                                              \
  _(vpaddl_s16)                                                             \
  _(vpaddl_s32)                                                             \
  _(vpaddl_u8)                                                              \
  _(vpaddl_u16)                                                             \
  _(vpaddl_u32)                                                             \
  _(vpaddlq_s8)                                                             \
  _(vpaddlq_s16)                                                            \
  _(vpaddlq_s32)                                                            \
  _(vpaddlq_u8)                                                             \
  _(vpaddlq_u16)                                                            \
  _(vpaddlq_u32)                                                            \
  _(vpadal_s8)                                                              \
  _(vpadal_s16)                                                             \
  _(vpadal_s32)                                                             \
  _(vpadal_u8)                                                              \
  _(vpadal_u16)                                                             \
  _(vpadal_u32)                                                             \
  _(vpadalq_s8)                                                             \
  _(vpadalq_s16)                                                            \
  _(vpadalq_s32)                                                            \
  _(vpadalq_u8)                                                             \
  _(vpadalq_u16)                                                            \
  _(vpadalq_u32)                                                            \
  _(vpmax_s8)                                                               \
  _(vpmax_s16)                                                              \
  _(vpmax_s32)                                                              \
  _(vpmax_f32)                                                              \
  _(vpmax_u8)                                                               \
  _(vpmax_u16)                                                              \
  _(vpmax_u32)                                                              \
  _(vpmin_s8)                                                               \
  _(vpmin_s16)                                                              \
  _(vpmin_s32)                                                              \
  _(vpmin_f32)                                                              \
  _(vpmin_u8)                                                               \
  _(vpmin_u16)                                                              \
  _(vpmin_u32)                                                              \
  _(vrecps_f32)                                                             \
  _(vrecpsq_f32)                                                            \
  _(vrsqrts_f32)                                                            \
  _(vrsqrtsq_f32)                                                           \
  _(vshl_s8)                                                                \
  _(vshl_s16)                                                               \
  _(vshl_s32)                                                               \
  _(vshl_s64)                                                               \
  _(vshl_u8)                                                                \
  _(vshl_u16)                                                               \
  _(vshl_u32)                                                               \
  _(vshl_u64)                                                               \
  _(vshlq_s8)                                                               \
  _(vshlq_s16)                                                              \
  _(vshlq_s32)                                                              \
  _(vshlq_s64)                                                              \
  _(vshlq_u8)                                                               \
  _(vshlq_u16)                                                              \
  _(vshlq_u32)                                                              \
  _(vshlq_u64)                                                              \
  _(vrshl_s8)                                                               \
  _(vrshl_s16)                                                              \
  _(vrshl_s32)                                                              \
  _(vrshl_s64)                                                              \
  _(vrshl_u8)                                                               \
  _(vrshl_u16)                                                              \
  _(vrshl_u32)                                                              \
  _(vrshl_u64)                                                              \
  _(vrshlq_s8)                                                              \
  _(vrshlq_s16)                                                             \
  _(vrshlq_s32)                                                             \
  _(vrshlq_s64)                                                             \
  _(vrshlq_u8)                                                              \
  _(vrshlq_u16)                                                             \
  _(vrshlq_u32)                                                             \
  _(vrshlq_u64)                                                             \
  _(vqshl_s8)                                                               \
  _(vqshl_s16)                                                              \
  _(vqshl_s32)                                                              \
  _(vqshl_s64)                                                              \
  _(vqshl_u8)                                                               \
  _(vqshl_u16)                                                              \
  _(vqshl_u32)                                                              \
  _(vqshl_u64)                                                              \
  _(vqshlq_s8)                                                              \
  _(vqshlq_s16)                                                             \
  _(vqshlq_s32)                                                             \
  _(vqshlq_s64)                                                             \
  _(vqshlq_u8)                                                              \
  _(vqshlq_u16)                                                             \
  _(vqshlq_u32)                                                             \
  _(vqshlq_u64)                                                             \
  _(vqrshl_s8)                                                              \
  _(vqrshl_s16)                                                             \
  _(vqrshl_s32)                                                             \
  _(vqrshl_s64)                                                             \
  _(vqrshl_u8)                                                              \
  _(vqrshl_u16)                                                             \
  _(vqrshl_u32)                                                             \
  _(vqrshl_u64)                                                             \
  _(vqrshlq_s8)                                                             \
  _(vqrshlq_s16)                                                            \
  _(vqrshlq_s32)                                                            \
  _(vqrshlq_s64)                                                            \
  _(vqrshlq_u8)                                                             \
  _(vqrshlq_u16)                                                            \
  _(vqrshlq_u32)                                                            \
  _(vqrshlq_u64)                                                            \
  _(vshr_n_s8)                                                              \
  _(vshr_n_s16)                                                             \
  _(vshr_n_s32)                                                             \
  _(vshr_n_s64)                                                             \
  _(vshr_n_u8)                                                              \
  _(vshr_n_u16)                                                             \
  _(vshr_n_u32)                                                             \
  _(vshr_n_u64)                                                             \
  _(vshrq_n_s8)                                                             \
  _(vshrq_n_s16)                                                            \
  _(vshrq_n_s32)                                                            \
  _(vshrq_n_s64)                                                            \
  _(vshrq_n_u8)                                                             \
  _(vshrq_n_u16)                                                            \
  _(vshrq_n_u32)                                                            \
  _(vshrq_n_u64)                                                            \
  _(vrshr_n_s8)                                                             \
  _(vrshr_n_s16)                                                            \
  _(vrshr_n_s32)                                                            \
  _(vrshr_n_s64)                                                            \
  _(vrshr_n_u8)                                                             \
  _(vrshr_n_u16)                                                            \
  _(vrshr_n_u32)                                                            \
  _(vrshr_n_u64)                                                            \
  _(vrshrq_n_s8)                                                            \
  _(vrshrq_n_s16)                                                           \
  _(vrshrq_n_s32)                                                           \
  _(vrshrq_n_s64)                                                           \
  _(vrshrq_n_u8)                                                            \
  _(vrshrq_n_u16)                                                           \
  _(vrshrq_n_u32)                                                           \
  _(vrshrq_n_u64)                                                           \
  _(vshrn_n_s16)                                                            \
  _(vshrn_n_s32)                                                            \
  _(vshrn_n_s64)                                                            \
  _(vshrn_n_u16)                                                            \
  _(vshrn_n_u32)                                                            \
  _(vshrn_n_u64)                                                            \
  _(vrshrn_n_s16)                                                           \
  _(vrshrn_n_s32)                                                           \
  _(vrshrn_n_s64)                                                           \
  _(vrshrn_n_u16)                                                           \
  _(vrshrn_n_u32)                                                           \
  _(vrshrn_n_u64)                                                           \
  _(vqshrn_n_s16)                                                           \
  _(vqshrn_n_s32)                                                           \
  _(vqshrn_n_s64)                                                           \
  _(vqshrn_n_u16)                                                           \
  _(vqshrn_n_u32)                                                           \
  _(vqshrn_n_u64)                                                           \
  _(vqrshrn_n_s16)                                                          \
  _(vqrshrn_n_s32)                                                          \
  _(vqrshrn_n_s64)                                                          \
  _(vqrshrn_n_u16)                                                          \
  _(vqrshrn_n_u32)                                                          \
  _(vqrshrn_n_u64)                                                          \
  _(vqshrun_n_s16)                                                          \
  _(vqshrun_n_s32)                                                          \
  _(vqshrun_n_s64)                                                          \
  _(vqrshrun_n_s16)                                                         \
  _(vqrshrun_n_s32)                                                         \
  _(vqrshrun_n_s64)                                                         \
  _(vshl_n_s8)                                                              \
  _(vshl_n_s16)                                                             \
  _(vshl_n_s32)                                                             \
  _(vshl_n_s64)                                                             \
  _(vshl_n_u8)                                                              \
  _(vshl_n_u16)                                                             \
  _(vshl_n_u32)                                                             \
  _(vshl_n_u64)                                                             \
  _(vshlq_n_s8)                                                             \
  _(vshlq_n_s16)                                                            \
  _(vshlq_n_s32)                                                            \
  _(vshlq_n_s64)                                                            \
  _(vshlq_n_u8)                                                             \
  _(vshlq_n_u16)                                                            \
  _(vshlq_n_u32)                                                            \
  _(vshlq_n_u64)                                                            \
  _(vqshl_n_s8)                                                             \
  _(vqshl_n_s16)                                                            \
  _(vqshl_n_s32)                                                            \
  _(vqshl_n_s64)                                                            \
  _(vqshl_n_u8)                                                             \
  _(vqshl_n_u16)                                                            \
  _(vqshl_n_u32)                                                            \
  _(vqshl_n_u64)                                                            \
  _(vqshlq_n_s8)                                                            \
  _(vqshlq_n_s16)                                                           \
  _(vqshlq_n_s32)                                                           \
  _(vqshlq_n_s64)                                                           \
  _(vqshlq_n_u8)                                                            \
  _(vqshlq_n_u16)                                                           \
  _(vqshlq_n_u32)                                                           \
  _(vqshlq_n_u64)                                                           \
  _(vqshlu_n_s8)                                                            \
  _(vqshlu_n_s16)                                                           \
  _(vqshlu_n_s32)                                                           \
  _(vqshlu_n_s64)                                                           \
  _(vqshluq_n_s8)                                                           \
  _(vqshluq_n_s16)                                                          \
  _(vqshluq_n_s32)                                                          \
  _(vqshluq_n_s64)                                                          \
  _(vshll_n_s8)                                                             \
  _(vshll_n_s16)                                                            \
  _(vshll_n_s32)                                                            \
  _(vshll_n_u8)                                                             \
  _(vshll_n_u16)                                                            \
  _(vshll_n_u32)                                                            \
  _(vsra_n_s8)                                                              \
  _(vsra_n_s16)                                                             \
  _(vsra_n_s32)                                                             \
  _(vsra_n_s64)                                                             \
  _(vsra_n_u8)                                                              \
  _(vsra_n_u16)                                                             \
  _(vsra_n_u32)                                                             \
  _(vsra_n_u64)                                                             \
  _(vsraq_n_s8)                                                             \
  _(vsraq_n_s16)                                                            \
  _(vsraq_n_s32)                                                            \
  _(vsraq_n_s64)                                                            \
  _(vsraq_n_u8)                                                             \
  _(vsraq_n_u16)                                                            \
  _(vsraq_n_u32)                                                            \
  _(vsraq_n_u64)                                                            \
  _(vrsra_n_s8)                                                             \
  _(vrsra_n_s16)                                                            \
  _(vrsra_n_s32)                                                            \
  _(vrsra_n_s64)                                                            \
  _(vrsra_n_u8)                                                             \
  _(vrsra_n_u16)                                                            \
  _(vrsra_n_u32)                                                            \
  _(vrsra_n_u64)                                                            \
  _(vrsraq_n_s8)                                                            \
  _(vrsraq_n_s16)                                                           \
  _(vrsraq_n_s32)                                                           \
  _(vrsraq_n_s64)                                                           \
  _(vrsraq_n_u8)                                                            \
  _(vrsraq_n_u16)                                                           \
  _(vrsraq_n_u32)                                                           \
  _(vrsraq_n_u64)                                                           \
  /*_(vsri_n_p64)                                                        */ \
  _(vsri_n_s8)                                                              \
  _(vsri_n_s16)                                                             \
  _(vsri_n_s32)                                                             \
  _(vsri_n_s64)                                                             \
  _(vsri_n_u8)                                                              \
  _(vsri_n_u16)                                                             \
  _(vsri_n_u32)                                                             \
  _(vsri_n_u64)                                                             \
  /*_(vsri_n_p8)                                                         */ \
  /*_(vsri_n_p16)                                                        */ \
  /*_(vsriq_n_p64)                                                       */ \
  _(vsriq_n_s8)                                                             \
  _(vsriq_n_s16)                                                            \
  _(vsriq_n_s32)                                                            \
  _(vsriq_n_s64)                                                            \
  _(vsriq_n_u8)                                                             \
  _(vsriq_n_u16)                                                            \
  _(vsriq_n_u32)                                                            \
  _(vsriq_n_u64)                                                            \
  /*_(vsriq_n_p8)                                                        */ \
  /*_(vsriq_n_p16)                                                       */ \
  /*_(vsli_n_p64)                                                        */ \
  _(vsli_n_s8)                                                              \
  _(vsli_n_s16)                                                             \
  _(vsli_n_s32)                                                             \
  _(vsli_n_s64)                                                             \
  _(vsli_n_u8)                                                              \
  _(vsli_n_u16)                                                             \
  _(vsli_n_u32)                                                             \
  _(vsli_n_u64)                                                             \
  /*_(vsli_n_p8)                                                         */ \
  /*_(vsli_n_p16)                                                        */ \
  /*_(vsliq_n_p64)                                                       */ \
  _(vsliq_n_s8)                                                             \
  _(vsliq_n_s16)                                                            \
  _(vsliq_n_s32)                                                            \
  _(vsliq_n_s64)                                                            \
  _(vsliq_n_u8)                                                             \
  _(vsliq_n_u16)                                                            \
  _(vsliq_n_u32)                                                            \
  _(vsliq_n_u64)                                                            \
  /*_(vsliq_n_p8)                                                        */ \
  /*_(vsliq_n_p16)                                                       */ \
  _(vneg_s8)                                                                \
  _(vneg_s16)                                                               \
  _(vneg_s32)                                                               \
  _(vneg_f32)                                                               \
  _(vnegq_s8)                                                               \
  _(vnegq_s16)                                                              \
  _(vnegq_s32)                                                              \
  _(vnegq_f32)                                                              \
  _(vqneg_s8)                                                               \
  _(vqneg_s16)                                                              \
  _(vqneg_s32)                                                              \
  _(vqnegq_s8)                                                              \
  _(vqnegq_s16)                                                             \
  _(vqnegq_s32)                                                             \
  _(vmvn_s8)                                                                \
  _(vmvn_s16)                                                               \
  _(vmvn_s32)                                                               \
  _(vmvn_u8)                                                                \
  _(vmvn_u16)                                                               \
  _(vmvn_u32)                                                               \
  /*_(vmvn_p8)                                                           */ \
  _(vmvnq_s8)                                                               \
  _(vmvnq_s16)                                                              \
  _(vmvnq_s32)                                                              \
  _(vmvnq_u8)                                                               \
  _(vmvnq_u16)                                                              \
  _(vmvnq_u32)                                                              \
  /*_(vmvnq_p8)                                                          */ \
  _(vcls_s8)                                                                \
  _(vcls_s16)                                                               \
  _(vcls_s32)                                                               \
  _(vclsq_s8)                                                               \
  _(vclsq_s16)                                                              \
  _(vclsq_s32)                                                              \
  _(vclz_s8)                                                                \
  _(vclz_s16)                                                               \
  _(vclz_s32)                                                               \
  _(vclz_u8)                                                                \
  _(vclz_u16)                                                               \
  _(vclz_u32)                                                               \
  _(vclzq_s8)                                                               \
  _(vclzq_s16)                                                              \
  _(vclzq_s32)                                                              \
  _(vclzq_u8)                                                               \
  _(vclzq_u16)                                                              \
  _(vclzq_u32)                                                              \
  _(vcnt_s8)                                                                \
  _(vcnt_u8)                                                                \
  /*_(vcnt_p8)                                                           */ \
  _(vcntq_s8)                                                               \
  _(vcntq_u8)                                                               \
  /*_(vcntq_p8)                                                          */ \
  _(vrecpe_f32)                                                             \
  _(vrecpe_u32)                                                             \
  _(vrecpeq_f32)                                                            \
  _(vrecpeq_u32)                                                            \
  _(vrsqrte_f32)                                                            \
  _(vrsqrte_u32)                                                            \
  _(vrsqrteq_f32)                                                           \
  _(vrsqrteq_u32)                                                           \
  _(vget_lane_s8)                                                           \
  _(vget_lane_s16)                                                          \
  _(vget_lane_s32)                                                          \
  _(vget_lane_f32)                                                          \
  _(vget_lane_u8)                                                           \
  _(vget_lane_u16)                                                          \
  _(vget_lane_u32)                                                          \
  /*_(vget_lane_p8)                                                      */ \
  /*_(vget_lane_p16)                                                     */ \
  _(vget_lane_s64)                                                          \
  /*_(vget_lane_p64)                                                     */ \
  _(vget_lane_u64)                                                          \
  _(vgetq_lane_s8)                                                          \
  _(vgetq_lane_s16)                                                         \
  _(vgetq_lane_s32)                                                         \
  _(vgetq_lane_f32)                                                         \
  _(vgetq_lane_u8)                                                          \
  _(vgetq_lane_u16)                                                         \
  _(vgetq_lane_u32)                                                         \
  /*_(vgetq_lane_p8)                                                     */ \
  /*_(vgetq_lane_p16)                                                    */ \
  _(vgetq_lane_s64)                                                         \
  /*_(vgetq_lane_p64)                                                    */ \
  _(vgetq_lane_u64)                                                         \
  _(vset_lane_s8)                                                           \
  _(vset_lane_s16)                                                          \
  _(vset_lane_s32)                                                          \
  _(vset_lane_f32)                                                          \
  _(vset_lane_u8)                                                           \
  _(vset_lane_u16)                                                          \
  _(vset_lane_u32)                                                          \
  /*_(vset_lane_p8)                                                      */ \
  /*_(vset_lane_p16)                                                     */ \
  _(vset_lane_s64)                                                          \
  _(vset_lane_u64)                                                          \
  /*_(vset_lane_p64)                                                     */ \
  _(vsetq_lane_s8)                                                          \
  _(vsetq_lane_s16)                                                         \
  _(vsetq_lane_s32)                                                         \
  _(vsetq_lane_f32)                                                         \
  _(vsetq_lane_u8)                                                          \
  _(vsetq_lane_u16)                                                         \
  _(vsetq_lane_u32)                                                         \
  /*_(vsetq_lane_p8)                                                     */ \
  /*_(vsetq_lane_p16)                                                    */ \
  _(vsetq_lane_s64)                                                         \
  _(vsetq_lane_u64)                                                         \
  /*_(vsetq_lane_p64)                                                    */ \
  /*_(vcreate_p64)                                                       */ \
  _(vcreate_s8)                                                             \
  _(vcreate_s16)                                                            \
  _(vcreate_s32)                                                            \
  _(vcreate_s64)                                                            \
  /*_(vcreate_f16)                                                       */ \
  _(vcreate_f32)                                                            \
  _(vcreate_u8)                                                             \
  _(vcreate_u16)                                                            \
  _(vcreate_u32)                                                            \
  _(vcreate_u64)                                                            \
  /*_(vcreate_p8)                                                        */ \
  /*_(vcreate_p16)                                                       */ \
  _(vdup_n_s8)                                                              \
  _(vdup_n_s16)                                                             \
  _(vdup_n_s32)                                                             \
  _(vdup_n_f32)                                                             \
  _(vdup_n_u8)                                                              \
  _(vdup_n_u16)                                                             \
  _(vdup_n_u32)                                                             \
  /*_(vdup_n_p8)                                                         */ \
  /*_(vdup_n_p16)                                                        */ \
  /*_(vdup_n_p64)                                                        */ \
  _(vdup_n_s64)                                                             \
  _(vdup_n_u64)                                                             \
  /*_(vdupq_n_p64)                                                       */ \
  _(vdupq_n_s8)                                                             \
  _(vdupq_n_s16)                                                            \
  _(vdupq_n_s32)                                                            \
  _(vdupq_n_f32)                                                            \
  _(vdupq_n_u8)                                                             \
  _(vdupq_n_u16)                                                            \
  _(vdupq_n_u32)                                                            \
  /*_(vdupq_n_p8)                                                        */ \
  /*_(vdupq_n_p16)                                                       */ \
  _(vdupq_n_s64)                                                            \
  _(vdupq_n_u64)                                                            \
  _(vmov_n_s8)                                                              \
  _(vmov_n_s16)                                                             \
  _(vmov_n_s32)                                                             \
  _(vmov_n_f32)                                                             \
  _(vmov_n_u8)                                                              \
  _(vmov_n_u16)                                                             \
  _(vmov_n_u32)                                                             \
  /*_(vmov_n_p8)                                                         */ \
  /*_(vmov_n_p16)                                                        */ \
  _(vmov_n_s64)                                                             \
  _(vmov_n_u64)                                                             \
  _(vmovq_n_s8)                                                             \
  _(vmovq_n_s16)                                                            \
  _(vmovq_n_s32)                                                            \
  _(vmovq_n_f32)                                                            \
  _(vmovq_n_u8)                                                             \
  _(vmovq_n_u16)                                                            \
  _(vmovq_n_u32)                                                            \
  /*_(vmovq_n_p8)                                                        */ \
  /*_(vmovq_n_p16)                                                       */ \
  _(vmovq_n_s64)                                                            \
  _(vmovq_n_u64)                                                            \
  _(vdup_lane_s8)                                                           \
  _(vdup_lane_s16)                                                          \
  _(vdup_lane_s32)                                                          \
  _(vdup_lane_f32)                                                          \
  _(vdup_lane_u8)                                                           \
  _(vdup_lane_u16)                                                          \
  _(vdup_lane_u32)                                                          \
  /*_(vdup_lane_p8)                                                      */ \
  /*_(vdup_lane_p16)                                                     */ \
  /*_(vdup_lane_p64)                                                     */ \
  _(vdup_lane_s64)                                                          \
  _(vdup_lane_u64)                                                          \
  _(vdupq_lane_s8)                                                          \
  _(vdupq_lane_s16)                                                         \
  _(vdupq_lane_s32)                                                         \
  _(vdupq_lane_f32)                                                         \
  _(vdupq_lane_u8)                                                          \
  _(vdupq_lane_u16)                                                         \
  _(vdupq_lane_u32)                                                         \
  /*_(vdupq_lane_p8)                                                     */ \
  /*_(vdupq_lane_p16)                                                    */ \
  /*_(vdupq_lane_p64)                                                    */ \
  _(vdupq_lane_s64)                                                         \
  _(vdupq_lane_u64)                                                         \
  /*_(vcombine_p64)                                                      */ \
  _(vcombine_s8)                                                            \
  _(vcombine_s16)                                                           \
  _(vcombine_s32)                                                           \
  _(vcombine_s64)                                                           \
  /*_(vcombine_f16)                                                      */ \
  _(vcombine_f32)                                                           \
  _(vcombine_u8)                                                            \
  _(vcombine_u16)                                                           \
  _(vcombine_u32)                                                           \
  _(vcombine_u64)                                                           \
  /*_(vcombine_p8)                                                       */ \
  /*_(vcombine_p16)                                                      */ \
  /*_(vget_high_p64)                                                     */ \
  _(vget_high_s8)                                                           \
  _(vget_high_s16)                                                          \
  _(vget_high_s32)                                                          \
  _(vget_high_s64)                                                          \
  /*_(vget_high_f16)                                                     */ \
  _(vget_high_f32)                                                          \
  _(vget_high_u8)                                                           \
  _(vget_high_u16)                                                          \
  _(vget_high_u32)                                                          \
  _(vget_high_u64)                                                          \
  /*_(vget_high_p8)                                                      */ \
  /*_(vget_high_p16)                                                     */ \
  _(vget_low_s8)                                                            \
  _(vget_low_s16)                                                           \
  _(vget_low_s32)                                                           \
  /*_(vget_low_f16)                                                      */ \
  _(vget_low_f32)                                                           \
  _(vget_low_u8)                                                            \
  _(vget_low_u16)                                                           \
  _(vget_low_u32)                                                           \
  /*_(vget_low_p8)                                                       */ \
  /*_(vget_low_p16)                                                      */ \
  /*_(vget_low_p64)                                                      */ \
  _(vget_low_s64)                                                           \
  _(vget_low_u64)                                                           \
  _(vcvt_s32_f32)                                                           \
  _(vcvt_f32_s32)                                                           \
  _(vcvt_f32_u32)                                                           \
  _(vcvt_u32_f32)                                                           \
  _(vcvtq_s32_f32)                                                          \
  _(vcvtq_f32_s32)                                                          \
  _(vcvtq_f32_u32)                                                          \
  _(vcvtq_u32_f32)                                                          \
  /*_(vcvt_f16_f32)                                                      */ \
  /*_(vcvt_f32_f16)                                                      */ \
  _(vcvt_n_s32_f32)                                                         \
  _(vcvt_n_f32_s32)                                                         \
  _(vcvt_n_f32_u32)                                                         \
  _(vcvt_n_u32_f32)                                                         \
  _(vcvtq_n_s32_f32)                                                        \
  _(vcvtq_n_f32_s32)                                                        \
  _(vcvtq_n_f32_u32)                                                        \
  _(vcvtq_n_u32_f32)                                                        \
  _(vmovn_s16)                                                              \
  _(vmovn_s32)                                                              \
  _(vmovn_s64)                                                              \
  _(vmovn_u16)                                                              \
  _(vmovn_u32)                                                              \
  _(vmovn_u64)                                                              \
  _(vqmovn_s16)                                                             \
  _(vqmovn_s32)                                                             \
  _(vqmovn_s64)                                                             \
  _(vqmovn_u16)                                                             \
  _(vqmovn_u32)                                                             \
  _(vqmovn_u64)                                                             \
  _(vqmovun_s16)                                                            \
  _(vqmovun_s32)                                                            \
  _(vqmovun_s64)                                                            \
  _(vmovl_s8)                                                               \
  _(vmovl_s16)                                                              \
  _(vmovl_s32)                                                              \
  _(vmovl_u8)                                                               \
  _(vmovl_u16)                                                              \
  _(vmovl_u32)                                                              \
  _(vtbl1_s8)                                                               \
  _(vtbl1_u8)                                                               \
  /*_(vtbl1_p8)                                                          */ \
  _(vtbl2_s8)                                                               \
  _(vtbl2_u8)                                                               \
  /*_(vtbl2_p8)                                                          */ \
  _(vtbl3_s8)                                                               \
  _(vtbl3_u8)                                                               \
  /*_(vtbl3_p8)                                                          */ \
  _(vtbl4_s8)                                                               \
  _(vtbl4_u8)                                                               \
  /*_(vtbl4_p8)                                                          */ \
  _(vtbx1_s8)                                                               \
  _(vtbx1_u8)                                                               \
  /*_(vtbx1_p8)                                                          */ \
  _(vtbx2_s8)                                                               \
  _(vtbx2_u8)                                                               \
  /*_(vtbx2_p8)                                                          */ \
  _(vtbx3_s8)                                                               \
  _(vtbx3_u8)                                                               \
  /*_(vtbx3_p8)                                                          */ \
  _(vtbx4_s8)                                                               \
  _(vtbx4_u8)                                                               \
  /*_(vtbx4_p8)                                                          */ \
  _(vmul_lane_s16)                                                          \
  _(vmul_lane_s32)                                                          \
  _(vmul_lane_f32)                                                          \
  _(vmul_lane_u16)                                                          \
  _(vmul_lane_u32)                                                          \
  _(vmulq_lane_s16)                                                         \
  _(vmulq_lane_s32)                                                         \
  _(vmulq_lane_f32)                                                         \
  _(vmulq_lane_u16)                                                         \
  _(vmulq_lane_u32)                                                         \
  _(vmla_lane_s16)                                                          \
  _(vmla_lane_s32)                                                          \
  _(vmla_lane_f32)                                                          \
  _(vmla_lane_u16)                                                          \
  _(vmla_lane_u32)                                                          \
  _(vmlaq_lane_s16)                                                         \
  _(vmlaq_lane_s32)                                                         \
  _(vmlaq_lane_f32)                                                         \
  _(vmlaq_lane_u16)                                                         \
  _(vmlaq_lane_u32)                                                         \
  _(vmlal_lane_s16)                                                         \
  _(vmlal_lane_s32)                                                         \
  _(vmlal_lane_u16)                                                         \
  _(vmlal_lane_u32)                                                         \
  _(vqdmlal_lane_s16)                                                       \
  _(vqdmlal_lane_s32)                                                       \
  _(vmls_lane_s16)                                                          \
  _(vmls_lane_s32)                                                          \
  _(vmls_lane_f32)                                                          \
  _(vmls_lane_u16)                                                          \
  _(vmls_lane_u32)                                                          \
  _(vmlsq_lane_s16)                                                         \
  _(vmlsq_lane_s32)                                                         \
  _(vmlsq_lane_f32)                                                         \
  _(vmlsq_lane_u16)                                                         \
  _(vmlsq_lane_u32)                                                         \
  _(vmlsl_lane_s16)                                                         \
  _(vmlsl_lane_s32)                                                         \
  _(vmlsl_lane_u16)                                                         \
  _(vmlsl_lane_u32)                                                         \
  _(vqdmlsl_lane_s16)                                                       \
  _(vqdmlsl_lane_s32)                                                       \
  _(vmull_lane_s16)                                                         \
  _(vmull_lane_s32)                                                         \
  _(vmull_lane_u16)                                                         \
  _(vmull_lane_u32)                                                         \
  _(vqdmull_lane_s16)                                                       \
  _(vqdmull_lane_s32)                                                       \
  _(vqdmulhq_lane_s16)                                                      \
  _(vqdmulhq_lane_s32)                                                      \
  _(vqdmulh_lane_s16)                                                       \
  _(vqdmulh_lane_s32)                                                       \
  _(vqrdmulhq_lane_s16)                                                     \
  _(vqrdmulhq_lane_s32)                                                     \
  _(vqrdmulh_lane_s16)                                                      \
  _(vqrdmulh_lane_s32)                                                      \
  _(vqrdmlahq_lane_s16)                                                     \
  _(vqrdmlahq_lane_s32)                                                     \
  _(vqrdmlah_lane_s16)                                                      \
  _(vqrdmlah_lane_s32)                                                      \
  _(vqrdmlshq_lane_s16)                                                     \
  _(vqrdmlshq_lane_s32)                                                     \
  _(vqrdmlsh_lane_s16)                                                      \
  _(vqrdmlsh_lane_s32)                                                      \
  _(vmul_n_s16)                                                             \
  _(vmul_n_s32)                                                             \
  _(vmul_n_f32)                                                             \
  _(vmul_n_u16)                                                             \
  _(vmul_n_u32)                                                             \
  _(vmulq_n_s16)                                                            \
  _(vmulq_n_s32)                                                            \
  _(vmulq_n_f32)                                                            \
  _(vmulq_n_u16)                                                            \
  _(vmulq_n_u32)                                                            \
  _(vmull_n_s16)                                                            \
  _(vmull_n_s32)                                                            \
  _(vmull_n_u16)                                                            \
  _(vmull_n_u32)                                                            \
  _(vqdmull_n_s16)                                                          \
  _(vqdmull_n_s32)                                                          \
  _(vqdmulhq_n_s16)                                                         \
  _(vqdmulhq_n_s32)                                                         \
  _(vqdmulh_n_s16)                                                          \
  _(vqdmulh_n_s32)                                                          \
  _(vqrdmulhq_n_s16)                                                        \
  _(vqrdmulhq_n_s32)                                                        \
  _(vqrdmulh_n_s16)                                                         \
  _(vqrdmulh_n_s32)                                                         \
  _(vmla_n_s16)                                                             \
  _(vmla_n_s32)                                                             \
  _(vmla_n_f32)                                                             \
  _(vmla_n_u16)                                                             \
  _(vmla_n_u32)                                                             \
  _(vmlaq_n_s16)                                                            \
  _(vmlaq_n_s32)                                                            \
  _(vmlaq_n_f32)                                                            \
  _(vmlaq_n_u16)                                                            \
  _(vmlaq_n_u32)                                                            \
  _(vmlal_n_s16)                                                            \
  _(vmlal_n_s32)                                                            \
  _(vmlal_n_u16)                                                            \
  _(vmlal_n_u32)                                                            \
  _(vqdmlal_n_s16)                                                          \
  _(vqdmlal_n_s32)                                                          \
  _(vmls_n_s16)                                                             \
  _(vmls_n_s32)                                                             \
  _(vmls_n_f32)                                                             \
  _(vmls_n_u16)                                                             \
  _(vmls_n_u32)                                                             \
  _(vmlsq_n_s16)                                                            \
  _(vmlsq_n_s32)                                                            \
  _(vmlsq_n_f32)                                                            \
  _(vmlsq_n_u16)                                                            \
  _(vmlsq_n_u32)                                                            \
  _(vmlsl_n_s16)                                                            \
  _(vmlsl_n_s32)                                                            \
  _(vmlsl_n_u16)                                                            \
  _(vmlsl_n_u32)                                                            \
  _(vqdmlsl_n_s16)                                                          \
  _(vqdmlsl_n_s32)                                                          \
  /*_(vext_p64)                                                          */ \
  _(vext_s8)                                                                \
  _(vext_s16)                                                               \
  _(vext_s32)                                                               \
  _(vext_s64)                                                               \
  _(vext_f32)                                                               \
  _(vext_u8)                                                                \
  _(vext_u16)                                                               \
  _(vext_u32)                                                               \
  _(vext_u64)                                                               \
  /*_(vext_p8)                                                           */ \
  /*_(vext_p16)                                                          */ \
  /*_(vextq_p64)                                                         */ \
  _(vextq_s8)                                                               \
  _(vextq_s16)                                                              \
  _(vextq_s32)                                                              \
  _(vextq_s64)                                                              \
  _(vextq_f32)                                                              \
  _(vextq_u8)                                                               \
  _(vextq_u16)                                                              \
  _(vextq_u32)                                                              \
  _(vextq_u64)                                                              \
  /*_(vextq_p8)                                                          */ \
  /*_(vextq_p16)                                                         */ \
  _(vrev64_s8)                                                              \
  _(vrev64_s16)                                                             \
  _(vrev64_s32)                                                             \
  _(vrev64_f32)                                                             \
  _(vrev64_u8)                                                              \
  _(vrev64_u16)                                                             \
  _(vrev64_u32)                                                             \
  /*_(vrev64_p8)                                                         */ \
  /*_(vrev64_p16)                                                        */ \
  _(vrev64q_s8)                                                             \
  _(vrev64q_s16)                                                            \
  _(vrev64q_s32)                                                            \
  _(vrev64q_f32)                                                            \
  _(vrev64q_u8)                                                             \
  _(vrev64q_u16)                                                            \
  _(vrev64q_u32)                                                            \
  /*_(vrev64q_p8)                                                        */ \
  /*_(vrev64q_p16)                                                       */ \
  _(vrev32_s8)                                                              \
  _(vrev32_s16)                                                             \
  _(vrev32_u8)                                                              \
  _(vrev32_u16)                                                             \
  /*_(vrev32_p8)                                                         */ \
  /*_(vrev32_p16)                                                        */ \
  _(vrev32q_s8)                                                             \
  _(vrev32q_s16)                                                            \
  _(vrev32q_u8)                                                             \
  _(vrev32q_u16)                                                            \
  /*_(vrev32q_p8)                                                        */ \
  /*_(vrev32q_p16)                                                       */ \
  _(vrev16_s8)                                                              \
  _(vrev16_u8)                                                              \
  /*_(vrev16_p8)                                                         */ \
  _(vrev16q_s8)                                                             \
  _(vrev16q_u8)                                                             \
  /*_(vrev16q_p8)                                                        */ \
  /*_(vbsl_p64)                                                          */ \
  _(vbsl_s8)                                                                \
  _(vbsl_s16)                                                               \
  _(vbsl_s32)                                                               \
  _(vbsl_s64)                                                               \
  _(vbsl_f32)                                                               \
  _(vbsl_u8)                                                                \
  _(vbsl_u16)                                                               \
  _(vbsl_u32)                                                               \
  _(vbsl_u64)                                                               \
  /*_(vbsl_p8)                                                           */ \
  /*_(vbsl_p16)                                                          */ \
  /*_(vbslq_p64)                                                         */ \
  _(vbslq_s8)                                                               \
  _(vbslq_s16)                                                              \
  _(vbslq_s32)                                                              \
  _(vbslq_s64)                                                              \
  _(vbslq_f32)                                                              \
  _(vbslq_u8)                                                               \
  _(vbslq_u16)                                                              \
  _(vbslq_u32)                                                              \
  _(vbslq_u64)                                                              \
  /*_(vbslq_p8)                                                          */ \
  /*_(vbslq_p16)                                                         */ \
  _(vtrn_s8)                                                                \
  _(vtrn_s16)                                                               \
  _(vtrn_u8)                                                                \
  _(vtrn_u16)                                                               \
  /*_(vtrn_p8)                                                           */ \
  /*_(vtrn_p16)                                                          */ \
  _(vtrn_s32)                                                               \
  _(vtrn_f32)                                                               \
  _(vtrn_u32)                                                               \
  _(vtrnq_s8)                                                               \
  _(vtrnq_s16)                                                              \
  _(vtrnq_s32)                                                              \
  _(vtrnq_f32)                                                              \
  _(vtrnq_u8)                                                               \
  _(vtrnq_u16)                                                              \
  _(vtrnq_u32)                                                              \
  /*_(vtrnq_p8)                                                          */ \
  /*_(vtrnq_p16)                                                         */ \
  _(vzip_s8)                                                                \
  _(vzip_s16)                                                               \
  _(vzip_u8)                                                                \
  _(vzip_u16)                                                               \
  /*_(vzip_p8)                                                           */ \
  /*_(vzip_p16)                                                          */ \
  _(vzip_s32)                                                               \
  _(vzip_f32)                                                               \
  _(vzip_u32)                                                               \
  _(vzipq_s8)                                                               \
  _(vzipq_s16)                                                              \
  _(vzipq_s32)                                                              \
  _(vzipq_f32)                                                              \
  _(vzipq_u8)                                                               \
  _(vzipq_u16)                                                              \
  _(vzipq_u32)                                                              \
  /*_(vzipq_p8)                                                          */ \
  /*_(vzipq_p16)                                                         */ \
  _(vuzp_s8)                                                                \
  _(vuzp_s16)                                                               \
  _(vuzp_s32)                                                               \
  _(vuzp_f32)                                                               \
  _(vuzp_u8)                                                                \
  _(vuzp_u16)                                                               \
  _(vuzp_u32)                                                               \
  /*_(vuzp_p8)                                                           */ \
  /*_(vuzp_p16)                                                          */ \
  _(vuzpq_s8)                                                               \
  _(vuzpq_s16)                                                              \
  _(vuzpq_s32)                                                              \
  _(vuzpq_f32)                                                              \
  _(vuzpq_u8)                                                               \
  _(vuzpq_u16)                                                              \
  _(vuzpq_u32)                                                              \
  /*_(vuzpq_p8)                                                          */ \
  /*_(vuzpq_p16)                                                         */ \
  /*_(vld1_p64)                                                          */ \
  _(vld1_s8)                                                                \
  _(vld1_s16)                                                               \
  _(vld1_s32)                                                               \
  _(vld1_s64)                                                               \
  /*_(vld1_f16)                                                          */ \
  _(vld1_f32)                                                               \
  _(vld1_u8)                                                                \
  _(vld1_u16)                                                               \
  _(vld1_u32)                                                               \
  _(vld1_u64)                                                               \
  /*_(vld1_p8)                                                           */ \
  /*_(vld1_p16)                                                          */ \
  /*_(vld1q_p64)                                                         */ \
  _(vld1q_s8)                                                               \
  _(vld1q_s16)                                                              \
  _(vld1q_s32)                                                              \
  _(vld1q_s64)                                                              \
  /*_(vld1q_f16)                                                         */ \
  _(vld1q_f32)                                                              \
  _(vld1q_u8)                                                               \
  _(vld1q_u16)                                                              \
  _(vld1q_u32)                                                              \
  _(vld1q_u64)                                                              \
  /*_(vld1q_p8)                                                          */ \
  /*_(vld1q_p16)                                                         */ \
  _(vld1_lane_s8)                                                           \
  _(vld1_lane_s16)                                                          \
  _(vld1_lane_s32)                                                          \
  /*_(vld1_lane_f16)                                                     */ \
  _(vld1_lane_f32)                                                          \
  _(vld1_lane_u8)                                                           \
  _(vld1_lane_u16)                                                          \
  _(vld1_lane_u32)                                                          \
  /*_(vld1_lane_p8)                                                      */ \
  /*_(vld1_lane_p16)                                                     */ \
  /*_(vld1_lane_p64)                                                     */ \
  _(vld1_lane_s64)                                                          \
  _(vld1_lane_u64)                                                          \
  _(vld1q_lane_s8)                                                          \
  _(vld1q_lane_s16)                                                         \
  _(vld1q_lane_s32)                                                         \
  /*_(vld1q_lane_f16)                                                    */ \
  _(vld1q_lane_f32)                                                         \
  _(vld1q_lane_u8)                                                          \
  _(vld1q_lane_u16)                                                         \
  _(vld1q_lane_u32)                                                         \
  /*_(vld1q_lane_p8)                                                     */ \
  /*_(vld1q_lane_p16)                                                    */ \
  /*_(vld1q_lane_p64)                                                    */ \
  _(vld1q_lane_s64)                                                         \
  _(vld1q_lane_u64)                                                         \
  _(vld1_dup_s8)                                                            \
  _(vld1_dup_s16)                                                           \
  _(vld1_dup_s32)                                                           \
  /*_(vld1_dup_f16)                                                      */ \
  _(vld1_dup_f32)                                                           \
  _(vld1_dup_u8)                                                            \
  _(vld1_dup_u16)                                                           \
  _(vld1_dup_u32)                                                           \
  /*_(vld1_dup_p8)                                                       */ \
  /*_(vld1_dup_p16)                                                      */ \
  /*_(vld1_dup_p64)                                                      */ \
  _(vld1_dup_s64)                                                           \
  _(vld1_dup_u64)                                                           \
  _(vld1q_dup_s8)                                                           \
  _(vld1q_dup_s16)                                                          \
  _(vld1q_dup_s32)                                                          \
  /*_(vld1q_dup_f16)                                                     */ \
  _(vld1q_dup_f32)                                                          \
  _(vld1q_dup_u8)                                                           \
  _(vld1q_dup_u16)                                                          \
  _(vld1q_dup_u32)                                                          \
  /*_(vld1q_dup_p8)                                                      */ \
  /*_(vld1q_dup_p16)                                                     */ \
  /*_(vld1q_dup_p64)                                                     */ \
  _(vld1q_dup_s64)                                                          \
  _(vld1q_dup_u64)                                                          \
  /*_(vst1_p64)                                                          */ \
  _(vst1_s8)                                                                \
  _(vst1_s16)                                                               \
  _(vst1_s32)                                                               \
  _(vst1_s64)                                                               \
  /*_(vst1_f16)                                                          */ \
  _(vst1_f32)                                                               \
  _(vst1_u8)                                                                \
  _(vst1_u16)                                                               \
  _(vst1_u32)                                                               \
  _(vst1_u64)                                                               \
  /*_(vst1_p8)                                                           */ \
  /*_(vst1_p16)                                                          */ \
  /*_(vst1q_p64)                                                         */ \
  _(vst1q_s8)                                                               \
  _(vst1q_s16)                                                              \
  _(vst1q_s32)                                                              \
  _(vst1q_s64)                                                              \
  /*_(vst1q_f16)                                                         */ \
  _(vst1q_f32)                                                              \
  _(vst1q_u8)                                                               \
  _(vst1q_u16)                                                              \
  _(vst1q_u32)                                                              \
  _(vst1q_u64)                                                              \
  /*_(vst1q_p8)                                                          */ \
  /*_(vst1q_p16)                                                         */ \
  _(vst1_lane_s8)                                                           \
  _(vst1_lane_s16)                                                          \
  _(vst1_lane_s32)                                                          \
  /*_(vst1_lane_f16)                                                     */ \
  _(vst1_lane_f32)                                                          \
  _(vst1_lane_u8)                                                           \
  _(vst1_lane_u16)                                                          \
  _(vst1_lane_u32)                                                          \
  /*_(vst1_lane_p8)                                                      */ \
  /*_(vst1_lane_p16)                                                     */ \
  /*_(vst1_lane_p64)                                                     */ \
  _(vst1_lane_s64)                                                          \
  _(vst1_lane_u64)                                                          \
  _(vst1q_lane_s8)                                                          \
  _(vst1q_lane_s16)                                                         \
  _(vst1q_lane_s32)                                                         \
  /*_(vst1q_lane_f16)                                                    */ \
  _(vst1q_lane_f32)                                                         \
  _(vst1q_lane_u8)                                                          \
  _(vst1q_lane_u16)                                                         \
  _(vst1q_lane_u32)                                                         \
  /*_(vst1q_lane_p8)                                                     */ \
  /*_(vst1q_lane_p16)                                                    */ \
  /*_(vst1q_lane_p64)                                                    */ \
  _(vst1q_lane_s64)                                                         \
  _(vst1q_lane_u64)                                                         \
  _(vld2_s8)                                                                \
  _(vld2_s16)                                                               \
  _(vld2_s32)                                                               \
  /*_(vld2_f16)                                                          */ \
  _(vld2_f32)                                                               \
  _(vld2_u8)                                                                \
  _(vld2_u16)                                                               \
  _(vld2_u32)                                                               \
  /*_(vld2_p8)                                                           */ \
  /*_(vld2_p16)                                                          */ \
  /*_(vld2_p64)                                                          */ \
  _(vld2_s64)                                                               \
  _(vld2_u64)                                                               \
  _(vld2q_s8)                                                               \
  _(vld2q_s16)                                                              \
  _(vld2q_s32)                                                              \
  /*_(vld2q_f16)                                                         */ \
  _(vld2q_f32)                                                              \
  _(vld2q_u8)                                                               \
  _(vld2q_u16)                                                              \
  _(vld2q_u32)                                                              \
  /*_(vld2q_p8)                                                          */ \
  /*_(vld2q_p16)                                                         */ \
  _(vld2_lane_s8)                                                           \
  _(vld2_lane_s16)                                                          \
  _(vld2_lane_s32)                                                          \
  /*_(vld2_lane_f16)                                                     */ \
  _(vld2_lane_f32)                                                          \
  _(vld2_lane_u8)                                                           \
  _(vld2_lane_u16)                                                          \
  _(vld2_lane_u32)                                                          \
  /*_(vld2_lane_p8)                                                      */ \
  /*_(vld2_lane_p16)                                                     */ \
  _(vld2q_lane_s16)                                                         \
  _(vld2q_lane_s32)                                                         \
  /*_(vld2q_lane_f16)                                                    */ \
  _(vld2q_lane_f32)                                                         \
  _(vld2q_lane_u16)                                                         \
  _(vld2q_lane_u32)                                                         \
  /*_(vld2q_lane_p16)                                                    */ \
  _(vld2_dup_s8)                                                            \
  _(vld2_dup_s16)                                                           \
  _(vld2_dup_s32)                                                           \
  /*_(vld2_dup_f16)                                                      */ \
  _(vld2_dup_f32)                                                           \
  _(vld2_dup_u8)                                                            \
  _(vld2_dup_u16)                                                           \
  _(vld2_dup_u32)                                                           \
  /*_(vld2_dup_p8)                                                       */ \
  /*_(vld2_dup_p16)                                                      */ \
  /*_(vld2_dup_p64)                                                      */ \
  _(vld2_dup_s64)                                                           \
  _(vld2_dup_u64)                                                           \
  _(vst2_s8)                                                                \
  _(vst2_s16)                                                               \
  _(vst2_s32)                                                               \
  /*_(vst2_f16)                                                          */ \
  _(vst2_f32)                                                               \
  _(vst2_u8)                                                                \
  _(vst2_u16)                                                               \
  _(vst2_u32)                                                               \
  /*_(vst2_p8)                                                           */ \
  /*_(vst2_p16)                                                          */ \
  /*_(vst2_p64)                                                          */ \
  _(vst2_s64)                                                               \
  _(vst2_u64)                                                               \
  _(vst2q_s8)                                                               \
  _(vst2q_s16)                                                              \
  _(vst2q_s32)                                                              \
  /*_(vst2q_f16)                                                         */ \
  _(vst2q_f32)                                                              \
  _(vst2q_u8)                                                               \
  _(vst2q_u16)                                                              \
  _(vst2q_u32)                                                              \
  /*_(vst2q_p8)                                                          */ \
  /*_(vst2q_p16)                                                         */ \
  _(vst2_lane_s8)                                                           \
  _(vst2_lane_s16)                                                          \
  _(vst2_lane_s32)                                                          \
  /*_(vst2_lane_f16)                                                     */ \
  _(vst2_lane_f32)                                                          \
  _(vst2_lane_u8)                                                           \
  _(vst2_lane_u16)                                                          \
  _(vst2_lane_u32)                                                          \
  /*_(vst2_lane_p8)                                                      */ \
  /*_(vst2_lane_p16)                                                     */ \
  _(vst2q_lane_s16)                                                         \
  _(vst2q_lane_s32)                                                         \
  /*_(vst2q_lane_f16)                                                    */ \
  _(vst2q_lane_f32)                                                         \
  _(vst2q_lane_u16)                                                         \
  _(vst2q_lane_u32)                                                         \
  /*_(vst2q_lane_p16)                                                    */ \
  _(vld3_s8)                                                                \
  _(vld3_s16)                                                               \
  _(vld3_s32)                                                               \
  /*_(vld3_f16)                                                          */ \
  _(vld3_f32)                                                               \
  _(vld3_u8)                                                                \
  _(vld3_u16)                                                               \
  _(vld3_u32)                                                               \
  /*_(vld3_p8)                                                           */ \
  /*_(vld3_p16)                                                          */ \
  /*_(vld3_p64)                                                          */ \
  _(vld3_s64)                                                               \
  _(vld3_u64)                                                               \
  _(vld3q_s8)                                                               \
  _(vld3q_s16)                                                              \
  _(vld3q_s32)                                                              \
  /*_(vld3q_f16)                                                         */ \
  _(vld3q_f32)                                                              \
  _(vld3q_u8)                                                               \
  _(vld3q_u16)                                                              \
  _(vld3q_u32)                                                              \
  /*_(vld3q_p8)                                                          */ \
  /*_(vld3q_p16)                                                         */ \
  _(vld3_lane_s8)                                                           \
  _(vld3_lane_s16)                                                          \
  _(vld3_lane_s32)                                                          \
  /*_(vld3_lane_f16)                                                     */ \
  _(vld3_lane_f32)                                                          \
  _(vld3_lane_u8)                                                           \
  _(vld3_lane_u16)                                                          \
  _(vld3_lane_u32)                                                          \
  /*_(vld3_lane_p8)                                                      */ \
  /*_(vld3_lane_p16)                                                     */ \
  _(vld3q_lane_s16)                                                         \
  _(vld3q_lane_s32)                                                         \
  /*_(vld3q_lane_f16)                                                    */ \
  _(vld3q_lane_f32)                                                         \
  _(vld3q_lane_u16)                                                         \
  _(vld3q_lane_u32)                                                         \
  /*_(vld3q_lane_p16)                                                    */ \
  _(vld3_dup_s8)                                                            \
  _(vld3_dup_s16)                                                           \
  _(vld3_dup_s32)                                                           \
  /*_(vld3_dup_f16)                                                      */ \
  _(vld3_dup_f32)                                                           \
  _(vld3_dup_u8)                                                            \
  _(vld3_dup_u16)                                                           \
  _(vld3_dup_u32)                                                           \
  /*_(vld3_dup_p8)                                                       */ \
  /*_(vld3_dup_p16)                                                      */ \
  /*_(vld3_dup_p64)                                                      */ \
  _(vld3_dup_s64)                                                           \
  _(vld3_dup_u64)                                                           \
  _(vst3_s8)                                                                \
  _(vst3_s16)                                                               \
  _(vst3_s32)                                                               \
  /*_(vst3_f16)                                                          */ \
  _(vst3_f32)                                                               \
  _(vst3_u8)                                                                \
  _(vst3_u16)                                                               \
  _(vst3_u32)                                                               \
  /*_(vst3_p8)                                                           */ \
  /*_(vst3_p16)                                                          */ \
  /*_(vst3_p64)                                                          */ \
  _(vst3_s64)                                                               \
  _(vst3_u64)                                                               \
  _(vst3q_s8)                                                               \
  _(vst3q_s16)                                                              \
  _(vst3q_s32)                                                              \
  /*_(vst3q_f16)                                                         */ \
  _(vst3q_f32)                                                              \
  _(vst3q_u8)                                                               \
  _(vst3q_u16)                                                              \
  _(vst3q_u32)                                                              \
  /*_(vst3q_p8)                                                          */ \
  /*_(vst3q_p16)                                                         */ \
  _(vst3_lane_s8)                                                           \
  _(vst3_lane_s16)                                                          \
  _(vst3_lane_s32)                                                          \
  /*_(vst3_lane_f16)                                                     */ \
  _(vst3_lane_f32)                                                          \
  _(vst3_lane_u8)                                                           \
  _(vst3_lane_u16)                                                          \
  _(vst3_lane_u32)                                                          \
  /*_(vst3_lane_p8)                                                      */ \
  /*_(vst3_lane_p16)                                                     */ \
  _(vst3q_lane_s16)                                                         \
  _(vst3q_lane_s32)                                                         \
  /*_(vst3q_lane_f16)                                                    */ \
  _(vst3q_lane_f32)                                                         \
  _(vst3q_lane_u16)                                                         \
  _(vst3q_lane_u32)                                                         \
  /*_(vst3q_lane_p16)                                                    */ \
  _(vld4_s8)                                                                \
  _(vld4_s16)                                                               \
  _(vld4_s32)                                                               \
  /*_(vld4_f16)                                                          */ \
  _(vld4_f32)                                                               \
  _(vld4_u8)                                                                \
  _(vld4_u16)                                                               \
  _(vld4_u32)                                                               \
  /*_(vld4_p8)                                                           */ \
  /*_(vld4_p16)                                                          */ \
  /*_(vld4_p64)                                                          */ \
  _(vld4_s64)                                                               \
  _(vld4_u64)                                                               \
  _(vld4q_s8)                                                               \
  _(vld4q_s16)                                                              \
  _(vld4q_s32)                                                              \
  /*_(vld4q_f16)                                                         */ \
  _(vld4q_f32)                                                              \
  _(vld4q_u8)                                                               \
  _(vld4q_u16)                                                              \
  _(vld4q_u32)                                                              \
  /*_(vld4q_p8)                                                          */ \
  /*_(vld4q_p16)                                                         */ \
  _(vld4_lane_s8)                                                           \
  _(vld4_lane_s16)                                                          \
  _(vld4_lane_s32)                                                          \
  /*_(vld4_lane_f16)                                                     */ \
  _(vld4_lane_f32)                                                          \
  _(vld4_lane_u8)                                                           \
  _(vld4_lane_u16)                                                          \
  _(vld4_lane_u32)                                                          \
  /*_(vld4_lane_p8)                                                      */ \
  /*_(vld4_lane_p16)                                                     */ \
  _(vld4q_lane_s16)                                                         \
  _(vld4q_lane_s32)                                                         \
  /*_(vld4q_lane_f16)                                                    */ \
  _(vld4q_lane_f32)                                                         \
  _(vld4q_lane_u16)                                                         \
  _(vld4q_lane_u32)                                                         \
  /*_(vld4q_lane_p16)                                                    */ \
  _(vld4_dup_s8)                                                            \
  _(vld4_dup_s16)                                                           \
  _(vld4_dup_s32)                                                           \
  /*_(vld4_dup_f16)                                                      */ \
  _(vld4_dup_f32)                                                           \
  _(vld4_dup_u8)                                                            \
  _(vld4_dup_u16)                                                           \
  _(vld4_dup_u32)                                                           \
  /*_(vld4_dup_p8)                                                       */ \
  /*_(vld4_dup_p16)                                                      */ \
  /*_(vld4_dup_p64)                                                      */ \
  _(vld4_dup_s64)                                                           \
  _(vld4_dup_u64)                                                           \
  _(vst4_s8)                                                                \
  _(vst4_s16)                                                               \
  _(vst4_s32)                                                               \
  /*_(vst4_f16)                                                          */ \
  _(vst4_f32)                                                               \
  _(vst4_u8)                                                                \
  _(vst4_u16)                                                               \
  _(vst4_u32)                                                               \
  /*_(vst4_p8)                                                           */ \
  /*_(vst4_p16)                                                          */ \
  /*_(vst4_p64)                                                          */ \
  _(vst4_s64)                                                               \
  _(vst4_u64)                                                               \
  _(vst4q_s8)                                                               \
  _(vst4q_s16)                                                              \
  _(vst4q_s32)                                                              \
  /*_(vst4q_f16)                                                         */ \
  _(vst4q_f32)                                                              \
  _(vst4q_u8)                                                               \
  _(vst4q_u16)                                                              \
  _(vst4q_u32)                                                              \
  /*_(vst4q_p8)                                                          */ \
  /*_(vst4q_p16)                                                         */ \
  _(vst4_lane_s8)                                                           \
  _(vst4_lane_s16)                                                          \
  _(vst4_lane_s32)                                                          \
  /*_(vst4_lane_f16)                                                     */ \
  _(vst4_lane_f32)                                                          \
  _(vst4_lane_u8)                                                           \
  _(vst4_lane_u16)                                                          \
  _(vst4_lane_u32)                                                          \
  /*_(vst4_lane_p8)                                                      */ \
  /*_(vst4_lane_p16)                                                     */ \
  _(vst4q_lane_s16)                                                         \
  _(vst4q_lane_s32)                                                         \
  /*_(vst4q_lane_f16)                                                    */ \
  _(vst4q_lane_f32)                                                         \
  _(vst4q_lane_u16)                                                         \
  _(vst4q_lane_u32)                                                         \
  /*_(vst4q_lane_p16)                                                    */ \
  _(vand_s8)                                                                \
  _(vand_s16)                                                               \
  _(vand_s32)                                                               \
  _(vand_u8)                                                                \
  _(vand_u16)                                                               \
  _(vand_u32)                                                               \
  _(vand_s64)                                                               \
  _(vand_u64)                                                               \
  _(vandq_s8)                                                               \
  _(vandq_s16)                                                              \
  _(vandq_s32)                                                              \
  _(vandq_s64)                                                              \
  _(vandq_u8)                                                               \
  _(vandq_u16)                                                              \
  _(vandq_u32)                                                              \
  _(vandq_u64)                                                              \
  _(vorr_s8)                                                                \
  _(vorr_s16)                                                               \
  _(vorr_s32)                                                               \
  _(vorr_u8)                                                                \
  _(vorr_u16)                                                               \
  _(vorr_u32)                                                               \
  _(vorr_s64)                                                               \
  _(vorr_u64)                                                               \
  _(vorrq_s8)                                                               \
  _(vorrq_s16)                                                              \
  _(vorrq_s32)                                                              \
  _(vorrq_s64)                                                              \
  _(vorrq_u8)                                                               \
  _(vorrq_u16)                                                              \
  _(vorrq_u32)                                                              \
  _(vorrq_u64)                                                              \
  _(veor_s8)                                                                \
  _(veor_s16)                                                               \
  _(veor_s32)                                                               \
  _(veor_u8)                                                                \
  _(veor_u16)                                                               \
  _(veor_u32)                                                               \
  _(veor_s64)                                                               \
  _(veor_u64)                                                               \
  _(veorq_s8)                                                               \
  _(veorq_s16)                                                              \
  _(veorq_s32)                                                              \
  _(veorq_s64)                                                              \
  _(veorq_u8)                                                               \
  _(veorq_u16)                                                              \
  _(veorq_u32)                                                              \
  _(veorq_u64)                                                              \
  _(vbic_s8)                                                                \
  _(vbic_s16)                                                               \
  _(vbic_s32)                                                               \
  _(vbic_u8)                                                                \
  _(vbic_u16)                                                               \
  _(vbic_u32)                                                               \
  _(vbic_s64)                                                               \
  _(vbic_u64)                                                               \
  _(vbicq_s8)                                                               \
  _(vbicq_s16)                                                              \
  _(vbicq_s32)                                                              \
  _(vbicq_s64)                                                              \
  _(vbicq_u8)                                                               \
  _(vbicq_u16)                                                              \
  _(vbicq_u32)                                                              \
  _(vbicq_u64)                                                              \
  _(vorn_s8)                                                                \
  _(vorn_s16)                                                               \
  _(vorn_s32)                                                               \
  _(vorn_u8)                                                                \
  _(vorn_u16)                                                               \
  _(vorn_u32)                                                               \
  _(vorn_s64)                                                               \
  _(vorn_u64)                                                               \
  _(vornq_s8)                                                               \
  _(vornq_s16)                                                              \
  _(vornq_s32)                                                              \
  _(vornq_s64)                                                              \
  _(vornq_u8)                                                               \
  _(vornq_u16)                                                              \
  _(vornq_u32)                                                              \
  _(vornq_u64)                                                              \
  /*_(vreinterpret_p8_p16)                                               */ \
  /*_(vreinterpret_p8_f16)                                               */ \
  /*_(vreinterpret_p8_f32)                                               */ \
  /*_(vreinterpret_p8_p64)                                               */ \
  /*_(vreinterpret_p8_s64)                                               */ \
  /*_(vreinterpret_p8_u64)                                               */ \
  /*_(vreinterpret_p8_s8)                                                */ \
  /*_(vreinterpret_p8_s16)                                               */ \
  /*_(vreinterpret_p8_s32)                                               */ \
  /*_(vreinterpret_p8_u8)                                                */ \
  /*_(vreinterpret_p8_u16)                                               */ \
  /*_(vreinterpret_p8_u32)                                               */ \
  /*_(vreinterpret_p16_p8)                                               */ \
  /*_(vreinterpret_p16_f16)                                              */ \
  /*_(vreinterpret_p16_f32)                                              */ \
  /*_(vreinterpret_p16_p64)                                              */ \
  /*_(vreinterpret_p16_s64)                                              */ \
  /*_(vreinterpret_p16_u64)                                              */ \
  /*_(vreinterpret_p16_s8)                                               */ \
  /*_(vreinterpret_p16_s16)                                              */ \
  /*_(vreinterpret_p16_s32)                                              */ \
  /*_(vreinterpret_p16_u8)                                               */ \
  /*_(vreinterpret_p16_u16)                                              */ \
  /*_(vreinterpret_p16_u32)                                              */ \
  /*_(vreinterpret_f16_bf16)                                             */ \
  /*_(vreinterpret_f16_p8)                                               */ \
  /*_(vreinterpret_f16_p16)                                              */ \
  /*_(vreinterpret_f16_f32)                                              */ \
  /*_(vreinterpret_f16_p64)                                              */ \
  /*_(vreinterpret_f16_s64)                                              */ \
  /*_(vreinterpret_f16_u64)                                              */ \
  /*_(vreinterpret_f16_s8)                                               */ \
  /*_(vreinterpret_f16_s16)                                              */ \
  /*_(vreinterpret_f16_s32)                                              */ \
  /*_(vreinterpret_f16_u8)                                               */ \
  /*_(vreinterpret_f16_u16)                                              */ \
  /*_(vreinterpret_f16_u32)                                              */ \
  /*_(vreinterpret_f32_p8)                                               */ \
  /*_(vreinterpret_f32_p16)                                              */ \
  /*_(vreinterpret_f32_f16)                                              */ \
  /*_(vreinterpret_f32_p64)                                              */ \
  _(vreinterpret_f32_s64)                                                   \
  _(vreinterpret_f32_u64)                                                   \
  _(vreinterpret_f32_s8)                                                    \
  _(vreinterpret_f32_s16)                                                   \
  _(vreinterpret_f32_s32)                                                   \
  _(vreinterpret_f32_u8)                                                    \
  _(vreinterpret_f32_u16)                                                   \
  _(vreinterpret_f32_u32)                                                   \
  /*_(vreinterpret_p64_p8)                                               */ \
  /*_(vreinterpret_p64_p16)                                              */ \
  /*_(vreinterpret_p64_f16)                                              */ \
  /*_(vreinterpret_p64_f32)                                              */ \
  /*_(vreinterpret_p64_s64)                                              */ \
  /*_(vreinterpret_p64_u64)                                              */ \
  /*_(vreinterpret_p64_s8)                                               */ \
  /*_(vreinterpret_p64_s16)                                              */ \
  /*_(vreinterpret_p64_s32)                                              */ \
  /*_(vreinterpret_p64_u8)                                               */ \
  /*_(vreinterpret_p64_u16)                                              */ \
  /*_(vreinterpret_p64_u32)                                              */ \
  /*_(vreinterpret_s64_p8)                                               */ \
  /*_(vreinterpret_s64_p16)                                              */ \
  /*_(vreinterpret_s64_f16)                                              */ \
  _(vreinterpret_s64_f32)                                                   \
  /*_(vreinterpret_s64_p64)                                              */ \
  _(vreinterpret_s64_u64)                                                   \
  _(vreinterpret_s64_s8)                                                    \
  _(vreinterpret_s64_s16)                                                   \
  _(vreinterpret_s64_s32)                                                   \
  _(vreinterpret_s64_u8)                                                    \
  _(vreinterpret_s64_u16)                                                   \
  _(vreinterpret_s64_u32)                                                   \
  /*_(vreinterpret_u64_p8)                                               */ \
  /*_(vreinterpret_u64_p16)                                              */ \
  /*_(vreinterpret_u64_f16)                                              */ \
  _(vreinterpret_u64_f32)                                                   \
  /*_(vreinterpret_u64_p64)                                              */ \
  _(vreinterpret_u64_s64)                                                   \
  _(vreinterpret_u64_s8)                                                    \
  _(vreinterpret_u64_s16)                                                   \
  _(vreinterpret_u64_s32)                                                   \
  _(vreinterpret_u64_u8)                                                    \
  _(vreinterpret_u64_u16)                                                   \
  _(vreinterpret_u64_u32)                                                   \
  /*_(vreinterpret_s8_p8)                                                */ \
  /*_(vreinterpret_s8_p16)                                               */ \
  /*_(vreinterpret_s8_f16)                                               */ \
  _(vreinterpret_s8_f32)                                                    \
  /*_(vreinterpret_s8_p64)                                               */ \
  _(vreinterpret_s8_s64)                                                    \
  _(vreinterpret_s8_u64)                                                    \
  _(vreinterpret_s8_s16)                                                    \
  _(vreinterpret_s8_s32)                                                    \
  _(vreinterpret_s8_u8)                                                     \
  _(vreinterpret_s8_u16)                                                    \
  _(vreinterpret_s8_u32)                                                    \
  /*_(vreinterpret_s16_p8)                                               */ \
  /*_(vreinterpret_s16_p16)                                              */ \
  /*_(vreinterpret_s16_f16)                                              */ \
  _(vreinterpret_s16_f32)                                                   \
  /*_(vreinterpret_s16_p64)                                              */ \
  _(vreinterpret_s16_s64)                                                   \
  _(vreinterpret_s16_u64)                                                   \
  _(vreinterpret_s16_s8)                                                    \
  _(vreinterpret_s16_s32)                                                   \
  _(vreinterpret_s16_u8)                                                    \
  _(vreinterpret_s16_u16)                                                   \
  _(vreinterpret_s16_u32)                                                   \
  /*_(vreinterpret_s32_p8)                                               */ \
  /*_(vreinterpret_s32_p16)                                              */ \
  /*_(vreinterpret_s32_f16)                                              */ \
  _(vreinterpret_s32_f32)                                                   \
  /*_(vreinterpret_s32_p64)                                              */ \
  _(vreinterpret_s32_s64)                                                   \
  _(vreinterpret_s32_u64)                                                   \
  _(vreinterpret_s32_s8)                                                    \
  _(vreinterpret_s32_s16)                                                   \
  _(vreinterpret_s32_u8)                                                    \
  _(vreinterpret_s32_u16)                                                   \
  _(vreinterpret_s32_u32)                                                   \
  /*_(vreinterpret_u8_p8)                                                */ \
  /*_(vreinterpret_u8_p16)                                               */ \
  /*_(vreinterpret_u8_f16)                                               */ \
  _(vreinterpret_u8_f32)                                                    \
  /*_(vreinterpret_u8_p64)                                               */ \
  _(vreinterpret_u8_s64)                                                    \
  _(vreinterpret_u8_u64)                                                    \
  _(vreinterpret_u8_s8)                                                     \
  _(vreinterpret_u8_s16)                                                    \
  _(vreinterpret_u8_s32)                                                    \
  _(vreinterpret_u8_u16)                                                    \
  _(vreinterpret_u8_u32)                                                    \
  /*_(vreinterpret_u16_p8)                                               */ \
  /*_(vreinterpret_u16_p16)                                              */ \
  /*_(vreinterpret_u16_f16)                                              */ \
  _(vreinterpret_u16_f32)                                                   \
  /*_(vreinterpret_u16_p64)                                              */ \
  _(vreinterpret_u16_s64)                                                   \
  _(vreinterpret_u16_u64)                                                   \
  _(vreinterpret_u16_s8)                                                    \
  _(vreinterpret_u16_s16)                                                   \
  _(vreinterpret_u16_s32)                                                   \
  _(vreinterpret_u16_u8)                                                    \
  _(vreinterpret_u16_u32)                                                   \
  /*_(vreinterpret_u32_p8)                                               */ \
  /*_(vreinterpret_u32_p16)                                              */ \
  /*_(vreinterpret_u32_f16)                                              */ \
  _(vreinterpret_u32_f32)                                                   \
  /*_(vreinterpret_u32_p64)                                              */ \
  _(vreinterpret_u32_s64)                                                   \
  _(vreinterpret_u32_u64)                                                   \
  _(vreinterpret_u32_s8)                                                    \
  _(vreinterpret_u32_s16)                                                   \
  _(vreinterpret_u32_s32)                                                   \
  _(vreinterpret_u32_u8)                                                    \
  _(vreinterpret_u32_u16)                                                   \
  /*_(vreinterpretq_p8_p16)                                              */ \
  /*_(vreinterpretq_p8_f16)                                              */ \
  /*_(vreinterpretq_p8_f32)                                              */ \
  /*_(vreinterpretq_p8_p64)                                              */ \
  /*_(vreinterpretq_p8_p128)                                             */ \
  /*_(vreinterpretq_p8_s64)                                              */ \
  /*_(vreinterpretq_p8_u64)                                              */ \
  /*_(vreinterpretq_p8_s8)                                               */ \
  /*_(vreinterpretq_p8_s16)                                              */ \
  /*_(vreinterpretq_p8_s32)                                              */ \
  /*_(vreinterpretq_p8_u8)                                               */ \
  /*_(vreinterpretq_p8_u16)                                              */ \
  /*_(vreinterpretq_p8_u32)                                              */ \
  /*_(vreinterpretq_p16_p8)                                              */ \
  /*_(vreinterpretq_p16_f16)                                             */ \
  /*_(vreinterpretq_p16_f32)                                             */ \
  /*_(vreinterpretq_p16_p64)                                             */ \
  /*_(vreinterpretq_p16_p128)                                            */ \
  /*_(vreinterpretq_p16_s64)                                             */ \
  /*_(vreinterpretq_p16_u64)                                             */ \
  /*_(vreinterpretq_p16_s8)                                              */ \
  /*_(vreinterpretq_p16_s16)                                             */ \
  /*_(vreinterpretq_p16_s32)                                             */ \
  /*_(vreinterpretq_p16_u8)                                              */ \
  /*_(vreinterpretq_p16_u16)                                             */ \
  /*_(vreinterpretq_p16_u32)                                             */ \
  /*_(vreinterpretq_f16_p8)                                              */ \
  /*_(vreinterpretq_f16_p16)                                             */ \
  /*_(vreinterpretq_f16_bf16)                                            */ \
  /*_(vreinterpretq_f16_f32)                                             */ \
  /*_(vreinterpretq_f16_p64)                                             */ \
  /*_(vreinterpretq_f16_p128)                                            */ \
  /*_(vreinterpretq_f16_s64)                                             */ \
  /*_(vreinterpretq_f16_u64)                                             */ \
  /*_(vreinterpretq_f16_s8)                                              */ \
  /*_(vreinterpretq_f16_s16)                                             */ \
  /*_(vreinterpretq_f16_s32)                                             */ \
  /*_(vreinterpretq_f16_u8)                                              */ \
  /*_(vreinterpretq_f16_u16)                                             */ \
  /*_(vreinterpretq_f16_u32)                                             */ \
  /*_(vreinterpretq_f32_p8)                                              */ \
  /*_(vreinterpretq_f32_p16)                                             */ \
  /*_(vreinterpretq_f32_f16)                                             */ \
  /*_(vreinterpretq_f32_p64)                                             */ \
  /*_(vreinterpretq_f32_p128)                                            */ \
  _(vreinterpretq_f32_s64)                                                  \
  _(vreinterpretq_f32_u64)                                                  \
  _(vreinterpretq_f32_s8)                                                   \
  _(vreinterpretq_f32_s16)                                                  \
  _(vreinterpretq_f32_s32)                                                  \
  _(vreinterpretq_f32_u8)                                                   \
  _(vreinterpretq_f32_u16)                                                  \
  _(vreinterpretq_f32_u32)                                                  \
  /*_(vreinterpretq_p64_p8)                                              */ \
  /*_(vreinterpretq_p64_p16)                                             */ \
  /*_(vreinterpretq_p64_f16)                                             */ \
  /*_(vreinterpretq_p64_f32)                                             */ \
  /*_(vreinterpretq_p64_p128)                                            */ \
  /*_(vreinterpretq_p64_s64)                                             */ \
  /*_(vreinterpretq_p64_u64)                                             */ \
  /*_(vreinterpretq_p64_s8)                                              */ \
  /*_(vreinterpretq_p64_s16)                                             */ \
  /*_(vreinterpretq_p64_s32)                                             */ \
  /*_(vreinterpretq_p64_u8)                                              */ \
  /*_(vreinterpretq_p64_u16)                                             */ \
  /*_(vreinterpretq_p64_u32)                                             */ \
  /*_(vreinterpretq_p128_p8)                                             */ \
  /*_(vreinterpretq_p128_p16)                                            */ \
  /*_(vreinterpretq_p128_f16)                                            */ \
  /*_(vreinterpretq_p128_f32)                                            */ \
  /*_(vreinterpretq_p128_p64)                                            */ \
  /*_(vreinterpretq_p128_s64)                                            */ \
  /*_(vreinterpretq_p128_u64)                                            */ \
  /*_(vreinterpretq_p128_s8)                                             */ \
  /*_(vreinterpretq_p128_s16)                                            */ \
  /*_(vreinterpretq_p128_s32)                                            */ \
  /*_(vreinterpretq_p128_u8)                                             */ \
  /*_(vreinterpretq_p128_u16)                                            */ \
  /*_(vreinterpretq_p128_u32)                                            */ \
  /*_(vreinterpretq_s64_p8)                                              */ \
  /*_(vreinterpretq_s64_p16)                                             */ \
  /*_(vreinterpretq_s64_f16)                                             */ \
  _(vreinterpretq_s64_f32)                                                  \
  /*_(vreinterpretq_s64_p64)                                             */ \
  /*_(vreinterpretq_s64_p128)                                            */ \
  _(vreinterpretq_s64_u64)                                                  \
  _(vreinterpretq_s64_s8)                                                   \
  _(vreinterpretq_s64_s16)                                                  \
  _(vreinterpretq_s64_s32)                                                  \
  _(vreinterpretq_s64_u8)                                                   \
  _(vreinterpretq_s64_u16)                                                  \
  _(vreinterpretq_s64_u32)                                                  \
  /*_(vreinterpretq_u64_p8)                                              */ \
  /*_(vreinterpretq_u64_p16)                                             */ \
  /*_(vreinterpretq_u64_f16)                                             */ \
  _(vreinterpretq_u64_f32)                                                  \
  /*_(vreinterpretq_u64_p64)                                             */ \
  /*_(vreinterpretq_u64_p128)                                            */ \
  _(vreinterpretq_u64_s64)                                                  \
  _(vreinterpretq_u64_s8)                                                   \
  _(vreinterpretq_u64_s16)                                                  \
  _(vreinterpretq_u64_s32)                                                  \
  _(vreinterpretq_u64_u8)                                                   \
  _(vreinterpretq_u64_u16)                                                  \
  _(vreinterpretq_u64_u32)                                                  \
  /*_(vreinterpretq_s8_p8)                                               */ \
  /*_(vreinterpretq_s8_p16)                                              */ \
  /*_(vreinterpretq_s8_f16)                                              */ \
  _(vreinterpretq_s8_f32)                                                   \
  /*_(vreinterpretq_s8_p64)                                              */ \
  /*_(vreinterpretq_s8_p128)                                             */ \
  _(vreinterpretq_s8_s64)                                                   \
  _(vreinterpretq_s8_u64)                                                   \
  _(vreinterpretq_s8_s16)                                                   \
  _(vreinterpretq_s8_s32)                                                   \
  _(vreinterpretq_s8_u8)                                                    \
  _(vreinterpretq_s8_u16)                                                   \
  _(vreinterpretq_s8_u32)                                                   \
  /*_(vreinterpretq_s16_p8)                                              */ \
  /*_(vreinterpretq_s16_p16)                                             */ \
  /*_(vreinterpretq_s16_f16)                                             */ \
  _(vreinterpretq_s16_f32)                                                  \
  /*_(vreinterpretq_s16_p64)                                             */ \
  /*_(vreinterpretq_s16_p128)                                            */ \
  _(vreinterpretq_s16_s64)                                                  \
  _(vreinterpretq_s16_u64)                                                  \
  _(vreinterpretq_s16_s8)                                                   \
  _(vreinterpretq_s16_s32)                                                  \
  _(vreinterpretq_s16_u8)                                                   \
  _(vreinterpretq_s16_u16)                                                  \
  _(vreinterpretq_s16_u32)                                                  \
  /*_(vreinterpretq_s32_p8)                                              */ \
  /*_(vreinterpretq_s32_p16)                                             */ \
  /*_(vreinterpretq_s32_f16)                                             */ \
  _(vreinterpretq_s32_f32)                                                  \
  /*_(vreinterpretq_s32_p64)                                             */ \
  /*_(vreinterpretq_s32_p128)                                            */ \
  _(vreinterpretq_s32_s64)                                                  \
  _(vreinterpretq_s32_u64)                                                  \
  _(vreinterpretq_s32_s8)                                                   \
  _(vreinterpretq_s32_s16)                                                  \
  _(vreinterpretq_s32_u8)                                                   \
  _(vreinterpretq_s32_u16)                                                  \
  _(vreinterpretq_s32_u32)                                                  \
  /*_(vreinterpretq_u8_p8)                                               */ \
  /*_(vreinterpretq_u8_p16)                                              */ \
  /*_(vreinterpretq_u8_f16)                                              */ \
  _(vreinterpretq_u8_f32)                                                   \
  /*_(vreinterpretq_u8_p64)                                              */ \
  /*_(vreinterpretq_u8_p128)                                             */ \
  _(vreinterpretq_u8_s64)                                                   \
  _(vreinterpretq_u8_u64)                                                   \
  _(vreinterpretq_u8_s8)                                                    \
  _(vreinterpretq_u8_s16)                                                   \
  _(vreinterpretq_u8_s32)                                                   \
  _(vreinterpretq_u8_u16)                                                   \
  _(vreinterpretq_u8_u32)                                                   \
  /*_(vreinterpretq_u16_p8)                                              */ \
  /*_(vreinterpretq_u16_p16)                                             */ \
  /*_(vreinterpretq_u16_f16)                                             */ \
  _(vreinterpretq_u16_f32)                                                  \
  /*_(vreinterpretq_u16_p64)                                             */ \
  /*_(vreinterpretq_u16_p128)                                            */ \
  _(vreinterpretq_u16_s64)                                                  \
  _(vreinterpretq_u16_u64)                                                  \
  _(vreinterpretq_u16_s8)                                                   \
  _(vreinterpretq_u16_s16)                                                  \
  _(vreinterpretq_u16_s32)                                                  \
  _(vreinterpretq_u16_u8)                                                   \
  _(vreinterpretq_u16_u32)                                                  \
  /*_(vreinterpretq_u32_p8)                                              */ \
  /*_(vreinterpretq_u32_p16)                                             */ \
  /*_(vreinterpretq_u32_f16)                                             */ \
  _(vreinterpretq_u32_f32)                                                  \
  /*_(vreinterpretq_u32_p64)                                             */ \
  /*_(vreinterpretq_u32_p128)                                            */ \
  _(vreinterpretq_u32_s64)                                                  \
  _(vreinterpretq_u32_u64)                                                  \
  _(vreinterpretq_u32_s8)                                                   \
  _(vreinterpretq_u32_s16)                                                  \
  _(vreinterpretq_u32_s32)                                                  \
  _(vreinterpretq_u32_u8)                                                   \
  _(vreinterpretq_u32_u16)                                                  \
  /*_(vldrq_p128)                                                        */ \
  /*_(vstrq_p128)                                                        */ \
  /*_(vceq_p64)                                                          */ \
  /*_(vceqz_p64)                                                         */ \
  /*_(vceqq_p64)                                                         */ \
  /*_(vceqzq_p64)                                                        */ \
  /*_(vtst_p64)                                                          */ \
  _(vaeseq_u8)                                                              \
  _(vaesdq_u8)                                                              \
  _(vaesmcq_u8)                                                             \
  _(vaesimcq_u8)                                                            \
  _(vsha1h_u32)                                                             \
  _(vsha1cq_u32)                                                            \
  _(vsha1pq_u32)                                                            \
  _(vsha1mq_u32)                                                            \
  _(vsha1su0q_u32)                                                          \
  _(vsha1su1q_u32)                                                          \
  _(vsha256hq_u32)                                                          \
  _(vsha256h2q_u32)                                                         \
  _(vsha256su0q_u32)                                                        \
  _(vsha256su1q_u32)                                                        \
  /*_(vmull_p64)                                                         */ \
  /*_(vmull_high_p64)                                                    */ \
  /* Intrinsics for FP16 instructions. */                                   \
  /*_(vabd_f16)                                                          */ \
  /*_(vabdq_f16)                                                         */ \
  /*_(vabs_f16)                                                          */ \
  /*_(vabsq_f16)                                                         */ \
  /*_(vadd_f16)                                                          */ \
  /*_(vaddq_f16)                                                         */ \
  /*_(vcage_f16)                                                         */ \
  /*_(vcageq_f16)                                                        */ \
  /*_(vcagt_f16)                                                         */ \
  /*_(vcagtq_f16)                                                        */ \
  /*_(vcale_f16)                                                         */ \
  /*_(vcaleq_f16)                                                        */ \
  /*_(vcalt_f16)                                                         */ \
  /*_(vcaltq_f16)                                                        */ \
  /*_(vceq_f16)                                                          */ \
  /*_(vceqq_f16)                                                         */ \
  /*_(vceqz_f16)                                                         */ \
  /*_(vceqzq_f16)                                                        */ \
  /*_(vcge_f16)                                                          */ \
  /*_(vcgeq_f16)                                                         */ \
  /*_(vcgez_f16)                                                         */ \
  /*_(vcgezq_f16)                                                        */ \
  /*_(vcgt_f16)                                                          */ \
  /*_(vcgtq_f16)                                                         */ \
  /*_(vcgtz_f16)                                                         */ \
  /*_(vcgtzq_f16)                                                        */ \
  /*_(vcle_f16)                                                          */ \
  /*_(vcleq_f16)                                                         */ \
  /*_(vclez_f16)                                                         */ \
  /*_(vclezq_f16)                                                        */ \
  /*_(vclt_f16)                                                          */ \
  /*_(vcltq_f16)                                                         */ \
  /*_(vcltz_f16)                                                         */ \
  /*_(vcltzq_f16)                                                        */ \
  /*_(vcvt_f16_s16)                                                      */ \
  /*_(vcvt_f16_u16)                                                      */ \
  /*_(vcvt_s16_f16)                                                      */ \
  /*_(vcvt_u16_f16)                                                      */ \
  /*_(vcvtq_f16_s16)                                                     */ \
  /*_(vcvtq_f16_u16)                                                     */ \
  /*_(vcvtq_s16_f16)                                                     */ \
  /*_(vcvtq_u16_f16)                                                     */ \
  /*_(vcvta_s16_f16)                                                     */ \
  /*_(vcvta_u16_f16)                                                     */ \
  /*_(vcvtaq_s16_f16)                                                    */ \
  /*_(vcvtaq_u16_f16)                                                    */ \
  /*_(vcvtm_s16_f16)                                                     */ \
  /*_(vcvtm_u16_f16)                                                     */ \
  /*_(vcvtmq_s16_f16)                                                    */ \
  /*_(vcvtmq_u16_f16)                                                    */ \
  /*_(vcvtn_s16_f16)                                                     */ \
  /*_(vcvtn_u16_f16)                                                     */ \
  /*_(vcvtnq_s16_f16)                                                    */ \
  /*_(vcvtnq_u16_f16)                                                    */ \
  /*_(vcvtp_s16_f16)                                                     */ \
  /*_(vcvtp_u16_f16)                                                     */ \
  /*_(vcvtpq_s16_f16)                                                    */ \
  /*_(vcvtpq_u16_f16)                                                    */ \
  /*_(vcvt_n_f16_s16)                                                    */ \
  /*_(vcvt_n_f16_u16)                                                    */ \
  /*_(vcvtq_n_f16_s16)                                                   */ \
  /*_(vcvtq_n_f16_u16)                                                   */ \
  /*_(vcvt_n_s16_f16)                                                    */ \
  /*_(vcvt_n_u16_f16)                                                    */ \
  /*_(vcvtq_n_s16_f16)                                                   */ \
  /*_(vcvtq_n_u16_f16)                                                   */ \
  /*_(vfma_f16)                                                          */ \
  /*_(vfmaq_f16)                                                         */ \
  /*_(vfms_f16)                                                          */ \
  /*_(vfmsq_f16)                                                         */ \
  /*_(vmax_f16)                                                          */ \
  /*_(vmaxq_f16)                                                         */ \
  /*_(vmaxnm_f16)                                                        */ \
  /*_(vmaxnmq_f16)                                                       */ \
  /*_(vmin_f16)                                                          */ \
  /*_(vminq_f16)                                                         */ \
  /*_(vminnm_f16)                                                        */ \
  /*_(vminnmq_f16)                                                       */ \
  /*_(vmul_f16)                                                          */ \
  /*_(vmul_lane_f16)                                                     */ \
  /*_(vmul_n_f16)                                                        */ \
  /*_(vmulq_f16)                                                         */ \
  /*_(vmulq_lane_f16)                                                    */ \
  /*_(vmulq_n_f16)                                                       */ \
  /*_(vneg_f16)                                                          */ \
  /*_(vnegq_f16)                                                         */ \
  /*_(vpadd_f16)                                                         */ \
  /*_(vpmax_f16)                                                         */ \
  /*_(vpmin_f16)                                                         */ \
  /*_(vrecpe_f16)                                                        */ \
  /*_(vrecpeq_f16)                                                       */ \
  /*_(vrnd_f16)                                                          */ \
  /*_(vrndq_f16)                                                         */ \
  /*_(vrnda_f16)                                                         */ \
  /*_(vrndaq_f16)                                                        */ \
  /*_(vrndm_f16)                                                         */ \
  /*_(vrndmq_f16)                                                        */ \
  /*_(vrndn_f16)                                                         */ \
  /*_(vrndnq_f16)                                                        */ \
  /*_(vrndp_f16)                                                         */ \
  /*_(vrndpq_f16)                                                        */ \
  /*_(vrndx_f16)                                                         */ \
  /*_(vrndxq_f16)                                                        */ \
  /*_(vrsqrte_f16)                                                       */ \
  /*_(vrsqrteq_f16)                                                      */ \
  /*_(vrecps_f16)                                                        */ \
  /*_(vrecpsq_f16)                                                       */ \
  /*_(vrsqrts_f16)                                                       */ \
  /*_(vrsqrtsq_f16)                                                      */ \
  /*_(vsub_f16)                                                          */ \
  /*_(vsubq_f16)                                                         */ \
  /* Half-precision data processing intrinsics. */                          \
  /*_(vbsl_f16)                                                          */ \
  /*_(vbslq_f16)                                                         */ \
  /*_(vdup_n_f16)                                                        */ \
  /*_(vdupq_n_f16)                                                       */ \
  /*_(vdup_lane_f16)                                                     */ \
  /*_(vdupq_lane_f16)                                                    */ \
  /*_(vext_f16)                                                          */ \
  /*_(vextq_f16)                                                         */ \
  /*_(vmov_n_f16)                                                        */ \
  /*_(vmovq_n_f16)                                                       */ \
  /*_(vrev64_f16)                                                        */ \
  /*_(vrev64q_f16)                                                       */ \
  /*_(vtrn_f16)                                                          */ \
  /*_(vtrnq_f16)                                                         */ \
  /*_(vuzp_f16)                                                          */ \
  /*_(vuzpq_f16)                                                         */ \
  /*_(vzip_f16)                                                          */ \
  /*_(vzipq_f16)                                                         */ \
  /* AdvSIMD Dot Product intrinsics. */                                     \
  _(vdot_u32)                                                               \
  _(vdotq_u32)                                                              \
  _(vdot_s32)                                                               \
  _(vdotq_s32)                                                              \
  _(vdot_lane_u32)                                                          \
  _(vdotq_lane_u32)                                                         \
  _(vdot_lane_s32)                                                          \
  _(vdotq_lane_s32)                                                         \
  _(vdot_laneq_u32)                                                         \
  _(vdotq_laneq_u32)                                                        \
  _(vdot_laneq_s32)                                                         \
  _(vdotq_laneq_s32)                                                        \
  /*_(vfmlal_low_f16)                                                    */ \
  /*_(vfmlsl_low_f16)                                                    */ \
  /*_(vfmlal_high_f16)                                                   */ \
  /*_(vfmlsl_high_f16)                                                   */ \
  /*_(vfmlalq_low_f16)                                                   */ \
  /*_(vfmlslq_low_f16)                                                   */ \
  /*_(vfmlalq_high_f16)                                                  */ \
  /*_(vfmlslq_high_f16)                                                  */ \
  /*_(vfmlal_lane_low_f16)                                               */ \
  /*_(vfmlal_lane_high_f16)                                              */ \
  /*_(vfmlalq_laneq_low_f16)                                             */ \
  /*_(vfmlalq_lane_low_f16)                                              */ \
  /*_(vfmlal_laneq_low_f16)                                              */ \
  /*_(vfmlalq_laneq_high_f16)                                            */ \
  /*_(vfmlalq_lane_high_f16)                                             */ \
  /*_(vfmlal_laneq_high_f16)                                             */ \
  /*_(vfmlsl_lane_low_f16)                                               */ \
  /*_(vfmlsl_lane_high_f16)                                              */ \
  /*_(vfmlslq_laneq_low_f16)                                             */ \
  /*_(vfmlslq_lane_low_f16)                                              */ \
  /*_(vfmlsl_laneq_low_f16)                                              */ \
  /*_(vfmlslq_laneq_high_f16)                                            */ \
  /*_(vfmlslq_lane_high_f16)                                             */ \
  /*_(vfmlsl_laneq_high_f16)                                             */ \
  /* AdvSIMD Complex numbers intrinsics. */                                 \
  /*_(vcadd_rot90_f16)                                                   */ \
  /*_(vcaddq_rot90_f16)                                                  */ \
  /*_(vcadd_rot270_f16)                                                  */ \
  /*_(vcaddq_rot270_f16)                                                 */ \
  /*_(vcmla_f16)                                                         */ \
  /*_(vcmlaq_f16)                                                        */ \
  /*_(vcmla_lane_f16)                                                    */ \
  /*_(vcmla_laneq_f16)                                                   */ \
  /*_(vcmlaq_lane_f16)                                                   */ \
  /*_(vcmlaq_laneq_f16)                                                  */ \
  /*_(vcmla_rot90_f16)                                                   */ \
  /*_(vcmlaq_rot90_f16)                                                  */ \
  /*_(vcmla_rot90_lane_f16)                                              */ \
  /*_(vcmla_rot90_laneq_f16)                                             */ \
  /*_(vcmlaq_rot90_lane_f16)                                             */ \
  /*_(vcmlaq_rot90_laneq_f16)                                            */ \
  /*_(vcmla_rot180_f16)                                                  */ \
  /*_(vcmlaq_rot180_f16)                                                 */ \
  /*_(vcmla_rot180_lane_f16)                                             */ \
  /*_(vcmla_rot180_laneq_f16)                                            */ \
  /*_(vcmlaq_rot180_lane_f16)                                            */ \
  /*_(vcmlaq_rot180_laneq_f16)                                           */ \
  /*_(vcmla_rot270_f16)                                                  */ \
  /*_(vcmlaq_rot270_f16)                                                 */ \
  /*_(vcmla_rot270_lane_f16)                                             */ \
  /*_(vcmla_rot270_laneq_f16)                                            */ \
  /*_(vcmlaq_rot270_lane_f16)                                            */ \
  /*_(vcmlaq_rot270_laneq_f16)                                           */ \
  _(vcadd_rot90_f32)                                                        \
  _(vcaddq_rot90_f32)                                                       \
  _(vcadd_rot270_f32)                                                       \
  _(vcaddq_rot270_f32)                                                      \
  _(vcmla_f32)                                                              \
  _(vcmlaq_f32)                                                             \
  _(vcmla_lane_f32)                                                         \
  _(vcmla_laneq_f32)                                                        \
  _(vcmlaq_lane_f32)                                                        \
  _(vcmlaq_laneq_f32)                                                       \
  _(vcmla_rot90_f32)                                                        \
  _(vcmlaq_rot90_f32)                                                       \
  _(vcmla_rot90_lane_f32)                                                   \
  _(vcmla_rot90_laneq_f32)                                                  \
  _(vcmlaq_rot90_lane_f32)                                                  \
  _(vcmlaq_rot90_laneq_f32)                                                 \
  _(vcmla_rot180_f32)                                                       \
  _(vcmlaq_rot180_f32)                                                      \
  _(vcmla_rot180_lane_f32)                                                  \
  _(vcmla_rot180_laneq_f32)                                                 \
  _(vcmlaq_rot180_lane_f32)                                                 \
  _(vcmlaq_rot180_laneq_f32)                                                \
  _(vcmla_rot270_f32)                                                       \
  _(vcmlaq_rot270_f32)                                                      \
  _(vcmla_rot270_lane_f32)                                                  \
  _(vcmla_rot270_laneq_f32)                                                 \
  _(vcmlaq_rot270_lane_f32)                                                 \
  _(vcmlaq_rot270_laneq_f32)                                                \
  /* AdvSIMD Matrix Multiply-Accumulate and Dot Product intrinsics. */      \
  _(vusdot_s32)                                                             \
  _(vusdotq_s32)                                                            \
  _(vusdot_lane_s32)                                                        \
  _(vusdotq_lane_s32)                                                       \
  _(vsudot_lane_s32)                                                        \
  _(vsudotq_lane_s32)                                                       \
  _(vusdot_laneq_s32)                                                       \
  _(vusdotq_laneq_s32)                                                      \
  _(vsudot_laneq_s32)                                                       \
  _(vsudotq_laneq_s32)                                                      \
  _(last) /* This indicates the end of macros */

namespace NEON2RVV {
// The way unit tests are implemented is that 10,000 random floating point and
// integer vec4 numbers are generated as sample data.
//
// A short C implementation of every intrinsic is implemented and compared to
// the actual expected results from the corresponding NEON intrinsic against all
// of the 10,000 randomized input vectors. When running on ARM, then the results
// are compared to the NEON approximate version.
static const char *instruction_string[] = {
#define _(x) #x,
    INTRIN_LIST
#undef _
};

enum INSTRUCTION_TEST {
#define _(x) it_##x,
  INTRIN_LIST
#undef _
};

class NEON2RVV_TEST {
 public:
  static NEON2RVV_TEST *create(void);  // create the test.

  // Run test of this instruction;
  // Passed: TEST_SUCCESS (1)
  // Failed: TEST_FAIL (0)
  // Unimplemented: TEST_UNIMPL (-1)
  virtual result_t run_test(INSTRUCTION_TEST test) = 0;
  virtual void release(void) = 0;
};

}  // namespace NEON2RVV

#endif  // NEON2RVV_TEST_H
