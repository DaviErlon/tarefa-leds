#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include <stdlib.h>

#include "ws2812b.pio.h"

#define ROWS 4
#define COLS 4
#define LED_COUNT 25
#define LED_PIN 7

const uint8_t ROW_PINS[ROWS] = {10,9,8,6}; // R1 R2 R3 R4
const uint8_t COL_PINS[COLS] = {5,4,3,2}; // C1 C2 C3 C4

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
    for(uint8_t i = 0; i < LED_COUNT; i++){
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
void Coracao(PIO pio, uint sm) {
    // Acionando (Brilho aumenta para vermelho)
    for (int16_t r = 0; r <= 255; r++) {
        sleep_ms(10);
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
        print_leds(pio, sm);
    }
    sleep_ms(1000);

    // Esmaecendo (Brilho diminui)
    for (int16_t r = 255; r >= 0; r--) {
        sleep_ms(10);
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
        print_leds(pio, sm);
    }
    sleep_ms(500);

    // Pulso com efeito laranja
    for (int16_t r = 0; r <= 255; r++) {
        sleep_ms(10);
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

        // Lilás nos LEDs internos
        set_led(16, r, 0, r);    
        set_led(18, r, 0, r); 
        set_led(13, r, 0, r);
        set_led(11, r, 0, r);  
        set_led(12, r, 0, r); 
        set_led(7, r, 0, r);
        print_leds(pio, sm);
        
    }

    sleep_ms(500);

    // Acende o coração vermelho
    for (int r = 0; r <= 255; r++) {
        sleep_ms(10);
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
        print_leds(pio, sm);
    }

    sleep_ms(2000);
    clear_leds();
    print_leds(pio, sm);
}

void TodosLEDsAzuis(PIO pio, uint sm) {
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 0, 0, 255); 
    }
    print_leds(pio, sm); 
}
void TodosLEDsVermelhos(PIO pio, uint sm){
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 204, 0, 0); //  80% de 255 igual a 204
    }
    print_leds(pio, sm);
}

void TodosLEDsVerdes(PIO pio, uint sm){
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 0, 127, 0); //  50% de 255 igual a aprox.127
    }
    print_leds(pio, sm);
}

void TodosLEDsBrancos(PIO pio, uint sm){
    for (int led = 0; led <= 24; led++) { 
        set_led(led, 51, 51, 51); //  50% de 255 igual a aprox.127
    }
    print_leds(pio, sm);
}

// função que liga os leds de tal forma que a frase "EU S2 CHURROS" passa deslizando para a esquerda 
void EU_AMO_CHURROS(PIO pio, uint sm){

    clear_leds(); // limpeza do array de leds para que não haja erro
    
    uint64_t dados[5] = {   // Analisando o funcionamento de alguns algoritmos relacionados ao display Oled 
        0x188CD558A57,      // presente na placa BitDogLab, percebi que é muito eficiente guardar informações
        0x5555545F51,       // em bits de inteiros do que dedicar um byte tipado para cada informação booleana.  
        0x94CD5C5F57,       // Esses numeros em hexadecimal na verdade são uma cadeia de bits que por si só já
        0x11555544E51,      // possuem a informação necessária para minha função, o bit[0] de cada um desses números
        0xC954958427        // diz a coluna mais a direita se os leds devem apagar ou ligar.
    };

    for(uint8_t i = 0; i < 51; i++){ 

        sleep_ms(200);

        // Este for desloca todos os dados dos leds uma vez para a esquerda
        for(uint8_t j = 0; j < 4; j++){
            matriz_led[24 - j] = matriz_led[23 - j];
            matriz_led[15 + j] = matriz_led[16 + j];
            matriz_led[14 - j] = matriz_led[13 - j];
            matriz_led[5 + j]  = matriz_led[6 + j] ;
            matriz_led[4 - j]  = matriz_led[3 - j] ; 
        }
        
        // Aqui está a magica, o código verifica o bit[0] de cada um dos hexadecimal e diz "ligado" ou "desligado"
        (dados[0] & 1)? set_led(20, 200,40,10) : set_led (20, 0,0,0);
        (dados[1] & 1)? set_led(19, 200,40,10) : set_led (19, 0,0,0);
        (dados[2] & 1)? set_led(10, 200,40,10) : set_led (10, 0,0,0);
        (dados[3] & 1)? set_led(9, 200,40,10) : set_led (9, 0,0,0);
        (dados[4] & 1)? set_led(0, 200,40,10) : set_led (0, 0,0,0);

        print_leds(pio, sm);

        // por fim, os bit[1] se tornam os bit[0] da vez e retorna o ciclo 
        dados[0] = dados[0] >> 1;
        dados[1] = dados[1] >> 1;
        dados[2] = dados[2] >> 1;
        dados[3] = dados[3] >> 1;
        dados[4] = dados[4] >> 1;
    }

    clear_leds();
}

void smile_face(PIO pio, uint sm) {
    sleep_ms(10);
    // Acende os olhos
    set_led(18, 0, 100, 0); 
    set_led(16, 0, 100, 0); 
    print_leds(pio, sm);
    sleep_ms(500); 
    // Acende o sorriso progressivamente
    int smile[5] = {9, 1, 2, 3, 5};
    for(int i = 0; i < 5; i++) {
        set_led(smile[i], 0, 100, 0);
        print_leds(pio, sm);
        sleep_ms(100); 
    }
    sleep_ms(1000); 
    // Pisca o olho direito
    set_led(18, 0, 0, 0); 
    print_leds(pio, sm);
    sleep_ms(1000); 
    set_led(18, 0, 100, 0); 
    print_leds(pio, sm);
}

void raiwbon_sort(PIO pio, uint sm) {
    uint8_t r_base = 10; // Base de intensidade
    uint8_t g_base = 10;
    uint8_t b_base = 10;

    uint16_t tmp = 0;
    uint16_t Ttmp = 0;

    while (true) {
        if(Ttmp < 3500){
            for (uint i = 0; i <= 24; i++)
            {
                if (i % 2 == 0)
                {
                    uint8_t b = b_base + rand() % 235;
                    uint8_t g= g_base + rand() % 135;
                    uint8_t r = b_base + rand() % 90;
                    set_led(i, r, g, b);
                    print_leds(pio, sm);
                }
                else
                {
                    uint8_t b = b_base + rand() % 120;
                    uint8_t g = g_base + rand() % 180;
                    uint8_t r = b_base + rand() % 240;
                    set_led(i, r, g, b);
                    print_leds(pio, sm);
                }
            }
            tmp = rand() % 255;
            Ttmp += tmp;
            sleep_ms(tmp); // Atras o aleatório para variação do efeito
        }else{
            break;
        }
    }
}
  
// Função de animação Kirby com 8 frames
void Kirby(PIO pio, uint sm) {
    // Definindo os 8 frames da animação Kirby
    uint8_t frames[8][5][5][3] = {
        // Frame 1 (Kirby inicial)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
        },
        // Frame 2 (Kirby lateral)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
        },
        // Frame 3 (Kirby sem perna)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
        },
        // Frame 4 (Kirby com uma perna)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 0, 85}, {255, 0, 85}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}
        },
        // Frame 5 (Kirby semi completo)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 0, 85}, {255, 0, 85}, {0, 0, 0}, {255, 0, 85}, {255, 0, 85}}
        },
        // Frame 6 (olho piscando)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {255, 149, 184}, {234, 165, 188}, {255, 149, 184}, {0, 0, 0}},
            {{255, 0, 85}, {255, 0, 85}, {0, 0, 0}, {255, 0, 85}, {255, 0, 85}}
        },
        // Frame 7 (olho piscando)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {39, 69, 201}, {255, 149, 184}, {39, 69, 201}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 0, 85}, {255, 0, 85}, {0, 0, 0}, {255, 0, 85}, {255, 0, 85}}
        },
        // Frame 8 (final, com LEDs 16 e 18 piscando)
        {
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 149, 184}, {39, 69, 201}, {255, 149, 184}, {39, 69, 201}, {255, 149, 184}},
            {{255, 149, 184}, {0, 0, 0}, {255, 149, 184}, {0, 0, 0}, {255, 149, 184}},
            {{0, 0, 0}, {255, 149, 184}, {255, 149, 184}, {255, 149, 184}, {0, 0, 0}},
            {{255, 0, 85}, {255, 0, 85}, {0, 0, 0}, {255, 0, 85}, {255, 0, 85}}
        }
    };

    // Exibindo os frames da animação Kirby com transição suave
    for (int i = 0; i < 8; i++) {
        // Limpa todos os LEDs antes de desenhar o próximo frame
        clear_leds();

        // Acende os LEDs do frame atual
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                // Inverte a linha para corrigir a posição
                set_led((4 - x) * 5 + y, frames[i][x][y][0], frames[i][x][y][1], frames[i][x][y][2]);
            }
        }

        // Atualiza os LEDs na matriz
        print_leds(pio, sm);

        // Delay para o FPS (10 FPS = 100ms por frame)
        sleep_ms(500);
    }

    // Agora, mantendo os LEDs acesos e piscando apenas os LEDs 16 e 18 3 vezes
    for (int j = 0; j < 3; j++) {
        // Pisca os LEDs 16 e 18
        set_led(16, 39, 69, 201); // LED 16 aceso
        set_led(18, 39, 69, 201); // LED 18 aceso
        print_leds(pio, sm);
        sleep_ms(500); // LEDs acesos por 500ms

        // Apaga os LEDs 16 e 18
        set_led(16, 0, 0, 0); // LED 16 apagado
        set_led(18, 0, 0, 0); // LED 18 apagado
        print_leds(pio, sm);
        sleep_ms(500); // LEDs apagados por 500ms
    }


   // A animação continua visível por 500ms
    sleep_ms(1000);

    // Apaga a animação com efeito suave
    for (int i = 0; i < 5; i++) {
        clear_leds();
        print_leds(pio, sm);
        sleep_ms(100);  // Delay para o efeito suave de apagamento
    }

    // Apaga todos os LEDs no final
    clear_leds();
    print_leds(pio, sm);
}

void contagem_regressiva(PIO pio, uint sm){
    //Esta função realizará a mostragem no painel de leds de uma contagem regressiva de 3 a 1 e depois apresentará
    //a animação representando um creeper

    clear_leds();
    
    int num_3[] = {21,22,23,18,13,12,11,8,3,2,1};
    int num_2[] = {21,22,23,18,13,12,11,6,3,2,1};
    int num_1[] = {16,22,17,12,7,2};
    int creeper[] = {20,21,23,24,15,16,18,19,12,5,6,7,8,9,4,0};

    for(int i=0;i<11;i++){
        set_led(num_3[i],255,0,0);
    }
    print_leds(pio, sm);

    sleep_ms(1000);
    clear_leds();

    for(int i=0;i<11;i++){
        set_led(num_2[i],0,255,0);
    }
    print_leds(pio, sm);
    
    sleep_ms(1000);
    clear_leds();

    for(int i=0;i<6;i++){
        set_led(num_1[i],0,0,255);
    }

    print_leds(pio, sm);
    sleep_ms(1000);
    clear_leds();

    for(int i=0;i<16;i++){
        set_led(creeper[i],255,0,0);
    }
    
    print_leds(pio, sm);
    sleep_ms(1000);
    clear_leds();
}


int main(){

    PIO pio = pio0; 
    bool ok;
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
                    Coracao(pio, sm);
                    break;
                case '1':
                    EU_AMO_CHURROS(pio, sm);
                    break;
                case '2':
                    smile_face(pio, sm);
                    break;
                case '3':
                    raiwbon_sort(pio, sm);
                    break;
                case '4':
                    Kirby(pio, sm);
                    break;
                case '5':
                    contagem_regressiva(pio,sm);
                    break;
                case 'A':
                    clear_leds();
                    print_leds(pio, sm);
                    break;
                case 'B':
                    TodosLEDsAzuis(pio, sm);
                    break;
                case 'C':
                    TodosLEDsVermelhos(pio, sm);
                    break;
                case 'D':
                    TodosLEDsVerdes(pio, sm);
                    break;
                case '#':
                    TodosLEDsBrancos(pio, sm);
                    break;
                case '*':
 
                    break;  
            }
        }
        sleep_ms(20);
    }
}
