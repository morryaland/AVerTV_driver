#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/averapi.h"

int AVERTV_init( AVERTV_DEVICE **device )
{
  *device = (AVERTV_DEVICE*)malloc(sizeof(AVERTV_DEVICE));
  if (!*device)
    return -1;
  memset(*device, 0, sizeof(AVERTV_DEVICE));
  puts("alloc");
  return 0;
}

void AVERTV_free( AVERTV_DEVICE **device )
{
  free(device);
}
