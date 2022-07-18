/**
 * @file ojousima_endpoint_af.h
 * @author Otso Jousimaa
 * @date 2022-07-13
 * @copyright Copyright 2022 Ruuvi Innovations.
 *   This project is released under the BSD-3-Clause License.
 *
 * Broadcast FFT data
 */


#ifndef OJOUSIMA_ENDPOINT_AF_H
#define OJOUSIMA_ENDPOINT_AF_H
#include <math.h>
#include "ruuvi_endpoints.h"
  
/** @ingroup ojousima_endpoints 
 *  @{
 */

#define APP_ENDPOINT_AF_DESTINATION                 (0xAF)
#define APP_ENDPOINT_AF_DATA_LENGTH                 (24U)

// Version 0, 1
#define APP_ENDPOINT_AF_OFFSET_HEADER               (0U)
#define APP_ENDPOINT_AF_OFFSET_VERSION              (1U)
// 0 - X-axis 
// 1 - Y-axis
// 2 - Z-axis
#define APP_ENDPOINT_AF_OFFSET_TYPE                 (2U)
// Scaling factor is 8.8 fractional
#define APP_ENDPOINT_AF_OFFSET_SCALE_MSB            (3U)
#define APP_ENDPOINT_AF_OFFSET_SCALE_LSB            (4U)
// Highest represented frequency, in Hz
#define APP_ENDPOINT_AF_OFFSET_FREQ_MSB             (5U)
#define APP_ENDPOINT_AF_OFFSET_FREQ_LSB             (6U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_1             (7U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_2             (8U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_3             (9U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_4             (10U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_5             (11U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_6             (12U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_7             (13U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_8             (14U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_9             (15U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_10            (16U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_11            (17U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_12            (18U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_13            (19U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_14            (20U)
#define APP_ENDPOINT_AF_OFFSET_BUCKET_15            (21U) 
#define APP_ENDPOINT_AF_OFFSET_BUCKET_16            (22U)
#define APP_ENDPOINT_AF_OFFSET_SEQUENCE             (23U)

// 8 bits, 0xFF reserved for error value. Float for scaling.
#define APP_ENDPOINT_AF_RESOLUTION_LEVELS           (254.0f)
#define APP_ENDPOINT_AF_ERROR_VALUE                         (0xFF)
#define APP_ENDPOINT_AF_X_TYPE                                   (0U)
#define APP_ENDPOINT_AF_Y_TYPE                                   (1U)
#define APP_ENDPOINT_AF_Z_TYPE                                   (2U)
#define APP_ENDPOINT_AF_NUM_BUCKETS                     (16U)

typedef struct{
  float buckets[APP_ENDPOINT_AF_NUM_BUCKETS];
  uint16_t frequency;
  float scale;
  uint8_t type;
  uint8_t sequence;
}app_endpoint_af_data_t;

/**
 * @brief Encode given data to given buffer in app format AF Version 0.
 *
 * @param[out] buffer: uint8_t array with length of 22 bytes.
 * @param[in]  data: Struct containing all necessary information for
 *                   encoding the data into buffer
 * @return @c RUUVI_ENDPOINT_SUCCESS on success. @c RUUVI_ENDPOINT_ERROR_NULL if null parameter was given.
 */
re_status_t app_endpoint_af_encode_v0(uint8_t* const buffer,
                                                  const app_endpoint_af_data_t* data);



/** @} */ // End of group ojousima_endpoints
#endif

