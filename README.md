# Atividade 1 - Semáforo (Unidade 4, Cáp. 5)

## Aluno
Gabriel Neponuceno Batista

## 📺 Demonstração + Instruções de uso

- **Simulação no Wokwi:** [Assista no YouTube](https://www.youtube.com/watch?v=XRLnDJYUwpE&ab_channel=GABRIELNEPONUCENOBATISTA)

## Reposta ao questionamento da atividade:
- **Com o emprego da Ferramenta Educacional BitDogLab, faça
um experimento com o código deste exercício utilizando o LED
RGB – GPIO 12. O que o discente observou no comportamento
da iluminação do referido LED? (15% da nota)**

**R:** Se substituirmos o servomotor por um LED vermelho utilizando esse código, o LED se comportaria de forma variável em termos de brilho, pois a largura do pulso PWM está sendo ajustada dinamicamente.
Como o LED responde à média do sinal PWM, ele pareceria aumentar e diminuir de brilho suavemente.

## Funcionamento
Os requisitos para a realização desta atividade são:

1) Considerando a GPIO 22, defina a sua frequência de PWM para,
aproximadamente, 50Hz – período de 20ms. (20% da nota)

2) Defina o ciclo ativo do módulo PWM para 2.400µs
(microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,12%. isto
ajustará a flange (braço) do servomotor para a posição de,
aproximadamente, 180 graus. Aguarde 05 segundos nesta
posição. (10% da nota)

3) Defina o ciclo ativo do módulo PWM para 1.470µs
(microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,0735%.
Isto ajustará a flange do servomotor para a posição de,
aproximadamente, 90 graus. Aguarde 05 segundos nesta
posição. (10% da nota)

4) Defina o ciclo ativo do módulo PWM para 500µs
(microssegundos) – Ciclo de Trabalho (Duty Cycle) de 0,025%.
Isto ajustará a flange do servomotor para a posição de,
aproximadamente, 0 graus. Aguarde 05 segundos nesta
posição. (10% da nota)

5) Após a realização das proposições anteriores, crie uma rotina
para movimentação periódica do braço do servomotor entre os
ângulos de 0 e 180 graus. Obs.: a movimentação da flange deve
ser suave, recomenda-se o incremento de ciclo ativo de ±5µs,
com um atraso de ajuste de 10ms. (35% da nota)
