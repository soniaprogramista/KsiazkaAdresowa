include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include<thread>
#include<vector>
#include<stdlib.h>
using namespace std;

struct DaneOsobowe
{
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;
};
string wczytajLinie()
{
    string input = "";
    getline (cin, input);
    return input;
}

char wczytajZnak()
{
    string input;
    char znak;

    while(true)
    {
        getline (cin, input);
        if (input.length() == 1)
        {
            znak = input[0];
            break;
        }
        else
            cout << "To nie jest pojedyczny znak"<<endl;
    }
    return znak;
}
void zapiszDoPlikuZaktualizowaneOsoby(vector <DaneOsobowe> &ksiazkaAdresowa)
{
    ofstream plik;
    plik.open("ksiazka_adresowa.txt");

    if(plik.good() == true)
    {
        for(int i = 0; (unsigned)i < ksiazkaAdresowa.size(); i++)
        {
            plik << ksiazkaAdresowa[i].id << '|';
            plik << ksiazkaAdresowa[i].imie << '|';
            plik << ksiazkaAdresowa[i].nazwisko << '|';
            plik << ksiazkaAdresowa[i].numerTelefonu << '|';
            plik << ksiazkaAdresowa[i].email << '|';
            plik << ksiazkaAdresowa[i].adres << '|'<<endl;
        }
        plik.close();
    }
    else
    {
        cout << "Brak dostepu do pliku"<<endl;
    }
}

void dopiszOsobeDoPliku(DaneOsobowe adresat)
{
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::app);

    if(plik.good() == true)
    {
        plik << adresat.id << '|';
        plik << adresat.imie << '|';
        plik << adresat.nazwisko << '|';
        plik << adresat.numerTelefonu << '|';
        plik << adresat.email << '|';
        plik << adresat.adres << '|' << endl;
        plik.close();
        cout << "Adresat zostal dodany" <<endl;
        this_thread::sleep_for(2000ms);
    }
    else
    {
        cout << "Brak dostepu do pliku"<<endl;
    }
}

void dopiszOsobeDoKsiazki(vector <DaneOsobowe> &ksiazkaAdresowa)
{
    DaneOsobowe adresat;

    if(ksiazkaAdresowa.empty() == true)
    {
        adresat.id = 1;
    }
    else
    {
        adresat.id = ksiazkaAdresowa.back().id + 1;
    }
    cout << "Podaj imie"<<endl;
    adresat.imie = wczytajLinie();
    cout << "Podaj nazwisko"<<endl;
    adresat.nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu"<<endl;
    adresat.numerTelefonu = wczytajLinie();
    cout << "Podaj adres email"<<endl;
    adresat.email = wczytajLinie();
    cout << "Podaj adres" <<endl;
    adresat.adres = wczytajLinie();

    ksiazkaAdresowa.push_back(adresat);
    dopiszOsobeDoPliku(adresat);
}

DaneOsobowe pobierzDanePojedynczegoAdresata(string daneAdresataOddzieloneKreskami)
{
    DaneOsobowe adresat;
    string pojedynczaDanaAdresata;
    int numerPojedynczejDanejAdresat = 1;

    for(int i = 0; (unsigned)i < daneAdresataOddzieloneKreskami.length(); i++)
    {
        if(daneAdresataOddzieloneKreskami[i] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzieloneKreskami[i];
        }
        else
        {
            switch(numerPojedynczejDanejAdresat)
            {
            case 1:
                adresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 3:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresat++;
        }
    }
    return adresat;
}

void wczytajOsobyZPliku(vector <DaneOsobowe> &ksiazkaAdresowa)
{
    DaneOsobowe adresat;
    string daneAdresataOddzieloneKreskami = "";
    fstream plik;
    plik.open("ksiazka_adresowa.txt",ios::in);

    if(plik.good() == true)
    {
        while(getline(plik, daneAdresataOddzieloneKreskami))
        {
            adresat = pobierzDanePojedynczegoAdresata(daneAdresataOddzieloneKreskami);
            ksiazkaAdresowa.push_back(adresat);
        }
        plik.close();
    }
}
void usunAdresata(vector <DaneOsobowe> &ksiazkaAdresowa)
{
    int idDoUsuniecia;
    char potwierdzenieUsuniecia;
    int i;

    if(ksiazkaAdresowa.size() > 0)
    {
        cout << "Podaj id adresata, ktorego chcesz usunac"<<endl;
        cin >> idDoUsuniecia;
        cin.sync();

        for(i = 0; (unsigned)i < ksiazkaAdresowa.size(); i++)
        {
            if(ksiazkaAdresowa[i].id == idDoUsuniecia)
            {
                cout << "Czy na pewno chcesz usunac adresata o ID: " << idDoUsuniecia <<  "(t/n)?" <<endl;
                potwierdzenieUsuniecia = wczytajZnak();

                if(potwierdzenieUsuniecia == 't')
                {
                    ksiazkaAdresowa.erase(ksiazkaAdresowa.begin() + i);
                    zapiszDoPlikuZaktualizowaneOsoby(ksiazkaAdresowa);
                    cout << "Osoba zostala usunieta"<<endl;
                    this_thread::sleep_for(2000ms);
                    break;
                }
                else
                {
                    cout << "Adresat nie zostal usuniety"<<endl;
                    this_thread::sleep_for(2000ms);
                    break;
                }
            }
            if(ksiazkaAdresowa[i].id != idDoUsuniecia && (unsigned)i == (ksiazkaAdresowa.size()-1))
            {
                cout << "Brak adresata o takim ID w ksiazce"<<endl;
                this_thread::sleep_for(2000ms);
            }
        }
    }
    else
        cout << "Brak adresatow do usuniecia"<<endl;
    this_thread::sleep_for(2000ms);
}

void edytujAdresata(vector <DaneOsobowe> &ksiazkaAdresowa)
{
    int idDoEdycji;
    char wyborZMenu;
    int i;

    cout << "Podaj id adresata, ktorego chcesz edytowac"<<endl;
    cin >> idDoEdycji;
    cin.sync();

    for(i = 0; (unsigned)i < ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].id == idDoEdycji)
        {
            system("clear");
            cout << ">>CO CHCESZ EDYTOWAC?<<"<<endl<<endl;
            cout << "1. Imie"<<endl;
            cout << "2. Nazwisko"<<endl;
            cout << "3. Numer telefonu"<<endl;
            cout << "4. Adres email"<<endl;
            cout << "5. Adres zamieszkania"<<endl;
            cout << "9. Wroc do menu glownego"<<endl;

            wyborZMenu = wczytajZnak();

            switch(wyborZMenu)
            {
            case '1':
            {
                cout << "Wpisz nowe imie:"<<endl;
                ksiazkaAdresowa[i].imie = wczytajLinie();
                cout << "Imie zostalo edytowane" <<endl;
                zapiszDoPlikuZaktualizowaneOsoby(ksiazkaAdresowa);
                this_thread::sleep_for(2000ms);
                break;
            }
            case '2':
            {
                cout << "Wpisz nowe nazwisko:"<<endl;
                ksiazkaAdresowa[i].nazwisko = wczytajLinie();
                cout << "Nazwisko zostalo edytowane" <<endl;
                zapiszDoPlikuZaktualizowaneOsoby(ksiazkaAdresowa);
                this_thread::sleep_for(2000ms);
                break;
            }
            case '3':
            {
                cout << "Wpisz nowy numer telefonu:"<<endl;
                ksiazkaAdresowa[i].numerTelefonu = wczytajLinie();
                cout << "Numer telefonu zostal edytowany" <<endl;
                zapiszDoPlikuZaktualizowaneOsoby(ksiazkaAdresowa);
                this_thread::sleep_for(2000ms);
                break;
            }
            case '4':
            {
                cout << "Wpisz nowy adres email:"<<endl;
                ksiazkaAdresowa[i].email = wczytajLinie();
                cout << "Email zostal edytowany" <<endl;
                zapiszDoPlikuZaktualizowaneOsoby(ksiazkaAdresowa);
                this_thread::sleep_for(2000ms);
                break;
            }
            case '5':
            {
                cout << "Wpisz nowy adres zamieszkania:"<<endl;
                ksiazkaAdresowa[i].adres = wczytajLinie();
                cout << "Adres zostal edytowany" <<endl;
                zapiszDoPlikuZaktualizowaneOsoby(ksiazkaAdresowa);
                this_thread::sleep_for(2000ms);
                break;
            }
            case '9':
                break;
            }
            break;
        }
        if(ksiazkaAdresowa[i].id != idDoEdycji && (unsigned)i == (ksiazkaAdresowa.size()-1))
        {
            cout << "Brak adresata o takim ID w ksiazce"<<endl;
            this_thread::sleep_for(2000ms);
        }
    }
}

void wyswietlWszystkich(vector <DaneOsobowe> ksiazkaAdresowa)
{
    for(int i = 0; (unsigned)i < ksiazkaAdresowa.size(); i++)
    {
        cout << ksiazkaAdresowa[i].id <<endl;
        cout << ksiazkaAdresowa[i].imie <<endl;
        cout << ksiazkaAdresowa[i].nazwisko <<endl;
        cout << ksiazkaAdresowa[i].numerTelefonu <<endl;
        cout << ksiazkaAdresowa[i].email <<endl;
        cout << ksiazkaAdresowa[i].adres<<endl<<endl;
    }
    system("read -n 1 -s -p\" Press any key to continue...\"");
}
void znajdzPoImieniu(vector <DaneOsobowe> ksiazkaAdresowa)
{
    string poszukiwaneImie;
    string znalezioneImie;
    cout << "Podaj imie adresata, ktorego chcesz odszukac" <<endl;
    poszukiwaneImie = wczytajLinie();

    for(int i = 0; (unsigned)i < ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].imie == poszukiwaneImie)
        {
            znalezioneImie = poszukiwaneImie;
            cout << ksiazkaAdresowa[i].id<<endl;
            cout << ksiazkaAdresowa[i].imie<<endl;
            cout << ksiazkaAdresowa[i].nazwisko<<endl;
            cout << ksiazkaAdresowa[i].numerTelefonu<<endl;
            cout << ksiazkaAdresowa[i].email<<endl;
            cout << ksiazkaAdresowa[i].adres<<endl<<endl;
        }
    }
    if(znalezioneImie != poszukiwaneImie)
    {
        cout << "Nie znaleziono osoby o takim imieniu w ksiazce adresowej"<<endl;
    }
    system("read -n 1 -s -p\" Press any key to continue...\"");
}
void znajdzPoNazwisku(vector <DaneOsobowe> ksiazkaAdresowa)
{
    string poszukiwaneNazwisko;
    string znalezioneNazwisko;
    cout << "Podaj nazwisko adresata, ktorego chcesz odszukac" <<endl;
    poszukiwaneNazwisko = wczytajLinie();

    for(int i = 0; (unsigned)i < ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].nazwisko == poszukiwaneNazwisko)
        {
            znalezioneNazwisko = poszukiwaneNazwisko;
            cout << ksiazkaAdresowa[i].id<<endl;
            cout << ksiazkaAdresowa[i].imie<<endl;
            cout << ksiazkaAdresowa[i].nazwisko<<endl;
            cout << ksiazkaAdresowa[i].numerTelefonu<<endl;
            cout << ksiazkaAdresowa[i].email<<endl;
            cout << ksiazkaAdresowa[i].adres<<endl<<endl;
        }
    }
    if(znalezioneNazwisko != poszukiwaneNazwisko)
    {
        cout << "Nie znaleziono osoby o takim nazwisku w ksiazce adresowej"<<endl;
    }
    system("read -n 1 -s -p\" Press any key to continue...\"");
}

int main()
{
    vector <DaneOsobowe> ksiazkaAdresowa;
    char wyborZMenu;
    wczytajOsobyZPliku(ksiazkaAdresowa);
    while(1)
    {
        system("clear");
        cout << ">>KSIAZKA ADRESOWA<<"<<endl<<endl;
        cout << "1. Dopisz osobe do ksiazki adresowej"<<endl;
        cout << "2. Wyszukaj osobe po imieniu"<<endl;
        cout << "3. Wyszukaj osobe po nazwisku"<<endl;
        cout << "4. Wyswietl wszystkie osoby"<<endl;
        cout << "5. Edytuj osobe"<<endl;
        cout << "6. Usun osobe"<<endl;
        cout << "9. Zakoncz program"<<endl;

        wyborZMenu = wczytajZnak();

        switch(wyborZMenu)
        {
        case '1':
            dopiszOsobeDoKsiazki(ksiazkaAdresowa);
            break;
        case '2':
            znajdzPoImieniu(ksiazkaAdresowa);
            break;
        case '3':
            znajdzPoNazwisku(ksiazkaAdresowa);
            break;
        case '4':
            wyswietlWszystkich(ksiazkaAdresowa);
            break;
        case '5':
            edytujAdresata(ksiazkaAdresowa);
            break;
        case '6':
            usunAdresata(ksiazkaAdresowa);
            break;
        case '9':
            exit(0);
            break;
        }
    }
}
