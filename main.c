#include <stdio.h>

//desenha a tabela do jogo
void drawGame(char *n) {

    for (int i = 0; i < 9; i++) {

        printf(" | ");

        if (n[i] == 'X' || n[i] == 'O') {
            printf("%c", n[i]);
            
        } else {
            printf("%d", i);
        }

        if (i == 2 || i == 5 || i == 8) printf(" |");

        if (i == 2 || i == 5 || i == 8) printf("\n");
        
    }
}

//valida as sequencias vencedoras ou se deu velha
int validateGame(char *n, char optionP1, char optionP2, int j) {
    int res = 0;
    
    //horizontais
    for (int i = 0; i < 9; i+=3) {
        if (n[i] == optionP1 && n[i+1] == optionP1 && n[i+2] == optionP1) {
            printf("P1 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i, i+1, i+2);
            res = 1;

        } else if (n[i] == optionP2 && n[i+1] == optionP2 && n[i+2] == optionP2) {
            printf("P2 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i, i+1, i+2);
            res = 2;
        } 
    }

    //verticais
    for (int i = 0; i < 3; i++) {
        if (n[i] == optionP1 && n[i+3] == optionP1 && n[i+6] == optionP1) {
            printf("P1 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i, i+3, i+6);
            res = 1;

        } else if (n[i] == optionP2 && n[i+3] == optionP2 && n[i+6] == optionP2) {
            printf("P2 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i, i+3, i+6);
            res = 2;
        }
    }

    //diagonal 0, 4, 8
    for (int i = 0; i < 1; i++){
         if (n[i] == optionP1 && n[i+4] == optionP1 && n[i+8] == optionP1) {
            printf("P1 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i, i+4, i+8);
            res = 1;

        } else if (n[i] == optionP2 && n[i+4] == optionP2 && n[i+8] == optionP2) {
            printf("P2 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i, i+4, i+8);
            res = 2;
        }
    }

    //diagonal 2, 4, 6
    for (int i = 0; i < 1; i++){
         if (n[i+2] == optionP1 && n[i+4] == optionP1 && n[i+6] == optionP1) {
            printf("P1 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i+2, i+4, i+6);
            res = 1;

        } else if (n[i+2] == optionP2 && n[i+4] == optionP2 && n[i+6] == optionP2) {
            printf("P2 ganhou!\n");
            printf("Sequencia: %d, %d, %d\n\n", i+2, i+4, i+6);
            res = 2;
        } 
    }

    if (j == 8 && res == 0) {
        printf("Deu velha!\n\n");
        res = 3;
    }

    return res;
}

//valida se os campos já estão preenchidos ou se os campos informados existem (0 a 8)
int validateFields(int indexOption, char *n, char *nickname, int id) {
    int index = 10;

    while (indexOption < 0 || indexOption > 8 ||
        n[indexOption] == 'X' || n[indexOption] == 'O') {

        if (id == 1) {
            printf("\nP1 (%s): ", nickname);
            scanf(" %d", &indexOption); 
            index = indexOption;

        } else if (id == 2) {
            printf("\nP2: ");
            scanf(" %d", &indexOption);
            index = indexOption;
        }
    }

    return index;
}

//faz o controle das partidas
int controlMatches(char choice, char *n) {
    int yesOrNo = 0;

    printf("\nJogar novamente? s/n: \n"); 
    scanf(" %c", &choice);
    
    while (choice != 's' && choice != 'n') {
        printf("\nJogar novamente? s/n: \n\n"); 
        scanf(" %c", &choice);
    }

    if (choice == 'n') return yesOrNo;

    for (int i = 0; i < 9; i++) {
        n[i] = 'a';
    }

    yesOrNo = -1;

    return yesOrNo;
}

//verifica quem ganhou pela ultima vez e quem jogou pela ultima vez
int winnerStarts(int res, int turn) {
    if (res == 1) return 1;
    if (res == 2) return 0;
    if (res == 3 && turn == 0) return 0;
    if (res == 3 && turn == 1) return 1;
}

int main() {
    char n[8];
    char nickname[20] = "";
    char optionP1;
    char optionP2;
    char choice;
    int turn = 1;
    int indexOptionP1;
    int indexOptionP2;
    int idP1 = 1;
    int idP2 = 2;
    int scoreP1 = 0;
    int scoreP2 = 0;

    printf("=== JOGO DA VELHA ===\n\n");
    printf("Insira seu apelido: ");
    scanf("%s", nickname);
    printf("Bem-vindo, %s!\n", nickname);
    printf("Escolha sua letra: \n");
    printf("X ou O? ");
    scanf(" %c", &optionP1);

    //verifica se as opções são X ou O
    while (optionP1 != 'X' && optionP1 != 'O') {
        printf("Valor invalido. Escolha X ou O: ");
        scanf(" %c", &optionP1);
    }
    
    if (optionP1 == 'X') {
        optionP2 = 'O';
    } else if (optionP1 == 'O') {
        optionP2 = 'X';
    }
    
    printf("\np1: %c p2: %c \n", optionP1, optionP2);
    printf("Comecem! \n\n");

    //realiza as jogadas  
    int j = 0;

    while (j < 9) {

        if (turn == 1) {
            drawGame(n);
            printf("\nP1 (%s): ", nickname); 
            scanf(" %d", &indexOptionP1);

            int indexP1 = validateFields(indexOptionP1, n, nickname, idP1);

            n[indexP1 == 10 ? indexOptionP1 : indexP1] = optionP1;
            printf("\n");
            turn = 0;

        } else if (turn == 0) {
            drawGame(n);
            printf("\nP2: ");
            scanf(" %d", &indexOptionP2);

            int indexP2 = validateFields(indexOptionP2, n, nickname, idP2);

            n[indexP2 == 10 ? indexOptionP2 : indexP2] = optionP2;
            printf("\n");
            turn = 1;
        }

        int resValidateGame = validateGame(n, optionP1, optionP2, j);

        if (resValidateGame == 1 || resValidateGame == 2 
        || resValidateGame == 3) {
            drawGame(n);
 
            int yesOrNo = controlMatches(choice, n);

            if (yesOrNo == 0) return 0;

            j = yesOrNo;
            turn = winnerStarts(resValidateGame, turn);
        }

        if (j == 8) drawGame(n);    

        j++;
    }

    return 0;
}