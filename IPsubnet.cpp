#include <iostream>
#include <string>
#include <math.h>
#include <conio.h>
using namespace std;

struct ip {
    int octet_decimal, mask_decimal, subnetmask_decimal;
    string octet_binary, mask_binary, subnetmask_binary;

};

ip orginal[4], sub_by_mask[4];
string binary;
int flaga1, flaga_type, decimal;

void ZeroOneCheck(string input) {

    for (char c : input) {
        if (c != '0' && c != '1') flaga1 = 1;
    }
}


string AddZero(int amount) {
    int to_add;

    to_add = 8 - amount;
    string supplement(to_add, '0');

    return supplement;


}

void ToBinary(int decimalToBinary)
{
    int bit, i, j, amount, to_add;
    int temp_binary[8]; // maksymalna liczba bitów potrzebna do zapisu liczby ca³kowitej

    if ((decimalToBinary != 0) && (decimalToBinary < 255)) {
        // zamiana na postaæ binarn¹
        for (i = 0; decimalToBinary > 0; i++) {
            temp_binary[i] = decimalToBinary % 2;
            decimalToBinary /= 2;
        }

        // konwersja na string
        binary = "";
        for (j = i - 1; j >= 0; j--) {
            binary += to_string(temp_binary[j]);
        }
        //sprawdzenie d³ugoœci oktetu
        amount = binary.length();
        //uzupe³nie oktetu o 0 z przodu jeœli to potrzbne
        if (amount < 8) {
            binary = AddZero(amount) + binary;
        }
    }
    else if (decimalToBinary == 0) {
        binary = "00000000";
    }
    else if (decimalToBinary == 255) {
        binary = "11111111";
    }
    else if (decimalToBinary > 255) {
        flaga1 = 1;
    }
}

void IpClass(string first_octet) {
    string first_bit, second_bit;
    int i;

    first_bit = first_octet.substr(0, 1);
    second_bit = first_octet.substr(1, 1);

    if (first_bit == "0") {
        cout << "\n\nKlasa A";
        orginal[0].mask_binary = "11111111";
        orginal[0].mask_decimal = 255;
        for (i = 1; i <= 3; i++) {
            orginal[i].mask_binary = "00000000";
            orginal[i].mask_decimal = 0;
        }


    }
    else if ((first_bit == "1") && (second_bit == "0")) {
        cout << "\n\nKlasa B";
        orginal[0].mask_binary = "11111111";
        orginal[1].mask_binary = "11111111";
        orginal[2].mask_binary = "00000000";
        orginal[3].mask_binary = "00000000";

        orginal[0].mask_decimal = 255;
        orginal[1].mask_decimal = 255;
        orginal[2].mask_decimal = 0;
        orginal[3].mask_decimal = 0;

    }
    else if ((first_bit == "1") && (second_bit == "1")) {
        cout << "\n\nKlasa C";
        orginal[3].mask_binary = "00000000";
        orginal[3].mask_decimal = 0;

        for (i = 0; i <= 2; i++) {
            orginal[i].mask_binary = "11111111";
            orginal[i].mask_decimal = 255;
        }
    }
    cout << "\n\nMaska w systemie dziesietnym: " << orginal[0].mask_decimal << "." << orginal[1].mask_decimal << "." << orginal[2].mask_decimal << "." << orginal[3].mask_decimal;
    cout << "\nMaska w systemie binarnym: " << orginal[0].mask_binary << "." << orginal[1].mask_binary << "." << orginal[2].mask_binary << "." << orginal[3].mask_binary;

}

int ToDecimal(string binaryToDecimal) {
    string bit;
    int temp_decimal, x, wykladnik, amount, to_add, choice;

    wykladnik = 7;
    temp_decimal = 0;

    //sprawdzenie d³ugoœci oktetu
    amount = binaryToDecimal.length();

    if (amount == 8) {
        for (int i = 0; i <= 7; i++) {

            bit = binaryToDecimal.substr(i, 1);

            if (bit == "1") {
                x = pow(2, wykladnik - i);
            }
            else x = 0;

            temp_decimal = temp_decimal + x;
        }
        decimal = temp_decimal;

    }
    else if (amount < 8) {
        cout << "\nGdzie dodac zera";
        cout << "\n1.Z przodu";
        cout << "\n2.Z tylu";
        cout << "\n: ";
        cin >> choice;

        if (choice == 1) {
            binaryToDecimal = AddZero(amount) + binaryToDecimal;
            for (int i = 0; i <= 7; i++) {

                bit = binaryToDecimal.substr(i, 1);

                if (bit == "1") {
                    x = pow(2, wykladnik - i);
                }
                else x = 0;

                temp_decimal = temp_decimal + x;
            }
            decimal = temp_decimal;
        }
        if (choice == 2) {
            binaryToDecimal = binaryToDecimal + AddZero(amount);
            for (int i = 0; i <= 7; i++) {

                bit = binaryToDecimal.substr(i, 1);

                if (bit == "1") {
                    x = pow(2, wykladnik - i);
                }
                else x = 0;

                temp_decimal = temp_decimal + x;
            }
            decimal = temp_decimal;
        }
    }
    else if (amount > 8) {
        flaga1 = 1;
    }

    binary = binaryToDecimal;

    return decimal;

}


void ChooseIP() {

    int i, choice;

    if (flaga_type == 0) {
        cout << "\nJak chcesz podac adres ip";
        cout << "\n--------------";
        cout << "\n1. w systemie dziesietnym";
        cout << "\n2. w systemie binarnym";
        cout << "\n: ";
        cin >> choice;


        switch (choice) {
        case 1:
        {
            i = 0;
            for (i = 0; i <= 3; i++) {

                cout << "\nPodaj " << i + 1 << " oktet: ";
                cin >> orginal[i].octet_decimal;

                if (cin.fail()) {
                    flaga1 = 1;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                ToBinary(orginal[i].octet_decimal);

                if (flaga1 == 1) {
                    cout << "\n Podaj oktet jeszcze raz";
                    i--;
                    flaga1 = 0;
                }
                else {
                    cout << "\nOktet " << i + 1 << ":" << binary;
                    orginal[i].octet_binary = binary;
                }
            }
        }

        cout << "\n\nAdres IP w systemie dziesietnym: " << orginal[0].octet_decimal << "." << orginal[1].octet_decimal << "." << orginal[2].octet_decimal << "." << orginal[3].octet_decimal;
        cout << "\nAdres IP w systemie binarnym: " << orginal[0].octet_binary << "." << orginal[1].octet_binary << "." << orginal[2].octet_binary << "." << orginal[3].octet_binary;
        break;
        case 2:
        {
            for (i = 0; i <= 3; i++) {

                cout << "\nPodaj " << i + 1 << " oktet: ";
                cin >> orginal[i].octet_binary;
                ZeroOneCheck(orginal[i].octet_binary);
                ToDecimal(orginal[i].octet_binary);

                if (flaga1 == 1) {
                    cout << "\n Podaj oktet jeszcze raz";
                    i--;
                    flaga1 = 0;
                }
                else {
                    cout << "\nOktet " << i + 1 << ":" << binary;
                    cout << "\nOktet " << i + 1 << ": " << decimal;
                    orginal[i].octet_decimal = decimal;
                    orginal[i].octet_binary = binary;
                }

            }

            cout << "\n\nAdres IP w systemie dziesietnym: " << orginal[0].octet_decimal << "." << orginal[1].octet_decimal << "." << orginal[2].octet_decimal << "." << orginal[3].octet_decimal;
            cout << "\nAdres IP w systemie binarnym: " << orginal[0].octet_binary << "." << orginal[1].octet_binary << "." << orginal[2].octet_binary << "." << orginal[3].octet_binary;

        }
        break;
        }
        binary = "t";
    }
    if (flaga_type == 1) {
        cout << "\nJak chcesz podac maske podsieci";
        cout << "\n--------------";
        cout << "\n1. w systemie dziesietnym";
        cout << "\n2. w systemie binarnym";
        cout << "\n: ";
        cin >> choice;


        switch (choice) {
        case 1:
        {
            i = 0;
            for (i = 0; i <= 3; i++) {

                cout << "\nPodaj " << i + 1 << " oktet: ";
                cin >> orginal[i].subnetmask_decimal;

                if (cin.fail()) {
                    flaga1 = 1;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                ToBinary(orginal[i].subnetmask_decimal);

                if (flaga1 == 1) {
                    cout << "\nPodaj oktet jeszcze raz";
                    i--;
                    flaga1 = 0;
                }
                else {
                    cout << "\nOktet " << i + 1 << ": " << binary;
                    orginal[i].subnetmask_binary = binary;
                }

            }

            cout << "\nMaska podsieci w systemie dziesietnym: " << orginal[0].subnetmask_decimal << "." << orginal[1].subnetmask_decimal << "." << orginal[2].subnetmask_decimal << "." << orginal[3].subnetmask_decimal;
            cout << "\nMaska podsieci w systemie binarnym: " << orginal[0].subnetmask_binary << "." << orginal[1].subnetmask_binary << "." << orginal[2].subnetmask_binary << "." << orginal[3].subnetmask_binary;
        }
        break;
        case 2:
        {
            for (i = 0; i <= 3; i++) {

                cout << "\nPodaj " << i + 1 << " oktet: ";
                cin >> orginal[i].subnetmask_binary;
                ZeroOneCheck(orginal[i].subnetmask_binary);
                ToDecimal(orginal[i].subnetmask_binary);

                if (flaga1 == 1) {
                    cout << "\nPodaj oktet jeszcze raz";
                    i--;
                    flaga1 = 0;
                }
                else {
                    cout << "\nOktet " << i + 1 << ":" << binary;
                    cout << "\nOktet " << i + 1 << ": " << decimal;
                    orginal[i].subnetmask_decimal = decimal;
                    orginal[i].subnetmask_binary = binary;
                }

            }

            cout << "\n\nMaska podsieci w systemie dziesietnym: " << orginal[0].subnetmask_decimal << "." << orginal[1].subnetmask_decimal << "." << orginal[2].subnetmask_decimal << "." << orginal[3].subnetmask_decimal;
            cout << "\nMaska podsieci w systemie binarnym: " << orginal[0].subnetmask_binary << "." << orginal[1].subnetmask_binary << "." << orginal[2].subnetmask_binary << "." << orginal[3].subnetmask_binary;

        }
        break;
        }
    }

}

void SubnetByMask() {
    int choice, prefix, subnet_octet, subnet_bits, amount, number_of_octets;

    cout << "\nJak chcesz podac maske pod podsieci";
    cout << "\n1. W formie binarnej lub dziesietnej";
    cout << "\n2. W formie /...";
    cout << "\n:";
    cin >> choice;

    switch (choice) {
    case 1:
    {
        flaga_type = 1;
        ChooseIP();
    }
    break;

    case 2:
    {
        cout << "\nPodaj prefix: /";
        cin >> prefix;

        subnet_octet = prefix / 8;
        subnet_bits = prefix % 8;

        for (int i = 0; i < subnet_octet; i++) {
            orginal[i].subnetmask_binary = "11111111";
            orginal[i].subnetmask_decimal = 255;
            number_of_octets = i + 1;
        }

        if (subnet_bits != 0) {
            string supplement(subnet_bits, '1');
            orginal[subnet_octet].subnetmask_binary = supplement + AddZero(subnet_bits);
            orginal[subnet_octet].subnetmask_decimal = ToDecimal(orginal[subnet_octet].subnetmask_binary);
            number_of_octets = number_of_octets + 1;
        }

        for (int i = number_of_octets; i <= 3; i++) {
            orginal[i].subnetmask_binary = "00000000";
            orginal[i].subnetmask_decimal = 0;
        }
    }
    cout << "\n\nMaska w systemie dziesietnym: " << orginal[0].subnetmask_decimal << "." << orginal[1].subnetmask_decimal << "." << orginal[2].subnetmask_decimal << "." << orginal[3].subnetmask_decimal;
    cout << "\nMaska w systemie binarnym: " << orginal[0].subnetmask_binary << "." << orginal[1].subnetmask_binary << "." << orginal[2].subnetmask_binary << "." << orginal[3].subnetmask_binary;
    cout << "\n test " << orginal[1].octet_binary[2] << " ";
    }


    //wyliczanie adresu podsieci
    for (int i = 0; i <= 3; i++) {
        if (orginal[i].subnetmask_binary == "11111111") {
            sub_by_mask[i].octet_binary = orginal[i].octet_binary;
            sub_by_mask[i].octet_decimal = orginal[i].octet_decimal;
        }
        else if (orginal[i].subnetmask_binary == "00000000") {
            sub_by_mask[i].octet_binary = "00000000";
            sub_by_mask[i].octet_decimal = 0;
        }
        else {
            // poprawione nawiasy w warunku
            for (int j = 0; j <= 7; j++) {
                if ((orginal[i].subnetmask_binary[j] == '1') && (orginal[i].octet_binary[j] == '1')) {
                    sub_by_mask[i].octet_binary += '1';
                }
                else {
                    sub_by_mask[i].octet_binary += '0';
                }
            }
            cout << "\n\ntest dlugosci: " << sub_by_mask[i].octet_binary.length();
            sub_by_mask[i].octet_decimal = ToDecimal(sub_by_mask[i].octet_binary);
        }
    }


    cout << "\n\nAdres IP podsieci w systemie dziesietnym: " << sub_by_mask[0].octet_decimal << "." << sub_by_mask[1].octet_decimal << "." << sub_by_mask[2].octet_decimal << "." << sub_by_mask[3].octet_decimal;
    cout << "\nAdres IP podsieci w systemie binarnym: " << sub_by_mask[0].octet_binary << "." << sub_by_mask[1].octet_binary << "." << sub_by_mask[2].octet_binary << "." << sub_by_mask[3].octet_binary;

}



int main()
{
    int  i, option;
    bool control;

    control = true;

    while (control = true) {

        cout << "\nOPCJE";
        cout << "\n--------------";
        cout << "\n1. Klasa i Maska";
        cout << "\n2. Adres podsieci na podstawie maski";
        cout << "\n3. Exit";
        cout << "\n: ";
        cin >> option;

        switch (option) {
            case 1:
            {
                cout << "\nPodaj ip";
                flaga_type = 0;
                ChooseIP();
                cout << "\n----------------------------------";
                if (orginal[0].octet_decimal > 223) {

                    cout << "\nProgram nie obsluguje klas wyzszych od C";
                    break;
                }
                else  IpClass(orginal[0].octet_binary);
            }
            break;

            case 2:
            {
                cout << "\nPodaj ip";
                flaga_type = 0;
                ChooseIP();
                cout << "\n----------------------------------";
                SubnetByMask();

            }

            case 3:
            {
                return 0;
            }
            break;

            default:
            {
                cout << "\nWcisnij 1, 2 lub 3";
            }
            break;

        }
        cout << "\n";

    }




    _getch();

    return 0;
}

