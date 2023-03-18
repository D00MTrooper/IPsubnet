#include <iostream>
using namespace std;

int main() {
    int liczba, bit, i;
    int binary[32]; // maksymalna liczba bit�w potrzebna do zapisu liczby ca�kowitej
    
    cout << "Podaj liczb� w systemie dziesi�tnym: ";
    cin >> liczba;

    // zamiana na posta� binarn�
    for (i = 0; liczba > 0; i++) {
        bit = liczba % 2;
        binary[i] = bit;
        liczba /= 2;
    }

    // wy�wietlenie wyniku
    cout << "Liczba w systemie binarnym: ";
    for (i--; i >= 0; i--) {
        cout << binary[i];
    }
    cout << endl;

    return 0;
}

