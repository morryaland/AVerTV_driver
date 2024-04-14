#ifndef AVERAPI_H
#define AVERAPI_H

#include <libusb-1.0/libusb.h>

#define AVER_LED 0x04

typedef struct {
  char led; /* led status (on, off) */

} AVERTV_DEVICE;

int AVERTV_init(  );

#endif
