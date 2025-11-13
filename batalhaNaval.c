#include <stdio.h>

#define BOARD 10
#define SKILL 7      // tamanho das matrizes de habilidade (pode ser 5 ou 7)
#define WATER 0
#define SHIP 3
#define HIT 5        // área afetada pela habilidade

int main() {

    // ---------------------------------------------------------
    // TABULEIRO 10x10
    // ---------------------------------------------------------
    int tabuleiro[BOARD][BOARD];

    // Inicializa tudo com água
    for (int i = 0; i < BOARD; i++) {
        for (int j = 0; j < BOARD; j++) {
            tabuleiro[i][j] = WATER;
        }
    }

    // (Apenas para visualização — navios fixos)
    tabuleiro[2][2] = SHIP;
    tabuleiro[2][3] = SHIP;
    tabuleiro[2][4] = SHIP;

    tabuleiro[5][7] = SHIP;
    tabuleiro[6][7] = SHIP;

    // ---------------------------------------------------------
    // MATRIZES DE HABILIDADE: CONE, CRUZ, OCTAEDRO (LOSANGO)
    // ---------------------------------------------------------

    int cone[SKILL][SKILL];
    int cruz[SKILL][SKILL];
    int octa[SKILL][SKILL];
    int center = SKILL / 2; // linha/coluna central

    // -------------------------
    // HABILIDADE: CONE
    // -------------------------
    // Forma triangular apontando PARA BAIXO
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {

            // Condição do cone:
            // A cada linha i, a largura aumenta (como pirâmide)
            if (j >= center - i && j <= center + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // -------------------------
    // HABILIDADE: CRUZ
    // -------------------------
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {

            if (i == center || j == center)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // -------------------------
    // HABILIDADE: OCTAEDRO (LOSANGO)
    // -------------------------
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {

            int distI = i - center;  if (distI < 0) distI = -distI;
            int distJ = j - center;  if (distJ < 0) distJ = -distJ;

            // Condição do losango
            if (distI + distJ <= center)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }

    // ---------------------------------------------------------
    // SOBREPOSIÇÃO DAS HABILIDADES NO TABULEIRO
    // ---------------------------------------------------------

    // Pontos de origem no tabuleiro
    int origemConeLinha = 1, origemConeCol = 5;   // topo do cone
    int origemCruzLinha = 5, origemCruzCol = 2;   // centro
    int origemOctaLinha = 7, origemOctaCol = 7;   // centro

    // -------------------------
    // Aplicar CONE (origem no topo da matriz)
    // -------------------------
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {
            if (cone[i][j] == 1) {

                int r = origemConeLinha + i;
                int c = origemConeCol + (j - center);

                if (r >= 0 && r < BOARD && c >= 0 && c < BOARD)
                    tabuleiro[r][c] = HIT;
            }
        }
    }

    // -------------------------
    // Aplicar CRUZ (origem no centro da matriz)
    // -------------------------
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {
            if (cruz[i][j] == 1) {

                int r = origemCruzLinha + (i - center);
                int c = origemCruzCol + (j - center);

                if (r >= 0 && r < BOARD && c >= 0 && c < BOARD)
                    tabuleiro[r][c] = HIT;
            }
        }
    }

    // -------------------------
    // Aplicar OCTAEDRO (origem no centro da matriz)
    // -------------------------
    for (int i = 0; i < SKILL; i++) {
        for (int j = 0; j < SKILL; j++) {
            if (octa[i][j] == 1) {

                int r = origemOctaLinha + (i - center);
                int c = origemOctaCol + (j - center);

                if (r >= 0 && r < BOARD && c >= 0 && c < BOARD)
                    tabuleiro[r][c] = HIT;
            }
        }
    }

    // ---------------------------------------------------------
    // EXIBIÇÃO FINAL
    // ---------------------------------------------------------

    printf("\n=== TABULEIRO COM HABILIDADES ===\n");
    printf("0 = Água | 3 = Navio | 5 = Área afetada\n\n");

    for (int i = 0; i < BOARD; i++) {
        for (int j = 0; j < BOARD; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
