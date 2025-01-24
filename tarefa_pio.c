#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "ws2812b.pio.h"

#define LED_COUNT 25
#define LED_PIN 7

typedef struct{
    uint8_t R;
    uint8_t G;
    uint8_t B;
} led;

led matriz_led[LED_COUNT];

uint32_t valor_rgb(uint8_t B, uint8_t R, uint8_t G){
  return (G << 24) | (R << 16) | (B << 8);
}

void set_led(uint8_t indice, uint8_t r, uint8_t g, uint8_t b){
    if(indice < 25){
    matriz_led[indice].R = r;
    matriz_led[indice].G = g;
    matriz_led[indice].B = b;
    }
}

void clear_leds(){
    for(uint8_t i = 0; i > LED_COUNT; i++){
        matriz_led[i].R = 0;
        matriz_led[i].B = 0;
        matriz_led[i].G = 0;
    }
}

void print_leds(PIO pio, uint sm){
    uint32_t valor;
    for(uint8_t i = 0; i < LED_COUNT; i++){
        valor = valor_rgb(matriz_led[i].B, matriz_led[i].G,matriz_led[i].R);
        pio_sm_put_blocking(pio, sm, valor);
    }
}

int main(){

    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;
    ok = set_sys_clock_khz(128000, false);

    //

    stdio_init_all();

    //configurações da PIO
    uint offset = pio_add_program(pio, &ws2812b_program);
    uint sm = pio_claim_unused_sm(pio, true);
    ws2812b_program_init(pio, sm, offset, LED_PIN);

    clear_leds();

    set_led(3, 100, 100, 100);
    
    print_leds(pio, sm);

    while (true) {
        sleep_ms(100);
    }
}
