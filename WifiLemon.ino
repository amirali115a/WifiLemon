#include <ESP8266WiFi.h>

#define LED_PIN 2              
#define BUZZER_PIN 5           
#define SERIAL_BAUD 115200     
#define CH_TIME 150            
#define PKT_RATE 5             
#define PKT_TIME 1             

const short channels[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

int ch_index = 0;             
int packet_rate = 0;          
int attack_counter = 0;       
unsigned long update_time = 0; 
unsigned long ch_time = 0;    

void sniffer(uint8_t *buf, uint16_t len) {
  if (!buf || len < 28) return;

  byte pkt_type = buf[12];

  if (pkt_type == 0xA0 || pkt_type == 0xC0) {
    packet_rate++;
  }
}

void attack_started() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, HIGH);
  Serial.println("ATTACK DETECTED!");
  Serial.write(0x07);
}

void attack_stopped() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("ATTACK STOPPED!");
  Serial.write(0x07);
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.disconnect();
  wifi_set_opmode(STATION_MODE);
  wifi_set_promiscuous_rx_cb(sniffer);
  wifi_set_channel(channels[0]);
  wifi_promiscuous_enable(true);
  Serial.println("WifiLemon Started ...");
  Serial.println("Started sniffing...");
}

void loop() {
  unsigned long current_time = millis();

  if (current_time - update_time >= (sizeof(channels) * CH_TIME)) {
    update_time = current_time;

    if (packet_rate >= PKT_RATE) {
      attack_counter++;
      if (attack_counter == 1) {
        attack_started();
      }
    } else {
      if (attack_counter >= PKT_TIME) attack_stopped();
      attack_counter = 0;
    }

    Serial.print("Packets/s: ");
    Serial.println(packet_rate);

    packet_rate = 0;
  }

  if (sizeof(channels) > 1 && current_time - ch_time >= CH_TIME) {
    ch_time = current_time;

    ch_index = (ch_index + 1) % (sizeof(channels) / sizeof(channels[0]));
    short ch = channels[ch_index];

    wifi_set_channel(ch);
  }

  if (attack_counter > 0) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
}

