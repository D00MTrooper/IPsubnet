#include <iostream>
#include <string>
#include <math.h>
using namespace std;

 struct ip {
    int octet_decimal, mask_decimal, subnetmask_decimal;
    string octet_binary, mask_binary, subnetmask_binary;

};

ip orginal[4];
string binary;
int flaga1, flaga_type, decimal;

string AddZero(int amount){
 int to_add;

 to_add = 8 - amount;
 string supplement(to_add, '0');

 return supplement;


}

void ToBinary(int decimalToBinary)
{
    int bit, i, j, amount, to_add;
    int temp_binary[8]; // maksymalna liczba bitów potrzebna do zapisu liczby całkowitej

    if ((decimalToBinary != 0) && (decimalToBinary < 255)) {
        // zamiana na postać binarną
        for (i = 0; decimalToBinary > 0; i++) {
            bit = decimalToBinary % 2;
            temp_binary[i] = bit;
            decimalToBinary /= 2;
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
    } else if (decimalToBinary == 0) {
        binary = "00000000";
    }else if (decimalToBinary > 255) {
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
  cout << "\n\nMaska w systemie dziesiętnym: " << orginal[0].mask_decimal << "." << orginal[1].mask_decimal << "." << orginal[2].mask_decimal << "." << orginal[3].mask_decimal;
  cout << "\nMaska w systemie binarnym: " << orginal[0].mask_binary << "." << orginal[1].mask_binary << "." << orginal[2].mask_binary << "." << orginal[3].mask_binary;

}

int ToDecimal(string binaryToDecimal){
  string bit;
  int temp_decimal, x, wykladnik, amount, to_add, choice;

  wykladnik = 7;
  temp_decimal = 0;

  //sprawdzenie długości oktetu
  amount = binaryToDecimal.length();

  if (amount==8){
    for (int i=0; i<=7; i++){

      bit = binaryToDecimal.substr(i,1);

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
      binaryToDecimal = AddZero(amount) + binaryToDecimal;
      for (int i=0; i<=7; i++){

        bit = binaryToDecimal.substr(i,1);

        if (bit=="1"){
          x = pow(2,wykladnik-i);
        }
        else x = 0;

      temp_decimal=temp_decimal+x;
      }
      decimal = temp_decimal;
    }
    if (choice == 2) {
        binaryToDecimal = binaryToDecimal + AddZero(amount) ;
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

  binary = binaryToDecimal;

  return decimal;

  }


void ChooseIP(){

  int i, choice;

  if (flaga_type==0) {
    cout << "\nJak chcesz podac adres ip";
    cout << "\n--------------";
    cout << "\n1. w systemie dziesiętnym";
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
            cout << "\nOktet " << i + 1 << ":" << binary;
            cout << "\nOktet " << i + 1 << ": " << decimal;
            orginal[i].octet_decimal = decimal;
            orginal[i].octet_binary = binary;

          }

          cout << "\n\nAdres IP w systemie dziesiętnym: " << orginal[0].octet_decimal << "." << orginal[1].octet_decimal << "." << orginal[2].octet_decimal << "." << orginal[3].octet_decimal;
          cout << "\nAdres IP w systemie binarnym: " << orginal[0].octet_binary << "." << orginal[1].octet_binary << "." << orginal[2].octet_binary << "." << orginal[3].octet_binary;

        }
      break;
    }
  }
  if (flaga_type==1){
    cout << "\nJak chcesz podac maske podsieci";
cout << "\n--------------";
cout << "\n1. w systemie dziesiętnym";
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
          ToBinary(orginal[i].subnetmask_decimal);

          if (flaga1 == 1) {
              cout << "\nPodaj oktet jeszcze raz";
              i--;
              flaga1=0;
          } else {
              cout << "\nOktet " << i + 1 << ": " << binary;
              orginal[i].subnetmask_binary = binary;
          }

      }

      cout << "\nMaska podsieci w systemie dziesiętnym: " << orginal[0].subnetmask_decimal << "." << orginal[1].subnetmask_decimal << "." << orginal[2].subnetmask_decimal << "." << orginal[3].subnetmask_decimal;
      cout << "\nMaska podsieci w systemie binarnym: " << orginal[0].subnetmask_binary << "." << orginal[1].subnetmask_binary << "." << orginal[2].subnetmask_binary << "." << orginal[3].subnetmask_binary;
    }
  break;
  case 2:
    {
      for (i = 0; i<=3; i++){

        cout << "\nPodaj " << i + 1 << " oktet: ";
        cin >> orginal[i].subnetmask_binary;

        ToDecimal(orginal[i].subnetmask_binary);
        cout << "\nOktet " << i + 1 << ":" << binary;
        cout << "\nOktet " << i + 1 << ": " << decimal;
        orginal[i].subnetmask_decimal = decimal;
        orginal[i].subnetmask_binary = binary;

      }

      cout << "\n\nMaska podsieci w systemie dziesiętnym: " << orginal[0].subnetmask_decimal << "." << orginal[1].subnetmask_decimal << "." << orginal[2].subnetmask_decimal << "." << orginal[3].subnetmask_decimal;
      cout << "\nMaska podsieci w systemie binarnym: " << orginal[0].subnetmask_binary << "." << orginal[1].subnetmask_binary << "." << orginal[2].subnetmask_binary << "." << orginal[3].subnetmask_binary;

    }
  break;
}
  }

}

void SubnetByMask(){
  int choice, prefix, subnet_octet, subnet_bits, amount, number_of_octets;

  cout << "\nJak chcesz podac maske pod podsieci";
  cout << "\n1. W formie binarnej lub dziesiętnej";
  cout << "\n2. W formie /...";
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

      subnet_octet = prefix/8;
      subnet_bits = prefix%8;

      for (int i = 0; i<=subnet_octet-1; i++){
        orginal[i].subnetmask_binary = "11111111";
        orginal[i].subnetmask_decimal = 255;
        number_of_octets = i;
      }

      if(subnet_bits != 0){
        string supplement(subnet_bits, '1');
        orginal[subnet_octet].subnetmask_binary = supplement + AddZero(subnet_bits);
        orginal[subnet_octet].subnetmask_decimal = ToDecimal(orginal[subnet_octet].subnetmask_binary);
        number_of_octets = number_of_octets+2;
      }

      for (int i = number_of_octets; i<=3; i++){
        orginal[i].subnetmask_binary = "00000000";
        orginal[i].subnetmask_decimal = 0;
      }
    }
  }

  cout << "\n\nMaska w systemie dziesiętnym: " << orginal[0].subnetmask_decimal << "." << orginal[1].subnetmask_decimal << "." << orginal[2].subnetmask_decimal << "." << orginal[3].subnetmask_decimal;
  cout << "\nMaska w systemie binarnym: " << orginal[0].subnetmask_binary << "." << orginal[1].subnetmask_binary << "." << orginal[2].subnetmask_binary << "." << orginal[3].subnetmask_binary;

}



int main()
{
    int  i, option;

    cout << "\nOpcje";
    cout << "\n--------------";
    cout << "\n1. Klasa i Maska";
    cout << "\n2. Adres podsieci na podstawie maski";
    cout << "\n3. Adres podsieci na podstawi liczby urządzen";
    cout << "\n: ";
    cin >> option;

    switch (option) {
      case 1:
      {
        cout << "\nPodaj ip";
        flaga_type = 0;
        ChooseIP();
        cout <<"\n----------------------------------";
        IpClass(orginal[0].octet_binary);
      }
      break;

      case 2:
      {
        cout << "\nPodaj ip";
        flaga_type = 0;
        ChooseIP();
        cout <<"\n----------------------------------";
        SubnetByMask();

      }
    }



    return 0;
}
