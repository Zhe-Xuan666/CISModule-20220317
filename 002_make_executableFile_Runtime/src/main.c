#include "get_image.h"
#include "myFuncts.h"
//time
#include <time.h>
#include <sys/time.h>

/*read_ini*/
char buffIni[40];
char iniFile[20];
int IMAGE_WIDTH;
int IMAGE_HEIGHT;
int IMAGE_SIZE;
/*read_ini*/

int main()
{
    int cam_fd;
    FILE *f;
    uint8_t *raw_buffer,*cvt_buffer;
    uint8_t file_header[16];
    char tmp[64] = {"---\n"};

    /*Run Time*/
    #define CLOCKS_PER_MSEC 1000
    clock_t S1_Begin, S1_End, S2_Begin, S2_End, S3_Begin, S3_End, S4_Begin, S4_End;
    double S1_duration, S2_duration, S3_duration, S4_duration;
    /*Run Time*/

    S1_Begin = clock();
    /*Read ini*/
    printf("Start calling <config.ini> to read raw data:\r\n");
    strcpy(iniFile,"config.ini");

    if(!initFuncts(iniFile))
    {
        puts("initFuncts error");
        return EXIT_FAILURE;
    }

    puts("initFuncts OK");
    /*Read ini*/
    S1_End = clock();
    S1_duration = double(S1_End - S1_Begin) / CLOCKS_PER_MSEC;
    printf("Read ini run time = %f ms\n",S1_duration);

    /*Set buffer size*/
    raw_buffer = (uint8_t *) malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 2 * sizeof(uint8_t));
    cvt_buffer = (uint8_t *) malloc(IMAGE_WIDTH * IMAGE_HEIGHT * 2 * sizeof(uint8_t));

    S2_Begin = clock();
    /*init cam*/
    cam_fd = cam_init(IMAGE_WIDTH,IMAGE_HEIGHT);
    if (cam_fd == -1)
    {
        printf("fail to init\n");
        free(raw_buffer);
        free(cvt_buffer);
        return -1;
    }
    /*printf("Init OK, sleep for 5 sec\n");
    sleep(5);*/
    /*init cam*/
    S2_End = clock();
    S2_duration = double(S2_End - S2_Begin) / CLOCKS_PER_MSEC;
    printf("Cam init run time = %f ms\n",S2_duration);

    S3_Begin = clock();
    /*Get Data*/
    if (cam_get_image(raw_buffer,IMAGE_SIZE,cam_fd) != 0 )
    {
        printf("error get image\n");
        goto end;
    }
    /*Get Data*/
    S3_End = clock();
    S3_duration = double(S3_End - S3_Begin) / CLOCKS_PER_MSEC;
    printf("Read Image Data run time = %f ms\n",S3_duration);

    /*Show Data*/
    for (int i = 0; i < 16; i++)
        sprintf(&tmp[strlen(tmp)], "%02x ", raw_buffer[i]);
    printf("%s\r\n", tmp);
    /*Show Data*/

    S4_Begin = clock();
    /*Convert Data Byte Order*/
    cvt_ByteOrder(cvt_buffer, raw_buffer, IMAGE_SIZE);
    /*Convert Data Byte Order*/
    S4_End = clock();
    S4_duration = double(S4_End - S4_Begin) / CLOCKS_PER_MSEC;
    printf("Convert Byte Order run time = %f ms\n", S4_duration);

    /*Write File*/
    f=fopen("./Pic/Test_Output.raw","wb");
    if (f== NULL)
    {
        printf("Fail to open file\n");
        goto end;
    }
    memset(file_header, 0, 16);
    file_header[8] = IMAGE_WIDTH % 256;
    file_header[9] = (int)IMAGE_WIDTH / 256;
    file_header[12] = IMAGE_HEIGHT % 256;
    file_header[13] = (int)IMAGE_HEIGHT / 256;
    fwrite(file_header, 1, 16, f);
    fseek(f,16,SEEK_SET);
    fwrite(cvt_buffer,1,IMAGE_SIZE,f);
    fclose(f);
    /*Write File*/

end:
    cam_close(cam_fd);
    free(raw_buffer);
    free(cvt_buffer);

    return 0;
}
