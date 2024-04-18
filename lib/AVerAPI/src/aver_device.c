#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/averapi.h"

#define TRANSFERRED_LEN 43
#define _CT(i,rt,r,v,in,l) \
ct[i].RequestType = rt; \
ct[i].bRequest = r; \
ct[i].wValue = v; \
ct[i].wIndex = in; \
ct[i].wLength = l;

typedef struct {
  uint8_t RequestType;
  uint8_t bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} DATA_TRANSFER;

static DATA_TRANSFER ct[TRANSFERRED_LEN];

static int AVERTV_device_connect( libusb_device_handle **device );
static void ct_init( void );

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

static void ct_init()
{
  _CT(0,  0x40,1, 0x0028, 0x0000,0)
  _CT(1,  0x40,1, 0x0068, 0x0002,0) /* led */
  _CT(2,  0x40,1, 0x0000, 0x000d,0)
  _CT(3,  0x40,1, 0x0002, 0x000f,0)
  _CT(4,  0x40,1, 0x0012, 0x0300,0)
  _CT(5,  0x40,1, 0x002d, 0x0350,0)
  _CT(6,  0x40,1, 0x0001, 0x0351,0)
  _CT(7,  0x40,1, 0x0000, 0x0352,0)
  _CT(8,  0x40,1, 0x0000, 0x0353,0)
  _CT(9,  0x40,1, 0x0080, 0x0300,0)
  _CT(10, 0x40,1, 0x0010, 0x0018,0)
  _CT(11, 0x40,1, 0x0000, 0x0019,0)
  _CT(12, 0x40,1, 0x001e, 0x0202,0)
  _CT(13, 0x40,1, 0x0004, 0x0110,0)
  _CT(14, 0x40,1, 0x0000, 0x0111,0)
  _CT(15, 0x40,1, 0x000d, 0x0112,0)
  _CT(16, 0x40,1, 0x0000, 0x0113,0)
  _CT(17, 0x40,1, 0x00a4, 0x0114,0)
  _CT(18, 0x40,1, 0x0005, 0x0115,0)
  _CT(19, 0x40,1, 0x00fd, 0x0116,0)
  _CT(20, 0x40,1, 0x0000, 0x0117,0)
  _CT(21, 0x40,1, 0x0033, 0x0100,0)
  _CT(22, 0x40,1, 0x00ba, 0x0203,0)
  _CT(23, 0x40,1, 0x0082, 0x0208,0)
  _CT(24, 0x40,1, 0x0020, 0x0200,0)
  _CT(25, 0xc0,0, 0x0000, 0x0201,1)
  _CT(26, 0xc0,0, 0x0000, 0x0209,1)
  _CT(27, 0x40,1, 0x0082, 0x0208,0)
  _CT(28, 0x40,1, 0x0020, 0x0200,0)
  _CT(29, 0xc0,0, 0x0000, 0x0201,1)
  _CT(30, 0xc0,0, 0x0000, 0x0209,1)
  _CT(31, 0x40,1, 0x000f, 0x0204,0)
  _CT(32, 0x40,1, 0x000a, 0x0205,0)
  _CT(33, 0x40,1, 0x0005, 0x0200,0)
  _CT(34, 0xc0,0, 0x0000, 0x0201,1)
  _CT(35, 0x40,1, 0x0030, 0x0204,0)
  _CT(36, 0x40,1, 0x0001, 0x0205,0)
  _CT(37, 0x40,1, 0x0005, 0x0200,0)
  _CT(38, 0xc0,0, 0x0000, 0x0201,1)
  _CT(39, 0x40,1, 0x0003, 0x0204,0)
  _CT(40, 0x40,1, 0x006f, 0x0205,0)
  _CT(41, 0x40,1, 0x0005, 0x0200,0)
  _CT(42, 0xc0,0, 0x0000, 0x0201,1)
}

static int AVERTV_device_connect( libusb_device_handle **device )
{
  int ret;

  *device = libusb_open_device_with_vid_pid(NULL, VID_AVERMEDIA, PID_AVERTV);
  if (*device == NULL) {
    puts("ERROR: connect device");
    return -1;
  }

  /* data_transfer */
  ct_init();
  unsigned char *data = NULL; 
  for (int i = 0; i < TRANSFERRED_LEN; i++) {
    ret = libusb_control_transfer(*device, ct[i].RequestType, ct[i].bRequest, ct[i].wValue, ct[i].wIndex, data, ct[i].wLength, 0);
    if (ret < 0) {
      puts("ERROR: transferred out data");
      return ret;
    }
    if (data)
      printf("%x\n", *data);
  }
  return 0;
}

void AVERTV_free( AVERTV_DEVICE **av_device )
{
  libusb_close((*av_device)->usb_device_handle);
  free(*av_device);
}
