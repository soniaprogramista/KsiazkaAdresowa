#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
#include<thread>
#include<vector>
#include<stdlib.h>
using namespace std;

struct Adresat
{
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;
    int idZalogowanengoUzytkownika;
};

struct Uzytkownik
{
    string login, haslo;
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
void zapiszDoPlikuZaktualizowaneOsoby(vector <Adresat> &ksiazkaAdresowa)
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

void dopiszOsobeDoPliku(Adresat adresat)
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

void dopiszOsobeDoKsiazki(vector <Adresat> &ksiazkaAdresowa)
{
    Adresat adresat;

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

Adresat pobierzDanePojedynczegoAdresata(string daneAdresataOddzieloneKreskami)
{
    Adresat adresat;
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

void wczytajOsobyZPliku(vector <Adresat> &ksiazkaAdresowa)
{
    Adresat adresat;
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
void usunAdresata(vector <Adresat> &ksiazkaAdresowa)
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

void edytujAdresata(vector <Adresat> &ksiazkaAdresowa)
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

void wyswietlWszystkich(vector <Adresat> ksiazkaAdresowa)
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
void znajdzPoImieniu(vector <Adresat> ksiazkaAdresowa)
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
void znajdzPoNazwisku(vector <Adresat> ksiazkaAdresowa)
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
void zapiszDoPlikuZaktualizowanychUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    ofstream plik;
    plik.open("uzytkownicy.txt");

    if(plik.good() == true)
    {
        for(int i = 0; (unsigned)i < uzytkownicy.size(); i++)
        {
            plik << uzytkownicy[i].id << '|';
            plik << uzytkownicy[i].login << '|';
            plik << uzytkownicy[i].haslo << '|';
            plik << endl;
        }
        plik.close();
    }
    else
    {
        cout << "Brak dostepu do pliku"<<endl;
    }
}

Uzytkownik pobierzDanePojedynczegoUzytkownika(string daneUzytkownikaOddzieloneKreskami)
{
    Uzytkownik uzuytkownikPobierany;
    string pojedynczaDanaUzytkownika;
    int numerPojedynczejDanejUzytkownika = 1;

    for(int i = 0; (unsigned)i < daneUzytkownikaOddzieloneKreskami.length(); i++)
    {
        if(daneUzytkownikaOddzieloneKreskami[i] != '|')
        {
            pojedynczaDanaUzytkownika += daneUzytkownikaOddzieloneKreskami[i];
        }
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzuytkownikPobierany.id = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzuytkownikPobierany.login = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzuytkownikPobierany.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
        }
    }
    return uzuytkownikPobierany;
}

void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownikWczytywany;
    string daneUzytkownikaOddzieloneKreskami = "";
    fstream plik;
    plik.open("uzytkownicy.txt",ios::in);

    if(plik.good() == true)
    {
        while(getline(plik, daneUzytkownikaOddzieloneKreskami))
        {
            uzytkownikWczytywany = pobierzDanePojedynczegoUzytkownika(daneUzytkownikaOddzieloneKreskami);
            uzytkownicy.push_back(uzytkownikWczytywany);
        }
        plik.close();
    }
}

int zarejestruj(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownikDodawany;
    string nazwaUzytkownika;
    string haslo;
    
    cout << "Podaj nazwe uzytkownika" << endl;
    nazwaUzytkownika = wczytajLinie();
    
    for (int i =0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].login == nazwaUzytkownika)
        {
            cout << "Taka nazwa juz istnieje. Podaj inna:" << endl;
            nazwaUzytkownika = wczytajLinie();
            i = 0;
        }
    }
    
    cout << "Podaj haslo" << endl;
    haslo = wczytajLinie();

    uzytkownikDodawany.login = nazwaUzytkownika;
    uzytkownikDodawany.haslo = haslo;
    uzytkownikDodawany.id = uzytkownicy.size() + 1;
    uzytkownicy.push_back(uzytkownikDodawany);
    cout << "Uzytkownik zarejestrowany" << endl;
    this_thread::sleep_for(4000ms);
    
    return uzytkownicy.size() + 1;
}

int zaloguj(vector <Uzytkownik> uzytkownicy)
{
    string podanyLogin;
    string podaneHaslo;
    
    cout << "Podaj login" << endl;
    podanyLogin = wczytajLinie();
    
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (podanyLogin == uzytkownicy[i].login)
        {
            for (int j =0; j <3; j++)
            {
                cout << "Podaj haslo" <<endl;
                podaneHaslo = wczytajLinie();
                if (podaneHaslo == uzytkownicy[i].haslo)
                {
                    cout << "Uzytkownik zalogowany" << endl;
                    this_thread::sleep_for(2000ms);
                    return uzytkownicy[i].id;
                }else
                {
                    cout << "Haslo nieprawidlowe. Pozostalo Ci: " << 2-j << "prob." <<endl;
                }
            }
            cout << "Podales 3 razy niepoprawne haslo. Poczekaj 5s i sprobuj ponownie"<<endl;
            this_thread::sleep_for(5000ms);
            return  0;
        }
    }
    cout << "Login niepoprawny" << endl;
    this_thread::sleep_for(2000ms);
    return 0;
}
void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika, int iloscUzytkownikow)
{
    string noweHaslo;
    cout << "Podaj nowe haslo" <<endl;
    noweHaslo = wczytajLinie();
    
    for (int i =0; i < iloscUzytkownikow; i++)
    {
        if (idZalogowanegoUzytkownika == uzytkownicy[i].id)
        {
            uzytkownicy[i].haslo = noweHaslo;
            cout << "Haslo zostalo zmienione" <<endl;
            this_thread::sleep_for(2000ms);
        }
    }
    zapiszDoPlikuZaktualizowanychUzytkownikow(uzytkownicy);
}

int main()
{
    char wyborZMenu;
        int iloscUzytkownikow = 0;;
        int idZalogowanegoUzytkownia = 0;
        vector <Adresat> ksiazkaAdresowa;
        vector <Uzytkownik> uzytkownicy;
        iloscUzytkownikow = uzytkownicy.size();
        wczytajUzytkownikowZPliku(uzytkownicy);
        
        while(1)
        {
            if (idZalogowanegoUzytkownia == 0)
            {
                system("clear");
                cout << ">>MENU GLOWNE<<"<<endl<<endl;
                cout << "1. Zarejestruj sie"<<endl;
                cout << "2. Zaloguj sie"<<endl;
                cout << "9. Zakoncz program"<<endl;
                
                wyborZMenu = wczytajZnak();
                
                switch(wyborZMenu)
                {
                    case '1':
                        iloscUzytkownikow = zarejestruj(uzytkownicy);
                        zapiszDoPlikuZaktualizowanychUzytkownikow(uzytkownicy);
                        break;
                    case '2':
                        idZalogowanegoUzytkownia = zaloguj(uzytkownicy);
                        break;
                    case '9':
                        exit(0);
                        break;
                }
            }else
            {
                system("clear");
                        cout << ">>KSIAZKA ADRESOWA<<"<<endl<<endl;
                        cout << "1. Dopisz osobe do ksiazki adresowej"<<endl;
                        cout << "2. Wyszukaj osobe po imieniu"<<endl;
                        cout << "3. Wyszukaj osobe po nazwisku"<<endl;
                        cout << "4. Wyswietl wszystkie osoby"<<endl;
                        cout << "5. Edytuj osobe"<<endl;
                        cout << "6. Usun osobe"<<endl;
                        cout << "7. Zmien haslo"<<endl;
                        cout << "8. Wyloguj sie"<<endl;
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
                        
                        break;
                    case '6':
                        
                        break;
                    case '7':
                        zmienHaslo(uzytkownicy, idZalogowanegoUzytkownia, iloscUzytkownikow);
                        break;
                    case '8':
                        idZalogowanegoUzytkownia = 0;
                        break;
                    case '9':
                        exit(0);
                        break;
                }
                
            }
        }
    }
