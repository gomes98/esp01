#include <ArduinoOTA.h>
#ifdef ESP32
#include <FS.h>
#include <SPIFFS.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <SPIFFSEditor.h>
#include <Bounce2.h>
#include <DNSServer.h>

// SKETCH BEGIN
AsyncWebServer server(80);
AsyncEventSource events("/events");

const char * hostName = "ESP01 IO";

bool timeout1 = false;
bool timeout2 = false;
uint32_t old1 = 0;
uint32_t old2 = 0;
uint32_t new1 = 0;
uint32_t new2 = 0;

bool GP0S = 0;
bool GP1S = 0;
byte IN0S = 1;
byte IN1S = 1;

#define GP0P 1
#define GP1P 3
#define BUTTON_PIN_1 0
#define BUTTON_PIN_2 2

Bounce b1 = Bounce();
Bounce b2 = Bounce();

IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;

void writeFile(String state, String path) {
  File rFile = SPIFFS.open(path, "w+");
  if (rFile) {
    rFile.println(state);
  }
  rFile.close();
}

String readFile(String path) {
  File rFile = SPIFFS.open(path, "r");
  if (rFile) {
    String content = rFile.readStringUntil('\r'); //desconsidera '\r\n'
    rFile.close();
    return content;
  }
}

void conWifi() {
  if (SPIFFS.exists("/cfg.ssid") && SPIFFS.exists("/cfg.password")) {
    String ssid = readFile("/cfg.ssid");
    String password = readFile("/cfg.password");
    WiFi.begin(ssid, password);
  }
}

void setup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(hostName);

  //pega todas as chamadas de dns e redireciona para o ap
  dnsServer.start(53, "*", apIP);

  //saidas
  pinMode(GP0P, OUTPUT);
  digitalWrite(GP0P, LOW);
  pinMode(GP1P, OUTPUT);
  digitalWrite(GP1P, LOW);
  //entradas
  b1.attach(BUTTON_PIN_1, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  b1.interval(50); // Use a debounce interval of 25 milliseconds
  b2.attach(BUTTON_PIN_2, INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  b2.interval(50); // Use a debounce interval of 25 milliseconds

  SPIFFS.begin();

  //inicializa wifi pela memoria
  conWifi();

  events.onConnect([](AsyncEventSourceClient * client) {
    client->send("hello!", NULL, millis(), 1000);
  });
  server.addHandler(&events);

  server.on("/scan", HTTP_GET, [](AsyncWebServerRequest * request) {
    String json = "[";
    int n = WiFi.scanComplete();
    if (n == -2) {
      WiFi.scanNetworks(true);
    } else if (n) {
      for (int i = 0; i < n; ++i) {
        if (i) json += ",";
        json += "{";
        json += "\"rssi\":" + String(WiFi.RSSI(i));
        json += ",\"ssid\":\"" + WiFi.SSID(i) + "\"";
        json += ",\"bssid\":\"" + WiFi.BSSIDstr(i) + "\"";
        json += ",\"channel\":" + String(WiFi.channel(i));
        json += ",\"secure\":" + String(WiFi.encryptionType(i));
        json += ",\"hidden\":" + String(WiFi.isHidden(i) ? "true" : "false");
        json += "}";
      }
      WiFi.scanDelete();
      if (WiFi.scanComplete() == -2) {
        WiFi.scanNetworks(true);
      }
    }
    json += "]";
    request->send(200, "application/json", json);
    json = String();
  });

  server.on("/gpio", HTTP_GET, [](AsyncWebServerRequest * request) {
    String ret = "{";
    ret += "\"gpio1\":";
    ret += GP0S;
    ret += ",\"gpio2\":";
    ret += GP1S;
    ret += "}";
    request->send(200, "application/json", ret);
  });

  server.on("/wstat", HTTP_GET, [](AsyncWebServerRequest * request) {
    String ret = "{";
    ret += "\"mac\":\"";
    ret += WiFi.macAddress();
    ret += "\",\"ip\":\"";
    ret += WiFi.localIP().toString();
    ret += "\",\"hostname\":\"";
    ret += WiFi.hostname();
    ret += "\",\"SSID\":\"";
    ret += WiFi.SSID();
    ret += "\",\"RSSI\":";
    ret += WiFi.RSSI();
    ret += ",\"status\":";
    ret += WiFi.status();
    ret += "}";
    request->send(200, "application/json", ret);
  });

  server.on("/input", HTTP_GET, [](AsyncWebServerRequest * request) {
    String ret = "{";
    ret += "\"in1\":";
    ret += IN0S;
    ret += ",\"in2\":";
    ret += IN1S;
    ret += "}";
    request->send(200, "application/json", ret);
  });

  server.on("/gpio", HTTP_POST, [](AsyncWebServerRequest * request) {
    String json = "{";
    long timeout = 0;
    if (request->hasParam("timeout", true)) {
      AsyncWebParameter* p = request->getParam("timeout", true);
      const char* state = p->value().c_str();
      timeout = atoi(state);
    }
    if (request->hasParam("gpio1", true)) {
      AsyncWebParameter* p = request->getParam("gpio1", true);
      const char* state = p->value().c_str();
      json += "\"gpio1\":";
      if (state[0] == '0') {
        GP0S = 0;
      } else if (state[0] == 't') {
        GP0S = !GP0S;
      } else {
        GP0S = 1;
      }
      json += GP0S;
      if (GP0S) {
        events.send("{\"gpio1\": 1}", "output");
      } else {
        events.send("{\"gpio1\": 0}", "output");
      }
      if (timeout > 0) {
        timeout1 = true;
        old1 = millis();
        new1 = old1 + timeout;
      }
    }
    if (request->hasParam("gpio2", true)) {
      AsyncWebParameter* p = request->getParam("gpio2", true);
      const char* state = p->value().c_str();
      json += "\"gpio2\":";
      if (state[0] == '0') {
        GP1S = 0;
      } else if (state[0] == 't') {
        GP1S = !GP1S;
      } else {
        GP1S = 1;
      }
      json += GP1S;
      if (GP1S) {
        events.send("{\"gpio2\": 1}", "output");
      } else {
        events.send("{\"gpio2\": 0}", "output");
      }
      if (timeout > 0) {
        timeout2 = true;
        old2 = millis();
        new2 = old2 + timeout;
      }
    }
    json += "}";
    request->send(200, "application/json", json);

  });

  server.on("/wifi", HTTP_POST, [](AsyncWebServerRequest * request) {
    String wifi = "{";
    if (request->hasParam("ssid", true)) {
      AsyncWebParameter* p = request->getParam("ssid", true);
      const char* state = p->value().c_str();
      wifi += "\"ssid\":\"";
      wifi += state;
      wifi += "\"";
      writeFile(state, "/cfg.ssid");
    }
    if (request->hasParam("password", true)) {
      AsyncWebParameter* p = request->getParam("password", true);
      const char* state = p->value().c_str();
      wifi += ",\"password\":\"";
      wifi += state;
      wifi += "\"}";
      writeFile(state, "/cfg.password");
      request->send(200, "application/json", wifi);
    }
    conWifi();
  });

  server.on("/wifi", HTTP_GET, [](AsyncWebServerRequest * request) {
    String wifi = "{";
    wifi += "\"ssid\":\"";
    wifi += readFile("/cfg.ssid");
    wifi += "\"";
    wifi += ",\"password\":\"";
    wifi += readFile("/cfg.password");
    wifi += "\"}";
    request->send(200, "application/json", wifi);
  });

  server.on("/config", HTTP_POST, [](AsyncWebServerRequest * request) {
    String wifi = "{";
    if (request->hasParam("save", true)) {
      AsyncWebParameter* p = request->getParam("save", true);
      const char* state = p->value().c_str();
      writeFile(state, "/config.json");
      request->send(200);
    } else {
      request->send(400);
    }
  });
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (SPIFFS.exists("/config.json")) {
      String ret = "";
      ret = readFile("/config.json");
      request->send(200, "application/json", ret);
    } else {
      request->send(404);
    }

  });
  server.on("/sse", HTTP_POST, [](AsyncWebServerRequest * request) {
    String wifi = "{";
    if (request->hasParam("data", true)) {
      AsyncWebParameter* p = request->getParam("data", true);
      String d = "";
      d += p->value().c_str();
      d += "";
      events.send(d.c_str(), "sse", millis());
      request->send(200);
    } else {
      request->send(400);
    }
  });

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html").setCacheControl("max-age=3600");

  server.onNotFound([](AsyncWebServerRequest * request) {
    request->redirect("/");
  });

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");

  server.begin();
}

void loop() {
  dnsServer.processNextRequest();

  digitalWrite(GP0P, GP0S);
  digitalWrite(GP1P, GP1S);

  b1.update();
  if ( b1.changed() ) {  // Call code if button transitions from HIGH to LOW
    IN0S = b1.read();
    if (IN0S == true) {
      events.send("{\"in1\": 1}", "input");
    } else {
      events.send("{\"in1\": 0}", "input");
    }
  }

  b2.update();
  if ( b2.changed() ) {  // Call code if button transitions from HIGH to LOW
    IN1S = b2.read();
    if (IN1S == true) {
      events.send("{\"in2\": 1}", "input");
    } else {
      events.send("{\"in2\": 0}", "input");
    }
  }
  if (timeout1) {
    old1 = millis();
  }
  if (timeout1 && old1 > new1) {
    GP0S = !GP0S;
    timeout1 = false;
    old1 = 0;
    new1 = 0;
    digitalWrite(GP0P, GP0S);
    if (GP0S) {
      events.send("{\"gpio1\": 1}", "output");
    } else {
      events.send("{\"gpio1\": 0}", "output");
    }
  }
  if (timeout2) {
    old2 = millis();
  }
  if (timeout2 && old2 > new2) {
    GP1S = !GP1S;
    timeout2 = false;
    old2 = 0;
    new2 = 0;
    digitalWrite(GP1P, GP1S);
    if (GP1S) {
      events.send("{\"gpio2\": 1}", "output");
    } else {
      events.send("{\"gpio2\": 0}", "output");
    }
  }
}
