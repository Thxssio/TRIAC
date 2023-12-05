#define CARGA_R 4

volatile int potencia = 100;

void interrupcao_zero_cross()
{
   // Cálculo do ângulo de disparo: 60Hz-> 8.33ms (1/2 ciclo)
   // (8333us - 8.33us) / 256 = 32 (aproximadamente)
   int tempoPotencia = (32*(256-potencia));
   // Mantém o circuito desligado por tempoPotencia microssegundos
   delayMicroseconds(tempoPotencia);
   // Envia um sinal para o TRIAC para que ele comece a conduzir
   digitalWrite(CARGA_R, HIGH);
   // Aguarda alguns microssegundos para o TRIAC perceber o pulso
   delayMicroseconds(8.33);
   // Desliga o pulso
   digitalWrite(CARGA_R, LOW);
}

void configurar()
{
   Serial.begin(9600);
   pinMode(CARGA_R, OUTPUT);
   // Inicializa a interrupção. O número zero indica a porta 2 do Arduino,
   // interrupcao_zero_cross é a função que será chamada toda vez que o pino 2
   // tiver um valor "RISING" de 0 para 1.
   attachInterrupt(0, interrupcao_zero_cross, RISING);
}

void loop()
{
   // Define a potência em diferentes níveis. Se o sistema estiver conectado a uma lâmpada,
   // isso variará o brilho.
   int niveisPotencia[] = {240, 220, 200, 180, 150, 130, 100};
   int numNiveis = sizeof(niveisPotencia) / sizeof(niveisPotencia[0]);

   for(int i = 0; i < numNiveis; i++)
   {
      potencia = niveisPotencia[i];
      Serial.println(potencia);
      delay(5000);
   }
}
