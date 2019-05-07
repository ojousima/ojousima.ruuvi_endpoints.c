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


ruuvi_endpoint_status_t app_endpoint_ac_encode(uint8_t* const buffer,
                                               const app_endpoint_ac_data_t* data,
                                               const float invalid)
{

  if(NULL == buffer || NULL == data) { return RUUVI_ENDPOINT_ERROR_NULL; }
  
  buffer[APP_ENDPOINT_AC_OFFSET_HEADER]  = APP_ENDPOINT_AC_DESTINATION;
  buffer[APP_ENDPOINT_AC_OFFSET_VERSION] = APP_ENDPOINT_AC_VERSION;

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
}
