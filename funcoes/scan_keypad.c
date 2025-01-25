#define ROWS 4  // Número de linhas
#define COLS 4  // Número de colunas

// Define os GPIOs para as linhas e colunas do teclado matricial
uint cols[ROWS] = {22, 26, 27, 28};  // Pinos GPIO das colunas
uint rows[COLS] = {18,19,20,21};  // Pinos GPIO das linhas

// Mapeamento das teclas
char key_map[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função que escaneia o teclado e retorna a tecla pressionada
char scan_keypad() {
    for (int i = 0; i < ROWS; i++) {
        gpio_put(rows[i], 0);  // Coloca a linha em nível baixo
        for (int j = 0; j < COLS; j++) {
            if (gpio_get(cols[j]) == 0) {  // Verifica se a coluna está em nível baixo
                while (gpio_get(cols[j]) == 0);  // Aguarda até a tecla ser solta
                gpio_put(rows[i], 1);  // Restaura a linha para nível alto
                return key_map[i][j];  // Retorna a tecla correspondente
            }
        }
        gpio_put(rows[i], 1);  // Restaura a linha para nível alto
    }
    return '\0';  // Retorna nulo se nenhuma tecla foi pressionada
}