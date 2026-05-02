#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

// ===============================
// PIN AUDIO
// ===============================
const int AUDIO_PIN = 14;   // GPIO14 = D5 su NodeMCU/Wemos

// ===============================
// CONFIG LETTURA
// ===============================
const int NUM_SAMPLES = 20;
const int READ_DELAY_MS = 80;

// Da regolare dopo aver visto il grafico
int rawMin = -500;
int rawMax = 500;

// Frequenza audio
int freqMin = 120;
int freqMax = 1200;

// Filtro per stabilizzare il segnale
float filteredRaw = 0;
float filterAmount = 0.90;

// ===============================
// SETUP
// ===============================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(D2, D1); // SDA = D2, SCL = D1

  if (!ads.begin()) {
    Serial.println("ADS1115 non trovato");
    while (1) {
      delay(1000);
    }
  }

  ads.setGain(GAIN_SIXTEEN); // più sensibile: +/-0.256V

  pinMode(AUDIO_PIN, OUTPUT);

  delay(500);

  // Intestazione per Serial Plotter
  Serial.println("raw\tfiltered\tfrequency");
}

// ===============================
// LOOP
// ===============================
void loop() {
  long sum = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    int16_t raw = ads.readADC_Differential_0_1();
    sum += raw;
    delay(2);
  }

  int rawAvg = sum / NUM_SAMPLES;

  filteredRaw = (filterAmount * filteredRaw) + ((1.0 - filterAmount) * rawAvg);
  int cleanRaw = (int)filteredRaw;

  int frequency = map(cleanRaw, rawMin, rawMax, freqMin, freqMax);
  frequency = constrain(frequency, freqMin, freqMax);

  tone(AUDIO_PIN, frequency);

  // Formato perfetto per il Serial Plotter
  Serial.print(rawAvg);
  Serial.print("\t");
  Serial.print(cleanRaw);
  Serial.print("\t");
  Serial.println(frequency);

  delay(READ_DELAY_MS);
}
