#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"
#include "desenhos/desenhosABCD.c"
#include "desenhos/carinhas.c"
#include "funcoes/mudar_LED.c"
#include "funcoes/scan_keypad.c"
#include "desenhos/coracao.c"
#include "desenhos/chuva.c"



//vetor para criar imagem na matriz de led - 1
double desenho1[25] =   {0.0, 0.3, 0.3, 0.3, 0.0,
                        0.0, 0.3, 0.0, 0.3, 0.0, 
                        0.0, 0.3, 0.3, 0.3, 0.0,
                        0.0, 0.3, 0.0, 0.3, 0.0,
                        0.0, 0.3, 0.3, 0.3, 0.0};

//vetor para criar imagem na matriz de led - 2
double animacao1[6][25] = {
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.1, 0.1},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
    {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}
};
//função principal
int main()
{
    PIO pio = pio0; 
    uint16_t i;
    bool ok;
    uint32_t valor_led;
    double r,b,g;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();
    //Configurações da PIO
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, OUT_PIN);

    //Inicializar o teclado matricial
    for (int i = 0; i < ROWS; i++) {
        gpio_init(rows[i]);//Inicializa a GPIO das linhas
        gpio_set_dir(rows[i], GPIO_OUT);//Define como saída
        gpio_put(rows[i], 1);  // Mantém as linhas em nível alto
    }
    for (int j = 0; j < COLS; j++) {
        gpio_init(cols[j]);//Inicializa a GPIO das colunas
        gpio_set_dir(cols[j], GPIO_IN);//Define como entrada
        gpio_pull_up(cols[j]);  // Ativa resistor pull-up nas colunas
    }

    while (true) {
        char key = scan_keypad();
        if (key != '\0') {         // Se uma tecla foi pressionada
            printf("A tecla pressionada foi: %c\n", key);
            if(key == 'A'){
               printf("Desligando todos os LEDs\n");
               desenho_pio(desenhoA, valor_led, pio, sm, 0, 0, 0);//Os três últimos argumentos são RGB -(0,0,0)=Desligado
            }
            else if(key == 'B'){
              printf("LEDs azuis 100%% de intencidade\n");
              desenho_pio(desenhoB, valor_led, pio, sm, 0, 0, 1);////Os três últimos termos são RGB -(0,0,1)=Azul
            }
            else if(key == 'C'){
              printf("LEDs vermelhos 80%% de intencidade\n");
              desenho_pio(desenhoC, valor_led, pio, sm, 1, 0, 0);////Os três últimos termos são RGB -(1,0,0)=Vermelho
            }
            else if(key == 'D'){
              printf("LEDs verde 50%% de intencidade\n");
              desenho_pio(desenhoD, valor_led, pio, sm, 0, 1, 0);////Os três últimos termos são RGB:(1,0,0)=Verde
            }
            else if(key == '#'){
              printf("LEDs branco 20%% de intencidade\n");
              desenho_pio(desenho_jgvelha, valor_led, pio, sm, 1, 1, 1);////Os três últimos termos são RGB:(1,1,1)=Branco
            }
            else if(key == '*'){
              printf("HABILITANDO O MODO GRAVAÇÃO");
	          reset_usb_boot(0,0); //habilita o modo de gravação do microcontrolador
            }
            else if(key == '1'){
              printf("Animação 1 rodando");
	      int j = 0;
	      for (j=0;j<6;j++)
	      {
		      desenho_pio(animacao1[j], valor_led, pio, sm, 1, 0, 1);////Os três últimos termos são RGB:(1,0,1)=Roxo
		      sleep_ms(500);
	      }
	    }
            else if(key == '2'){
              printf("Emojis\n");
              
              desenho_pio(emoji1, valor_led, pio, sm, 0, 0, 1);
              sleep_ms(500);
              desenho_pio(emoji2, valor_led, pio, sm, 0, 0, 1);
              sleep_ms(500);
              desenho_pio(emoji3, valor_led, pio, sm, 0, 0, 1);
              sleep_ms(500);
              desenho_pio(emoji4, valor_led, pio, sm, 0, 0, 1);
              sleep_ms(500);
              desenho_pio(emoji5, valor_led, pio, sm, 0, 0, 1);
              sleep_ms(500);
              desenho_pio(emoji6, valor_led, pio, sm, 0, 0, 1);
              sleep_ms(500);
              desenho_pio(emoji7, valor_led, pio, sm, 0, 0, 1);////Os três últimos termos são RGB:(0,0,1)= Azul
            } else if (key == '5'){
              coracao_animacao(pio, sm);

            } else if (key == '6'){
              chuva_animacao(pio, sm);
            }
            else{
              printf("Não foi programado uma ação para esta tecla\n");
            }
            }

        sleep_ms(100);
        }
    
}
