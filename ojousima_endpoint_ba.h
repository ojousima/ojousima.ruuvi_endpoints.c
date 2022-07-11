/**
 * Application endpoint helper.
 * Defines necessary data for creating application specific BA broadcast
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#ifndef APP_ENDPOINT_BA_H
#define APP_ENDPOINT_BA_H
#include "ruuvi_endpoints.h"

#define APP_ENDPOINT_BA_DESTINATION                 0xBA
#define APP_ENDPOINT_BA_VERSION                     0
#define APP_ENDPOINT_BA_DATA_LENGTH                 14

#define APP_ENDPOINT_BA_OFFSET_HEADER               0
#define APP_ENDPOINT_BA_OFFSET_VERSION              1
#define APP_ENDPOINT_BA_OFFSET_TEMPERATURE_MSB      2
#define APP_ENDPOINT_BA_OFFSET_TEMPERATURE_LSB      3
#define APP_ENDPOINT_BA_OFFSET_HUMIDITY_MSB         4
#define APP_ENDPOINT_BA_OFFSET_HUMIDITY_LSB         5
#define APP_ENDPOINT_BA_OFFSET_SIMPLE_MSB           6
#define APP_ENDPOINT_BA_OFFSET_SIMPLE_LSB           7
#define APP_ENDPOINT_BA_OFFSET_RADIO_MSB            8
#define APP_ENDPOINT_BA_OFFSET_RADIO_LSB            9
#define APP_ENDPOINT_BA_OFFSET_DROOP_MSB            10
#define APP_ENDPOINT_BA_OFFSET_DROOP_LSB            11
#define APP_ENDPOINT_BA_OFFSET_SEQUENCE_COUNTER_MSB 12
#define APP_ENDPOINT_BA_OFFSET_SEQUENCE_COUNTER_LSB 13



typedef struct{
  float humidity_rh;
  float pressure_pa;
  float temperature_c;
  float simple_v;
  float radio_v;
  float droop_v;
  uint16_t measurement_count;
}app_endpoint_ba_data_t;

/**
 * Encode given data to given buffer in app format BA.
 *
 * parameter data: uint8_t array with length of 24 bytes.
 * parameter data: Struct containing all necessary information for
 *                 encoding the data into buffer
 * parameter invalid: A float which signals that given data point is invalid.
 */
re_status_t app_endpoint_ba_encode(uint8_t* const buffer,
                                               const app_endpoint_ba_data_t* data,
                                               const float invalid);


#endif