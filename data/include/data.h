
typedef struct {
    char* name;
    char* mac;
    int rssi;
} bluetooth_frame;

bluetooth_frame* new_frame();
int calc_len(bluetooth_frame* frame);
char* format_data(char* str, bluetooth_frame* frame);

