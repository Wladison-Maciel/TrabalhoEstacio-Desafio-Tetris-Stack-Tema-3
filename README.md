# 🧱 Tetris Stack — Gerenciador de Peças com Fila Circular e Pilha

Este projeto implementa o sistema de gerenciamento de peças do **Tetris Stack**, utilizando uma **fila circular** para peças futuras e uma **pilha** para peças reservadas.  
O objetivo é simular mecânicas reais de jogos, praticando:

- Integração entre **fila** e **pilha**
- Operações dinâmicas com **estruturas lineares**
- Controle lógico de entrada, saída e trocas
- Modularização e organização de código em C

---

## 🧠 Funcionalidades

- 🔄 **Fila circular** com 5 peças sempre preenchida  
- 📦 **Pilha de reserva** com capacidade para 3 peças  
- ⚙️ Operações disponíveis:
  - **Jogar peça** (remove da fila)
  - **Reservar peça** (move da fila → pilha)
  - **Usar peça reservada** (pop da pilha)
  - **Trocar peça atual** (frente da fila ↔ topo da pilha)
  - **Troca múltipla** (3 primeiras da fila ↔ 3 da pilha)
  - **Exibir estado atual**
  - **Sair**
- 🔁 A cada remoção ou envio à pilha, **uma nova peça é gerada automaticamente**
- 🧱 Peças sempre compostas por:
  - Tipo: `'I'`, `'O'`, `'T'`, `'L'`
  - ID único incremental

---

## 📦 Estrutura da `struct Peca`

| Campo | Tipo         | Descrição |
|-------|--------------|-----------|
| `nome` | `char`      | Tipo da peça (I, O, T, L) |
| `id`   | `int`       | Identificador único da peça |

---

## 🔧 Funções principais

| Função | Descrição |
|--------|-----------|
| `gerarPeca()` | Cria automaticamente uma nova peça |
| `enqueue()` | Insere peça no final da fila circular |
| `dequeue()` | Remove peça da frente da fila |
| `push()` | Insere peça no topo da pilha |
| `pop()` | Remove peça da pilha |
| `trocarSimples()` | Troca frente da fila ↔ topo da pilha |
| `trocaMultipla()` | Troca bloco de 3 peças entre fila e pilha |
| `mostrarEstado()` | Exibe fila + pilha formatadas |

---

## 🕹️ Exemplo de saída

Fila de peças: [I 0] [L 1] [T 2] [O 3] [I 4]
Pilha (Topo → Base): [O 8] [L 7] [T 6]


---

## 🛠️ Tecnologias Utilizadas

- **Linguagem C**
- Bibliotecas:
  - `stdio.h`
  - `stdlib.h`
  - `time.h`

---

## ▶️ Como executar

Compile o programa:

```bash
gcc main.c -o main
```

```bash
./main
```