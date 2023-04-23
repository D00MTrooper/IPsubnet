#include <iostream>
#include <string>
#include <math.h>
using namespace std;

 struct ip {
    int octet_decimal, mask_decimal;
    string octet_binary, mask_binary;

};

ip orginal[4];
string binary;
int flaga1, decimal;

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
        //sprawdzenie długości oktetu
        amount = binary.length();
        //uzupełnie oktetu o 0 z przodu jeśli to potrzbne
        if (amount < 8) {
            to_add = 8 - amount;
            string supplement(to_add, '0');
            binary = supplement + binary;
        }
    } else if (decimal == 0) {
        binary = "00000000";
    }else if (decimal > 255) {
        flaga1 = 1;
    }
}

void IpClass(string first_octet){
  string first_bit, second_bit;

  first_bit = first_octet.substr(0,1);
  second_bit = first_octet.substr(1,1);

  if(first_bit=="0"){
    cout <<"\n\nKlasa A";
    orginal[0].mask_binary = "11111111";
    orginal[1].mask_binary = "00000000";
    orginal[2].mask_binary = "00000000";
    orginal[3].mask_binary = "00000000";

    orginal[0].mask_decimal = 255;
    orginal[1].mask_decimal = 0;
    orginal[2].mask_decimal = 0;
    orginal[3].mask_decimal = 0;

  } else if((first_bit=="1")&&(second_bit=="0")){
    cout <<"\n\nKlasa B";
    orginal[0].mask_binary = "11111111";
    orginal[1].mask_binary = "11111111";
    orginal[2].mask_binary = "00000000";
    orginal[3].mask_binary = "00000000";

    orginal[0].mask_decimal = 255;
    orginal[1].mask_decimal = 255;
    orginal[2].mask_decimal = 0;
    orginal[3].mask_decimal = 0;

  } else if((first_bit=="1")&&(second_bit=="1")){
    cout <<"\n\nKlasa C";
    orginal[0].mask_binary = "11111111";
    orginal[1].mask_binary = "11111111";
    orginal[2].mask_binary = "11111111";
    orginal[3].mask_binary = "00000000";

    orginal[0].mask_decimal = 255;
    orginal[1].mask_decimal = 255;
    orginal[2].mask_decimal = 255;
    orginal[3].mask_decimal = 0;
  }
}

void ToDecimal(string binary){
  string bit;
  int temp_decimal, x, wykladnik, amount, to_add, choice;

  wykladnik = 7;
  temp_decimal = 0;

  //sprawdzenie długości oktetu
  amount = binary.length();

  if (amount==8){
    for (int i=0; i<=7; i++){

      bit = binary.substr(i,1);

      if (bit=="1"){
        x = pow(2,wykladnik-i);
      }
      else x = 0;

    temp_decimal=temp_decimal+x;
    }
    decimal = temp_decimal;

  } else if (amount<8){
    cout << "\nGdzie dodać zera";
    cout << "\n1.Z przodu";
    cout << "\n2.Z tylu";
    cout << "\n: ";
    cin >> choice;

    if (choice==1){
      to_add = 8 - amount;
      string supplement(to_add, '0');
      binary = supplement + binary;
      for (int i=0; i<=7; i++){

        bit = binary.substr(i,1);

        if (bit=="1"){
          x = pow(2,wykladnik-i);
        }
        else x = 0;

      temp_decimal=temp_decimal+x;
      }
      decimal = temp_decimal;
    }
  } else if (choice==2){
    to_add = 8 - amount;
    string supplement(to_add, '0');
    binary = binary + supplement;
    for (int i=0; i<=7; i++){

      bit = binary.substr(i,1);

      if (bit=="1"){
        x = pow(2,wykladnik-i);
      }
      else x = 0;

    temp_decimal=temp_decimal+x;
    }
    decimal = temp_decimal;
  }
  }


int main()
{
    int liczba, i, choice_ip;

    cout << "\nJak chcesz podac adres ip";
    cout << "\n--------------";
    cout << "\n1. w systemie dziesiętnym";
    cout << "\n2. w systemie binarnym";
    cout << "\n: ";
    cin >> choice_ip;

    switch (choice_ip) {
      case 1:
        {
          i = 0;
          for (i = 0; i <= 3; i++) {

              cout << "\nPodaj " << i + 1 << " oktet: ";
              cin >> orginal[i].octet_decimal;
              ToBinary(orginal[i].octet_decimal);

              if (flaga1 == 1) {
                  cout << "\nPodaj oktet jeszcze raz";
                  i--;
                  flaga1=0;
              } else {
                  cout << "\nOktet " << i + 1 << ": " << binary;
                  orginal[i].octet_binary = binary;
              }

          }

          cout << "\n\nAdres IP w systemie dziesiętnym: " << orginal[0].octet_decimal << "." << orginal[1].octet_decimal << "." << orginal[2].octet_decimal << "." << orginal[3].octet_decimal;
          cout << "\nAdres IP w systemie binarnym: " << orginal[0].octet_binary << "." << orginal[1].octet_binary << "." << orginal[2].octet_binary << "." << orginal[3].octet_binary;
        }
      break;
      case 2:
        {
          for (i = 0; i<=3; i++){

            cout << "\nPodaj " << i + 1 << " oktet: ";
            cin >> orginal[i].octet_binary;

            ToDecimal(orginal[i].octet_binary);
            cout << "\nOktet " << i + 1 << ": " << decimal;
            orginal[i].octet_decimal = decimal;

          }

          cout << "\n\nAdres IP w systemie dziesiętnym: " << orginal[0].octet_decimal << "." << orginal[1].octet_decimal << "." << orginal[2].octet_decimal << "." << orginal[3].octet_decimal;
          cout << "\nAdres IP w systemie binarnym: " << orginal[0].octet_binary << "." << orginal[1].octet_binary << "." << orginal[2].octet_binary << "." << orginal[3].octet_binary;

        }
      break;
    }
    return 0;
}
