#ifndef MYFUNCTS_H_INCLUDED
#define MYFUNCTS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif
    //read_ini
    extern char buffIni[40];
    extern char iniFile[20];
    extern int IMAGE_WIDTH;
    extern int IMAGE_HEIGHT;
    extern int IMAGE_SIZE;
    int convert_buf(int frame_num);
    bool initFuncts(char* _iniFile);
    int ini_gets(const char *Section, const char *Key, const char *DefValue, char *Buffer, int BufferSize, const char *Filename);

#ifdef __cplusplus
}
#endif


#endif // MYFUNCTS_H_INCLUDED
