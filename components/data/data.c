#include <stdio.h>
#include "data.h"


int calc_len(time_t timestamp, csha_bt_packet* frame)
{
            // characters for device name
    return // strlen(frame->name) + 
            // characters required for rssi value
            (frame->rssi == 0 || frame->rssi == 1 ? 1 : ceil(log10(abs(frame->rssi)))) + 
            (frame->rssi < 0 ? 1:0) +  //negative takes on extra
            // characters required for timestamp 
            (timestamp == 0 ? 1: ceil(log10(timestamp))) +
            // number of separator characters + characters for mac + characters for mac + 
            6 + 17 + 17;
}

char* format_data(char* str, time_t timestamp, char* sourcemac, csha_bt_packet* frame)
{
    sprintf(str, "%s%s%d%s%s%s%d%s%s",
            sourcemac, SEPARATOR, 
            (int) timestamp, SEPARATOR,
            //frame->name,SEPARATOR, 
            frame->mac,SEPARATOR, 
            frame->rssi,SEPARATOR,SEPARATOR
            );
    return str;
}

char* format_heartbeat(char* str, size_t packet_len, time_t timestamp, char* sourcemac)
{
    //size_t packet_len = sizeof("heartbeat") + sizeof(timestamp) + sizeof(sourcemac) + 4;
    // fuck it's still too short.
    snprintf(str, packet_len,
            "heartbeat%s%s%s%ld%s%s",
            SEPARATOR, sourcemac, SEPARATOR, timestamp, SEPARATOR, SEPARATOR);
    return str;
}
