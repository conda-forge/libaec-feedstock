#include <stdint.h>
#include <string.h>

#include <libaec.h>

int main(void) {
  const uint16_t input[] = {1, 1, 2, 3, 5, 8, 13, 21};
  uint16_t output[sizeof(input) / sizeof(input[0])] = {0};
  unsigned char compressed[256] = {0};
  struct aec_stream encoder = {0};
  struct aec_stream decoder = {0};

  encoder.next_in = (const unsigned char *)input;
  encoder.avail_in = sizeof(input);
  encoder.next_out = compressed;
  encoder.avail_out = sizeof(compressed);
  encoder.bits_per_sample = 16;
  encoder.block_size = 8;
  encoder.rsi = 1;
  encoder.flags = AEC_DATA_PREPROCESS;
  if (aec_buffer_encode(&encoder) != AEC_OK)
    return 1;

  decoder.next_in = compressed;
  decoder.avail_in = encoder.total_out;
  decoder.next_out = (unsigned char *)output;
  decoder.avail_out = sizeof(output);
  decoder.bits_per_sample = 16;
  decoder.block_size = 8;
  decoder.rsi = 1;
  decoder.flags = AEC_DATA_PREPROCESS;
  if (aec_buffer_decode(&decoder) != AEC_OK)
    return 2;

  return memcmp(input, output, sizeof(input)) == 0 ? 0 : 3;
}
