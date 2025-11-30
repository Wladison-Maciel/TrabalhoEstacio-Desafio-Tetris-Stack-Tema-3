#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ===============================
// CONFIGURAÇÕES
// ===============================
#define TAM_FILA 5
#define TAM_PILHA 3

// ===============================
// STRUCT DA PEÇA
// ===============================
typedef struct {
    char nome;  
    int id;     
} Peca;

// ===============================
// VARIÁVEIS GLOBAIS
// ===============================
Peca fila[TAM_FILA];
Peca pilha[TAM_PILHA];

int frente = 0, tras = 0, qtdFila = 0;
int topo = -1;
int ultimoID = 0;

// ===============================
// GERAR PEÇA AUTOMÁTICA
// ===============================
Peca gerarPeca() {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    Peca nova;

    nova.nome = tipos[rand() % 4];
    nova.id = ultimoID++;

    return nova;
}

// ===============================
// FUNÇÕES DE FILA
// ===============================
int filaCheia() { return qtdFila == TAM_FILA; }
int filaVazia() { return qtdFila == 0; }

void enqueue(Peca p) {
    if (filaCheia()) {
        printf("⚠️  ERRO: Fila cheia! (isso nunca deveria acontecer)\n");
        return;
    }

    fila[tras] = p;
    tras = (tras + 1) % TAM_FILA;
    qtdFila++;
}

Peca dequeue() {
    Peca removida;

    if (filaVazia()) {
        printf("\n⚠️  ERRO: Fila está vazia! Não é possível jogar peça.\n");
        removida.nome = '?';
        removida.id = -1;
        return removida;
    }

    removida = fila[frente];
    frente = (frente + 1) % TAM_FILA;
    qtdFila--;

    return removida;
}

// ===============================
// FUNÇÕES DE PILHA
// ===============================
int pilhaCheia() { return topo == TAM_PILHA - 1; }
int pilhaVazia() { return topo == -1; }

void push(Peca p) {
    if (pilhaCheia()) {
        printf("\n⚠️  A pilha está cheia! Não é possível reservar mais peças.\n");
        return;
    }

    pilha[++topo] = p;
    printf("\n📦 Peça [%c %d] reservada com sucesso!\n", p.nome, p.id);
}

Peca pop() {
    Peca removida;

    if (pilhaVazia()) {
        printf("\n⚠️  Não há peças reservadas!\n");
        removida.nome = '?';
        removida.id = -1;
        return removida;
    }

    removida = pilha[topo--];

    printf("\n🔧 Peça usada da reserva: [%c %d]\n", removida.nome, removida.id);
    return removida;
}

// ===============================
// EXIBIÇÃO DA FILA E PILHA
// ===============================
void exibirEstado() {
    printf("\n====================================\n");
    printf("           ESTADO ATUAL\n");
    printf("====================================\n");

    // Fila
    printf("Fila de peças: ");
    if (filaVazia()) {
        printf("(vazia)\n");
    } else {
        int i = frente;
        for (int c = 0; c < qtdFila; c++) {
            printf("[%c %d] ", fila[i].nome, fila[i].id);
            i = (i + 1) % TAM_FILA;
        }
        printf("\n");
    }

    // Pilha
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia()) {
        printf("(vazia)\n");
    } else {
        for (int i = topo; i >= 0; i--) {
            printf("[%c %d] ", pilha[i].nome, pilha[i].id);
        }
        printf("\n");
    }
}

// ===============================
// PROGRAMA PRINCIPAL
// ===============================
int main() {
    srand(time(NULL));

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(gerarPeca());
    }

    int opcao;

    do {
        exibirEstado();

        printf("\n========== MENU ==========\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                // Jogar peça
                if (!filaVazia()) {
                    Peca jogada = dequeue();
                    printf("\n🎮 Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }

                // Sempre gerar nova peça ao final da ação
                enqueue(gerarPeca());
                break;
            }

            case 2: {
                // Reservar peça
                if (!filaVazia()) {
                    Peca reservada = dequeue();
                    push(reservada);
                }

                enqueue(gerarPeca());
                break;
            }

            case 3: {
                // Usar peça reservada
                pop();

                enqueue(gerarPeca());
                break;
            }

            case 0:
                printf("\nEncerrando sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
