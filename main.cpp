#include <iostream>
#include <string>
#include <mysql.h>
#include <cstdlib>

using namespace std;

// ==========================================
// CONEXÃO COM BANCO DE DADOS
// ==========================================
MYSQL* conectar() {
    MYSQL* conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "", "steam_db", 0, NULL, 0);
    return conn;
}

// ==========================================
// FUNÇÕES UTILITÁRIAS.
// ==========================================
void pausar_e_limpar() {
    cout << "\n";
    system("pause");
    system("cls");
}

// ==========================================
// FUNÇÕES DO MENU.
// ==========================================
void adicionar_jogo() {
    string titulo;
    double preco;
    int id_cat;

    cout << "Titulo do Jogo: ";
    cin.ignore();
    getline(cin, titulo);

    cout << "Preco: ";
    cin >> preco;

    cout << "Insira o número correspondente a categoria do jogo:";
    cout << "\n[1] - RPG";
    cout << "\n[2] - Aventura";
    cout << "\n[3] - Estratégia";
    cout << "\n[4] - FPS";
    cout << "\n[5] - Outras";
    cin >> id_cat;

    MYSQL* conn = conectar();
    string query = "INSERT INTO Jogo (titulo, preco, id_categoria) VALUES ('" + titulo + "', " + to_string(preco) + ", " + to_string(id_cat) + ")";

    mysql_query(conn, query.c_str());

    cout << "\nJogo salvo no banco de dados com sucesso!\n";
    mysql_close(conn);
}

void listar_jogos() {
    MYSQL* conn = conectar();
    mysql_query(conn, "SELECT id_jogo, titulo, preco FROM Jogo");

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW linha;

    cout << "\n--- Lista de Jogos ---\n";

    // Flag para verificar se a lista está vazia
    bool tem_jogos = false;

    while ((linha = mysql_fetch_row(res))) {
        tem_jogos = true;
        cout << "ID: " << linha[0] << " | Titulo: " << linha[1] << " | Preco: R$" << linha[2] << "\n";
    }

    if (!tem_jogos) {
        cout << "Nenhum jogo encontrado na sua biblioteca.\n";
    }

    mysql_free_result(res);
    mysql_close(conn);
}

void atualizar_preco() {
    int id;
    double preco;

    cout << "Insira o ID do jogo que terá o preço alterado:\n";
    cin >> id;
    cout << "Insira o novo preço deste jogo:\n";
    cin >> preco;

    MYSQL* conn = conectar();
    string query = "UPDATE Jogo SET preco = " + to_string(preco) + " WHERE id_jogo = " + to_string(id);

    mysql_query(conn, query.c_str());

    cout << "\nPreco alterado com sucesso!\n";
    mysql_close(conn);
}

void remover_jogo() {
    int id;

    cout << "Insira o ID do jogo a ser apagado:\n";
    cin >> id;

    MYSQL* conn = conectar();
    string query = "DELETE FROM Jogo WHERE id_jogo = " + to_string(id);

    mysql_query(conn, query.c_str());

    cout << "\nJogo excluído da sua biblioteca com sucesso!\n";
    mysql_close(conn);
}

void remover_jogos() {
    MYSQL* conn = conectar();
    mysql_query(conn, "DELETE FROM Jogo");

    cout << "\nTodos os jogos foram apagados da sua biblioteca com sucesso!\n";
    mysql_close(conn);
}

// ==========================================
// MENU
// ==========================================
int main() {
    int opcao_selecionada = -1;

    system("cls");

    while (opcao_selecionada != 0) {
        cout << "==== Projeto Banco de Dados - Steam ====\n";
        cout << "[1] - Adicionar novo jogo.\n";
        cout << "[2] - Listar jogos obtidos.\n";
        cout << "[3] - Editar preco de um jogo.\n";
        cout << "[4] - Remover um jogo da biblioteca.\n";
        cout << "[5] - Apagar todos os jogos da biblioteca.\n";
        cout << "[0] - Fechar o programa.\n";
        cout << "Opcao desejada:\n";
        cin >> opcao_selecionada;

        switch (opcao_selecionada) {
            case 1:
                adicionar_jogo();
                pausar_e_limpar();
                break;
            case 2:
                listar_jogos();
                pausar_e_limpar();
                break;
            case 3:
                atualizar_preco();
                pausar_e_limpar();
                break;
            case 4:
                remover_jogo();
                pausar_e_limpar();
                break;
            case 5:
                remover_jogos();
                pausar_e_limpar();
                break;
            case 0:
                cout << "\nEncerrando o programa...\n";
                break;
            default:
                cout << "\nOpcao invalida!\nPor favor, insira um numero valido.\n";
                pausar_e_limpar();
                break;
        }
    }

    return 0;
}
