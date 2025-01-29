# Tarefa_Aula_20: Controle de Matriz de LEDs WS2818B com Teclado Matricial 4x4

## Descrição
Este projeto utiliza o microcontrolador **Raspberry Pi Pico** para controlar uma matriz de LEDs endereçáveis **WS2812B** e um teclado matricial 4x4. O teclado permite selecionar diferentes padrões e efeitos de luz que são exibidos nos LEDs. Cada tecla do teclado está associada a uma funcionalidade específica, como acender todos os LEDs em uma cor ou exibir uma animação específica.

## Funcionalidades Principais
- Controle de uma matriz de 25 LEDs WS2812B utilizando **PIO (Programmable I/O)**.
- Entrada interativa por meio de um teclado matricial 4x4 com mapeamento configurável.
- Efeitos de luz, incluindo:
  - Iluminação uniforme nas cores azul, vermelho, verde ou branco.
  - Efeitos com Iluminação oscilante por meio de PWM.
- Limpeza da matriz de LEDs e inicialização para estados personalizados.

## Mapeamento das Teclas
- **'A'**: Desliga todos os LEDs.
- **'B'**: Acende todos os LEDs na cor azul.
- **'C'**: Acende todos os LEDs na cor vermelha.
- **'D'**: Acende todos os LEDs na cor verde.
- **'#'**: Configura todos os LEDs para branco suave.
- Outras teclas, as númericas, serão utilizadas com animações.

## Componentes Utilizados
- **Raspberry Pi Pico W** como microcontrolador principal.
- **Matriz de LEDs WS2812B** (25 LEDs endereçáveis).
- **Teclado matricial 4x4** para controle interativo.

## Tecnologias de Software Utilizadas
- Linguagem: **C** e **Assembly**
- Ferramentas: Kit de desenvolvimento de software SDK e simulador [Wokwi](https://wokwi.com/).

## Como Executar
1. Certifique-se de que você possui o hardware montado conforme o projeto:
   - Raspberry Pi Pico conectado à matriz de LEDs WS2812B.
   - Teclado matricial 4x4 devidamente conectado.
2. Compile o código no Raspberry Pi Pico utilizando o arquivo CMakeLists.
3. Alimente o Raspberry Pi Pico e observe os LEDs reagirem às teclas pressionadas no teclado.

## Demonstração
Assista ao funcionamento do projeto neste [vídeo demonstrativo](https://drive.google.com/file/d/1FgbEsmVrS0p45zUd5166RY3K0_J8ikeR/view?usp=drivesdk).


