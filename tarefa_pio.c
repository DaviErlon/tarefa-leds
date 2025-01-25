#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "ws2812b.pio.h"

#define ROWS 4
#define COLS 4
#define LED_COUNT 25
#define LED_PIN 7

const uint8_t ROW_PINS[ROWS] = {8, 9, 6, 5}; // R1 R2 R3 R4
const uint8_t COL_PINS[COLS] = {4, 3, 2, 27}; // C1 C2 C3 C4

// Mapeamento do teclado matricial
const char KEY_MAP[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Inicialização da GPIOs utilizadas pelo KeyPad
void keypad_init() {
    for (int i = 0; i < ROWS; i++) {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_OUT);
        gpio_put(ROW_PINS[i], 0);
    }
    for (int i = 0; i < COLS; i++) {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_IN);
        gpio_pull_down(COL_PINS[i]);
    }
}

// Leitura do Keypad
char read_keypad() {
    for (int row = 0; row < ROWS; row++) {
        gpio_put(ROW_PINS[row], 1);

        for (int col = 0; col < COLS; col++) {
            if (gpio_get(COL_PINS[col])) {
                gpio_put(ROW_PINS[row], 0);
                sleep_ms(20);
                return KEY_MAP[row][col];
            }
        }
        gpio_put(ROW_PINS[row], 0);
    }
    return '\0';
}

// Estrutura com os dados de cor e luminozidade para um led
typedef struct{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} led;

// Array que armazena os dados dos 25 leds
led matriz_led[LED_COUNT]; 

// Função que junta 3 bytes com informações de cores e mais 1 byte vazio para temporização
uint32_t valor_rgb(uint8_t B, uint8_t R, uint8_t G){
  return (G << 24) | (R << 16) | (B << 8);
}

// Função que configura um led específico
void set_led(uint8_t indice, uint8_t r, uint8_t g, uint8_t b){
    if(indice < 25){
    matriz_led[indice].R = r;
    matriz_led[indice].G = g;
    matriz_led[indice].B = b;
    }
}

// Função de limpar o array de leds
void clear_leds(){
    for(uint8_t i = 0; i > LED_COUNT; i++){
        matriz_led[i].R = 0;
        matriz_led[i].B = 0;
        matriz_led[i].G = 0;
    }
}

// Função que envia os dados do array para os leds via PIO
void print_leds(PIO pio, uint sm){
    uint32_t valor;
    for(uint8_t i = 0; i < LED_COUNT; i++){
        valor = valor_rgb(matriz_led[i].B, matriz_led[i].R,matriz_led[i].G);
        pio_sm_put_blocking(pio, sm, valor);
    }
}

// Efeito_1: Coração pulsante
void Coracao() {
    // Acionando (Brilho aumenta para vermelho)
    for (int r = 0; r <= 255; r++) {
        sleep_ms(3);
        set_led(23, r, 0, 0);  
        set_led(21, r, 0, 0); 
        set_led(19, r, 0, 0);
        set_led(17, r, 0, 0);
        set_led(15, r, 0, 0);    
        set_led(14, r, 0, 0); 
        set_led(10, r, 0, 0);
        set_led(6, r, 0, 0);  
        set_led(8, r, 0, 0); 
        set_led(2, r, 0, 0);
        print_leds();
    }
    sleep_ms(1000);

    // Esmaecendo (Brilho diminui)
    for (int r = 255; r >= 0; r--) {
        sleep_ms(3);
        set_led(23, r, 0, 0);  
        set_led(21, r, 0, 0); 
        set_led(19, r, 0, 0);
        set_led(17, r, 0, 0);
        set_led(15, r, 0, 0);    
        set_led(14, r, 0, 0); 
        set_led(10, r, 0, 0);
        set_led(6, r, 0, 0);  
        set_led(8, r, 0, 0); 
        set_led(2, r, 0, 0);
        print_leds();
    }
    sleep_ms(500);

    // Pulso com efeito laranja
    for (int r = 0, g = 0; r <= 235; r++, g += 2) {
        sleep_ms(3);
        // Vermelho principal
        set_led(23, r, 0, 0);  
        set_led(21, r, 0, 0); 
        set_led(19, r, 0, 0);
        set_led(17, r, 0, 0);
        set_led(15, r, 0, 0);    
        set_led(14, r, 0, 0); 
        set_led(10, r, 0, 0);
        set_led(6, r, 0, 0);  
        set_led(8, r, 0, 0); 
        set_led(2, r, 0, 0);

        // Laranja nos LEDs internos
        set_led(16, r, g, 0);    
        set_led(18, r, g, 0); 
        set_led(13, r, g, 0);
        set_led(11, r, g, 0);  
        set_led(12, r, g, 0); 
        set_led(7, r, g, 0);
        print_leds();
        
    }

    // Acende o coração vermelho
    for (int r = 0; r <= 255; r++) {
        sleep_ms(3);
        set_led(23, r, 0, 0);  
        set_led(21, r, 0, 0); 
        set_led(19, r, 0, 0);
        set_led(17, r, 0, 0);
        set_led(15, r, 0, 0);    
        set_led(14, r, 0, 0); 
        set_led(10, r, 0, 0);
        set_led(6, r, 0, 0);  
        set_led(8, r, 0, 0); 
        set_led(2, r, 0, 0);
        set_led(16, r, 0, 0);    
        set_led(18, r, 0, 0); 
        set_led(13, r, 0, 0);
        set_led(11, r, 0, 0);  
        set_led(12, r, 0, 0); 
        set_led(7, r, 0, 0);
        print_leds();
    }

    sleep_ms(2000);
    clear_leds();
    print_leds();
}

/*
  ATENÇÃO: PARTE DESTINADA AS FUNÇÕES DOS CARACTERES E OUTRAS TAGs
==================================================================================================================================
*/

void TodosLEDsAzuis() {
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 0, 0, 255); 
    }
    print_leds(); 
}
void TodosLEDsVermelhos(){
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 204, 0, 0); //  80% de 255 igual a 204
    }
    print_leds();
}

void TodosLEDsVerdes(){
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 0, 127, 0); //  50% de 255 igual a aprox.127
    }
    print_leds();
}

void TodosLEDsBrancos(){
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 51, 51, 51); //  50% de 255 igual a aprox.127
    }
    print_leds();
}

int main(){

    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;
    ok = set_sys_clock_khz(128000, false);

    // Inicializações básicas

    stdio_init_all();
    keypad_init();

    //configurações da PIO
    uint offset = pio_add_program(pio, &ws2812b_program);
    uint sm = pio_claim_unused_sm(pio, true);
    ws2812b_program_init(pio, sm, offset, LED_PIN);


    while (true) {
        char key = read_keypad();

        if (key != '\0') {
            switch (key) {
                case '0':

                    break;
                case '1':

                    break;
                case '2':

                    break;
                case 'A':

                    break;
                case 'B':

                    break;
                case 'C':

                    break;
                case 'D':
  
                    break;
                case '#':

                    break;
                case '*':
 
                    break;  
            }
        }
        sleep_ms(20);
    }
}
