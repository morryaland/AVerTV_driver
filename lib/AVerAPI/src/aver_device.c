#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/averapi.h"

#define INIT_DATA_FILE "bin/init.dat"

typedef struct {
  uint8_t RequestType;
  uint8_t bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} DATA_TRANSFER;

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
  int ret;
  unsigned char data[1]; 

  *device = libusb_open_device_with_vid_pid(NULL, VID_AVERMEDIA, PID_AVERTV);
  if (*device == NULL) {
    puts("ERROR: connect device");
    return -1;
  }

  /* data_transfer */
  printf("received date:");

  char *c = NULL;
  DATA_TRANSFER *ct = NULL;
  int data_exists = 1;
  
  ct = malloc (sizeof(DATA_TRANSFER));
  c = (char*)ct;

  FILE *fp = fopen(INIT_DATA_FILE, "r");
  if (!fp) {
    puts("ERROR: open init data file");
    return -1;
  }

  for (;data_exists;) {
    /* data read */
    for (int j = 0; j < sizeof(DATA_TRANSFER); j++) {
      if ((*c = getc(fp)) == EOF) {
        data_exists = 0;
        break;
      }
      else
        c++;
    }
    c = (char*)ct;
    /* data trans */
    if (data_exists)
      ret = libusb_control_transfer(*device, ct->RequestType, ct->bRequest, ct->wValue, ct->wIndex, data, ct->wLength, 0);
    if (ret < 0) {
      puts("ERROR: transferred out data");
      return ret;
    }
    if (ct->wLength) {
      printf(" %x", *data);
    }
  }
  putchar('\n');

  free(ct);
  fclose(fp);
  return 0;
}

void AVERTV_free( AVERTV_DEVICE **av_device )
{
  libusb_close((*av_device)->usb_device_handle);
  free(*av_device);
}
