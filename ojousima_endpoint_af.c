/**
 * @file ojousima_endpoint_af.c
 * @author Otso Jousimaa
 * @date 2022-07-13
 * @copyright Copyright 2022 Ruuvi Innovations.
 *   This project is released under the BSD-3-Clause License.
 *
 * Broadcast FFT data
 */

#include "ojousima_endpoint_af.h"
#include "ruuvi_endpoints.h"

static uint8_t clip_in_bucket (const float value, const float scale)
{
  float scaled = value * scale;
  uint8_t rvalue = 0;
  if(isnan(scaled))
  {
    rvalue = 255U;
  }
  else if(scaled > 254)
  {
    rvalue = 254;
  }
  else if (scaled < 0)
  {
    rvalue = 0;
  }
  else
  {
    rvalue = roundf(scaled);
  }
  return rvalue;
}

re_status_t app_endpoint_af_encode_v0(uint8_t* const buffer,
                                      const app_endpoint_af_data_t* data)
{
  buffer[APP_ENDPOINT_AF_OFFSET_HEADER] = (0xAFU);
  buffer[APP_ENDPOINT_AF_OFFSET_VERSION] = (0x00U);
  buffer[APP_ENDPOINT_AF_OFFSET_TYPE] = data->type;
  uint16_t fixed_point = roundf(data->scale * (1 << 8));
  buffer[APP_ENDPOINT_AF_OFFSET_SCALE_MSB] = fixed_point >> 8U;
  buffer[APP_ENDPOINT_AF_OFFSET_SCALE_LSB] = fixed_point & (0xFFU);
  buffer[APP_ENDPOINT_AF_OFFSET_FREQ_MSB] = data->frequency >> 8U;
  buffer[APP_ENDPOINT_AF_OFFSET_FREQ_LSB] = data->frequency & (0xFFU);
  for(size_t ii = 0; ii < 16; ii++)
  {
    buffer[APP_ENDPOINT_AF_OFFSET_BUCKET_1 + ii] = clip_in_bucket(data->buckets[ii], data->scale);
  }

  return RE_SUCCESS;
}