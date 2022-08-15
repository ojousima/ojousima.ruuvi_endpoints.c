// See header file for copyright etc. 
#include "ojousima_endpoint_ac.h"
#include "ruuvi_endpoints.h"
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

static void encode_value(uint8_t* const target, const float value, const float invalid)
{
  uint16_t mg = APP_ENDPOINT_AC_INVALID_UNSIGNED;
  if(isfinite(value) && value != invalid)
  {
    if(UINT16_MAX < value * 1000) { mg = UINT16_MAX; }
    else if(0 > value * 1000) { mg = 0; }
    else { mg = (uint16_t) (value * 1000); }
  }
  target[0] = (mg >> 8) & 0xFF;
  target[1] = (mg >> 0) & 0xFF;
}


re_status_t app_endpoint_ac_encode_v0(uint8_t* const buffer,
                                                  const app_endpoint_ac_data_t* data,
                                                  const float invalid)
{

  if(NULL == buffer || NULL == data) { return RE_ERROR_NULL; }
  
  buffer[APP_ENDPOINT_AC_OFFSET_HEADER]  = APP_ENDPOINT_AC_DESTINATION;
  buffer[APP_ENDPOINT_AC_OFFSET_VERSION] = 0;

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_P2P_X_MSB]),
                      data->p2p[APP_ENDPOINT_AC_X_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_P2P_Y_MSB]),
                      data->p2p[APP_ENDPOINT_AC_Y_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_P2P_Z_MSB]),
                      data->p2p[APP_ENDPOINT_AC_Z_INDEX],
                      invalid);

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RMS_X_MSB]),
                      data->rms[APP_ENDPOINT_AC_X_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RMS_Y_MSB]),
                      data->rms[APP_ENDPOINT_AC_Y_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RMS_Z_MSB]),
                      data->rms[APP_ENDPOINT_AC_Z_INDEX],
                      invalid);

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_DEV_X_MSB]),
                      data->dev[APP_ENDPOINT_AC_X_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_DEV_Y_MSB]),
                      data->dev[APP_ENDPOINT_AC_Y_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_DEV_Z_MSB]),
                      data->dev[APP_ENDPOINT_AC_Z_INDEX],
                      invalid);

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RADIO_MSB]),
                      data->voltage,
                      invalid);

  buffer[APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_MSB] = data->sequence >> 8;
  buffer[APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_LSB] = data->sequence & 0xFF;

  return RE_SUCCESS;
}

re_status_t app_endpoint_ac_encode_v1(uint8_t* const buffer,
                                                  const app_endpoint_ac_data_t* data,
                                                  const float invalid)
{

  if(NULL == buffer || NULL == data) { return RE_ERROR_NULL; }
  
  buffer[APP_ENDPOINT_AC_OFFSET_HEADER]  = APP_ENDPOINT_AC_DESTINATION;
  buffer[APP_ENDPOINT_AC_OFFSET_VERSION] = 1;

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_P2P_X_MSB]),
                      data->p2p[APP_ENDPOINT_AC_X_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_P2P_Y_MSB]),
                      data->p2p[APP_ENDPOINT_AC_Y_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_P2P_Z_MSB]),
                      data->p2p[APP_ENDPOINT_AC_Z_INDEX],
                      invalid);

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RMS_X_MSB]),
                      data->rms[APP_ENDPOINT_AC_X_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RMS_Y_MSB]),
                      data->rms[APP_ENDPOINT_AC_Y_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_RMS_Z_MSB]),
                      data->rms[APP_ENDPOINT_AC_Z_INDEX],
                      invalid);

  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_DEV_X_MSB]),
                      data->dev[APP_ENDPOINT_AC_X_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_DEV_Y_MSB]),
                      data->dev[APP_ENDPOINT_AC_Y_INDEX],
                      invalid);
  encode_value(&(buffer[APP_ENDPOINT_AC_OFFSET_DEV_Z_MSB]),
                      data->dev[APP_ENDPOINT_AC_Z_INDEX],
                      invalid);

  if(invalid == data->voltage)
  {
    buffer[APP_ENDPOINT_AC_OFFSET_RADIO_MSB] = 0xFF;
  }
  else
  {
    float voltage;
    if(data->voltage > 3.600) { voltage = 3.6; }
    else if(data->voltage < 1.600) { voltage = 1.6; }
    else { voltage = data->voltage; }
    // Offset by 1.6 V, multiply into millivolts, scale to 8 mV/bit.
    buffer[APP_ENDPOINT_AC_OFFSET_RADIO_MSB] = (uint8_t)((voltage - 1.6) * 1000 / 8) ;
  }
  if(invalid == data->temperature)
  {
    buffer[APP_ENDPOINT_AC_V1_OFFSET_TEMPERATURE_MSB] = 0x80;
  }
  else
  {
    float temperature;
    if(data->temperature > 125) { temperature = 125; }
    else if(data->temperature < -125) { temperature = -125; }
    else { temperature = data->temperature; }
    buffer[APP_ENDPOINT_AC_V1_OFFSET_TEMPERATURE_MSB] = (int8_t)(temperature) ;
  }

  buffer[APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_MSB] = data->sequence >> 8;
  buffer[APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_LSB] = data->sequence & 0xFF;

  return RE_SUCCESS;
}

re_status_t app_endpoint_ac_encode_v2(uint8_t* const buffer,
                                                  const app_endpoint_ac_data_t* data)
{

  if(NULL == buffer || NULL == data) { return RE_ERROR_NULL; }
  
  buffer[APP_ENDPOINT_AC_V2_OFFSET_HEADER]  = APP_ENDPOINT_AC_DESTINATION;
  buffer[APP_ENDPOINT_AC_V2_OFFSET_VERSION] = APP_ENDPOINT_AC_V2_VERSION;

  encode_value(&(buffer[APP_ENDPOINT_AC_V2_OFFSET_P2P_X_MSB]),
                      data->p2p[APP_ENDPOINT_AC_X_INDEX],
                      NAN);
  encode_value(&(buffer[APP_ENDPOINT_AC_V2_OFFSET_P2P_Y_MSB]),
                      data->p2p[APP_ENDPOINT_AC_Y_INDEX],
                      NAN);
  encode_value(&(buffer[APP_ENDPOINT_AC_V2_OFFSET_P2P_Z_MSB]),
                      data->p2p[APP_ENDPOINT_AC_Z_INDEX],
                      NAN);

  encode_value(&(buffer[APP_ENDPOINT_AC_V2_OFFSET_RMS_X_MSB]),
                      data->rms[APP_ENDPOINT_AC_X_INDEX],
                      NAN);
  encode_value(&(buffer[APP_ENDPOINT_AC_V2_OFFSET_RMS_Y_MSB]),
                      data->rms[APP_ENDPOINT_AC_Y_INDEX],
                      NAN);
  encode_value(&(buffer[APP_ENDPOINT_AC_V2_OFFSET_RMS_Z_MSB]),
                      data->rms[APP_ENDPOINT_AC_Z_INDEX],
                      NAN);

  if(isnan(data->voltage))
  {
    buffer[APP_ENDPOINT_AC_V2_OFFSET_VOLTAGE_MSB] = 0xFF;
  }
  else
  {
    float voltage;
    if(data->voltage > 3.600) { voltage = 3.6; }
    else if(data->voltage < 1.600) { voltage = 1.6; }
    else { voltage = data->voltage; }
    // Offset by 1.6 V, multiply into millivolts, scale to 8 mV/bit.
    buffer[APP_ENDPOINT_AC_V2_OFFSET_VOLTAGE_MSB] = (uint8_t)((voltage - 1.6) * 1000 / 8) ;
  }
  if(isnan(data->temperature))
  {
    buffer[APP_ENDPOINT_AC_V1_OFFSET_TEMPERATURE_MSB] = 0x80;
  }
  else
  {
    float temperature;
    if(data->temperature > 125) { temperature = 125; }
    else if(data->temperature < -125) { temperature = -125; }
    else { temperature = data->temperature; }
    buffer[APP_ENDPOINT_AC_V2_OFFSET_TEMPERATURE_MSB] = (int8_t)(temperature);
  }

  buffer[APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_MSB] = data->sequence >> 8;
  buffer[APP_ENDPOINT_AC_OFFSET_SEQUENCE_COUNTER_LSB] = data->sequence & 0xFF;

  return RE_SUCCESS;
}
