#include <stdio.h> 
#include "pico/stdlib.h" 
#include "hardware/pwm.h"
#include "hardware/irq.h" 

#define SERVO_PIN 22  // Define o pino GPIO 22 para controle do servomotor

volatile uint pulse_width_us = 500; // Variável global que armazena a largura do pulso PWM
volatile bool increasing = true;    // Flag que indica a direção do movimento do servo

// Função para configurar o PWM no pino desejado
uint pwm_setup(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM); // Configura o pino como saída PWM
    uint sliceNum = pwm_gpio_to_slice_num(gpio); // Obtém o número do slice PWM correspondente ao pino
    pwm_config config = pwm_get_default_config(); // Obtém a configuração padrão do PWM
    pwm_config_set_clkdiv(&config, 125.0f); // Define o divisor de clock para ajustar a frequência do PWM
    pwm_config_set_wrap(&config, 20000);   // Define o valor de wrap para um período de 20ms (50Hz)
    pwm_init(sliceNum, &config, true); // Inicializa o PWM com as configurações definidas
    return sliceNum; // Retorna o número do slice PWM configurado
}
// Função para definir o ângulo do servo ajustando a largura do pulso PWM
void set_servo_angle(uint gpio, uint pulse_width) {
    uint level = (pulse_width * 20000) / 20000; // Calcula o nível PWM baseado no tempo de pulso
    pwm_set_gpio_level(gpio, level); // Aplica o valor calculado ao PWM
}


// Rotina de interrupção para movimentação suave do servo
void pwm_irq_handler() {
    pwm_clear_irq(pwm_gpio_to_slice_num(SERVO_PIN)); // Limpa a interrupção do PWM
    
    if (increasing) { // Se estiver aumentando o ângulo do servo
        pulse_width_us += 5; // Incrementa a largura do pulso
        if (pulse_width_us >= 2400) { // Se atingir 180° (máximo permitido)
            pulse_width_us = 2400; // Mantém no limite superior
            increasing = false; // Inverte a direção para diminuir
        }
    } else { // Se estiver diminuindo o ângulo do servo
        pulse_width_us -= 5; // Decrementa a largura do pulso
        if (pulse_width_us <= 500) { // Se atingir 0° (mínimo permitido)
            pulse_width_us = 500; // Mantém no limite inferior
            increasing = true; // Inverte a direção para aumentar
        }
    }
    
    set_servo_angle(SERVO_PIN, pulse_width_us); // Aplica a nova largura de pulso ao servo
}

int main() {
    stdio_init_all(); // Inicializa a entrada e saída padrão
    uint servo_slice = pwm_setup(SERVO_PIN); // Configura o PWM no pino do servo  
    // Posiciona o servo em 180° e acende o LED
    set_servo_angle(SERVO_PIN, 2400);
    sleep_ms(5000); // Aguarda 5 segundos
    
    // Posiciona o servo em 90° e apaga o LED
    set_servo_angle(SERVO_PIN, 1470);
    sleep_ms(5000); // Aguarda 5 segundos
    
    // Posiciona o servo em 0° e acende o LED
    set_servo_angle(SERVO_PIN, 500);
    sleep_ms(5000); // Aguarda 5 segundos
    
    // Configuração da interrupção do PWM para movimentação suave do servo
    pwm_clear_irq(servo_slice); // Limpa a flag de interrupção do PWM
    pwm_set_irq_enabled(servo_slice, true); // Habilita a interrupção do PWM
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_irq_handler); // Configura a rotina de interrupção
    irq_set_enabled(PWM_IRQ_WRAP, true); // Habilita a interrupção no controlador de IRQ
    
    while (1) {
        tight_loop_contents(); // Mantém o loop principal ativo sem bloquear a CPU
    }
}
