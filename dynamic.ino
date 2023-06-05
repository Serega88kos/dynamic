#include <Arduino.h>
#define AP_SSID "HOME"
#define AP_PASS ""
#include <GyverHUB.h>
GyverHUB hub("MyDevices", "ESP8266", "");
#include <LittleFS.h>
#include <Arduino.h>
#include <FileData.h>
struct MODES {
  uint8_t max_modes = 7;      // максимум режимов
  uint8_t number_of_modes = 5;// кол-во режимов
  uint8_t time_spin = 2;     // значение времени
  uint8_t selelect_mode = 0;  // выбор режима
  uint8_t selelect_mode_0 = 0;
  uint8_t selelect_mode_1 = 0;
  uint8_t selelect_mode_2 = 0;
  uint8_t selelect_mode_3 = 0;
  uint8_t selelect_mode_4 = 0;
  uint8_t selelect_mode_5 = 0;
  uint8_t selelect_mode_6 = 0;
  uint8_t selelect_mode_7 = 0;
  uint8_t selelect_mode_ = 0;
  uint8_t time_spin_0 = 0;
  uint8_t time_spin_1 = 0;
  uint8_t time_spin_2 = 0;
  uint8_t time_spin_3 = 0;
  uint8_t time_spin_4 = 0;
  uint8_t time_spin_5 = 0;
  uint8_t time_spin_6 = 0;
  uint8_t time_spin_7 = 0;
  uint8_t time_spin_ = 0;
};
MODES modes;
FileData modes_ (&LittleFS, "/mod.dat", 'A', &modes, sizeof(modes));

void build() {
  hub.BeginWidgets();
  bool flag_modes = 0;
  hub.WidgetSize(20);
  if (flag_modes |= hub.Spinner(F("number_of_modes"), &modes.number_of_modes, GH_UINT8, F("Кол-во режимов"), 0, modes.max_modes, 1)) {
    hub.refresh();
  }
  hub.Title("");
  for (int i = 0; i < modes.number_of_modes; i++) {
    hub.WidgetSize(50);
    flag_modes |= hub.Select (String("mode_") + i,  &modes.selelect_mode_ + i, F("Часы,Темп. дома,Темп. улица,Давление,Влажность,Дата"), String("Режим ") + (i + 1));
    flag_modes |= hub.Spinner(String("time_spin_") + i, &modes.time_spin_ + i, GH_UINT16, String("Время ") + (i + 1), 2, 30, 1);
  }
  if (flag_modes) {
    modes_.update();
  }
}

int myMods[modes.number_of_modes] = {0, 1, 2, 3, 4}; // режимы
int myTime[modes.number_of_modes] = {2, 2, 2, 2, 2}; // время


void mod() {
  uint8_t sel_mod;
  uint8_t sel_time;
  switch (sel_mod) {
    case 0:
      timeToStringDots();
      timeToString();
      //delay(sel_time);
      break;
    case 1:
      TemperToString();
      delay(sel_time);
      break;
    case 2:
      TemperOutToString();
      delay(sel_time);
      break;
    case 3:
      PressToString();
      delay(sel_time);
      break;
    case 4:
      HumToString();
      delay(sel_time);
      break;
    case 5:
      DateToString();
      delay(sel_time);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  LittleFS.begin();
  FDstat_t stat6 = modes_.read();
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  hub.onBuild(build);
  hub.begin();
}
void loop() {
  hub.tick();
  modes_.tick();
}
void timeToStringDots() {}
void timeToString() {}
void TemperToString() {}
void TemperOutToString() {}
void PressToString() {}
void HumToString() {}
void DateToString() {}
