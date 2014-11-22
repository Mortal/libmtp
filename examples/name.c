/**
 * \file name.c
 * Example program to get/set device friendly name.
 *
 * Copyright (C) 2014 The libmtp development team.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#include "common.h"
#include <stdlib.h>
#include <limits.h>

static void usage (void)
{
  fprintf(stderr, "name [name]\n");
}

int main (int argc, char **argv)
{
  LIBMTP_mtpdevice_t *device;
  uint32_t id;
  char *endptr;
  char *name;
  int ret;
  LIBMTP_error_t *error;

  fprintf(stdout, "libmtp version: " LIBMTP_VERSION_STRING "\n\n");

  if (argc == 1) {
    name = NULL;
  } else if (argc == 2) {
    name = argv[1];
  } else {
    usage();
    return 1;
  }

  LIBMTP_Init();
  device = LIBMTP_Get_First_Device();
  if (device == NULL) {
    printf("No devices. Connect/replug device and try again.\n");
    return 1;
  }

  if (name == NULL) {
    name = LIBMTP_Get_Friendlyname(device);
    if (name == NULL) {
      printf("LIBMTP_Get_Friendlyname returned NULL\n");
    } else {
      printf("%s\n", name);
      free(name);
    }
  } else {
    ret = LIBMTP_Set_Friendlyname(device, name);
    if (ret != 0) {
      LIBMTP_Dump_Errorstack(device);
      goto err;
    }
  }

  LIBMTP_Release_Device(device);
  return 0;

err:
  LIBMTP_Release_Device(device);
  return 1;
}

