#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/averapi.h"

static int AVERTV_device_connect( libusb_device_handle **device );

int AVERTV_init( AVERTV_DEVICE **av_device )
{
  *av_device = malloc(sizeof(AVERTV_DEVICE));
  if (!(*av_device)) {
    puts("ERROR: alloc device");
    return -1;
  }
  memset(*av_device, 0, sizeof(AVERTV_DEVICE));

  /* device connect */
  if (AVERTV_device_connect(&((*av_device)->usb_device_handle)) < 0) {
    puts("ERROR: avertv_device_connect");
    return -1;
  }
  return 0;
}

static int AVERTV_device_connect( libusb_device_handle **device )
{
  *device = libusb_open_device_with_vid_pid(NULL, VID_AVERMEDIA, PID_AVERTV);
  if (*device == NULL) {
    puts("ERROR: connect device");
    return -1;
  }
  return 0;
}

void AVERTV_free( AVERTV_DEVICE **av_device )
{
  libusb_close((*av_device)->usb_device_handle);
  free(*av_device);
}
