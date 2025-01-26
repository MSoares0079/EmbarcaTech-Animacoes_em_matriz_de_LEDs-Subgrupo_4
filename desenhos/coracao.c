#include "hardware/pio.h"

double coracao[2][25] = {
    // Quadro 1: Coração preenchido
    {0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
     1.0, 1.0, 1.0, 1.0, 1.0,
     0.0, 1.0, 1.0, 1.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0},

    // Quadro 2: Coração contorno
    {0.0, 1.0, 0.0, 1.0, 0.0,
     1.0, 0.0, 0.0, 0.0, 1.0,
     1.0, 0.0, 0.0, 0.0, 1.0,
     0.0, 1.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0}
};


void coracao_animacao(PIO pio, uint sm) {
    uint32_t valor_led;
    int num_frames = 2;

    for (int i = 0; i < 10; i++) { // Repetir a animação 10 vezes
        for (int j = 0; j < num_frames; j++) {
            desenho_pio(coracao[j], valor_led, pio, sm, 1, 0, 0); // RGB Vermelho
            sleep_ms(500);
        }
    }
}