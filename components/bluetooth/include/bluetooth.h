#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "data.h"
#include "udp.h"
#include "network.h"
#include "esp_gap_bt_api.h"


#define BT_TAG "CSHA Bluetooth"
#define BLE_TAG "CSHA BLE"

#ifdef CONFIG_BT_CLASSIC_ENABLED 
/*
* possible BT app states or states 
*/
typedef enum {
    APP_GAP_STATE_IDLE = 0,
    APP_GAP_STATE_DEVICE_DISCOVERING,
    APP_GAP_STATE_DEVICE_DISCOVER_COMPLETE,
    APP_GAP_STATE_SERVICE_DISCOVERING,
    APP_GAP_STATE_SERVICE_DISCOVER_COMPLETE,
} app_gap_state_t;

/*
* all event information passed to BT app callback 
*/
typedef struct {
    bool dev_found;
    uint8_t bdname_len;
    uint8_t eir_len;
    uint8_t rssi;
    uint32_t cod;
    uint8_t eir[ESP_BT_GAP_EIR_DATA_LEN];
    uint8_t bdname[ESP_BT_GAP_MAX_BDNAME_LEN + 1];
    esp_bd_addr_t bda;
    app_gap_state_t state;
} bt_app_gap_cb_t;

bt_app_gap_cb_t bt_m_dev_info;

/*
* update detection information to most recent detection data
*/
void update_device_info(esp_bt_gap_cb_param_t *param);

/*
* setup bluetooth application
*/
void bt_app_gap_init(void);

/*
* callback on bluetooth app state change
*/
void bt_app_gap_cb(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

/*
* start bluetooth application
*/
void bt_app_gap_start_up(void);

#endif


/*
* format Bluetooth Device Address into string
* returns pointer to string
*/
char *bda2str(esp_bd_addr_t bda, char *str, size_t size);

/*
* format UUID to string
*/
char *uuid2str(esp_bt_uuid_t *uuid, char *str, size_t size);

/* 
* get string name from Extended Inquiry Response data
*/
bool get_name_from_eir(uint8_t *eir, uint8_t *bdname, uint8_t *bdname_len);

#ifdef CONFIG_BT_BLE_ENABLED 
#include "esp_gap_ble_api.h"

/*
* callback on BLE app state change
*/
void ble_app_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
/*
* start BLE application with specified random address
*/
void ble_app_gap_start_up(esp_bd_addr_t tag_template);

#endif

#endif
