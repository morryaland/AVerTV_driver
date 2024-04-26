#ifndef AVERAPI_H
#define AVERAPI_H

#include <libusb-1.0/libusb.h>

#define VID_AVERMEDIA 0x07ca
#define PID_AVERTV    0x0026

typedef enum {
  NTSC,
  PAL
} RCA_FORMAT;

typedef struct {
  char status;
  libusb_device_handle *usb_device_handle;
} AVERTV_DEVICE;

int AVERTV_init( AVERTV_DEVICE **av_device );
void AVERTV_free( AVERTV_DEVICE **av_device );

int AVERTV_get_video_RCA( RCA_FORMAT form );

#endif
