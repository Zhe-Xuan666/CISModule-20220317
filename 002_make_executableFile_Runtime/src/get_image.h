#ifndef __GET_IMAGE_H__
#define __GET_IMAGE_H__

/* Std Libs */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"

/* Linux Libs */

#include <fcntl.h>
#include <unistd.h> // For close

/* V4L2 Libs*/
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>

#define VIDEO_DEVICE "/dev/video0"
#define SENSOR_COLORFORMAT V4L2_PIX_FMT_SRGGB12
#define BUFFER_COUNT 5

#ifdef __cplusplus
extern "C"
{
#endif
uint8_t *video_buffer_ptr[BUFFER_COUNT];

/* Return cam_fd or -1 for error */
int cam_init(int IMAGE_WIDTH, int IMAGE_HEIGHT);

/* Convert Data Byte Order */
void cvt_ByteOrder(uint8_t *new_file,uint8_t *raw_file, int raw_buffer_size);

/* Return 0 for success, -1 for error */
int cam_get_image(uint8_t *out_buffer, int buffer_size, int cam_fd);

/* Close camera before leaving */
int cam_close(int cam_fd);

#ifdef __cplusplus
}
#endif

#endif
