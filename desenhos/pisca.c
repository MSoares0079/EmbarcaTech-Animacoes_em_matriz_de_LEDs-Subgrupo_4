// Estrutura que define a cor dos LEDs (RGB)
struct pixel_t {
    uint8_t G, R, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[Nleds];

// Variáveis para controle do PIO e da máquina de estado
PIO np_pio;
uint sm;

// Função para inicializar o controle dos LEDs
void npInit(uint pin) {
    uint offset = pio_add_program(pio0, &ws2818b_program); // Adiciona o programa PIO
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);                // Reserva uma máquina de estado
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f); // Inicializa a PIO

    // Inicializa o buffer de LEDs com todos apagados
    for (uint i = 0; i < Nleds; ++i) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
}

// Função para definir a cor dos LEDs
void cor(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

// Função para desligar os LEDs
void desliga() {
    for (uint i = 0; i < Nleds; ++i) {
        cor(i, 0, 0, 0); // Define todos os LEDs como apagados
    }
}

// Função para enviar os dados do buffer para os LEDs
void buffer() {
    for (uint i = 0; i < Nleds; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G); // verde
        pio_sm_put_blocking(np_pio, sm, leds[i].R); // vermelho
        pio_sm_put_blocking(np_pio, sm, leds[i].B); // azul
    }
    sleep_us(100);
}

// Função com a animação específica
void animacao1() {
    for (int linha = 0; linha < 5; linha++) {
        desliga(); // Apaga todos os LEDs
        for (int i = linha * 5; i < (linha + 1) * 5; i++) {
            cor(i, 255, 255, 0); // Ativa os LEDs R+G (amarelo)
        }
        buffer();
        sleep_ms(800); // Pausa
    }

    for (int j = 0; j < 3; j++) {
        desliga();
        buffer();
        sleep_ms(500); // Pausa
        for (int i = 0; i < 25; i++) {
            cor(i, 0, 0, 255); // Ativa os LEDs B (azul)
        }
        buffer();
        sleep_ms(800); // Pausa
    }
    desliga();
    buffer();
}
