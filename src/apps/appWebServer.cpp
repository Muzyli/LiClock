#include "AppManager.h"
static const uint8_t webserver_bits[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x7f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x87, 0x03, 0x00, 0xe0,
    0x87, 0x03, 0x00, 0xe0, 0x87, 0x03, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xe0,
    0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0,
    0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0,
    0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0,
    0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0,
    0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0, 0x07, 0x00, 0x00, 0xe0,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0x7f,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
class AppWebserver : public AppBase
{
private:
    /* data */
public:
    AppWebserver()
    {
        name = "webserver";
        title = "网页配置";
        description = "通过网页配置此设备";
        image = webserver_bits;
        _showInList = true;
        _reentrant = false;
    }
    void setup();
};
static AppWebserver app;

void AppWebserver::setup()
{
    if (GUI::msgbox_yn("是否连接WiFi", "如果使用WiFi，选择“确定”如果使用SoftAP，选择“取消”", "WiFi(右)", "SoftAP(左)"))
    {
        display.clearScreen();
        u8g2Fonts.setCursor(0, 15);
        u8g2Fonts.setFontMode(1);
        u8g2Fonts.printf("将连接WiFi并启动HTTP服务器\n");
        display.display(true);
        hal.autoConnectWiFi();
        beginWebServer();
        u8g2Fonts.printf("请在浏览器中打开以下网址\n");
        u8g2Fonts.printf("http://%s\n", WiFi.localIP().toString().c_str());
        u8g2Fonts.printf("Lua未运行时按左键重启\n");
        display.display(true);
        while (1)
        {
            updateWebServer();
            if (LuaRunning)
                continue;
            if (hal.btnl.isPressing())
            {
                while(hal.btnl.isPressing())delay(20);
                ESP.restart();
                break;
            }
        }
    }
    else
    {
        hal.WiFiConfigManual();
        ESP.restart();
    }
}
