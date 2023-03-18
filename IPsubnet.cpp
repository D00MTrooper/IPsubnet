#include <iostream>
using namespace std;

int main() {
    int liczba, bit, i;
    int binary[32]; // maksymalna liczba bitów potrzebna do zapisu liczby ca³kowitej
    
    cout << "Podaj liczbê w systemie dziesiêtnym: ";
    cin >> liczba;

    // zamiana na postaæ binarn¹
    for (i = 0; liczba > 0; i++) {
        bit = liczba % 2;
        binary[i] = bit;
        liczba /= 2;
    }

    // wyœwietlenie wyniku
    cout << "Liczba w systemie binarnym: ";
    for (i--; i >= 0; i--) {
        cout << binary[i];
    }
    cout << endl;

    return 0;
}

