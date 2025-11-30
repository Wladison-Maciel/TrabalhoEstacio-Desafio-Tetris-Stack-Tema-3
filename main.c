#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// -----------------------------
// STRUCT DA PEÇA
// -----------------------------
typedef struct {
    char tipo;  // I, O, T, L
    int id;     // identificador único
} Peca;

// -----------------------------
// VARIÁVEIS GLOBAIS
// -----------------------------
Peca fila[TAM_FILA];
int ini = 0, fim = 0, qtd = 0;

Peca pilha[TAM_PILHA];
int topo = -1;

int proxID = 0;  // controla IDs únicos

// -----------------------------
// Função para gerar uma nova peça
// -----------------------------
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = proxID++;
    return p;
}

// -----------------------------
// Operações da fila circular
// -----------------------------
int filaCheia() { return qtd == TAM_FILA; }
int filaVazia() { return qtd == 0; }

void enfileirar(Peca p) {
    if (!filaCheia()) {
        fila[fim] = p;
        fim = (fim + 1) % TAM_FILA;
        qtd++;
    }
}

Peca desenfileirar() {
    Peca removida = fila[ini];
    ini = (ini + 1) % TAM_FILA;
    qtd--;
    return removida;
}

// -----------------------------
// Operações da pilha
// -----------------------------
int pilhaCheia() { return topo == TAM_PILHA - 1; }
int pilhaVazia() { return topo == -1; }

void push(Peca p) {
    if (!pilhaCheia()) {
        pilha[++topo] = p;
    }
}

Peca pop() {
    return pilha[topo--];
}

// -----------------------------
// Exibir estado atual
// -----------------------------
void exibirEstado() {
    int i;

    printf("\n================== ESTADO ATUAL ==================\n");

    printf("Fila de peças: ");
    int idx = ini;
    for (i = 0; i < qtd; i++) {
        printf("[%c %d] ", fila[idx].tipo, fila[idx].id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha de reserva (Topo -> Base): ");
    for (i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].tipo, pilha[i].id);
    }
    printf("\n==================================================\n");
}

// -----------------------------
// Trocar peça da fila com peça da pilha
// -----------------------------
void trocarSimples() {
    if (filaVazia() || pilhaVazia()) {
        printf("\nNão é possível trocar. Fila ou pilha vazia.\n");
        return;
    }

    Peca temp = fila[ini];
    fila[ini] = pilha[topo];
    pilha[topo] = temp;

    printf("\nTroca simples realizada!\n");
}

// -----------------------------
// Troca múltipla (3 peças)
// -----------------------------
void trocarMultipla() {
    if (qtd < 3 || topo < 2) {
        printf("\nNão é possível fazer troca múltipla. Estruturas insuficientes.\n");
        return;
    }

    int i;
    int idxFila = ini;

    for (i = 0; i < 3; i++) {
        Peca temp = fila[idxFila];
        fila[idxFila] = pilha[topo - i];
        pilha[topo - i] = temp;

        idxFila = (idxFila + 1) % TAM_FILA;
    }

    printf("\nTroca múltipla concluída (3 peças)!\n");
}

// -----------------------------
// Programa principal
// -----------------------------
int main() {
    srand(time(NULL));

    // Preencher fila inicial
    while (!filaCheia()) {
        enfileirar(gerarPeca());
    }

    int op;

    do {
        exibirEstado();

        printf("\nOpções:\n");
        printf("1 - Jogar peça da fila\n");
        printf("2 - Reservar peça (fila -> pilha)\n");
        printf("3 - Usar peça da pilha\n");
        printf("4 - Trocar peça da fila com pilha\n");
        printf("5 - Troca múltipla (3 peças)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {

            case 1:  // Jogar peça
                if (!filaVazia()) {
                    desenfileirar();
                    enfileirar(gerarPeca());
                    printf("\nPeça jogada!\n");
                }
                break;

            case 2:  // Reservar peça
                if (!filaVazia() && !pilhaCheia()) {
                    push(desenfileirar());
                    enfileirar(gerarPeca());
                    printf("\nPeça reservada!\n");
                } else {
                    printf("\nNão foi possível reservar.\n");
                }
                break;

            case 3:  // Usar da pilha
                if (!pilhaVazia()) {
                    pop();
                    printf("\nPeça usada da reserva!\n");
                } else {
                    printf("\nPilha vazia.\n");
                }
                break;

            case 4:
                trocarSimples();
                break;

            case 5:
                trocarMultipla();
                break;

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while (op != 0);

    return 0;
}
