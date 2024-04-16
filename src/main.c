#include <stdio.h>

#include "../lib/AVerAPI/src/include/averapi.h"

int main() {
  int ret = 0;
  AVERTV_DEVICE *av_device;

  ret = libusb_init(NULL);
  if (ret < 0) {
    puts("ERROR: libusb_init");
    return ret;
  }
  ret = AVERTV_init(&av_device);
  if (ret < 0) {
    puts("ERROR: avertv_init");
    return ret;
  }
  AVERTV_free(&av_device);
  libusb_exit(NULL);
  return ret;
}
