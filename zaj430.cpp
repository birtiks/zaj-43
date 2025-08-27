#include <iostream>
 
using namespace std;
 
struct Para
{
    int dana;
    Para * nastepna;
 
    Para(int wartosc): dana(wartosc), nastepna(nullptr){}
};
 
class LinkedList
{
    public:
        LinkedList(): poczatek(nullptr){}
 
        ~LinkedList()
        {
            wyczysc();
        }
 
        void dodaj(int wartosc)
        {
            _rozmiar++;
            // Tworzymy zmeinna tymczasowa
            Para * nowaPara = new Para(wartosc);
 
            if(poczatek == nullptr)
            {
                // jezeli dodajemyu pierwsza pare to stanie sie ona poczatkiem naszej linked listy
                poczatek = nowaPara;
            }
 
            else
            {
                // tworzymy sobie nasza zmienna tymczasaowa
                Para * tmp = poczatek;
 
                while(tmp->nastepna != nullptr)
                {
                    // korzystajac z naszej zmiennej tymczasowej odczytujemy kolejne pary z linked listy az odczytamy ostatnia
                    // Dla ostatniej pary adres nastepnej pary bedzie null !!!
                    tmp = tmp->nastepna;
                }
                // Teraz tmp jest ostatnia para na naszej liscie i wpisujemy nowa pare jako nastepna po aktulanie ostatniej 
                // nowa para stala sie wlasnie ostatnia para w liscie
                tmp->nastepna = nowaPara;
            }
        }
 
        int& pobierz(int index)
        {
            // Tworzymy zmeinna tymczasowa
            Para * tmp = poczatek;
 
 
            // licznik sluzacy nam do liczenia na ktorej parze jestesmy
            int i = 0;
 
            while(tmp!=nullptr)
            {
                if (i == index)
                {
                    // jesli jestesmy na indexie ktory chcemy odczytac to go zwracamy
                    return tmp->dana;
                }
                // przeksakujemy na kolejna pare
                tmp = tmp->nastepna;
 
                // podbijamy licznik
                i++;
            }
 
            throw out_of_range("Out of bounds error");
        }
 
        int& operator [](int index)
        {
            return pobierz(index);
        }
 
        int rozmiar() const
        {
            return _rozmiar;
        }
 
        void operator +(LinkedList& lista)
        {
            for(int i = 0; i < lista.rozmiar();i++)
            {
                this->dodaj(lista[i]);
            }
        }
 
        void wyczysc()
        {
            // Tworzymy zmeinna tymczasowa
            Para * tmp = poczatek;
 
            while (tmp != nullptr)
            {
                // tworzymy zmienna pomocnicza to bedzie nasza nastepna para
                Para * nastepna = tmp->nastepna;
 
                // Zwalniamy pamiec
                delete tmp;
 
                // Nastepna para staje sie aktualna para
                tmp = nastepna;
                _rozmiar = 0;
            }
 
            poczatek = nullptr;
        }
 
        void wypisz() const
        {
            cout << "[ ";
            Para * tmp = poczatek;
            while(tmp != nullptr)
            {
                cout << tmp->dana;
                if(tmp->nastepna !=nullptr)
                {
                cout<< ", ";
                }
                tmp = tmp->nastepna;
            }
            cout << " ](rozmiar: "<< _rozmiar <<  ")"<<endl;
        }
 
    private:
        Para * poczatek;
        int _rozmiar{};
};
 
int main()
{
    LinkedList lista;
    lista.dodaj(4);
    lista.dodaj(8);
    lista.dodaj(12);
    lista.dodaj(20);
    lista.dodaj(-8);
 
    cout << "Pierwszy element listy: " << lista[0] << endl;
    cout << "Drugi element listy: " << lista[1] << endl;
 
    lista[1] = 5;
 
    cout << "Drugi element listy: " << lista[1] << endl;
 
    cout << "Rozmiar naszej Linked Listy: " << lista.rozmiar() << endl;
 
    lista.wypisz();
 
    LinkedList lista2;
    lista2.dodaj(1);
    lista2.dodaj(2);
    lista2.dodaj(3);
    lista2.dodaj(4);
    lista2.dodaj(5);
 
    lista + lista2;
 
    lista.wypisz();
 
    lista2.wyczysc();
 
    return 0;
}
 
 