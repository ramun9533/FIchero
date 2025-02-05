#include <Adafruit_NeoPixel.h>

// Configuración
#define PIN 6          // Pin donde está conectado el DIN de la matriz
#define NUMPIXELS 64   // Número total de LEDs en la matriz (8x8)
#define WIDTH 8        // Ancho de la matriz
#define HEIGHT 8       // Alto de la matriz

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Definir las letras "H", "O", "L", "A" como arreglos de bytes (8 filas de 8 bits)
const uint8_t letters[4][8] = {
  {0b10000001, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b10000001, 0b10000001}, // H
  {0b01111110, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b10000001, 0b01111110}, // O
  {0b01000000, 0b00000010, 0b01000000, 0b00000010, 0b01000000, 0b00000010, 0b01000000, 0b00111110}, // L
  {0b00111100, 0b01000010, 0b10000001, 0b10000001, 0b11111111, 0b10000001, 0b10000001, 0b10000001}  // A
};

// Colores para cada letra (en formato GRB)
const uint32_t colors[4] = {
  strip.Color(0, 255, 0),   // Verde para H
  strip.Color(255, 0, 0),   // Rojo para O
  strip.Color(0, 0, 255),   // Azul para L
  strip.Color(255, 255, 0)  // Amarillo para A
};

void setup() {
  strip.begin();           // Inicializa la matriz
  strip.setBrightness(32); // Configura el brillo (0-255)
  strip.show();            // Asegúrate de que todos los LEDs estén apagados inicialmente
}

void loop() {
  for (int i = 0; i < 4; i++) {
    drawLetter(letters[i], colors[i]); // Dibuja la letra con su color
    delay(1000);                       // Espera 1 segundo
  }
}

// Dibuja una letra en la matriz
void drawLetter(const uint8_t letter[8], uint32_t color) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int pixelIndex = getPixelIndex(x, y);
      if (bitRead(letter[y], 7 - x)) { // Lee el bit correspondiente (de derecha a izquierda)
        strip.setPixelColor(pixelIndex, color); // Enciende el LED con el color
      } else {
        strip.setPixelColor(pixelIndex, 0);    // Apaga el LED
      }
    }
  }
  strip.show();
}

// Convierte coordenadas X, Y a índice de píxel
int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    return y * WIDTH + x; // Fila par (normal)
  } else {
    return y * WIDTH + (WIDTH - 1 - x); // Fila impar (invertida)
  }
}
