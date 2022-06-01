
//Inclui a biblioteca wifi
#include <WiFi.h>

//Avisa que sera uma constante que não mudara de valor
const char* ssid     = "Nome da sua rede wifi";
const char* password = "senha";

//Porta a ser conectado
WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // Pino de saida

    delay(10);

    // Codigo para conexão do wifi

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi conectando....");
    Serial.println("Endereço de IP: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

//valor recebe 0 de inicio
int value = 0;

void loop(){
 WiFiClient client = server.available();   // lista quantos clientes tem conectado

  if (client) {                             // se houver cliente conectado,
    Serial.println("Novo Cliente.");           // Mostra o endereço do cliente
    String currentLine = "";                // Esta string recebe os dados do cliente
    while (client.connected()) {            // Enquanto o cliente estiver conectado
      if (client.available()) {             // se houver atividade do cliente,
        char c = client.read();             // Salva os bytes do cliente
        Serial.write(c);                    // escreve no monitor
        if (c == '\n') {                    // pula a linha para um novo caracter

          // se a linha for == 0, faz a inicalização do servidor http.
          // Se o cliente fizer alguma requisição
          if (currentLine.length() == 0) {
            // verifica se o dado é 0, e começa o codigo (e.g. HTTP/1.1 200 OK)
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html"); //Tipo de texto a ser escrito
            client.println();

            // Comandos em html a serem exibidos:
            client.print("<!DOCTYPE html>");
            client.print("<html lang=\"pt-br\">");
            client.print("<head>");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta http-equiv=\"X-UA-Compatible\" content=\"/IE=edge\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.print("<title>Automação IoT</title>");
            client.print("<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@4.4.1/dist/css/bootstrap.min.css\" integrity=\"sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh\" crossorigin=\"anonymous\">");
            client.print("</head>");
            client.print("<body class=\"bg-secondary h-100\">");
            client.print("<div class=\"container bg-dark border rounded mt-3 border-white\">");
            client.print("<div class=\"text-center text-white\">");
            client.print("<h1>Controle de Automação IoT</h1>");
            client.print("</div>");
            client.print("</div>");
            client.print("<div class=\"container\">");
            client.print("<div class=\"row justify-content-center\">");
            client.print("<a href=\"/H\" class=\"/col-md-5 m-1 col-sm-10 bg-success p-5 text-white text-center rounded border-white\">");
            client.print("<strong>Liga</strong>");
            client.print("</a>");
            client.print("<a href=\"/L\" class=\"/col-md-5 m-1 col-sm-10 bg-danger p-5 text-white text-center rounded border-w\">");
            client.print("<strong>Desliga</strong> ");
            client.print("</a>");
            client.print("</div>");
            client.print("</div>");
            client.print("<footer class=\"footer navbar-fixed-bottom \">");
            client.print("<div class= \"container text-center text-white\">");
            client.print("<p><strong><i>Desenvolvido por Cesar Reis</i></strong></p> ");
            client.print("</div>");
            client.print("</footer>");
            client.print("</body>");
            client.print("</html>");
          
            
            // se houver respostra, faz o fim do servidor:
            client.println();
            // break out of the while loop:
            break;
          } else {    // se houver uma nova linha:
            currentLine = "";
          }
        } else if (c != '\r') {  //se a linha for diferente de r, adiciona +1 linha,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Vai receber ou liga ou desliga:
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(5, HIGH);               // recebe H de HIGH/liga
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(5, LOW);                // recebe L de LOW/desliga
        }
      }
    }
    // fecha a conexão
    client.stop();
    Serial.println("Cliente Desconectado da IOT.");
  }
}
