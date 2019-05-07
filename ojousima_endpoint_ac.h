/**
 * @file ojousima_endpoint_ac.h
 * @author Otso Jousimaa
 * @date 2019-01-25
 * @brief Function for finding peak to peak amplitude of a signal sample.
 * @copyright Copyright 2019 Ruuvi Innovations.
 *   This project is released under the BSD-3-Clause License.
 *
 * Broadcast extended accelerometer data. 
 */

#ifndef OJOUSIMA_ENDPOINT_AC_H
#define OJOUSIMA_ENDPOINT_AC_H
#include <math.h>
#include "ruuvi_endpoints.h"
  
/** @ingroup ojousima_endpoints 
 *  @{
 */

#define APP_ENDPOINT_AC_DESTINATION                 0xAC
#define APP_ENDPOINT_AC_VERSION                     0
#define APP_ENDPOINT_AC_DATA_LENGTH                 24

#define APP_ENDPOINT_AC_OFFSET_HEADER               0
#define APP_ENDPOINT_AC_OFFSET_VERSION              1
#define APP_ENDPOINT_AC_OFFSET_P2P_X_MSB            2
#define APP_ENDPOINT_AC_OFFSET_P2P_X_LSB            3
#define APP_ENDPOINT_AC_OFFSET_P2P_Y_MSB            4
#define APP_ENDPOINT_AC_OFFSET_P2P_Y_LSB            5
#define APP_ENDPOINT_AC_OFFSET_P2P_Z_MSB            6
#define APP_ENDPOINT_AC_OFFSET_P2P_Z_LSB            7
#define APP_ENDPOINT_AC_OFFSET_RMS_X_MSB            8
#define APP_ENDPOINT_AC_OFFSET_RMS_X_LSB            9
#define APP_ENDPOINT_AC_OFFSET_RMS_Y_MSB            10
#define APP_ENDPOINT_AC_OFFSET_RMS_Y_LSB            11
#define APP_ENDPOINT_AC_OFFSET_RMS_Z_MSB            12
#define APP_ENDPOINT_AC_OFFSET_RMS_Z_LSB            13
#define APP_ENDPOINT_AC_OFFSET_DEV_X_MSB            14
#define APP_ENDPOINT_AC_OFFSET_DEV_X_LSB            15
#define APP_ENDPOINT_AC_OFFSET_DEV_Y_MSB            16
#define APP_ENDPOINT_AC_OFFSET_DEV_Y_LSB            17
#define APP_ENDPOINT_AC_OFFSET_DEV_Z_MSB            18
#define APP_ENDPOINT_AC_OFFSET_DEV_Z_LSB            19
#define APP_ENDPOINT_AC_OFFSET_RADIO_MSB            20
#define APP_ENDPOINT_AC_OFFSET_RADIO_LSB            21
#define APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_MSB 22
#define APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_LSB 23

#define APP_ENDPOINT_AC_INVALID_UNSIGNED            0xFFFF

#define APP_ENDPOINT_AC_X_INDEX                     0
#define APP_ENDPOINT_AC_Y_INDEX                     1
#define APP_ENDPOINT_AC_Z_INDEX                     2

typedef struct{
  float p2p[3];
  float rms[3];
  float dev[3];
  float voltage;
  uint16_t sequence;
}app_endpoint_ac_data_t;

/**
 * @brief Encode given data to given buffer in app format AC.
 *
 * @param[out] buffer: uint8_t array with length of 24 bytes.
 * @param[in]  data: Struct containing all necessary information for
 *                   encoding the data into buffer
 * @param[in]  invalid: A float which signals that given data point is invalid.
 * @return @c RUUVI_ENDPOINT_SUCCESS on success. @c RUUVI_ENDPOINT_ERROR_NULL if null parameter was given.
 */
ruuvi_endpoint_status_t app_endpoint_ac_encode(uint8_t* const buffer,
                                               const app_endpoint_ac_data_t* data,
                                               const float invalid);


/** @} */ // End of group analysis
#endif