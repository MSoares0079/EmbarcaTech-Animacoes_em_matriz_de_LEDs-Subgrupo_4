# Animações em matriz de LEDs

Este projeto tem como objetivo verificar e testar o funcionamento de uma matriz de LEDs WS2812 em um Raspberry Pi Pico W através de comandos obtidos via um teclado matricial.

# Como baixar e executar o código
    1-Baixar ou utilizar git clone no repositório.
          git clone https://github.com/MSoares0079/EmbarcaTech-Animacoes_em_matriz_de_LEDs-Subgrupo_4.git
    2-Ter o VS Code instalado e devidamente configurado.
    3-Ter a extensão do Raspberry Pi Pico instalada no VS Code.
    4-Compilar o arquivo "pio_matrix.c" utilizando o compilador do Raspberry Pi Pico.
    5-O código pode ser simulado pelo "diagram.json" apartir da extensão Wokwi,
        mas caso deseje utilizar em um Raspberry Pi Pico W, especificamente o disponibilizado pelo EmbarcaTech,
        é necessário ter um teclado matricial nos pinos definidos pelo código.
# Estrutura do código

O código foi desenvolvido para ler a tecla precionada pelo usuário através de um teclado matricial,
no qual resulta em ações diferentes conforme a funcionalidade programada. Essas ações estão relacionadas ao
acionamento da matriz de LEDs, em que foram definidas algumas animações a determinadas teclas.

# Funcionamento
    Foram atribuidas as seguintes funcionalidades para as teclas:
    1- Enchendo
    2- Emoji
    3- Estrela
    4- Coração
    5- Chuva
    6- Movimentação
    7- Círculo
    8- Formas geométricas
    A- Desliga os LEDs
    B- Liga os LEDs azuis com 100% de intensidade
    C- Liga os LEDs vermelhos com 80% de intensidade
    D- Liga os LEDs verdes com 50% de intensidade
    #- Liga os LEDs brancos com 20% de intensidade
    *- Ativa o modo de gravação
# Video demonstrando o funcionamento do código
https://drive.google.com/file/d/1LDBZ3KITXQmIsosHGkvlviRPdzxLnJT2/view?usp=sharing

