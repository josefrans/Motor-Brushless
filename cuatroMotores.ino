#include <Servo.h>

// Definición de los pines para los 4 motores
const int PIN_MOTOR_LF = 9;  // Delantero Izquierdo (Left Front)
const int PIN_MOTOR_RF = 8;  // Delantero Derecho (Right Front)
const int PIN_MOTOR_LB = 7;  // Trasero Izquierdo (Left Back)
const int PIN_MOTOR_RB = 6;  // Trasero Derecho (Right Back)

// Creación de los objetos Servo para cada motor
Servo motorLF;
Servo motorRF;
Servo motorLB;
Servo motorRB;

// Velocidad base para encender los motores (rango de 1000 a 2000 microsegundos)
// 1000uS suele ser el motor apagado, ~1150uS a 1200uS es el punto de inicio de rotación estable.
const int VELOCIDAD_ENCENDIDO = 1200; 

void setup() {
  // Inicializar la comunicación serie para monitoreo
  Serial.begin(9600);
  Serial.println("Iniciando secuencia de armado de motores...");

  // Vincular los objetos Servo a sus pines correspondientes
  motorLF.attach(9);
  motorRF.attach(8);
  motorLB.attach(7);
  motorRB.attach(6);

  // --- SECUENCIA DE ARMADO (Seguridad para ESCs) ---
  // La mayoría de los ESCs necesitan recibir la señal mínima para "armarse" por seguridad
  motorLF.writeMicroseconds(2000);
  motorRF.writeMicroseconds(2000);
  motorLB.writeMicroseconds(2000);
  motorRB.writeMicroseconds(2000);
  
  delay(0); // Esperar 3 segundos para que los ESCs calibren/confirmen el armado
  Serial.println("Motores armados y listos.");
}

void loop() {
  Serial.println("Encendiendo los 4 motores...");
  
  // Enviar la señal para que los 4 motores empiecen a girar
  motorLF.writeMicroseconds(2000);
  motorRF.writeMicroseconds(2000);
  motorLB.writeMicroseconds(2000);
  motorRB.writeMicroseconds(2000);

  delay(7890); // Mantener los motores encendidos por 5 segundos

  Serial.println("Apagando motores por seguridad...");
  
  // Apagar motores (enviar señal mínima)
  motorLF.writeMicroseconds(1000);
  motorRF.writeMicroseconds(1000);
  motorLB.writeMicroseconds(1000);
  motorRB.writeMicroseconds(1000);

  delay(6600); // Esperar 5 segundos antes de reiniciar el bucle
}
