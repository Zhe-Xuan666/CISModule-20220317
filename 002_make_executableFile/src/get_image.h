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
#define SENSOR_COLORFORMAT V4L2_PIX_FMT_SBGGR10
#define BUFFER_COUNT 5

/* BufferType */
#define BufferType uint8_t

/* Output buffer format defines*/
#define INT_8 1
#define INT_16 2
#define INT_32 3
#define FLOAT_32 4

#ifdef __cplusplus
extern "C"
{
#endif
    /* camera setting */
    /* Return cam_fd or -1 for error */
    int cam_init(int IMAGE_WIDTH, int IMAGE_HEIGHT);

    /* Return 0 for success, -1 for error */
    int cam_get_image(BufferType *out_buffer, int buffer_size, int cam_fd);

    /* Return 0 for success, -1 for error */
    /* Use fmt to decide output buffer format */
    int cam_get_image_ext_fmt(void *out_buffer, int out_buffer_size, int cam_fd, int fmt);

    /* Close camera before leaving */
    int cam_close(int cam_fd);

    /* ByteSetting and Printout */
    /* Convert Data Byte Order */
    void cvt_ByteOrder(BufferType *new_file, BufferType *raw_file, int raw_buffer_size, int pixel_bit);
    void init_log();
    void write_log(char *log_msg);

#ifdef __cplusplus
}
#endif

#endif
