#ifndef AVERAPI_H
#define AVERAPI_H

#include <libusb-1.0/libusb.h>

typedef struct {
} AVERTV_DEVICE;

int AVERTV_init( AVERTV_DEVICE **device );

void AVERTV_free( AVERTV_DEVICE **device );

#endif
