#include <stdint.h>
#include <string.h>

#include <szlib.h>

int main(void) {
  const uint16_t input[] = {1, 1, 2, 3, 5, 8, 13, 21};
  uint16_t output[sizeof(input) / sizeof(input[0])] = {0};
  unsigned char compressed[256] = {0};
  size_t compressed_size = sizeof(compressed);
  size_t output_size = sizeof(output);
  SZ_com_t options = {
      SZ_NN_OPTION_MASK,
      16,
      8,
      8,
  };

  if (SZ_BufftoBuffCompress(compressed, &compressed_size, input, sizeof(input),
                            &options) != SZ_OK)
    return 1;
  if (SZ_BufftoBuffDecompress(output, &output_size, compressed, compressed_size,
                              &options) != SZ_OK)
    return 2;

  return output_size == sizeof(input) &&
                 memcmp(input, output, sizeof(input)) == 0
             ? 0
             : 3;
}
