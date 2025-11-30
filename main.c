#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------------------------------------
// STRUCT DA PEÇA
// ---------------------------------------------
typedef struct {
    char nome;   // Tipo da peça ('I', 'O', 'T', 'L')
    int id;      // ID único
} Peca;

// ---------------------------------------------
// CONFIGURAÇÕES DA FILA
// ---------------------------------------------
#define TAM_FILA 5

Peca fila[TAM_FILA];
int frente = 0;
int tras = 0;
int qtd = 0;
int ultimoID = 0;

// ---------------------------------------------
// FUNÇÃO PARA GERAR UMA NOVA PEÇA AUTOMATICAMENTE
// ---------------------------------------------
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = ultimoID++;

    return nova;
}

// ---------------------------------------------
// VERIFICA SE A FILA ESTÁ CHEIA
// ---------------------------------------------
int filaCheia() {
    return qtd == TAM_FILA;
}

// ---------------------------------------------
// VERIFICA SE A FILA ESTÁ VAZIA
// ---------------------------------------------
int filaVazia() {
    return qtd == 0;
}

// ---------------------------------------------
// INSERIR NOVA PEÇA (ENQUEUE)
// ---------------------------------------------
void enqueue(Peca p) {
    if (filaCheia()) {
        printf("\n⚠️  A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    qtd++;

    printf("\n➕ Peça [%c %d] inserida com sucesso!\n", p.nome, p.id);
}

// ---------------------------------------------
// REMOVER PEÇA (DEQUEUE)
// ---------------------------------------------
void dequeue() {
    if (filaVazia()) {
        printf("\n⚠️  Não há peças para jogar! A fila está vazia.\n");
        return;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    qtd--;

    printf("\n🎮 Peça jogada: [%c %d]\n", removida.nome, removida.id);
}

// ---------------------------------------------
// EXIBIR FILA ATUAL
// ---------------------------------------------
void exibirFila() {
    printf("\n=====================\n");
    printf("     FILA ATUAL      \n");
    printf("=====================\n");

    if (filaVazia()) {
        printf("A fila está vazia!\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < qtd; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

// ---------------------------------------------
// FUNÇÃO PRINCIPAL
// ---------------------------------------------
int main() {
    srand(time(NULL));

    // Inicializando a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;

    do {
        exibirFila();

        printf("\n======= MENU =======\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("====================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue(gerarPeca());
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
