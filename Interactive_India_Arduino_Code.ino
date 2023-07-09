#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 9
#define LED_COUNT 90

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int joy_x = A0;
int joy_y = A1;
int joy_sw = 7;
bool displayed_info = false;

char* states[] = {"Andhra Pradesh", "Arunachal Pradesh", "Assam", "Bihar", "Chhattisgarh", "Gujarat", "Haryana", "Himachal Pradesh", "Jharkhand", "Karnataka", "Kerala", "Madhya Pradesh", "Maharashtra", "Manipur", "Meghalaya", "Mizoram", "Odisha", "Punjab", "Rajasthan", "Sikkim", "Tamil Nadu", "Telangana", "Tripura", "Uttar Pradesh", "Uttarakhand", "West Bengal","Jammu and Kashmir"};
long areas[] = {160205, 83743, 78438, 94163, 135191, 196024, 44212, 55673, 79714, 191791, 38863, 308252, 307713, 22327, 22429, 16579, 155707, 50362, 342239, 7096, 130058, 112077, 10486, 240928, 53483, 88752,222236};
long population[] = {53903393, 1570458, 35607039, 124799926, 29436231, 63872399, 28941133, 7306183, 38593948, 67562686, 35699443, 85358965, 123144223, 3091545, 3366710, 2299724, 46356334, 30141373, 81032689, 690251, 77841267, 39184011, 4169794, 236410968, 11141032, 996093, 12541302};
double literacyRate[] = {67.02, 66.95, 72.19, 63.82, 71.04, 79.31, 76.64, 83.78, 66.41, 75.36, 96.2, 69.32, 82.34, 79.85, 75.48, 80.11, 72.87, 76.68, 67.06, 81.42, 80.33, 66.54, 87.75, 67.68, 79.63,76.2,68.74};
char* stateCapitals[] = {"Amaravati", "Itanagar", "Dispur", "Patna", "Raipur", "Gandhinagar", "Chandigarh", "Shimla", "Ranchi", "Bengaluru", "Thiruvananthapuram", "Bhopal", "Mumbai", "Imphal", "Shillong", "Aizawl", "Bhubaneswar", "Chandigarh", "Jaipur", "Gangtok", "Chennai", "Hyderabad", "Agartala", "Lucknow", "Dehradun", "Kolkata","Srinagar(s),Jammu(w)"};

int state_leds[] = {14,30,28,42,17,55,62,74,45,11,8,51,12,27,36,26,19,63,59,39,5,13,25,80,76,24,70};

int num_states = 27;
int current_state = 0;

void setup() {
  lcd.begin(20, 4);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // Set up the joystick
  pinMode(joy_sw, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Read the joystick values
  int x = analogRead(joy_x);
  int y = analogRead(joy_y);
  int sw = digitalRead(joy_sw);

  Serial.println(sw);

  // Determine the direction of the joystick
  int dir = -1; // -1 for no direction
  if (x < 100) {
    dir = 0; // Left
  } else if (x > 900) {
    dir = 1; // Right
  } else if (y < 100) {
    dir = 2; // Up
  } else if (y > 900) {
    dir = 3; // Down
  }

  // Update the current state based on joystick input
  if (dir == 0) {
    // Move left (wrap around to last state if necessary)
    strip.setPixelColor(state_leds[current_state], strip.Color(0, 0, 0));
    current_state--;
    if (current_state < 0) {
      current_state = num_states - 1;
    }
    displayed_info = false;
    //delay(100)
  } else if (dir == 1) {
    // Move right (wrap around to first state if necessary)
    strip.setPixelColor(state_leds[current_state], strip.Color(0, 0, 0));
    current_state++;
    if (current_state >= num_states) {
      current_state = 0;
    }
    displayed_info = false;
    //delay(100)
  }
  strip.setPixelColor(state_leds[current_state], strip.Color(255, 0, 0));

  
  if (sw == LOW) {
    display_state_info(current_state);
  }else{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(states[current_state]);

  }

  strip.show();
  delay(200);
}

void display_state_info(int current_state) {
lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(stateCapitals[current_state]);
    lcd.setCursor(0, 1);
    lcd.print("Area:");
    lcd.print(areas[current_state]);
    lcd.setCursor(0, 2);
    lcd.print("Population:");
    lcd.print(population[current_state]);
    lcd.setCursor(0, 3);
    lcd.print("Literacy Rate:");
    lcd.print(literacyRate[current_state]);
    displayed_info = true;
    delay(50);

}