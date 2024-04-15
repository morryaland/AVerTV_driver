#include <stdio.h>

#include "../lib/AVerAPI/src/include/averapi.h"

int main() {
  AVERTV_DEVICE *av_device;
  AVERTV_init(&av_device);
  AVERTV_free(&av_device);
  return 0;
}
