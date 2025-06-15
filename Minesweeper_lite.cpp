#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Minesweeper_class {
private:
    char board[6][6];
    bool revealed[6][6];
    int data[6][6];

public:
    Minesweeper() {
        clearBoard();
    }

    void clearBoard() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                board[i][j] = '*';
                revealed[i][j] = false;
                data[i][j] = 0;
            }
        }
    }

    void generateBoard(int jumlahBom) {
        clearBoard();
        srand(time(0));
        int bombsPlaced = 0;
        while (bombsPlaced < jumlahBom) {
            int row = rand() % 6;
            int col = rand() % 6;
            if (data[row][col] != -1) {
                data[row][col] = -1;
                bombsPlaced++;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int ni = row + i, nj = col + j;
                        if (ni >= 0 && ni < 6 && nj >= 0 && nj < 6 && data[ni][nj] != -1) {
                            data[ni][nj]++;
                        }
                    }
                }
            }
        }
    }

    void displayBoard() {
        cout << "   ";
        for (int j = 0; j < 6; j++) {
            cout << j << " ";
        }
        cout << endl;
        for (int i = 0; i < 6; i++) {
            cout << i << "  ";
            for (int j = 0; j < 6; j++) {
                if (revealed[i][j]) {
                    if (data[i][j] == -1) {
                        board[i][j] = 'X';
                    } else {
                        board[i][j] = '0' + data[i][j];
                    }
                }
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool openCell(int row, int col) {
        if (row < 0 || row >= 6 || col < 0 || col >= 6 || revealed[row][col]) {
            return true;
        }
        revealed[row][col] = true;
        if (data[row][col] == -1) {
            return false;
        }
        return true;
    }

    bool isWin() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (!revealed[i][j] && data[i][j] != -1) {
                    return false;
                }
            }
        }
        return true;
    }

    void displayAllBoard() {
        cout << "   ";
        for (int j = 0; j < 6; j++) {
            cout << j  << " ";
        }
        cout << endl;
        for (int i = 0; i < 6; i++) {
            cout << i << "  ";
            for (int j = 0; j < 6; j++) {
                if (data[i][j] == -1) {
                    cout << "X ";
                } else {
                    cout << data[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    bool isRevealed(int row, int col) {
        return revealed[row][col];
    }

    int getSize() {
        return 6;
    }
};

int main() {
    system("cls");
    int jumlahBom;
    char ulang;
    do {
        cout << "Selamat datang di permainan Minesweeper!" << endl;
        cout << "Silakan pilih jumlah bom (5 - 10): ";
        cin >> jumlahBom;
        if (jumlahBom < 5 || jumlahBom > 10) {
            cout << "Jumlah bom harus antara 5 dan 10!" << endl;
        }
    } while (jumlahBom < 5 || jumlahBom > 10);

    Minesweeper_class game;
    game.generateBoard(jumlahBom);

    while (true) {
        game.displayBoard();
        int row, col;
        cout << "Tebak baris dan kolom (contoh: 2 3): ";
        cin >> row >> col;
        if (row < 0 || row >= game.getSize() || col < 0 || col >= game.getSize()) {
            system("cls");
            cout << "Koordinat tidak valid!" << endl;
            continue;
        }
        if (game.isRevealed(row, col)) {
            system("cls");
            cout << "Kotak sudah dibuka." << endl;
            continue;
        }
        if (!game.openCell(row, col)) {
            cout << "DUAR BOOM! Kamu kena BOM. Game Over." << endl;
            game.displayAllBoard();
            break;
        }
        if (game.isWin()) {
            cout << "Selamat! Kamu menang!" << endl;
            game.displayAllBoard();
            break;
        }
    }

    ulang_lagi:
    cout << "Apakah Anda ingin bermain lagi? (1: Ya, 0: Tidak): ";
    cin >> ulang;
    
    if (ulang == '1') {
        main();
    } else if (ulang == '0') {
        cout << "Terima kasih telah bermain!" << endl;
    } else {
        cout << "Pilihan tidak valid. Program akan berakhir." << endl;
        goto ulang_lagi;
    }
    return 0;
}
