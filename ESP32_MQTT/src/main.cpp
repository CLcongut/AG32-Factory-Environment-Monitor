#include <Arduino.h>
#include "main.h"
#include <WIFI.h>
#include "PubSubClient.h"
#include "ArduinoJson.h"
#include <Preferences.h>
#include <U8g2lib.h>

/********************************************************************************
 * 根据不同用户需要修改的部分
 * 开始 >>
 */
/*要让ESP01S连接的WIFI信息*/
#define wifi_SSID "CLcongut" // WIFI名字，不可中文
#define wifi_PSWD "88888888" // WIFI密码，不可中文，最好 8 位

/*设备名称*/
#define DeviceName "AG32FacEnv"
#define ProductKey "a1gPCA1OFYd"

/*MQTT三元组*/
#define mqtt_USERNAME DeviceName "&" ProductKey
#define mqtt_PASSWORD "1db72ec3d4161b0394e0c684733ffbd64c719238828dcd48d60b4ada8301bff5"
#define mqtt_CLIENTID "a1gPCA1OFYd.AG32FacEnv|securemode=2,signmethod=hmacsha256,timestamp=1718700107295|"

/*MQTT域名*/
#define mqtt_PORT 1883
#define mqtt_HOST_URL ProductKey ".iot-as-mqtt.cn-shanghai.aliyuncs.com"

/*发布主题*/
#define mqtt_pub_TOPIC "/sys/" ProductKey "/" DeviceName "/thing/event/property/post"
#define mqtt_pub_FORMAT "{\"id\":\"" DeviceName "\",\"version\":\"1.0\",\"method\":\"thing.event.property.post\",\"params\":%s}"
/*订阅主题*/
#define mqtt_sub_TOPIC "/sys/" ProductKey "/" DeviceName "/thing/service/property/set"

/*受控设备对象关键字*/
#define setClass_NAME1 "AirAlarm"  // 空气质量阈值
#define setClass_NAME2 "FumeAlarm" // 烟雾报警阈值

/*状态发送对象关键字*/
#define postClass_NAME1 "EnvTemperature" // 环境温度
#define postClass_NAME2 "EnvHumidity"    // 环境湿度
#define postClass_NAME3 "EnvAir"         // 环境空气质量
#define postClass_NAME4 "EnvFume"        // 环境烟雾浓度
#define postClass_NAME5 "FlameState"     // 火焰状态
#define postClass_NAME6 "AirAlarm"       // 空气质量阈值
#define postClass_NAME7 "FumeAlarm"      // 烟雾报警阈值
#define postClass_NAME8 "power"          // 电池电量

/********************************************************************************
 * << 结束
 */
#define HEAD 0xAA
#define ADDRESS 0x39
#define CMD 0x02
#define DATACNT 2
#define DATALEN 7

uint8_t txbuf[DATALEN];

uint64_t lastMs;

Receive_Value_Struct Receive_VS;
Transmit_Value_Struct Transmit_VS;

WiFiClient espClient;
PubSubClient client(espClient);

Preferences AG32Pref;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0);

/*WIFI连接*/
void wifiInit()
{
  WiFi.begin(wifi_SSID, wifi_PSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    oled.clearBuffer();
    oled.drawStr(0, 20, "WIFI Connecting ...");
    oled.sendBuffer();
  }
  oled.clearBuffer();
  oled.drawStr(0, 20, "WIFI Connected !");
  oled.sendBuffer();
}

/*MQTT连接*/
void mqttCheckConnect()
{
  while (!client.connected())
  {
    oled.clearBuffer();
    oled.drawStr(0, 20, "MQTT Connecting ...");
    oled.sendBuffer();
    if (client.connect(mqtt_CLIENTID, mqtt_USERNAME, mqtt_PASSWORD))
    {
      oled.clearBuffer();
      oled.drawStr(0, 20, "MQTT Connected !");
      oled.sendBuffer();
      client.subscribe(mqtt_sub_TOPIC);
    }
    else
    {
      oled.clearBuffer();
      oled.drawStr(0, 20, "MQTT Connect err :");
      oled.setCursor(0, 40);
      oled.println(client.state());
      oled.sendBuffer();
      delay(5000);
    }
  }
}

/*MQTT发布*/
void mqttIntervalPost()
{
  char param[32];
  char jsonBuf[128];

  /*温度发送*/
  sprintf(param, "{\"" postClass_NAME1 "\":%d}", Receive_VS.temp);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*湿度发送*/
  sprintf(param, "{\"" postClass_NAME2 "\":%d}", Receive_VS.humi);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*空气质量发送*/
  sprintf(param, "{\"" postClass_NAME3 "\":%d}", Receive_VS.airt);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*烟雾浓度发送*/
  sprintf(param, "{\"" postClass_NAME4 "\":%d}", Receive_VS.fume);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*火焰发送*/
  sprintf(param, "{\"" postClass_NAME5 "\":%d}", Receive_VS.fire);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*空气质量阈值发送*/
  sprintf(param, "{\"" postClass_NAME6 "\":%d}", Receive_VS.air_ts);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*烟雾浓度阈值发送*/
  sprintf(param, "{\"" postClass_NAME7 "\":%d}", Receive_VS.fume_ts);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  /*电池电量发送*/
  sprintf(param, "{\"" postClass_NAME8 "\":%d}", Receive_VS.power);
  sprintf(jsonBuf, mqtt_pub_FORMAT, param);
  client.publish(mqtt_pub_TOPIC, jsonBuf);
  oled.clearBuffer();
  oled.drawStr(0, 20, "Data Posted");
  oled.sendBuffer();
}

/*和校验*/
uint8_t CheckSum(uint8_t *Buf, uint8_t Len)
{
  uint8_t i = 0;
  uint8_t sum = 0;
  uint8_t checksum = 0;

  for (i = 0; i < Len; i++)
  {
    sum += *Buf++;
  }

  checksum = sum & 0xff;

  return checksum;
}

/*MQTT接收处理*/
void callback(char *topic, byte *payload, unsigned int length)
{
#if 0
  Serial.print("Message arrived [");
  Serial.print(topic); // 打印主题信息
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]); // 打印主题内容
  }
  Serial.println();
#endif

  JsonDocument doc;                              // 创建了一个名为 doc 的动态 JSON 文档
  deserializeJson(doc, String((char *)payload)); // 从一个名为 payload 的数据中解析 JSON 数据并将其填充到 doc 中

  // DynamicJsonDocument params = doc["params"];
  oled.clearBuffer();
  oled.drawStr(0, 20, "Get Sub Data");
  
  if (doc["params"].containsKey(setClass_NAME1))
  {
    Transmit_VS.air_ts = doc["params"][setClass_NAME1];
    // Serial.printf("GOT " setClass_NAME1 "is %d", (uint32_t)Transmit_VS.air_ts);
    oled.drawStr(0, 40, "Air:");
    oled.setCursor(23, 40);
    oled.println(Transmit_VS.air_ts);
  }
  else if (doc["params"].containsKey(setClass_NAME2))
  {
    Transmit_VS.fume_ts = doc["params"][setClass_NAME2];
    // Serial.printf("GOT " setClass_NAME2 "is %d", (uint32_t)Transmit_VS.fume_ts);
    oled.drawStr(0, 60, "Fume:");
    oled.setCursor(40, 60);
    oled.println(Transmit_VS.fume_ts);
  }
  oled.sendBuffer();

  txbuf[0] = HEAD;
  txbuf[1] = ADDRESS;
  txbuf[2] = CMD;
  txbuf[3] = DATACNT;
  txbuf[4] = Transmit_VS.air_ts;
  txbuf[5] = Transmit_VS.fume_ts;
  uint8_t *pcheck = txbuf + 4;
  txbuf[6] = CheckSum(pcheck, DATACNT);
  Serial2.printf((const char *)txbuf);
}

/*串口接收处理*/
void Communicate_AG32(void)
{
  String inString = "";
  while (Serial2.available() > 0)
  {
    inString += char(Serial2.read());
    delay(10); // 延时函数用于等待字符完全进入缓冲区，可以尝试没有延时，输出结果会是什么
  }
  // 检查是否接收到数据，如果接收到数据，则输出该数据
  if (inString != "")
  {
    if (inString[2] == 0x01)
    {
      Receive_VS.temp = inString[4];
      Receive_VS.humi = inString[5];
      Receive_VS.airt = inString[6];
      Receive_VS.fume = inString[7];
      Receive_VS.fire = inString[8];
      Receive_VS.power = inString[9];
      Receive_VS.air_ts = inString[10];
      Receive_VS.fume_ts = inString[11];
      oled.clearBuffer();
      oled.drawStr(0, 20, "Get Data From");
      oled.drawStr(0, 40, "Terminal 1");
      oled.sendBuffer();
      if (Receive_VS.air_ts != Transmit_VS.air_ts || Receive_VS.fume_ts != Transmit_VS.fume_ts)
      {
        Transmit_VS.air_ts = Receive_VS.air_ts;
        Transmit_VS.fume_ts = Receive_VS.fume_ts;

        AG32Pref.begin("alarmthreshold");
        AG32Pref.putChar("air_ts", Transmit_VS.air_ts);
        AG32Pref.putChar("fume_ts", Transmit_VS.fume_ts);
        AG32Pref.end();

        oled.drawStr(0, 60, "Threshold Stored");
        oled.sendBuffer();
      }
    }
  }
}

void setup()
{
  // pinMode(19, OUTPUT);
  // digitalWrite(19, HIGH);

  Serial2.begin(115200);

  oled.begin();
  oled.clearBuffer();
  oled.setFont(u8g2_font_crox2h_tr);
  oled.drawStr(20, 20, "Hello, ESP32!");
  oled.sendBuffer();
  delay(1000);

  AG32Pref.begin("alarmthreshold");
  Transmit_VS.air_ts = AG32Pref.getChar("air_ts", 0);
  Transmit_VS.fume_ts = AG32Pref.getChar("fume_ts", 0);
  AG32Pref.end();

  oled.clearBuffer();
  oled.drawStr(0, 20, "Read threshold");
  oled.drawStr(0, 40, "Air:");
  oled.setCursor(23, 40);
  oled.println(Transmit_VS.air_ts);
  oled.drawStr(0, 60, "Fume:");
  oled.setCursor(40, 60);
  oled.println(Transmit_VS.fume_ts);
  oled.sendBuffer();
  delay(1000);

  // digitalWrite(19, LOW);
  txbuf[0] = HEAD;
  txbuf[1] = ADDRESS;
  txbuf[2] = 0x03;
  txbuf[3] = DATACNT;
  txbuf[4] = Transmit_VS.air_ts;
  txbuf[5] = Transmit_VS.fume_ts;
  uint8_t *pcheck = txbuf + 4;
  txbuf[6] = CheckSum(pcheck, DATACNT);
  Serial2.printf((const char *)txbuf);

  oled.clearBuffer();
  oled.setFont(u8g2_font_crox2h_tr);
  oled.drawStr(0, 20, "Activate Info");
  oled.drawStr(0, 40, "Transmited !");
  oled.sendBuffer();
  delay(1000);

  // wifiInit();
  // client.setServer(mqtt_HOST_URL, mqtt_PORT); /* 连接MQTT服务器 */
  // client.setCallback(callback);
}

void loop()
{
  Communicate_AG32();
  // if (millis() - lastMs >= 5000)
  // {
  //   lastMs = millis();
  //   mqttCheckConnect();
  //   /* 上报 */
  //   mqttIntervalPost();
  // }
  // client.loop();
  // delay(2000);
}
