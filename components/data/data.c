#include <stdio.h>
#include "data.h"

#define SEPARATOR "|"

bluetooth_frame* new_frame()
{
    return malloc(sizeof(bluetooth_frame));
}

int calc_len(bluetooth_frame* frame)
{
    return strlen(frame -> name) + strlen(frame -> mac) + (frame -> rssi == 0 || frame -> rssi == 1 ? 1 : ceil(log10(frame -> rssi))) + 4;
}

char* format_data(char* str, bluetooth_frame* frame)
{
    sprintf(str, "%s%s%s%s%d%s%s", frame -> name,SEPARATOR, frame -> mac,SEPARATOR, frame -> rssi,SEPARATOR,SEPARATOR);
    return str;
}