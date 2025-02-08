#include <Adafruit_NeoPixel.h>

// Configuración
#define PIN 6          // Pin donde está conectado el DIN de la matriz
#define NUMPIXELS 64   // Número total de LEDs en la matriz (8x8)
#define WIDTH 8        // Ancho de la matriz
#define HEIGHT 8       // Alto de la matriz

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Definición de las letras en formato de 8x8 bits
//     DER        REV          DER         rev          DER         REV        DER         REV
const uint8_t letters[17][8] = {
  {0b00111100, 0b01000010, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b10000001},  // A
  {0b11111000, 0b00100001, 0b10001000, 0b00001111, 0b10001000, 0b00100001, 0b10000100, 0b00011111},  // B
  {0b00111100, 0b01000010, 0b10000000, 0b00000001, 0b10000000, 0b00000001, 0b10000010, 0b00111110},  // C
  {0b11110000, 0b00010001, 0b10000100, 0b00100001, 0b10000100, 0b00100001, 0b10001000, 0b00001111},  // D
  {0b11111111, 0b00000001, 0b10000000, 0b00111111, 0b10000000, 0b00000001, 0b10000000, 0b11111111},  // E
  {0b11111111, 0b00000001, 0b10000000, 0b00111111, 0b10000000, 0b00000001, 0b10000000, 0b00000001},  // F
  {0b00111100, 0b01000010, 0b10000000, 0b00000001, 0b10011110, 0b00100001, 0b10000100, 0b00111110},  // G
  {0b10000001, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b10000001, 0b10000001},  // H
  {0b01111100, 0b00001000, 0b00010000, 0b00001000, 0b00010000, 0b00001000, 0b00010000, 0b00111110},  // I
  {0b00111110, 0b00010000, 0b00001000, 0b00010000, 0b00001000, 0b00010100, 0b00101000, 0b00011000},  // J
  {0b00010001, 0b01001000, 0b00010100, 0b00011000, 0b00011000, 0b00101000, 0b00010010, 0b10001000},  // K
  {0b01000000, 0b00000010, 0b01000000, 0b00000010, 0b01000000, 0b00000010, 0b01000000, 0b00111110},  // L
  {0b11000011, 0b10100101, 0b10011001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001},  // M
  {0b10000001, 0b10000011, 0b10100001, 0b10001001, 0b10001001, 0b10100001, 0b10000011, 0b10000001},  // N
  {0b01010100, 0b00010100, 0b11000001, 0b10000101, 0b10010001, 0b10010001, 0b10000101, 0b11000001},  // Ñ
  {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b01111110},   // O
  {0b11111000, 0b00100001, 0b10001000, 0b00001111, 0b10000000, 0b00000001, 0b10000000, 0b00000001}  // P
};
//     DER        REV          DER         rev          DER         REV        DER         REV
// Colores para cada letra
const uint32_t colors[17] = {
  strip.Color(255, 0, 0),     // Rojo para A
  strip.Color(0, 255, 0),     // Verde para B
  strip.Color(0, 0, 255),     // Azul para C
  strip.Color(255, 255, 0),   // Amarillo para D
  strip.Color(255, 0, 255),   // Magenta para E
  strip.Color(0, 255, 255),   // Cian para F
  strip.Color(255, 165, 0),   // Naranja para G
  strip.Color(128, 0, 128),   // Púrpura para H
  strip.Color(255, 215, 0),   // Dorado para I
  strip.Color(0, 128, 128),   // Verde Azulado para J
  strip.Color(169, 169, 169), // Gris Oscuro para K
  strip.Color(255, 105, 180), // Rosa para L
  strip.Color(75, 0, 130),    // Índigo para M
  strip.Color(255, 140, 0),   // Naranja Oscuro para N
  strip.Color(128, 0, 0),     // Granate para Ñ
  strip.Color(255, 255, 255),  // Blanco para O
  strip.Color(0, 191, 255) // Azul Celeste para P
};


void setup() {
  strip.begin();           
  strip.setBrightness(8); 
  strip.show();            
}

void loop() {
  for (int i = 0; i < 17; i++) { // Cambié a 10 para mostrar todas las letras
    drawLetter(letters[i], colors[i]); 
    delay(2000);  
  }
}

// Dibuja una letra en la matriz
void drawLetter(const uint8_t letter[8], uint32_t color) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int pixelIndex = getPixelIndex(x, y);
      if (bitRead(letter[y], 7 - x)) { 
        strip.setPixelColor(pixelIndex, color);
      } else {
        strip.setPixelColor(pixelIndex, 0); 
      }
    }
  }
  strip.show();
}

// Convierte coordenadas X, Y a índice de píxel
int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    return y * WIDTH + x; 
  } else {
    return y * WIDTH + (WIDTH - 1 - x);
  }
}
