/*
 * ov5693_mode_tbls.h - ov5693 sensor mode tables
 *
 * Copyright (c) 2015-2019, NVIDIA CORPORATION, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __OV5693_TABLES__
#define __OV5693_TABLES__

#include <media/camera_common.h>

#define OV5693_TABLE_WAIT_MS	0
#define OV5693_TABLE_END	1
#define OV5693_MAX_RETRIES	3
#define OV5693_WAIT_MS		10

#define ENABLE_EXTRA_MODES 0

#define ov5693_reg struct reg_8

static const ov5693_reg ov5693_start[] = {
	{0x0100, 0x01}, /* mode select streaming on */
	{OV5693_TABLE_END, 0x00}
};

static const ov5693_reg ov5693_stop[] = {
	{0x0100, 0x00}, /* mode select streaming on */
	{OV5693_TABLE_END, 0x00}
};

static const ov5693_reg tp_colorbars[] = {
	{0x0600, 0x00},
	{0x0601, 0x02},

	{OV5693_TABLE_WAIT_MS, OV5693_WAIT_MS},
	{OV5693_TABLE_END, 0x00}
};

static const ov5693_reg mode_2592x1944[] = {
	{OV5693_TABLE_WAIT_MS, OV5693_WAIT_MS},
	{0x0100, 0x00},/* Including sw reset */
	{OV5693_TABLE_END, 0x0000}
};

enum {
	OV5693_MODE_2592X1944,

	OV5693_MODE_START_STREAM,
	OV5693_MODE_STOP_STREAM,
	OV5693_MODE_TEST_PATTERN
};

static const ov5693_reg *mode_table[] = {
	[OV5693_MODE_2592X1944]			= mode_2592x1944,

	[OV5693_MODE_START_STREAM]		= ov5693_start,
	[OV5693_MODE_STOP_STREAM]		= ov5693_stop,
	[OV5693_MODE_TEST_PATTERN]		= tp_colorbars,
};


static const int ov5693_30fps[] = {
	30,
};


static const struct camera_common_frmfmt ov5693_frmfmt[] = {
	{{1948, 1096},	ov5693_30fps,	1, 0,	OV5693_MODE_2592X1944},
};
#endif  /* __OV5693_TABLES__ */

