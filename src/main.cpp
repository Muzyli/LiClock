#include <A_Config.h>
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ CONFIG_SPI_CS, /*DC=*/CONFIG_PIN_DC, /*RST=*/CONFIG_PIN_RST, /*BUSY=*/CONFIG_PIN_BUSY)); // 注意：此类略微修改过，使用两个缓冲区
DynamicJsonDocument config(1024);

void task_appManager(void *)
{
    while (1)
    {
        appManager.update();
        delay(10);
    }
}
void setup()
{
    bool initResult = hal.init();
    // openLua();
    // lua_execute("/spiffs/boot.lua");
    xTaskCreate(task_appManager, "appManager", 10240, NULL, 1, NULL);
    hal.getTime();
    if (hal.timeinfo.tm_year > (2016 - 1900))
    {
        // 判断是否是手动退出夜间模式
        if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0 || esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT1)
        {
            if (night_sleep != 0)
            {
                night_sleep = 0;
                night_sleep_today = hal.timeinfo.tm_mday;
            }
        }
        hal.checkNightSleep();
    }
    if (initResult == false)
    {
        appManager.parameter = "p";
    }
    bool recoverLast = false;
    if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_UNDEFINED)
    {
        recoverLast = appManager.recover();
    }
    if (recoverLast == false)
    {
        String bootapp = hal.pref.getString("boot", "");
        if (bootapp == "")
        {
            hal.pref.putString("boot", "clock");
            bootapp = "clock";
        }
        if (bootapp == "clock")
        {
            appManager.gotoApp(appManager.getRealClock());
        }
        else
        {
            appManager.gotoApp(bootapp.c_str());
        }
    }
    return;
}

int NTPCounter = 0;
void loop()
{
    vTaskDelay(portMAX_DELAY);
}
