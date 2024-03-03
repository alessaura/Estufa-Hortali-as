// Pinos dos componentes
#define MOTOR_PIN 3
#define LED_PIN 4
#define BUZZER_PIN 5
#define TEMPERATURE_PIN A0

void setup() {
  // Inicialização dos pinos como saídas
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Inicialização do monitor serial
  Serial.begin(9600);
}

void loop() {
  // Leitura da temperatura
  int rawValue = analogRead(TEMPERATURE_PIN);

  // Convertendo a leitura analógica para temperatura em graus Celsius
  float voltage = rawValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;

  // Verificação da temperatura
  if (!isnan(temperature)) {
    Serial.print("Temperatura: ");
    Serial.println(temperature);

    // Verificação da temperatura para acionar o motor do ventilador
    if (temperature >= 30) {
      digitalWrite(MOTOR_PIN, HIGH);
    } else {
      digitalWrite(MOTOR_PIN, LOW);
    }

    // Verificação da temperatura para acionar LED e buzina de emergência
    if (temperature > 50) {
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000, 1000); // Frequência de 1000 Hz por 1 segundo
    } else {
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
    }
  }

  // Aguarda um intervalo antes de realizar a próxima leitura
  delay(1000);
}
