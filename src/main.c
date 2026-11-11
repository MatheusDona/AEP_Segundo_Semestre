#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define INVALIDO -999

struct Acao {
    int codigo;
    char escola[60];
    char tema[60];
    char data[11];
    char publico[60];
    char responsavel[60];
    int prevista;
    int efetiva;
    int situacao; 
};

struct Acao acoes[MAX];
int total = 0;


void lerTexto(char msg[], char destino[], int tamanho) {
    char linha[200];

    while (1) {
        printf("%s", msg);
        if (fgets(linha, 200, stdin) == NULL) {
            exit(0);
        }
        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) == 0) {
            printf("Erro: este campo e obrigatorio.\n");
        } else if ((int)strlen(linha) >= tamanho) {
            printf("Erro: texto muito longo.\n");
        } else {
            strcpy(destino, linha);
            return;
        }
    }
}


int lerNumero(char msg[]) {
    char linha[200];
    char resto;
    int n;

    printf("%s", msg);
    if (fgets(linha, 200, stdin) == NULL) {
        exit(0);
    }

    if (sscanf(linha, "%d %c", &n, &resto) != 1) {
        return INVALIDO;
    }
    return n;
}


int lerCodigo(char msg[]) {
    int c;

    while (1) {
        c = lerNumero(msg);
        if (c == INVALIDO) {
            printf("Erro: o codigo deve conter somente numeros.\n");
        } else if (c <= 0) {
            printf("Erro: o codigo deve ser maior que zero.\n");
        } else {
            return c;
        }
    }
}


int lerQuantidade(char msg[], int minimo) {
    int q;

    while (1) {
        q = lerNumero(msg);
        if (q == INVALIDO) {
            printf("Erro: digite um numero inteiro.\n");
        } else if (q < 0) {
            printf("Erro: a quantidade nao pode ser negativa.\n");
        } else if (q < minimo) {
            printf("Erro: a quantidade deve ser maior que zero.\n");
        } else {
            return q;
        }
    }
}


int dataValida(char data[]) {
    return strlen(data) == 10 && data[2] == '/' && data[5] == '/';
}


int buscarCodigo(int codigo) {
    int i;

    for (i = 0; i < total; i++) {
        if (acoes[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

char *nomeSituacao(int situacao) {
    if (situacao == 1) {
        return "PLANEJADA";
    } else if (situacao == 2) {
        return "REALIZADA";
    }
    return "CANCELADA";
}

void mostrarAcao(int i) {
    printf("----------------------------------------\n");
    printf("Codigo: %d | Situacao: %s\n", acoes[i].codigo, nomeSituacao(acoes[i].situacao));
    printf("Escola: %s\n", acoes[i].escola);
    printf("Tema: %s\n", acoes[i].tema);
    printf("Data prevista: %s\n", acoes[i].data);
    printf("Publico-alvo: %s\n", acoes[i].publico);
    printf("Responsavel: %s\n", acoes[i].responsavel);
    printf("Participantes previstos: %d | efetivos: %d\n", acoes[i].prevista, acoes[i].efetiva);
}

void cadastrar() {
    struct Acao nova;

    if (total >= MAX) {
        printf("Erro: limite de %d acoes atingido.\n", MAX);
        return;
    }

    printf("\n--- Cadastro de acao de vacinacao ---\n");
    printf("Use apenas dados ficticios e coletivos.\n");

    while (1) {
        nova.codigo = lerCodigo("Codigo da acao (somente numeros): ");
        if (buscarCodigo(nova.codigo) >= 0) {
            printf("Erro: ja existe uma acao com este codigo.\n");
        } else {
            break;
        }
    }
    lerTexto("Escola: ", nova.escola, 60);
    lerTexto("Tema: ", nova.tema, 60);
    while (1) {
        lerTexto("Data prevista (DD/MM/AAAA): ", nova.data, 11);
        if (dataValida(nova.data)) {
            break;
        }
        printf("Erro: data invalida. Use DD/MM/AAAA.\n");
    }
    lerTexto("Publico-alvo: ", nova.publico, 60);
    lerTexto("Responsavel (equipe ou cargo): ", nova.responsavel, 60);
    nova.prevista = lerQuantidade("Quantidade prevista de participantes: ", 1);
    nova.efetiva = 0;
    nova.situacao = 1;

    acoes[total] = nova;
    total++;
    printf("Acao cadastrada com sucesso.\n");
}

void listar() {
    int i;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }
    printf("\n--- Acoes cadastradas (%d) ---\n", total);
    for (i = 0; i < total; i++) {
        mostrarAcao(i);
    }
    printf("----------------------------------------\n");
}

void pesquisar() {
    char termo[60];
    int criterio, i, achou, encontradas, codigoBusca = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    while (1) {
        printf("\nPesquisar por: 1-Codigo 2-Escola 3-Tema 0-Voltar\n");
        criterio = lerNumero("Escolha: ");
        if (criterio >= 0 && criterio <= 3) {
            break;
        }
        printf("Erro: opcao invalida.\n");
    }
    if (criterio == 0) {
        return;
    }

    if (criterio == 1) {
        codigoBusca = lerCodigo("Digite o codigo: ");
    } else {
        lerTexto("Digite o que procurar: ", termo, 60);
    }
    encontradas = 0;
    for (i = 0; i < total; i++) {
        achou = 0;
        if (criterio == 1 && acoes[i].codigo == codigoBusca) {
            achou = 1;
        } else if (criterio == 2 && strstr(acoes[i].escola, termo) != NULL) {
            achou = 1;
        } else if (criterio == 3 && strstr(acoes[i].tema, termo) != NULL) {
            achou = 1;
        }
        if (achou) {
            mostrarAcao(i);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf("Nenhuma acao encontrada.\n");
    } else {
        printf("%d acao(oes) encontrada(s).\n", encontradas);
    }
}

void atualizar() {
    int codigo, pos, nova, participantes;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    codigo = lerCodigo("Codigo da acao: ");
    pos = buscarCodigo(codigo);
    if (pos < 0) {
        printf("Erro: registro inexistente.\n");
        return;
    }
    mostrarAcao(pos);

    while (1) {
        nova = lerNumero("Nova situacao (1-Planejada 2-Realizada 3-Cancelada): ");
        if (nova >= 1 && nova <= 3) {
            break;
        }
        printf("Erro: opcao invalida. Digite 1, 2 ou 3.\n");
    }

    participantes = 0;
    if (nova == 2) {
        participantes = lerQuantidade("Quantidade efetiva de participantes: ", 0);
    }
    acoes[pos].situacao = nova;
    acoes[pos].efetiva = participantes;
    printf("Situacao atualizada para %s.\n", nomeSituacao(nova));
}

void resumo() {
    int i, planejadas = 0, realizadas = 0, canceladas = 0;
    int participantes = 0, previstos = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        if (acoes[i].situacao == 1) {
            planejadas++;
        } else if (acoes[i].situacao == 2) {
            realizadas++;
            participantes = participantes + acoes[i].efetiva;
            previstos = previstos + acoes[i].prevista;
        } else {
            canceladas++;
        }
    }

    printf("\n===== Resumo geral =====\n");
    printf("Planejadas: %d | Realizadas: %d | Canceladas: %d\n", planejadas, realizadas, canceladas);
    printf("Total de participantes: %d\n", participantes);
    if (previstos > 0) {
        printf("Participacao em relacao ao previsto: %.1f%%\n", participantes * 100.0 / previstos);
    } else {
        printf("Participacao: nenhuma acao realizada ainda.\n");
    }
}

int main() {
    int opcao;

    printf("PSE em Acao - vacinacao escolar (somente dados ficticios)\n");

    do {
        printf("\n===== PSE em Acao - Vacinacao =====\n");
        printf("1 - Cadastrar acao de vacinacao\n");
        printf("2 - Listar acoes\n");
        printf("3 - Pesquisar acao (codigo, escola ou tema)\n");
        printf("4 - Atualizar situacao da acao\n");
        printf("5 - Gerar resumo geral\n");
        printf("6 - Encerrar\n");
        opcao = lerNumero("Escolha uma opcao: ");

        if (opcao == 1) {
            cadastrar();
        } else if (opcao == 2) {
            listar();
        } else if (opcao == 3) {
            pesquisar();
        } else if (opcao == 4) {
            atualizar();
        } else if (opcao == 5) {
            resumo();
        } else if (opcao == 6) {
            printf("Encerrando o sistema...\n");
        } else {
            printf("Erro: opcao invalida. Digite de 1 a 6.\n");
        }
    } while (opcao != 6);

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}
