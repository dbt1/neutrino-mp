/*
 * determine the capabilities of the hardware.
 * part of libstb-hal
 *
 * (C) 2010-2012,2016 Stefan Seyfried
 *
 * License: GPL v2 or later
 */
#include "cs_api.h"
#include <stdio.h>
#include <string.h>
#include "hardware_caps.h"

static int initialized = 0;
static hw_caps_t caps;

hw_caps_t *get_hwcaps(void) {
	if (initialized)
		return &caps;
	int rev = cs_get_revision();
	caps.has_fan = (rev < 8);
	caps.has_HDMI = 1;
	caps.has_SCART = (rev != 10);
	caps.has_SCART_input = 0;
	caps.has_YUV_cinch = 1;
	caps.can_shutdown = (rev > 7);
	caps.can_cec = 1;
	caps.display_type = HW_DISPLAY_LINE_TEXT;
	caps.display_xres = 12;
	caps.display_yres = 0;
	caps.can_set_display_brightness = 1;
	strcpy(caps.boxvendor, "Coolstream");
	/* list of boxnames from neutrinoyparser.cpp */
	strcpy(caps.boxarch, "Nevis");
	switch (rev) {
	case 6:
	case 7: // Black Stallion Edition
		strcpy(caps.boxname, "HD1");
		break;
	case 8:
		strcpy(caps.boxname, "Neo");
		break;
	case 9:
		strcpy(caps.boxname, "Tank");
		strcpy(caps.boxarch, "Apollo");
		break;
	case 10:
		strcpy(caps.boxname, "Zee");
		break;
	case 11:
		strcpy(caps.boxname, "Trinity");
		strcpy(caps.boxarch, "Shiner");
		break;
	case 12:
		strcpy(caps.boxname, "Zee2");
		strcpy(caps.boxarch, "Kronos");
		break;
	default:
		strcpy(caps.boxname, "UNKNOWN_BOX");
		strcpy(caps.boxarch, "Unknown");
		fprintf(stderr, "[%s] unhandled box revision %d\n", __func__, rev);
	}
	initialized = 1;
	return &caps;
}

