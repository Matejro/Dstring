// Lab3Dstring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(suppress : 4996)
#include <iostream>
#include <sstream>
#include<cmath>
using namespace std;

class DString {
protected:
    char* sp;
    void copy(const DString& b);

public:
    DString();
    DString(const DString& b);
    DString(const char* s);
    ~DString();
    operator const char* (); // operator rzutowanie Dstring na const char*
    DString& operator=(const DString& b); // operator przypisania typu a= b
    friend ostream& operator<<(ostream&, DString&); //operacja typu cout<< a
    friend istream& operator>>(istream&, DString&); // operacja typu cin >> a
    DString operator+(const DString&) const; //operator dodawania a+b
    DString operator+(char*) const; //operator dodawanie typu a+”tekst”
    DString& operator+=(const DString&); // dodawanie typu a = a+b
    int operator==(const DString& other); // operator porównania czy oba teksty sa takie same
    int operator!=(const char* other); // operator porównania czy oba teksty s¹ró¿ne
    char& operator[] (int i); // zwraca wybrany zanak z tesktu ->a[3] –czwarty znak w tekœcie
    char* asChars(); // metoda zwracajaca dostêp do tablicyznaków
    int asInt(); // konwersja z tesktu na int np: “123” da 123 ale “123ala” nie powinna zwrocic 123 tylko informacje ze nie da sie przeprowadzic konwersji
    int empty(); //czyszczenie tekstu
    int IsEmpty(); // sprawdzanie czy tekst jest pusty
    int getLen(); // d³ugoœæ tekstu
    DString IsString(char*); // szukanie podciagu w teksie w razie znalezienia zwraca jako nowy obiekt
    DString GetString(int, int); // zwraca nowy obiekt zawierajacy wyciety tekst 1 argument – od ktorego znaku, 2 argument ile znakow
    DString TrimRight(int); // obciecie z prawej strony iloœci znaków podanych jako argument
    DString TrimLeft(int); //obciecie z lewej strony iloœæ znaków podanych jako argument
};

void DString::copy(const DString& b) {
    if (this->sp != nullptr)delete[] sp;
    this->sp = new char[strlen(b.sp) + 1];
    strcpy(this->sp, b.sp);
   
};

DString::DString() {
    this->sp = NULL;
};

DString::DString(const DString& b) {
    this->sp = new char [strlen(b.sp)+1];
    strcpy(this->sp, b.sp);
};

DString::DString(const char* s) {
    this->sp = new char[strlen(s) + 1];
    strcpy(this->sp, s);

    //strcpy(sp, s);
};
DString::~DString() {
    if (this->sp != nullptr)delete[] sp;
}

DString::operator const char* () {
    //const char* result = (const char*)sp;
    //return result;
    return static_cast<const char*>(sp);
};

DString& DString::operator=(const DString& b) {
    if (this!= &b) {
        delete[] this->sp;
        this->sp = new char[strlen(b.sp) + 1];
        strcpy(this->sp, b.sp);
        return *this;
    }
};

DString DString::operator+(const DString& b) const
{
    char* s = new char[strlen(this->sp) + strlen(b.sp) + 1];
    strcpy(s, this->sp);
    strcat(s, b.sp);
    DString c(s);
    delete[] s;
    return c;
};

DString DString::operator+(char* b) const {
    char* s = new char[strlen(this->sp) + strlen(b) + 1];
    strcpy(s, this->sp);
    strcat(s, b);
    DString c(s);
    delete[] s;
    return c;
};

DString& DString::operator+=(const DString& b) {
    
    if (this->sp != NULL) {
        char* mys = "-";
        char* temp = new char[strlen(this->sp) + 1];
        temp = this->sp;
        this->sp = nullptr;
        delete[] this->sp;
        cout << temp<<endl;
        this->sp = new char[strlen(temp) + strlen(b.sp) + 1];
        strcpy(this->sp, temp);
        strcat(this->sp, b.sp);
        delete[] temp;
        return *this;
    }
    else {
        this->sp = new char[strlen(b.sp) + 1];
        strcpy(this->sp, b.sp);
        return *this;
    };
};


ostream& operator<<(ostream& os, DString& a) {
    os << a.sp;
    return os;
};

istream& operator>>(istream& is, DString& b) {
    is >> b.sp;
    return is;
};

char& DString::operator[](int i){
    return *(sp+i);
};

int DString::operator==(const DString& other) {
    if (this->sp == other.sp)return 1;
    else return 0;
};

int DString::operator!=(const char* other) {
    if (this->sp != other) return 1;
    else return 0;
};

char* DString::asChars() {
    return this->sp;
};

int DString::asInt() {
    bool liczba = true;
    int result = 0;
    int len = (int)strlen(this->sp);
    for (int i = 0; i < len; i++) {
        if (!isdigit(this->sp[i])) {
            liczba = false;
            break;
        }
        else {
            result += ((int)*(this->sp + i) - '0') * pow(10, len-1-i);
        };

    };
    if (liczba) return result;
    else {
        cout << "Przeprowadzenie konwersji jest niemozliwe" << endl;
        return 0;
    };

};

int DString::empty() {
    delete[] this->sp;
    return 0;
};

int DString::IsEmpty() {
    if (this->sp != NULL)return 0;
    else return 1;
};

int DString::getLen() {
    return strlen(this->sp);
};

DString DString::IsString(char* b) {
    if (strstr(this->sp, b)) {
        DString c(b);
        return c;
    }
    else return *this;

};// szukanie podciagu w teksie w razie znalezienia zwraca jako nowy obiekt

DString DString::GetString(int a, int b) {

    if (b-a + 1 > int(strlen(this->sp)) - 1) {
        cout << "Wpisane wartosci sa poza zakresem\n";
        return *this;
    }
    else {
        char* result = new char[b + 1];
        for (int i = a; i < a+b; i++) {          
            result[i-a]=(this->operator[](i));
        };
        result[b] = 0;
        DString c(result);
        delete[] result;
        return c;
    }    
};

DString DString::TrimRight(int a) {
   return this->GetString(strlen(this->sp) - a, a);
};

DString DString::TrimLeft(int a) {
    return this->GetString(0, a);
};

int main()
{
   
    DString imie("Mateusz");
    DString nazwisko("Mrowca");
    DString imienazwisko;
    DString podciag("owca");
    imienazwisko = imie;
    imienazwisko += nazwisko;
    cout << imienazwisko;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
