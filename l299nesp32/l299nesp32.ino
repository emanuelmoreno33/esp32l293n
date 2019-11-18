// Motor A
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

// Motor B
int motor2Pin1 = 18; 
int motor2Pin2 = 19; 
int enable2Pin = 21; 

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel1 = 1;
const int resolution = 8;
int dutyCycle = 200;


//bluetooth
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino
BluetoothSerial ESP_BT; //Object for Bluetooth
int incoming;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(pwmChannel1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel1);

  Serial.begin(115200);
  // testing
  Serial.print("Testing DC Motor...");

  ESP_BT.begin("ESP32Carrito"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  
}
int actual =0;
int velocidad = 200;
void loop() {
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive 
    Serial.print("Received:"); Serial.println(incoming);
    
    if(incoming==50)
        {
        actual = 2;
        ESP_BT.println("Atras");
        }
    if (incoming == 49)
        {
        actual = 1;
        ESP_BT.println("Adelante");
        }
        
    if (incoming == 48)
        {
        actual = 0;
        ESP_BT.println("Paro automatico");
        }     
  }
  delay(20);  
direccion(actual,velocidad);
}

void direccion(int dir, int velocidad)
{
  ledcWrite(pwmChannel, velocidad);
  ledcWrite(pwmChannel1, velocidad);
  //adelante
  if (dir == 1)
  {
  Serial.println("Moviendo hacia enfrente");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  }
  else if(dir == 2)
  {
  //atras
  Serial.println("Moviendo hacia atras");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW); 
  }
  else if(dir==0)
  {
  // paro completo
  Serial.println("Motor Detenido");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  }
  }
  
