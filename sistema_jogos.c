#include <locale.h>  // inclui declarações relacionadas a configuração local
#include <stdio.h>   // necessário para uso da função printf
#include <stdlib.h>  // necessário para uso das funções srand e rand
#include <wchar.h>   // necessário para uso das funções wcscmp e wcscpy
#include <time.h>    // necessário para uso da função time
#include <ctype.h>   // necessário para uso da função tolower
#include <stdbool.h> // necessário para uso do tipo booleano



// função para saber se uma string está num vetor de n strings 
bool seNomeValido(wchar_t nome[], wchar_t lista[][100], int n) {

    // percorre todos os n elementos do vetor lista
    for (int i = 0; i < n; i++) {
        
        // compara se a string nome é igual à string lista[i]
        if (wcscmp(nome, lista[i]) == 0) {
            
        return true;
        }
    }
    return false;
}


// função para posicionamento do cursor na coluna x e na linha y do terminal
void vaParaXY(int x, int y) {

    printf("\033[%d;%dH", y, x);
}

// define uma struct chamada Caixa composta de dois campos
struct Caixa{
    int numeroCaixa; // armazena o int do número da caixa
    char tipoCaixa;  // armazena o char do tipo da caixa
};

// função para imprimir a situação das 2 gousmas possíveis de um jogador
void cenarioGousmasJogador(int matriz[][2], int i) {
    
    // percorre todas as gousmas (ativas ou destruídas) do jogador i
    for (int j = 0; j < 2; j++) {
        
        // verifica se a gousma j do jogador i tem fúria >= 1 e <= 5, ou seja, se está ativa
        if (matriz[i][j] >= 1 && matriz[i][j] <= 5) {
        
            wprintf(L"A gousma (%d) tem fúria = %d.\n", j + 1, matriz[i][j]);
        }
        else {

            wprintf(L"A gousma (%d) está destruída.\n", j + 1);
        }
    }
}

// função para aumentar a fúria de uma gousma do jogador atacado 
// pelo valor da fúria de uma gousma do jogador atacante
void atacarGousma(int *atacante, int *atacado) {
 
    *atacado = *atacado + *atacante;

    // verifica se a fúria da gousma do jogador atacado após o ataque ficou mair do que 5
    if (*atacado > 5) {
        
        *atacado = 0; // estabelece a gousma do jogador atacado como destruída
    }
}

// função para doar fúria = valor de uma gousma para outra do mesmo jogador
void dividirGousma(int *doador, int *recebedor, int valor) {

    *doador = *doador - valor;       // diminui a fúria da gousma doadora em valor
    *recebedor = *recebedor + valor; // aumenta a fúria da gousma recebedora em valor

    // verifica se a fúria da gousma recebedora após o ataque ficou mair do que 5
    if (*recebedor > 5) {

        *recebedor = 0; // estabelece a gousma recebedora como destruída
    }
}


int main(){

    setlocale(LC_ALL, ""); // configura para usar as configurações regionais (locale) 
                           // do sistema operacional (no caso: pt-br).
    srand(time(NULL)); // determina o seed
    
    int qualJogo = 0;

    // se mantém jogando enquanto a opção não for 4
    while (qualJogo != 4) {
        
        // imprime as opções de jogos e de sair
        wprintf(L"\nTÍTULO DO JOGO\n\n"); 
        printf("1: Pergunta e Resposta\n");
        printf("2: Cobra na Caixa!\n");
        printf("3: Gousmas War\n");
        printf("4: Sair\n");
        
        // lê a entrada de int do usuário e a atribui à variável qualJogo 
        scanf("%i", &qualJogo); 

        // entra no jogo Pergunta e Resposta
        if (qualJogo == 1){

            wprintf(L"\nNo Pergunta e Resposta se apresenta uma pergunta com 4 alternativas\n");
            wprintf(L"e se solicita que o usuário escolha a resposta correta. Após a seleção\n");
            wprintf(L"o sistema indicará se a resposta está correta ou incorreta.\n");
            wprintf(L"Caso a resposta seja incorreta, será exibida a resposta correta.\n\n");
            
            // declara e inicializa o vetor de strings de perguntas
            wchar_t perguntas[5][100] = {
                L"Em que ano foi lançado o álbum Kind of Blue, de Miles Davis?",
                L"Em que ano Ozzy Osbourne gravou o primeiro álbum com Randy Rhoads?",
                L"Em que ano ocorreu o primeiro festival de Woodstock?",
                L"Em que ano foi lançado o álbum Nevermind, do Nirvana?",
                L"Qual o ano em que Charlie Parker faleceu?"
            };

            // declara e inicializa o vetor de char de respostas corretas
            char respostas[5] = {
                'a',
                'c',
                'd',
                'c',
                'b'
            };

            // declara e inicializa a matriz de int de alternativas
            int alternativas[5][4] = {
                 {1959, 1970, 1942, 1966},   
                 {1985, 1975, 1980, 1973},    
                 {1970, 1981, 1983, 1969},
                 {1994, 1988, 1991, 1985},
                 {1960, 1955, 1975, 1970}
            };

            // declara o vetor de char de respostas possíveis
            char letrasAlternativas[4] = {
                'a',
                'b',
                'c',
                'd'    
            };

            char alternativaEscolhida; // declara variável char da alternativa digitada pelo usuário

            wchar_t tempPergunta[100]; // declara variável string temporária
            char tempResposta;         // declara variável char temporária
            int tempAlternativas[4];   // declara variável vetor de int temporária
           
            char seContinuaJogandoPR = 's'; // declara e inicializa a flag se continua
                                            // jogando o Pergunta e Resposta: "s" de Sim ou "n" de Não
                        
            // enquanto se deseja continuar jogando o Pergunta e Resposta
            while (seContinuaJogandoPR == 's'){

                // embaralha o vetor perguntas, respostas e alternativas
                for (int i = 4; i > 0; i--) { // i tem valor inicial 4 e final 1
                    
                    int j = rand() % (i + 1); // na 1a iteração atribui a j o resto da divisão de um 
                                              // int aleatório por 5: j = 0, 1, 2, 3 ou 4
                                              // ...
                                              // na 4a iteração atribui a j o resto da divisão de um
                                              // int aleatório por 2: j = 0, ou 1
            
                    // troca a posição entre duas perguntas
                    wcscpy(tempPergunta, perguntas[i]); // aloca perguntas[i] a tempPergunta
                    wcscpy(perguntas[i], perguntas[j]); // aloca perguntas[j] a perguntas[i]
                    wcscpy(perguntas[j], tempPergunta); // aloca tempPergunta a perguntas[j]

                    // troca a posição entre duas respostas
                    tempResposta = respostas[i]; // aloca respostas[i] a tempResposta
                    respostas[i] = respostas[j]; // aloca respostas[j] a respostas[i]
                    respostas[j] = tempResposta; // aloca tempResposta a respostas[j]

                    // troca a posição entre dois conjuntos de alternativas
                    for(int k = 0; k < 4; k++) {
                        tempAlternativas[k] = alternativas[i][k];
                        alternativas[i][k] = alternativas[j][k];
                        alternativas[j][k] = tempAlternativas[k];
                    }
                }              

                // percorre as 5 perguntas
                for (int i = 0; i < 5; i++) {
                    
                    // imprime uma pergunta
                    wprintf(L"%ls\n", perguntas[i]);
                    
                    // percorre as letras alternativas e seu conteúdo de cada pergunta
                    for (int j = 0; j < 4; j++) {
                        
                        // imprime uma letra alternativa e seu conteúdo
                        printf("%c) %d\n", letrasAlternativas[j], alternativas[i][j]);
                    }
                    
                    // valida a entrada do usuário
                    while (1) {
                        // lê a entrada de char do usuário e a atribui à variável alternativaEscolhida
                        scanf(" %c", &alternativaEscolhida);
                        // converte-a para lower case
                        alternativaEscolhida = tolower(alternativaEscolhida);
                        
                        // verifica se a entrada é válida
                        if (alternativaEscolhida == 'a' ||
                            alternativaEscolhida == 'b' ||
                            alternativaEscolhida == 'c' ||
                            alternativaEscolhida == 'd') {
                            
                            break; // sai do laço while
                        }
                        // imprime que a alternativa digitada é inválida
                        wprintf(L"Alternativa inválida. Digite apenas a, b, c ou d:\n");
                    }

                    // verifica e imprime se a alternativa escolhida corresponde ou não à correta
                    if (alternativaEscolhida == respostas[i]) {
                        wprintf(L"A resposta está correta.\n");
                    }
                    else {
                        wprintf(L"A resposta está errada. A resposta correta é a alternativa '%c'.\n", respostas[i]);
                    }

                    printf("\n");
                }

                do {
                    
                    // imprime a pergunta se o usuário deseja continuar jogando o Pergunta e Resposta
                    printf("Quer jogar novamente o Pergunta e Resposta? (s/n)\n");
                    // lê a entrada de char do usuário e a atribui à variável seContinuaJogandoPR
                    scanf(" %c", &seContinuaJogandoPR);
                    // converte-a para lower case
                    seContinuaJogandoPR = tolower(seContinuaJogandoPR);
                
                // continua no laço do-while caso o valor seja diferente de "s" e "n"
                } while (seContinuaJogandoPR != 's' && seContinuaJogandoPR != 'n');
            }
        }
        
        // entra no jogo Cobra na Caixa!
        else if (qualJogo == 2) {

            wprintf(L"\nNo Cobra na Caixa! a história se passa dentro de uma tumba egípcia onde\n");
            wprintf(L"dois exploradores ficaram presos. No centro da sala, há cinco caixas:\n");
            wprintf(L"uma delas contém o botão para abrir a porta, outra esconde uma cobra mortal\n");
            wprintf(L"e as outras três estão vazias. A cada rodada, o local do botão e da cobra\n");
            wprintf(L"mudam de caixa de forma aleatória, aumentando o desafio e a imprevisibilidade do jogo.\n\n");

            // declara e inicializa o vetor de strings de nomes de exploradores
            wchar_t exploradores[7][100] = {
                L"Joplin",
                L"Eller",
                L"Barrett",
                L"Waters",
                L"Gilmour",
                L"Wright",
                L"Mason"
            };
            
            wchar_t jogador[100];      // declara variável string do nome do explorador digitado pelo usuário 
            wchar_t jogadores[2][100]; // declara o vetor de string do nome dos dois exploradores escolhidos
            int indiceJogador;         // declara a variável int do índice do jogador: 0 ou 1

            bool seNomeExploradorValido; // declara variável booleana se o nome de explorador é um dos
                                         // contidos no vetor exploradores

            int indiceQuemComeca; // declara variável int do índice de qual jogador começa

            int limiteEsquerdo; // declara variável int do limite esquerdo do cursor do terminal 
            int limiteDireito;  // declara variável int do limite direito do cursor do terminal
            int limiteSuperior; // declara variável int do limite superior do cursor do terminal
            int limiteInferior; // declara variável int do limite inferior do cursor do terminal

            bool seCobraEncontrada;      // declara variável booleana relativa a se a cobra foi encontrada
            bool seBotaoEncontrado;      // declara variável booleana relativa a se o botão foi encontrado
            char seContinuaJogandoCobra; // declara a flag se continua
                                         // jogando o Cobra na Caixa!: "s" de Sim ou "n" de Não

            struct Caixa caixas[5];      // declara uma variável com 5 duplas do tipo struct Caixa
            char tempTipoCaixa;          // declara variável char temporária

            int tamanhoSala;             // declara variável int da quantidade de caixas da sala
            int escolhaCaixa;            // declara variável int da caixa digitada pelo usuário
            int pos;                     // declara variável int que funciona como índice de caixa e flag
            bool seCaixaJaAbertaAntes;   // declara variável booleana de flag se uma caixa já foi aberta
            
            indiceJogador = 0;           // inicializa o índice do jogador (0 ou 1)

            // continua no laço enquanto os dois jogadores escolhem seu explorador
            while(indiceJogador == 0 || indiceJogador == 1){
                // verifica se é o primeiro explorador a ser escolhido ou não
                if(indiceJogador == 0) {
                    // imprime para um jogador escolher seu explorador
                    printf("Escolha o seu explorador:\n\n");  
                }

                else {
                    // imprime para o outro jogador escolher seu explorador mencionando
                    // o nome do explorador já escolhido
                    wprintf(L"\nEscolha o seu explorador, exceto %ls:\n\n", jogadores[0]);  
                }
                
                // imprime na mesma linha os nomes dos 7 exploradores existentes 
                for (int i = 0; i < 7; i++) {

                    if (i == 0) {

                        wprintf(L"|| %ls || ", exploradores[0]);
                    }
                    else {

                        wprintf(L"%ls || ", exploradores[i]);
                    }
                }

                printf("\n\n");
                
                // lê a entrada de wchar_t do usuário e a atribui à variável jogador
                scanf("%ls", jogador);

                // percorre cada elemento da string jogador exceto o último
                for (int j = 0; jogador[j] != '\0'; j++) {
                    
                    // deixa o elemento da string jogador de índice j como lower case
                    jogador[j] = tolower((unsigned char)jogador[j]);
                }

                // coloca o primeiro caractere da string jogador como upper case
                jogador[0] = toupper((unsigned char)jogador[0]);
                
                // compara se a string jogador corresponde a um dos 7 nomes de exploradores
                // em caso de corresponder a função seNomeValido retorna true e em caso
                // contrário retorna false
                seNomeExploradorValido = seNomeValido(jogador, exploradores, 7);
                
                // verifica se seNomeExploradorValido = false
                if (!seNomeExploradorValido) {
                    // imprime que o nome digitado não corresponde a um dos 7 nomes de exploradores
                    wprintf(L"\nNome de explorador inválido!\n");
                }
                // verifica se:
                // 1. seNomeExploradorValido = true E
                // 2. se se trata do segundo jogador E
                // 3. se o nome digitado corresponde a um nome de explorador já escolhido
                if (seNomeExploradorValido && indiceJogador == 1 && wcscmp(jogador, jogadores[0]) == 0) {
                    // imprime que o nome de explorador já foi escolhido pelo adversário
                    wprintf(L"\nSeu adversário já escolheu esse explorador!\n");
                }
                
                // verifica se seNomeExploradorValido = true
                if (seNomeExploradorValido) {
                    
                    // verifica se:
                    // 1. se se trata do primeiro jogador, OU (EXCLUSIVO)
                    // 2. se se trata do segundo jogador E
                    // 3. se o nome digitado não corresponde a um nome de explorador já escolhido
                    if (indiceJogador == 0 ^ (indiceJogador == 1 && wcscmp(jogador, jogadores[0]) != 0)) {
                        // aloca a string jogador ao vetor de string do nome dos dois exploradores
                        wcscpy(jogadores[indiceJogador], jogador);
                        // incrementa o indiceJogador para 1 no caso de ser verdade antes do OU (EXCLUSIVO)
                        // ou incrementa o indiceJogador para 2 no caso de ser verdade depois do OU (EXCLUSIVO),
                        // gerando a saída do laço while nesse segundo caso
                        indiceJogador++;
                    }
                }
            }
            // imprime o nome dos 2 exploradores válidos escolhidos
            wprintf(L"Um jogador escolheu %ls e o outro escolheu %ls.\n", jogadores[0], jogadores[1]);
            
            // atribui aleatoriamente à variável indiceQuemComeca o indice de qual explorador
            // começa a jogar: 0 ou 1
            indiceQuemComeca = rand() % 2;
            
            // imprime o nome do explorador que começa a jogar
            wprintf(L"\nQuem começa o jogo é %s.\n", jogadores[indiceQuemComeca]);

            // limpa o terminal
            printf("\033[2J");

            limiteEsquerdo = 11;  // estabelece o valor mínimo de coluna    
            limiteDireito = 41;   // estabelece o valor máximo de coluna
            limiteSuperior = 3;   // estabelece o valor mínimo de linha
            limiteInferior = 13;  // estabelece o valor máximo de linha

            // desenha o retângulo da "sala"
            // x varia entre o valor mínimo e o valor máximo de coluna
            for (int x = limiteEsquerdo; x <= limiteDireito; x++) {

                vaParaXY(x, limiteSuperior); // posiciona o cursor na coluna x e no limiteSuperior de linha
                printf("-");                 // imprime "-"
                vaParaXY(x, limiteInferior); // posiciona o cursor na coluna x e no limiteInferior de linha
                printf("-");                 // imprime "-"
            }

            // y varia entre o valor mínimo e o valor máximo de linha
            for (int y = limiteSuperior; y <= limiteInferior; y++) {

                vaParaXY(limiteEsquerdo, y); // posiciona o cursor na coluna y e no limiteEsquerdo de coluna
                printf("|");               // imprime "|"
                vaParaXY(limiteDireito, y);  // posiciona o cursor na coluna y e no limiteDireito de coluna
                printf("|");               // imprime "|"
            }

            // desenha cinco "portas"
            vaParaXY(25, 4);   printf("[1]"); // topo
            vaParaXY(37, 8);  printf("[2]");  // direita superior
            vaParaXY(31, 12);  printf("[3]"); // direita inferior
            vaParaXY(19, 12);  printf("[4]"); // esquerda inferior
            vaParaXY(13, 8);  printf("[5]");  // esquerda superior

            // posiciona o cursor abaixo da sala
            vaParaXY(1, limiteInferior + 2);

            seCobraEncontrada = false;    // inicializa a variável booleana relativa a se a cobra foi encontrada
            seBotaoEncontrado = false;    // inicializa a variável booleana relativa a se o botão foi encontrada
            seContinuaJogandoCobra = 's'; // inicializa a flag se continua
                                          // jogando o Pergunta e Resposta: "s" de Sim ou "n" de Não
            
            // enquanto se deseja continuar jogando o Cobra na Caixa!
            while (seContinuaJogandoCobra == 's'){
                
                // inicializa os 2 campos da 5 caixas definindo que uma contém a cobra ("c"),
                // que uma contém o botão ("b"), e que 3 estão vazias ("v")
                caixas[0].numeroCaixa = 1;
                caixas[0].tipoCaixa = 'v';
                caixas[1].numeroCaixa = 2;
                caixas[1].tipoCaixa = 'c';
                caixas[2].numeroCaixa = 3;
                caixas[2].tipoCaixa = 'v';
                caixas[3].numeroCaixa = 4;
                caixas[3].tipoCaixa = 'b';
                caixas[4].numeroCaixa = 5;
                caixas[4].tipoCaixa = 'v';

                // embaralha o vetor de caixas
                for (int i = 4; i > 0; i--) { // i tem valor inicial 4 e final 1
                    
                    int j = rand() % (i + 1); // na 1a iteração atribui a j o resto da divisão de um 
                                              // int aleatório por 5: j = 0, 1, 2, 3 ou 4
                                              // ...
                                              // na 4a iteração atribui a j o resto da divisão de um
                                              // int aleatório por 2: j = 0, ou 1
                
                    // aloca a uma caixa um tipo ("c", "b" ou "v") de outra caixa e vice-versa 
                    tempTipoCaixa = caixas[i].tipoCaixa;       // aloca caixas[i] a tempTipoCaixa
                    caixas[i].tipoCaixa = caixas[j].tipoCaixa; // aloca caixas[j] a caixas[i]
                    caixas[j].tipoCaixa = tempTipoCaixa;       // aloca tempTipoCaixa a caixas[j]
                }

                tamanhoSala = 5; // inicializa a quantidade inicial de caixas da sala

                // enquanto a cobra OU (EXLCUSIVO) o botão não são encontrados continua jogando
                while (!(seCobraEncontrada ^ seBotaoEncontrado)){
                    
                    // itera sobre cada um dos 2 jogadores
                    for (int i = 0; i < 2; i++) {

                        do {
                            // imprime para um jogador escolher uma caixa
                            wprintf(L"%ls escolha uma caixa:\n", jogadores[i]);
                            
                            do {
                                // lê a entrada de int do usuário e a atribui à variável escolhaCaixa
                                scanf("%d", &escolhaCaixa);
                                
                                // verifica se o valor de escolhaCaixa é um número de caixa inválido
                                if (escolhaCaixa < 1 || escolhaCaixa > 5) {
                                    // imprime que o valor não é válido
                                    wprintf(L"Valor inválido! Escolha um valor válido:\n");
                                }
                            // continua no laço do-while caso o valor de escolhaCaixa for inválido
                            } while (escolhaCaixa < 1 || escolhaCaixa > 5);

                            pos = -1; // inicializa o índice de caixa que também funciona como flag
                            
                            // percorre todas as caixas ainda não abertas da sala
                            for (int j = 0; j < tamanhoSala; j++) {
                                
                                // verifica se a caixa ainda está fechada
                                if (caixas[j].numeroCaixa == escolhaCaixa) {

                                    pos = j; // atribui a variável pos o índice da caixa escolhida
                                    break;   // sai do laço for
                                }
                            }
                            
                            // verifica se foi escolhida uma caixa fechada
                            if (pos != -1) {
                                
                                // verifica se a caixa escolhida contém a cobra
                                if (caixas[pos].tipoCaixa == 'c') {
                                    
                                    // imprime que o explorador em questão perdeu
                                    wprintf(L"%ls você perdeu, pois escolheu a caixa com cobra!\n\n", jogadores[i]);
                                    seCobraEncontrada = true; // declara a cobra encontrada como verdadeiro
                                    break; // sai do laço do-while, pois o jogo acabou
                                }
                                // verifica se a caixa escolhida contém o botão
                                else if (caixas[pos].tipoCaixa == 'b') {
                                    
                                    // imprime que o explorador em questão ganhou
                                    wprintf(L"%ls você ganhou, pois escolheu a caixa com botão!\n\n", jogadores[i]);
                                    seBotaoEncontrado = true; // declara o botão encontrado como verdadeiro
                                    break; // sai do laço do-while, pois o jogo acabou
                                }
                                // verifica se a caixa escolhida está vazia
                                else if (caixas[pos].tipoCaixa == 'v') {
                                    
                                    // imprime que o explorador em questão não ganhou nem perdeu
                                    wprintf(L"%ls você escolheu uma caixa vazia.\n\n", jogadores[i]);

                                    // percorre cada caixa entre o índice pos e a penúltima considerando
                                    // a quantidade de caixas atual da sala
                                    for (int k = pos; k < tamanhoSala - 1; k++) {
                                        
                                        // da a uma caixa anterior os valores de numeroCaixa e tipoCaixa
                                        // da caixa seguinte, fazendo com que penúltima caixa tenha 
                                        // os mesmos valores de numeroCaixa e tipoCaixa da última caixa
                                        caixas[k] = caixas[k + 1];
                                    }
                                    // atualiza a quantidade de caixas atual reduzindo essa quantidade em 1
                                    tamanhoSala--;
                                }
                                // define que uma caixa nova foi aberta por um explorador 
                                seCaixaJaAbertaAntes = false;
                            }
                            else {
                                // imprime que a caixa já estava aberta
                                wprintf(L"A caixa %d já foi aberta.\n\n", escolhaCaixa);
                                // define que nenhuma caixa nova foi aberta por um explorador
                                seCaixaJaAbertaAntes = true;
                            }
                        // permanece no laço do-while enquanto uma caixa nova não é aberta por um explorador
                        } while (seCaixaJaAbertaAntes);
                         
                        // verifica se o jogo acabou com o encontro da caixa com cobra OU (EXCLUSIVO)
                        // da caixa com botão
                        if (seCobraEncontrada ^ seBotaoEncontrado) {
                            
                            break; // sai do laço for, e devido a uma única das duas condições do if serem
                                   // verdadeiras sai do laço while em seguida
                        }
                    }
                }

                do {

                    // imprime a pergunta se o usuário deseja continuar jogando o Cobra na Caixa!
                    printf("Quer jogar novamente o Cobra na Caixa? (s/n)\n");
                    // lê a entrada de char do usuário e a atribui à variável seContinuaJogandoCobra
                    scanf(" %c", &seContinuaJogandoCobra);
                    // converte-a para lower case
                    seContinuaJogandoCobra = tolower(seContinuaJogandoCobra);
                
                // continua no laço do-while caso o valor seja diferente de "s" e "n"
                } while (seContinuaJogandoCobra != 's' && seContinuaJogandoCobra != 'n');
                
                // verifica se a opção do usuário foi de continuar jogando o Cobra na Caixa!
                if (seContinuaJogandoCobra == 's') {

                    seCobraEncontrada = false; // estabelece como falso que a cobra já foi encontrada
                    seBotaoEncontrado = false; // estabelece como falso que o botão já foi encontrado
                }
            }    
        }

        // entra no jogo Gousmas War
        else if (qualJogo == 3) {

            wprintf(L"\nNo Gousmas War os jogadores controlam criaturas chamadas Gousmas, que \n");
            wprintf(L"podem se dividir e aumentar fúria ao serem atacadas. Cada jogador inicia\n");
            wprintf(L"com duas Gousmas, cada uma com nível de fúria 1. Quando uma Gousma ataca\n");
            wprintf(L"outra, adiciona todo o seu nível de fúria para a Gousma atacada.\n");
                        
            char seContinuaJogandoGousmas = 's'; // declara e inicializa a flag se continua
                                                 // jogando o Gousmas War: "s" de Sim ou "n" de Não

            // permanece se deseja continuar jogando o Gousmas War
            while (seContinuaJogandoGousmas == 's'){

                // declara e inicializa matriz de int que cada um dos 2 jogadores 
                // possui 2 gousmas com fúria = 1 cada uma
                int gousmas[2][2] = {
                    {1, 1}, // jogador 1 com 2 gousmas cada uma com fúria 1
                    {1, 1}  // jogador 2 com 2 gousmas cada uma com fúria 1
                };

                // declara e inicializa vetor de 2 strings dos labels dos jogadores
                wchar_t gousmers[2][100] = {
                    L"Jogador 1",
                    L"Jogador 2"
                };

                wchar_t tipoAcao[100]; // declara variável string do tipo de ação digitada pelo usuário
                
                // declara e inicializa variável int do total de gousmas destruídas do jogador atacado
                int totalGousmasDestruidasJogadorAtacado = -1; 

                bool seAcaoValida; // declara variável booleana relativa a se a ação pretendida
                                   // pelo jogador é válida

                bool seGousmaAtacanteValida; // declara variável booleana relativa a se o jogador
                                             // atacante escolheu gousma ativa
                int gousmaAtacante;          // declara variável int da gousma escolhida pelo jogador
                                             // atacante para a ação de "atacar"

                bool seGousmaAtacadoValida; // declara variável booleana relativa a se o jogador
                                            // atacante escolheu gousma ativa do jogador atacado
                int gousmaAtacado;          // declara variável int da gousma do jogador atacado
                                            // escolhida pelo atacante como alvo

                bool seGousmaDoadoraValida; // declara variável booleana relativa a se a gousma 
                                            // escolhida como doadora pelo jogador é válida
                int gousmaDoadora;          // declara variável int da gousma do jogador
                                            // escolhida como doadora

                int gousmaRecebedora; // declara variável int se a gousma recebedora da doação
                                      // se trata da gousma (1) ou da gousma (2) do jogador

                bool seDoacaoValida; // declara variável booleana relativa a se a doação é válida
                int valorADoar;      // declara variável int da quantidade de fúria a doar

                // enquanto o total de gousmas destruídas do jogador atacado é menor que 2
                while (totalGousmasDestruidasJogadorAtacado < 2) {

                    // percorre cada um dos dois jogadores
                    for (int i = 1; i >= 0; i--) {

                        // verifica se ambas as gousmas do jogador de índice i - 1
                        // tem fúria menor ou igual a 1 (destruída ou ativa não doadora)
                        if (gousmas[1 - i][0] <= 1 && gousmas[1 - i][1] <= 1) {
                            
                            // imprime que o jogador consegue apenas atacar                        
                            wprintf(L"\n%ls você consegue apenas atacar.\n\n", gousmers[1 - i]);
                            // cópia a string "atacar" para a variável string tipoAcao
                            wcscpy(tipoAcao, L"atacar");

                        }
                        // em caso contrário (se tiver alguma gousma do jogador com fúria > 1)
                        else {

                            seAcaoValida = false; // inicializa a variável booleana relativa 
                                                  // a se a ação pretendida pelo jogador é válida

                            // enquanto o contrário de seAcaoValida for true
                            while (!seAcaoValida) {

                                // imprime com a pergunta se o jogador deseja atacar ou dividir
                                wprintf(L"\n%ls você deseja 'atacar' ou 'dividir'?\n", gousmers[1 - i]);
                                // lê a entrada de string do usuário e a atribui à variável tipoAcao
                                scanf("%ls", tipoAcao);
                                
                                // percorre cada elemento da string tipoAcao exceto o último
                                for (int j = 0; tipoAcao[j] != '\0'; j++) {
                                
                                    // deixa o elemento da string tipoAcao de índice j como lower case
                                    tipoAcao[j] = tolower((unsigned char)tipoAcao[j]);
                                }
                                
                                // verifica se a string passada pelo usuário é igual a:
                                // 1. "atacar"; OU (EXCLUSIVO)
                                // 2. "dividir"
                                if ((wcscmp(L"atacar", tipoAcao) == 0) ^ (wcscmp(L"dividir", tipoAcao) == 0)) {
                                    // coloca o boolenano seAcaoValida como true e sai do laço while
                                    seAcaoValida = true;    
                                }
                                // em caso contrário
                                else {
                                    
                                    // imprime que a escolha do usuário não foi válida e não sai do laço while
                                    wprintf(L"\nEscolha uma ação válida!\n");
                                }
                            }
                        }          
                        // verifica se a ação digitada pelo usuário foi "atacar"
                        if (wcscmp(L"atacar", tipoAcao) == 0) {
                            
                            // imprime para o jogador atacante selecionar a gousma ativa (fúria >= 1) com
                            // a qual deseja atacar
                            wprintf(L"Selecione a gousma ativa com a qual deseja atacar:\n");

                            // imprime a situação das 2 gousmas possíveis do jogador atacante
                            cenarioGousmasJogador(gousmas, 1 - i);

                            
                            seGousmaAtacanteValida = false; // inicializa variável booleana relativa a se 
                                                            // o jogador atacante escolheu gousma ativa 
                            
                            // enquanto o contrário de seGousmaAtacanteValida for true
                            while (!seGousmaAtacanteValida) {

                                // lê a entrada de int do usuário e a atribui à variável gousmaAtacante
                                scanf("%d", &gousmaAtacante);
                                
                                // verifica se:
                                // 1. gousmaAtacante corresponde a 1 ou 2; E
                                // 2. a fúria da gousma de índice gousmaAtacante - 1 do jogador atacante
                                // é maior ou igual a 1
                                if ((gousmaAtacante == 1 || gousmaAtacante == 2) 
                                && gousmas[1 - i][gousmaAtacante - 1] >= 1) {
                                    // coloca o boolenano seGousmaAtacanteValida como true e sai do laço while
                                    seGousmaAtacanteValida = true;
                                }
                                else {
                                    // imprime que o jogador atacante escolha gousma ativa
                                    // e com fúria, e não sai do laço while
                                    wprintf(L"Escolha uma gousma ativa e que tenha fúria!\n");
                                }
                            }
                            // imprime que o jogador atacante selecione a gousma do jogador atacado
                            // que esteja ativa
                            wprintf(L"Selecione a gousma ativa do %ls que é alvo da sua gousma (%d):\n", gousmers[i], gousmaAtacante);
                            
                            // imprime a situação das 2 gousmas possíveis do jogador atacado
                            cenarioGousmasJogador(gousmas, i);

                            seGousmaAtacadoValida = false; // inicializa variável booleana relativa a se o jogador
                                                           // atacante escolheu gousma ativa do jogador atacado 
                            
                            // enquanto o contrário de seGousmaAtacadoValida for true
                            while (!seGousmaAtacadoValida) {

                                // lê a entrada de int do usuário e a atribui à variável gousmaAtacado
                                scanf("%d", &gousmaAtacado);
                                
                                // verifica se:
                                // 1. gousmaAtacado corresponde a 1 ou 2; E
                                // 2. a fúria da gousma de índice gousmaAtacado - 1 do jogador atacado
                                // é maior ou igual a 1
                                if ((gousmaAtacado == 1 || gousmaAtacado == 2) 
                                && gousmas[i][gousmaAtacado - 1] >= 1) {
                                    // coloca o boolenano seGousmaAtacadoValida como true e sai do laço while
                                    seGousmaAtacadoValida = true;
                                }
                                else {
                                    // imprime que o jogador atacante escolha gousma ativa
                                    // e com fúria do jogador atacado, e não sai do laço while
                                    wprintf(L"Escolha uma gousma ativa!\n");
                                    seGousmaAtacadoValida = false;
                                }
                            }

                            // imprime o detalhamento do ataque jogador atacante ao jogador atacado
                            wprintf(L"A gousma (%d) do %ls ataca com fúria = %d a gousma (%d) do %ls.\n", 
                                gousmaAtacante, 
                                gousmers[1 - i], 
                                gousmas[1 - i][gousmaAtacante - 1], 
                                gousmaAtacado, 
                                gousmers[i]);

                            // executa o ataque
                            atacarGousma(&gousmas[1 - i][gousmaAtacante - 1], &gousmas[i][gousmaAtacado - 1]);

                            // coloca como 0 o total de gosumas destruídas do jogador atacado
                            totalGousmasDestruidasJogadorAtacado = 0;

                            // perceore cada uma das 2 gousmas possíveis do jogador atacado
                            for (int j = 0; j < 2; j++) {

                                // verifica se a gousma de índice j está destruída
                                if (gousmas[i][j] == 0) {
                                    // incrementa totalGousmasDestruidasJogadorAtacado de 1
                                    totalGousmasDestruidasJogadorAtacado++;
                                }
                            }
                            
                            // imprime a situação do Jogador 1 e do Jogador 2 após o ataque 
                            wprintf(L"\n----------Situação após ataque----------\n");

                            wprintf(L"Jogador 1:\n");
                            cenarioGousmasJogador(gousmas, 0);

                            wprintf(L"Jogador 2:\n");
                            cenarioGousmasJogador(gousmas, 1);

                            wprintf(L"----------------------------------------\n");
                            
                            // verifica que o total de gousmas detruídas do jogador atacado é igual a 2
                            if (totalGousmasDestruidasJogadorAtacado == 2) {
                                // imprime que o jogador atacante venceu
                                wprintf(L"\nO %ls venceu!\n\n", gousmers[1 - i]);
                                break; // sai do laço for, e devido a totalGousmasDestruidasJogadorAtacado = 2
                                       // sai do laço while em seguida
                            }
                        }
                        // em caso contrário (ação "dividir")
                        else {
                            
                            // imprime para o jogador selecionar a gousma ativa (fúria >= 1)
                            // para distribuir fúria
                            wprintf(L"Escolha uma gousma ativa para distribuir fúria?\n");

                            // imprime a situação das 2 gousmas possíveis do jogador
                            cenarioGousmasJogador(gousmas, 1 - i);

                            seGousmaDoadoraValida = false; // inicializa variável booleana relativa a se 
                                                           // a gousma escolhida como doadora pelo jogador
                                                           // é válida
                            
                            // enquanto o contrário de seGousmaDoadoraValida for true
                            while (!seGousmaDoadoraValida) {

                                // lê a entrada de int do usuário e a atribui à variável gousmaDoadora
                                scanf("%d", &gousmaDoadora);
                                
                                // verifica se:
                                // 1. gousmaDoadora corresponde a 1 ou 2; E
                                // 2. a fúria da gousma de índice gousmaDoadora - 1 do jogador
                                // é maior ou igual a 1  
                                if ((gousmaDoadora == 1 || gousmaDoadora == 2) 
                                && gousmas[1 - i][gousmaDoadora - 1] > 1) {
                                    // coloca o boolenano seGousmaDoadoraValida como true e sai do laço while
                                    seGousmaDoadoraValida = true;
                                }
                                else {
                                    
                                    // imprime que o jogador escolha gousma ativa e com fúria,
                                    // e não sai do laço while
                                    wprintf(L"Escolha uma gousma ativa e com fúria maior que 1!\n");
                                }
                            }
                            
                            // calcula que a gousma recebedora da doação é a outra gousma do jogador
                            gousmaRecebedora = 3 - gousmaDoadora;

                            seDoacaoValida = false; // inicializa variável booleana relativa a se
                                                    // a doação é válida

                            // imprime a pergunta ao jogador de quanto ele deseja distribuir da
                            // de sua gousma (gousmaDoadora)
                            wprintf(L"%ls quanto você deseja distribuir da gousma (%d)?\n", gousmers[1 - i], gousmaDoadora);
                            
                            // enquanto o contrário de seDoacaoValida for true
                            while (!seDoacaoValida) {
                                
                                // lê a entrada de int do usuário e a atribui à variável gousmaDoadora
                                scanf("%d", &valorADoar);
                                // verifica se:
                                // 1. a fúria da gousma doadora após a doação será ao menos 1; E
                                // 2. o valor a doar é ao menos 1
                                if ((gousmas[1 - i][gousmaDoadora - 1] - valorADoar >= 1) && valorADoar >= 1) {
                                    
                                    // coloca o boolenano seDoacaoValida como true e sai do laço while
                                    seDoacaoValida = true;
                                }
                                else {
                                    
                                    // imprime que o jogador distribua um valor válido,
                                    // e não sai do laço while
                                    wprintf(L"Distribua um valor válido:\n");
                                    seDoacaoValida = false;
                                }
                            }

                            // verifica se a gousma que receberá a doação está destruída
                            if (gousmas[1 - i][gousmaRecebedora - 1] == 0) {
                                // imprime o detalhamento da doação
                                wprintf(L"A gousma (%d) do %ls foi revivida com a doação de %d fúria(s) da gousma (%d).\n", 
                                gousmaRecebedora, 
                                gousmers[1 - i], 
                                valorADoar, 
                                gousmaDoadora);
                            }
                            // em caso contrário (a gousma recebedora está ativa)
                            else {

                                // imprime o detalhamento da doação
                                wprintf(L"A gousma (%d) do %ls recebeu a doação de %d fúria(s) da gousma (%d).\n", 
                                gousmaRecebedora, 
                                gousmers[1 - i], 
                                valorADoar, 
                                gousmaDoadora);

                            }
                            
                            // executa a divisão
                            dividirGousma(&gousmas[1 - i][gousmaDoadora - 1], &gousmas[1 - i][gousmaRecebedora - 1], valorADoar);

                             // imprime a situação do Jogador 1 e do Jogador 2 após a divisão 
                            wprintf(L"\n----------Situação após divisão----------\n");

                            wprintf(L"\nJogador 1:\n");
                            cenarioGousmasJogador(gousmas, 0);

                            wprintf(L"\nJogador 2:\n");
                            cenarioGousmasJogador(gousmas, 1);

                            wprintf(L"\n-----------------------------------\n");
                        }
                    }
                }

                do {
                    // imprime a pergunta se o usuário deseja continuar jogando o Gousmas War
                    printf("Quer jogar novamente o Gousmas War? (s/n)\n");

                    // lê a entrada de char do usuário e a atribui à variável seContinuaJogandoGousmas
                    scanf(" %c", &seContinuaJogandoGousmas);
                    
                    // converte-a para lower case
                    seContinuaJogandoGousmas = tolower(seContinuaJogandoGousmas);
                
                // continua no laço do-while caso o valor seja diferente de "s" e "n"
                } while (seContinuaJogandoGousmas != 's' && seContinuaJogandoGousmas != 'n');
            }
        }
        // verifica se o usuário não escolheu nenhum dos três jogos nem a opção de sair
        else if (qualJogo != 1 && qualJogo != 2 && qualJogo != 3 && qualJogo != 4) {
            
            // imprime que o usuário escolha uma opção válida
            wprintf(L"Opção inválida! Escolha novamente:\n");
        }
    }

    // imprime que se terminou de jogar
    printf("\nFim!\n");    
        
    return 0;    
       
}