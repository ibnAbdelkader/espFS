#include <stdio.h>
#include "esp_spiffs.h"
#include "esp_log.h"

static const char *TAG = "FileSystem";

void app_main(void)
{
    printf("Hello from ESP32\n");
    esp_vfs_spiffs_conf_t config = {
        .partition_label = NULL,
        .format_if_mount_failed = true,
        .max_files = 5,
        .base_path = "/storage"};

    esp_err_t result = esp_vfs_spiffs_register(&config);

    if (result != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to Intialize SPIFFS (%s) \n", esp_err_to_name(result));
        return;
    }

    size_t total = 0, used = 0;
    result = esp_spiffs_info(config.partition_label, &total, &used);
    if (result != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get partition info \n");
    }
    else
    {
        ESP_LOGI(TAG, "Partition Total space size= %d, used space size= %d", total, used);
    }

    FILE *f = fopen("/storage/myfile.txt", "r");
    if (f == NULL)
    {
        ESP_LOGE(TAG, "Failed to open file");
        return;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    printf("%s \n", line);
}
