/**
 * Application endpoint helper.
 * Defines necessary data for creating application spceific BA broadcast
 *
 * License: BSD-3
 * Author: Otso Jousimaa <otso@ojousima.net>
 */

#include "ojousima_endpoint_ba.h"
#include "ruuvi_endpoints.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

ruuvi_endpoint_status_t app_endpoint_ba_encode(uint8_t* const buffer,
                                               const app_endpoint_ba_data_t* data,
                                               const float invalid)
{
  if(NULL == buffer  || NULL == data) { return RUUVI_ENDPOINT_ERROR_NULL; }

  buffer[APP_ENDPOINT_BA_OFFSET_HEADER]  = APP_ENDPOINT_BA_DESTINATION;
  buffer[APP_ENDPOINT_BA_OFFSET_VERSION] = APP_ENDPOINT_BA_VERSION;

  // HUMIDITY
  uint16_t humidity = 0;
  if(invalid != data->humidity_rh && 0 < data->humidity_rh)
  {
    //Humidity (16bit unsigned) in 0.0025% (0-163.83% range, though realistically 0-100%)
     humidity = (uint16_t)(data->humidity_rh*400);
  }
  buffer[APP_ENDPOINT_BA_OFFSET_HUMIDITY_MSB] = (humidity >> 8);
  buffer[APP_ENDPOINT_BA_OFFSET_HUMIDITY_LSB] = humidity & 0xFF;

  // Temperature is in 0.005 degrees
  int16_t temperature = 0;
  if(invalid != data->temperature_c)
  {
    temperature = (int16_t)(data->temperature_c * 200 );
  }
  buffer[APP_ENDPOINT_BA_OFFSET_TEMPERATURE_MSB] = (temperature >> 8);
  buffer[APP_ENDPOINT_BA_OFFSET_TEMPERATURE_LSB] = (temperature & 0xFF);

  // voltages
  uint16_t simple_v = 0;
  uint16_t radio_v = 0;
  uint16_t droop_v = 0;
  if(invalid != data->simple_v)
  {
    // Convert to millivolts
    simple_v = (data->simple_v > 0) ? data->simple_v * 1000 : 0;
    buffer[APP_ENDPOINT_BA_OFFSET_SIMPLE_MSB] = (simple_v >> 8);
    buffer[APP_ENDPOINT_BA_OFFSET_SIMPLE_LSB] = (simple_v & 0xFF);
  }

  if(invalid != data->radio_v)
  {
    // Convert to millivolts
    radio_v = (data->radio_v > 0) ? data->radio_v * 1000 : 0;
    buffer[APP_ENDPOINT_BA_OFFSET_RADIO_MSB] = (radio_v >> 8);
    buffer[APP_ENDPOINT_BA_OFFSET_RADIO_LSB] = (radio_v & 0xFF);
  }

  if(invalid != data->droop_v)
  {
    // Convert to millivolts
    droop_v = (data->droop_v > 0) ? data->droop_v * 1000 : 0;
    buffer[APP_ENDPOINT_BA_OFFSET_DROOP_MSB] = (droop_v >> 8);
    buffer[APP_ENDPOINT_BA_OFFSET_DROOP_LSB] = (droop_v & 0xFF);
  }

  buffer[APP_ENDPOINT_BA_OFFSET_SEQUENCE_COUNTER_MSB] = (data->measurement_count >> 8);
  buffer[APP_ENDPOINT_BA_OFFSET_SEQUENCE_COUNTER_LSB] = (data->measurement_count & 0xFF);

  return RUUVI_ENDPOINT_SUCCESS;
}