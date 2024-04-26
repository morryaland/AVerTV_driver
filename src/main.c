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
  for (int i = 0; i < 1; i++) {
    ret = AVERTV_get_video_RCA(NTSC);
    if(ret < 0) {
      puts("ERROR: get_video_RCA");  
      return ret;
    }
  }
  AVERTV_free(&av_device);
  libusb_exit(NULL);
  return ret;
}
