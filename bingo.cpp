#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <thread>

using namespace std;

const string COLOR_RED = "\u001b[31m";
const string COLOR_BLUE = "\u001b[34m";
const string COLOR_GREEN = "\u001b[32m";
const string COLOR_RESET = "\u001b[0m";
const string COLOR_BOLD = "\u001b[1m";

const int MAX_NUMEROS = 100;

void mostrarPainelBingo(const int todosNumeros[], int tamanho, const int numerosSorteados[], int tamanhoSorteados) {
    cout << COLOR_BOLD << "BINGOH!" << COLOR_RESET << endl;
    cout << string(104, '.') << endl;
    cout << endl;
    for (int i = 1; i <= MAX_NUMEROS; ++i) {
        auto it = find(todosNumeros, todosNumeros + tamanho, i);
        if (it != todosNumeros + tamanho) {
            int indice = distance(todosNumeros, it);
            if (find(numerosSorteados, numerosSorteados + tamanhoSorteados, i) != numerosSorteados + tamanhoSorteados) {
                cout << COLOR_BOLD << COLOR_RED << "| " << setw(2) << i << " |" << COLOR_RESET << " ";
            } else {
                cout << "| " << setw(2) << i << " | ";
            }

            if ((indice + 1) % 15 == 0) {
                cout << endl;
            }
        }
    }
    cout << endl;
    cout << string(104, '.') << endl;
}

void gerarCartoes(int quantidadeCartoes) {
    for (int i = 1; i <= quantidadeCartoes; i++) {
        string nomeArquivo = "cartao_" + to_string(i) + ".txt";
        ofstream arquivo(nomeArquivo);

        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                arquivo << "x  ";
            }
            arquivo << endl;
        }

        arquivo.close();
        cout << "O cartão foi gerado!: " << nomeArquivo << endl;
    }
}

int main() {
    srand(time(0));

    char escolha;
    int maxNumero;
    int todosNumeros[MAX_NUMEROS];
    int numerosSorteados[MAX_NUMEROS];
    int contadorSorteados = 0;

    for (int i = 1; i <= MAX_NUMEROS; ++i) {
        todosNumeros[i - 1] = i;
    }

    do {
        cout << COLOR_BOLD << "Menu Principal" << COLOR_RESET << endl;
        cout << "\n---- Opções ----" << endl;
        cout << "1. Sorteios Automáticos Infinitos" << endl;
        cout << "2. Sorteio Manual" << endl;
        cout << "3. Gerar Cartões" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolhe uma opção: ";
        cin >> escolha;

        switch (escolha) {
            case '1':
                do {
                    maxNumero = 100;
                    int novoNumero = rand() % maxNumero + 1;
                    numerosSorteados[contadorSorteados++] = novoNumero;
                    cout << COLOR_BOLD << COLOR_GREEN << "[★] Número sorteado: " << novoNumero << " [★]" << COLOR_RESET << endl;
                    mostrarPainelBingo(todosNumeros, MAX_NUMEROS, numerosSorteados, contadorSorteados);
                    cout << "A aguardar próximo sorteio automático..." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                } while (true);
                break;
            case '2':
                do {
                    maxNumero = 100;
                    int novoNumeroManual = rand() % maxNumero + 1;
                    numerosSorteados[contadorSorteados++] = novoNumeroManual;
                    cout << COLOR_BOLD << COLOR_GREEN << "[★] Número sorteado: " << novoNumeroManual << " [★]" << COLOR_RESET << endl;
                    mostrarPainelBingo(todosNumeros, MAX_NUMEROS, numerosSorteados, contadorSorteados);
                    cout << "Queres continuar o sorteio manual? (s/n): ";
                    cin >> escolha;
                } while (escolha == 's' || escolha == 'S');
                break;
            case '3':
                int quantidadeCartoes;
                cout << "Escreve a quantidade de cartões a serem gerados: ";
                cin >> quantidadeCartoes;
                gerarCartoes(quantidadeCartoes);
                break;
            case '4':
                cout << "Até à próxima!" << endl;
                break;
            default:
                cout << "Opção inválida. Escolhe novamente." << endl;
        }
    } while (escolha != '4');
    return 0;
}
