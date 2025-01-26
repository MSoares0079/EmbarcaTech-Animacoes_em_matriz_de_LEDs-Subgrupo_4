#include <stdlib.h>
#include "hardware/pio.h"
 

// Função para criar a animação de chuva
void chuva_animacao(PIO pio, uint sm) {
    uint32_t valor_led;
    double chuva[25] = {0.0};

    for (int iteracao = 0; iteracao < 20; iteracao++) { // Repetir a animação 20 vezes
        // Limpa a matriz
        for (int i = 0; i < 25; i++) {
            chuva[i] = 0.0;
        }

        // Gera novas gotas aleatórias no topo
        for (int col = 0; col < 5; col++) {
            if (rand() % 2 == 0) { 
                chuva[col] = 1.0; 
            }
        }

        // Anima a descida das gotas
        for (int linha = 0; linha < 5; linha++) {

            for (int i = 24; i >= 5; i--) {
                chuva[i] = chuva[i - 5];
            }

            for (int col = 0; col < 5; col++) {
                chuva[col] = 0.0;
            }

            desenho_pio(chuva, valor_led, pio, sm, 0, 0, 1); // RGB Azul
            sleep_ms(300); 
        }
    }
}
