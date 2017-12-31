/* * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * *
 * *     *   COMANDOS   *                * *
 * *     * * * * * * * * *               * *
 * *                                     * *
 * *     W -> Frente                     * *
 * *     S -> Trás                       * *
 * *     A -> Esquerda                   * *
 * *     D -> Direita                    * *
 * *     Q -> Giro anti-horário          * *
 * *     E -> Giro horário               * *
 * *     X -> Parar                      * *
 * *     B -> Buzinar                    * *
 * *     P -> Piscar                     * *
 * *     Z -> Ligar/Desligar farois      * *
 * *                                     * *
 * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * *
 */ 

#include <SoftwareSerial.h>       // Biblioteca que simula pinos digitais como pinos de comunicação TX e RX

#define MotorA1 4                 // Motor da Direita
#define MotorA2 5                 // Motor da Direita
#define MotorB1 6                 // Motor da Esquerda
#define MotorB2 7                 // Motor da Esquerda
 
int t;                            // Váriavel que guarda o delay ( atraso )

SoftwareSerial bluetooth(10,11);  // Instanciamento da classe SoftwareSerial no objeto Bluetooth

String comando;                   // String que irá recolher os comandos enviados (pode ser via SoftwareSerial(No nosso caso o bluetooth) ou via COM)

void frente(int t){               // Função que movimenta o carrinho para a frente ( Acelerar )
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,HIGH);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,HIGH);
  bluetooth.println("FRENTE");    // Imprime para os canais de comunicação do Bluetooth a informação que o Arduino recebeu
  Serial.println("FRENTE");       // Imprime para os canais de comunicação do COM a informação que o Arduino recebeu
  delay(t);                       // Pequeno atraso para evitar erros
}
void direita(int t){              // Função que movimenta o carrinho para a direita
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,HIGH);
  bluetooth.println("DIREITA");   // Imprime para os canais de comunicação do Bluetooth a informação que o Arduino recebeu
  Serial.println("DIREITA");      // Imprime para os canais de comunicação do COM a informação que o Arduino recebeu
  delay(t);                       // Pequeno atraso para evitar erros
}
void esquerda(int t){             // Função que movimenta o carrinho para a esquerda
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,HIGH);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,LOW);
  bluetooth.println("ESQUERDA");  // Imprime para os canais de comunicação do Bluetooth a informação que o Arduino recebeu
  Serial.println("ESQUERDA");     // Imprime para os canais de comunicação do COM a informação que o Arduino recebeu
  delay(t);                       // Pequeno atraso para evitar erros
}
void tras(int t){                 // Função que movimenta o carrinho para a trás ( RÉ )
  digitalWrite(MotorA1,255);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,HIGH);
  digitalWrite(MotorB2,LOW);
  bluetooth.println("RÉ");        // Imprime para os canais de comunicação do Bluetooth a informação que o Arduino recebeu
  Serial.println("RÉ");           // Imprime para os canais de comunicação do COM a informação que o Arduino recebeu
  delay(t);                       // Pequeno atraso para evitar erros
}
 
void parar(int t){
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,LOW);
  bluetooth.println("PARAR");
  Serial.println("PARAR");
  delay(t);
}

void girod(int t){
  digitalWrite(MotorA1,HIGH);
  digitalWrite(MotorA2,LOW);
  digitalWrite(MotorB1,LOW);
  digitalWrite(MotorB2,HIGH);
  bluetooth.println("HORARIO");
  Serial.println("HORARIO");
  delay(t);
}

void giroe(int t){
  digitalWrite(MotorA1,LOW);
  digitalWrite(MotorA2,HIGH);
  digitalWrite(MotorB1,HIGH);
  digitalWrite(MotorB2,LOW);
  bluetooth.println("ANTI-HORARIO");
  Serial.println("ANTI-HORARIO");
  delay(t);
}

void buzinar(){

  bluetooth.println("BUZINANDO");
  Serial.println("BUZINANDO");
}

void piscar(){
  t = 5;
  while (t>=0){
    digitalWrite(3,!digitalRead(3));
    t--;
  }
  bluetooth.println("PISCAR");
  Serial.println("PISCAR");
}

void farol(){

  bluetooth.println("PISCAR");
  Serial.println("PISCAR");
}

void conex(){                                         // Função que faz a leitura dos comando enviados para o Arduino

  comando = "";                                       // Definindo a string comando como vazia

  if(Serial.available()){                             // Caso o bluetooth esteja disponivel (Available, em inglês) o código será desviado para esse bloco 
    
    while(Serial.available()){                        // Enquanto ele estiver disponível...
      
      char c = Serial.read();                         // A váriavel c vai ler o que for digitado
      comando += c;                                   // A váriavel comando vai recebendo letra por letra o que foi enviado
      delay(10);                                      // Pequeno atraso para evitar falhas
    }
    bluetooth.print("Comando: ");                     // Mostra o que o Arduino recebeu
    bluetooth.println(comando);                       // Imprime o que foi enviado

    Serial.print("Comando: ");                        // Mostra na tela o comando que o Arduino leu
    Serial.println(comando);                          // Imprime no Monitor Serial o comando enviado
    
    char cx = comando.indexOf("x");                    // Verifica se na váriavel comando existe a letra X, que tem a função de PARAR
    int cw = comando.indexOf("w");                    // Verifica se na váriavel comando existe a letra X, que tem a função de IR PARA A FRENTE ( ACELERAR )
    int ca = comando.indexOf("a");                    // Verifica se na váriavel comando existe a letra X, que tem a função de IR PARA A ESQUERDA
    int cs = comando.indexOf("s");                    // Verifica se na váriavel comando existe a letra X, que tem a função de IR PARA TRÁS ( RÉ )
    int cd = comando.indexOf("d");                    // Verifica se na váriavel comando existe a letra X, que tem a função de IR PARA A DIREITA
    int cq = comando.indexOf("q");                    // Verifica se na váriavel comando existe a letra X, que tem a função de GIRAR NO SENTIDO ANTI-HORÁRIO
    int ce = comando.indexOf("e");                    // Verifica se na váriavel comando existe a letra X, que tem a função de GIRAR NO SENTIDO HORÁRIO
    int cz = comando.indexOf("z");                    // Verifica se na váriavel comando existe a letra X, que tem a função de LIGAR/DESLIGAR os leds
    int cb = comando.indexOf("b");                    // Verifica se na váriavel comando existe a letra X, que tem a função de BUZINAR
    int cp = comando.indexOf("p");                    // Verifica se na váriavel comando existe a letra X, que tem a função de PISCAR os leds
    
        if(cw >= 0){
          frente(1000);                                  // O carrinho tem que acelerar
        }
        if(ca >= 0){
          esquerda(1000);                                // O carrinho tem que dobrar para a esquerda
        }
        if(cd >= 0){
          direita(1000);                                 // O carrinho tem que dobrar para a direita
        }
        if(cs >= 0){
          tras(1000);                                    // O carrinho tem que dá ré
        }
        if(cx >= 0){
          parar(1000);                                   // O carrinho tem que parar
        }
        if(cb >= 0){
          buzinar();                                  // A buzina deve ser acionada
        }
        if(cq >= 0){
          giroe(1000);                                   // O carrinho tem que girar no sentido anti-horário
        }
        if(ce >= 0){
          girod(1000);                                   // O carrinho tem que girar no sentido horário
        }
        if(cp >= 0){
          piscar();                                   // Os leds devem piscar
        }
        if(cz >= 0){
          farol();                                    // Os leds devem ser acessos
        }
     }
  }

void setup(){
  
  //OUTPUT = SAÍDA
  
  pinMode(MotorA1,OUTPUT);                          // Define a porta 4 (MotorA1) como saída
  pinMode(MotorA2,OUTPUT);                          // Define a porta 5 (MotorA2) como saída
  pinMode(MotorB1,OUTPUT);                          // Define a porta 6 (MotorB1) como saída
  pinMode(MotorB2,OUTPUT);                          // Define a porta 7 (MotorB2) como saída
  bluetooth.begin(9600);                            // Inicializa a porta de comunicação bluetooth (SoftwareSerial) para o prosseguimento do programa
  Serial.begin(9600);                               // Inicializa a porta Serial (COM), para casos de testes e/ou atualizações
  pinMode(3, OUTPUT);                               // Led de teste ligado na porta digital 3
  
}
void loop() {
  
conex();                                     // Chama a função conex, que fica sendo executada várias vezes, até ser interrompida pelo usuário, ou por exceções.
  
}
