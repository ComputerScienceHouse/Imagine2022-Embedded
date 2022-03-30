#include "network.h"
#include <stdint.h>

char* byte_mac_to_str(char* str, uint8_t* mac)
{
    //17 char long
    sprintf(str, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    return str;
}

char* get_wifi_mac_str(char* str)
{
    uint8_t mac[6];
/*  esp_netif_t *my_netif = NULL;
    my_netif = esp_netif_next(my_netif);
    esp_netif_get_mac(my_netif, mac);*/
    esp_efuse_mac_get_default(mac);
    snprintf(str, 18, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    return str;
}

// TODO: Aw fuck I have to fix this.
bool wifi_connected(void)
{
    //return connected;
    return true; // don't worry about it lol
}

void time_sync_notification_cb(struct timeval* tv)
{
    //Nothing yet you fool
}

void init_sntp(void)
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, NTP_SERVER);
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_init();
    sntp_setup = true;
}

bool sntp_update_time(void)
{
    init_sntp();
    int retry = 0;
    for (; retry < SNTP_MAX_RETRY_COUNT && sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET; ++retry)
    {
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    return sntp_get_sync_status() == SNTP_SYNC_STATUS_COMPLETED;
}
