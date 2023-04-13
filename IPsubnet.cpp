#include <iostream>
#include <string>
using namespace std;

typedef struct ip {
    int octet_decimal;
    string octet_binary;
} ip;

ip orginal[4];
string binary;
bool flaga1;

void ToBinary(int decimal)
{
    int bit, i, j, amount, to_add;
    int temp_binary[8]; // maksymalna liczba bitów potrzebna do zapisu liczby całkowitej

    if ((decimal != 0) && (decimal < 255)) {
        // zamiana na postać binarną
        for (i = 0; decimal > 0; i++) {
            bit = decimal % 2;
            temp_binary[i] = bit;
            decimal /= 2;
        }

        // konwersja na string
        binary = "";
        for (j = i - 1; j >= 0; j--) {
            binary += to_string(temp_binary[j]);
        }

        amount = binary.length();

        if (amount < 8) {
            to_add = 8 - amount;
            string supplement(to_add, '0');
            binary = supplement + binary;
        }
    } else if (decimal == 0) {
        binary = "00000000";
    }else if (decimal > 255) {
        flaga1 = true;
    }
}

int main()
{
    int liczba, i;

    for (i = 0; i <= 3; i++) {
        cout << "\nPodaj " << i + 1 << " oktet: ";
        cin >> orginal[i].octet_decimal;

        if (flaga1 == true) {
            cout << "\n za duzo";
            i--;
        } else {
            ToBinary(orginal[i].octet_decimal);
            cout << "\nOktet " << i + 1 << ": " << binary;
            orginal[i].octet_binary = binary;
            flaga1 = false;
        }

    }

    cout << "\nAdres IP w systemie dziesiętnym: " << orginal[0].octet_decimal << "." << orginal[1].octet_decimal << "." << orginal[2].octet_decimal << "." << orginal[3].octet_decimal;
    cout << "\nAdres IP w systemie binarnym: " << orginal[0].octet_binary << "." << orginal[1].octet_binary << "." << orginal[2].octet_binary << "." << orginal[3].octet_binary;

    return 0;
}
