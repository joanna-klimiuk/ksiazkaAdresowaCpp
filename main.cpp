#include <iostream>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};

struct Adresat
{
    string imie, nazwisko, nrTel, adres, email;
    int id;
};

char wczytajZnak ()
{
    string daneWejsciowe = "";
    char znak = {0};

    while (true)
    {
        cin.sync();
        getline (cin, daneWejsciowe);

        if (daneWejsciowe.length() == 1)
        {
            znak = daneWejsciowe[0];
            break;
        }

        else
            cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

string wczytajLinie()
{
    string tekstWejsciowy;

    cin.sync();
    getline(cin, tekstWejsciowy);

    return tekstWejsciowy;
}

void wyswietlMenuGlowne()
{
    system("cls");
    cout << "Ksiazka adresowa" << endl << "MENU PROGRAMU" << endl << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3. Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "9. Wyloguj sie" << endl << endl;

    cout << "Wybierz opcje: ";
}

void wyswietlMenuLogowaniaIRejestracji()
{
    system("cls");
    cout << "Ksiazka adresowa" << endl << "Logowanie i rejestracja" << endl << endl;
    cout << "1. Rejestracja" << endl;
    cout << "2. Logowanie" << endl;
    cout << "9. Zakoncz program" << endl << endl;

    cout << "Wybierz opcje: ";
}

void zapiszDaneJednegoUzytkownika (Uzytkownik nowyUzytkownik)
{
    fstream daneZPliku;
    daneZPliku.open("KsiazkaAdresowa_uzytkownicy.txt", ios::out | ios::app);

    daneZPliku << nowyUzytkownik.idUzytkownika << '|';
    daneZPliku << nowyUzytkownik.login << '|';
    daneZPliku << nowyUzytkownik.haslo << '|' << endl;

    daneZPliku.close();
}

void zapiszDaneWszystkichUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    fstream daneZPliku;
    daneZPliku.open("KsiazkaAdresowa_uzytkownicy.txt", ios::out);

    for(int i = 0; i < uzytkownicy.size(); i++)
    {
        daneZPliku << uzytkownicy[i].idUzytkownika << '|';
        daneZPliku << uzytkownicy[i].login << '|';
        daneZPliku << uzytkownicy[i].haslo << '|' << endl;
    }
    daneZPliku.close();
}

string rozbijDane (string tekstWejsciowy, int &licznik)
{
    string odczytaneDane = "";

    while (tekstWejsciowy[licznik] != '|' && licznik < (int) tekstWejsciowy.size())
    {
        odczytaneDane += tekstWejsciowy[licznik];
        licznik++;
    }
    licznik ++;

    return odczytaneDane;
}

int przyporzadkujDaneDoAdresata (string tekstWejsciowy, vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    int licznik = 0;
    int idUzytkownikawKsiazce;
    int ostatniNrId;
    Adresat nowyAdresat;

    nowyAdresat.id = atoi(rozbijDane(tekstWejsciowy, licznik).c_str());
    idUzytkownikawKsiazce = atoi(rozbijDane(tekstWejsciowy, licznik).c_str());
    nowyAdresat.imie = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.nazwisko = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.nrTel = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.adres = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.email = rozbijDane(tekstWejsciowy, licznik);

    if(idUzytkownikawKsiazce == idZalogowanegoUzytkownika)
    {
        adresaci.push_back(nowyAdresat);
    }

    return ostatniNrId = nowyAdresat.id;
}

void przyporzadkujDaneDoUzytkownika (string tekstWejsciowy, vector <Uzytkownik> &uzytkownicy)
{
    int licznik = 0;
    Uzytkownik nowyUzytkownik;

    nowyUzytkownik.idUzytkownika = atoi(rozbijDane(tekstWejsciowy, licznik).c_str());
    nowyUzytkownik.login = rozbijDane(tekstWejsciowy, licznik);
    nowyUzytkownik.haslo = rozbijDane(tekstWejsciowy, licznik);

    uzytkownicy.push_back(nowyUzytkownik);
}

void pobierzDaneUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    string linia;
    fstream daneZPliku;
    string tekstWejsciowy;

    daneZPliku.open("KsiazkaAdresowa_uzytkownicy.txt", ios::in | ios::app);

    if(daneZPliku.good() == false)
    {
        cout << "Brak danych do wczytania lub bledna sciezka dostepu";
        Sleep(1000);
    }

    else
    {
        while(getline(daneZPliku, linia))
        {
            tekstWejsciowy = linia;
            przyporzadkujDaneDoUzytkownika(tekstWejsciowy, uzytkownicy);
        }
    }
    daneZPliku.close();
}

int pobierzDane(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    int najwyzszyNrId = 0;
    string linia, tekstWejsciowy;
    ifstream daneZPliku("KsiazkaAdresowa.txt", ios::in);

    if(!daneZPliku.good())
    {
        cout << "Brak danych do wczytania lub bledna sciezka dostepu";
        Sleep(1000);
    }

    else
    {
        while(getline(daneZPliku, linia))
        {
            tekstWejsciowy = linia;
            najwyzszyNrId = przyporzadkujDaneDoAdresata(tekstWejsciowy, adresaci, idZalogowanegoUzytkownika);
        }
    }
    daneZPliku.close();

    return najwyzszyNrId;
}

void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    string login, haslo;
    size_t i = 0;

    nowyUzytkownik.idUzytkownika = (uzytkownicy.size() > 0) ? uzytkownicy.back().idUzytkownika + 1 : 1;

    system("cls");
    cout << "Podaj login: ";
    cin >> login;

    while (i < uzytkownicy.size())
    {
        if (uzytkownicy[i].login == login)
        {
            system("cls");
            cout << "Taki login istnieje juz w bazie. Wybierz inny login: ";
            cin >> login;
        }

        else
            i++;
    }

    cout << "Podaj haslo: ";
    cin >> haslo;

    nowyUzytkownik.login = login;
    nowyUzytkownik.haslo = haslo;

    uzytkownicy.push_back(nowyUzytkownik);
    zapiszDaneJednegoUzytkownika(nowyUzytkownik);

    cout << "Dodano uzytkownika";
    Sleep (600);
}

int zalogujUzytkownika(vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    int nrUzytkownika;
    bool czyUzytkownikJestWBazie = false;

        cout << "Podaj nazwe uzytkownika: ";
        cin >> login;

    for (size_t i = 0; i < uzytkownicy.size(); i++)
    {
        if (login == uzytkownicy[i].login)
        {
            czyUzytkownikJestWBazie = true;
            nrUzytkownika = i;
        }
    }

    if (!czyUzytkownikJestWBazie)
    {
        cout << "Brak uzytkownika o danym loginie. ";
        Sleep(600);
        return 0;
    }

    for (int k = 0; k < 3; k++)
        {
            cout << "Podaj haslo. Pozostalo " << 3 - k << " prob: ";
            cin >> haslo;

            if (haslo == uzytkownicy[nrUzytkownika].haslo)
            {
                cout << "Zalogowano uzytkownika";
                Sleep(1000);
                return uzytkownicy[nrUzytkownika].idUzytkownika;
            }
        }
        cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba.";
        Sleep(3000);
        return 0;
}

void zmienHaslo (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;

    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for (size_t i = 0; i < uzytkownicy.size(); i++)
    {
        if (idZalogowanegoUzytkownika == uzytkownicy[i].idUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
        }
    }

    cout << "Haslo zostalo zmienione";
    zapiszDaneWszystkichUzytkownikow(uzytkownicy);
    Sleep(600);
}

int wyloguj(int idZalogowanegoUzytkownika, vector <Adresat> &adresaci)
{
    cout << "Czy na pewno chcesz sie wylogowac? aby potwierdzic, wcisnij t: ";

    if (tolower(wczytajZnak()) == 't')
    {
        cout << "Wylogowano uzytkownika";
        adresaci.clear();
        Sleep(600);
        return 0;
    }

    else
    {
        return idZalogowanegoUzytkownika;
    }
}

void zapiszDaneJednegoAdresata(Adresat nowyAdresat, int nrUzytkownika)
{
    fstream daneZPliku;
    daneZPliku.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    daneZPliku << nowyAdresat.id << '|';
    daneZPliku << nrUzytkownika << '|';
    daneZPliku << nowyAdresat.imie << '|';
    daneZPliku << nowyAdresat.nazwisko << '|';
    daneZPliku << nowyAdresat.nrTel << '|';
    daneZPliku << nowyAdresat.adres << '|';
    daneZPliku << nowyAdresat.email << '|' << endl;

    daneZPliku.close();
}

void zapiszWszystkieDanePoUsunieciu(vector <Adresat> &adresaci, int nrId)
{
    string linia, tekstWejsciowy;
    int licznik;
    Adresat wczytywanyAdresat;
    ifstream daneZPliku("KsiazkaAdresowa.txt", ios::in);
    ofstream plikTymczasowy("KsiazkaAdresowa_temp.txt", ios::out | ios::app);

    if(!daneZPliku.good())
    {
        cout << "Brak danych do wczytania lub bledna sciezka dostepu";
        Sleep(1000);
    }

    else
    {
        while(getline(daneZPliku, linia))
        {
            tekstWejsciowy = linia;
            licznik = 0;
            wczytywanyAdresat.id = atoi(rozbijDane(tekstWejsciowy, licznik).c_str());
            if (wczytywanyAdresat.id != nrId)
            {
                plikTymczasowy << tekstWejsciowy << endl;
            }
        }
    }
    daneZPliku.close();
    plikTymczasowy.close();

    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowa_temp.txt", "KsiazkaAdresowa.txt");
}

void zapiszWszystkieDanePoEdycji(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika, int numerEdytowanegoAdresata)
{
    string linia, tekstWejsciowy;
    int licznik;
    Adresat wczytywanyAdresat;
    ifstream daneZPliku("KsiazkaAdresowa.txt", ios::in);
    ofstream plikTymczasowy("KsiazkaAdresowa_temp.txt", ios::out | ios::app);

    if(!daneZPliku.good())
    {
        cout << "Brak danych do wczytania lub bledna sciezka dostepu";
        Sleep(1000);
    }

    else
    {
        while(getline(daneZPliku, linia))
        {
            tekstWejsciowy = linia;
            licznik = 0;
            wczytywanyAdresat.id = atoi(rozbijDane(tekstWejsciowy, licznik).c_str());

            if (wczytywanyAdresat.id != adresaci[numerEdytowanegoAdresata].id)
            {
                plikTymczasowy << tekstWejsciowy << endl;
            }

            else if (wczytywanyAdresat.id = adresaci[numerEdytowanegoAdresata].id)
            {
                plikTymczasowy << adresaci[numerEdytowanegoAdresata].id << '|';
                plikTymczasowy << idZalogowanegoUzytkownika << '|';
                plikTymczasowy << adresaci[numerEdytowanegoAdresata].imie << '|';
                plikTymczasowy << adresaci[numerEdytowanegoAdresata].nazwisko << '|';
                plikTymczasowy << adresaci[numerEdytowanegoAdresata].nrTel << '|';
                plikTymczasowy << adresaci[numerEdytowanegoAdresata].adres << '|';
                plikTymczasowy << adresaci[numerEdytowanegoAdresata].email << '|' << endl;
            }
        }
    }
    daneZPliku.close();
    plikTymczasowy.close();

    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowa_temp.txt", "KsiazkaAdresowa.txt");
}

int dodajAdresata (vector <Adresat> &adresaci, int najwyzszyNrId, int idZalogowanegoUzytkownika)
{
    string imie, nazwisko, nrTel, adres, email;
    int id = najwyzszyNrId + 1;
    Adresat nowyAdresat;

    nowyAdresat.id = id;

    system("cls");
    cout << "Dodawanie adresata" << endl;
    cout << "Id adresata: " << nowyAdresat.id << endl;

    cout << "Podaj imie: ";
    nowyAdresat.imie = wczytajLinie();

    cout << "Podaj nazwisko: ";
    nowyAdresat.nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu: ";
    nowyAdresat.nrTel = wczytajLinie();

    cout << "Podaj adres zamieszkania: ";
    nowyAdresat.adres = wczytajLinie();

    cout << "Podaj adres email: ";
    nowyAdresat.email = wczytajLinie();

    adresaci.push_back(nowyAdresat);

    zapiszDaneJednegoAdresata(nowyAdresat, idZalogowanegoUzytkownika);

    cout << "Dodano adresata";
    Sleep(1000);

    return najwyzszyNrId + 1;
}

void wyswietlDane (vector <Adresat> &adresaci, int numerAdresata)
{
    cout << adresaci[numerAdresata].id << ". " << adresaci[numerAdresata].imie << " " << adresaci[numerAdresata].nazwisko << endl;
    cout << "Numer telefonu: " << adresaci[numerAdresata].nrTel << endl;
    cout << "Adres zamieszkania: " << adresaci[numerAdresata].adres << endl;
    cout << "Adres email: " << adresaci[numerAdresata].email << endl << endl;
}

void wyszukajAdresataPoImieniu(vector <Adresat> &adresaci)
{
    string imie;
    bool czyAdresatJestWBazie = false;

    system("cls");
    cout << "Wyszukiwanie po imieniu" << endl;
    cout << "Podaj imie: ";
    cin >> imie;

    for (size_t i = 0; i < adresaci.size(); i++)
    {
        if (adresaci[i].imie == imie)
        {
            wyswietlDane(adresaci, i);
            czyAdresatJestWBazie = true;
        }
    }

    if (!czyAdresatJestWBazie)
    {
        cout << "Brak w ksiazce osob o takim imieniu" << endl;
    }

    system("pause");
}

void wyszukajAdresataPoNazwisku(vector <Adresat> &adresaci)
{
     string nazwisko;
     bool czyAdresatJestWBazie = false;

     system("cls");
     cout << "Wyszukiwanie po nazwisku" << endl;
     cout << "Podaj nazwisko do wyszukania: ";
     cin >> nazwisko;

     for (size_t i = 0; i < adresaci.size(); i++)
     {
         if (adresaci[i].nazwisko == nazwisko)
         {
             wyswietlDane(adresaci, i);
             czyAdresatJestWBazie = true;
         }
     }

     if (czyAdresatJestWBazie == false)
     {
         cout << "Brak w ksiazce osob o takim nazwisku" << endl;
     }
     system("pause");
}

void wyswietlWszystkichAdresatow (vector <Adresat> &adresaci)
{
    system("cls");

    if (adresaci.empty())
    {
        cout << "Ksiazka adresowa jest pusta";
        Sleep(600);
    }

    else
    {
        for (size_t i = 0; i < adresaci.size(); i++)
        {
            wyswietlDane(adresaci, i);
        }

        system("pause");
    }
}

int usunAdresata(vector <Adresat> &adresaci, int najwyzszyNrId)
{
    int nrId;
    bool czyIstniejeAdresat = false;
    vector <Adresat>::iterator itrUsuwanegoAdresata = adresaci.end();

    system("cls");
    cout << "Podaj Id adresata, ktorego chcesz usunac: ";
    cin >> nrId;

    for (itrUsuwanegoAdresata = adresaci.begin(); itrUsuwanegoAdresata != adresaci.end(); itrUsuwanegoAdresata++)
    {
        if (itrUsuwanegoAdresata -> id == nrId)
        {
            czyIstniejeAdresat = true;
            cout << "Aby potwierdzic usuniecie adresata, wcisnij t: ";

            if(tolower(wczytajZnak()) == 't')
            {
                if (itrUsuwanegoAdresata == adresaci.end() - 1)
                {
                    najwyzszyNrId--;
                }

                adresaci.erase(itrUsuwanegoAdresata);
                zapiszWszystkieDanePoUsunieciu(adresaci, nrId);
                cout << "Adresat zostal usuniety";
                Sleep(600);
                break;
            }

            else
            {
                cout << "Anulowano usuwanie adresata";
                Sleep(600);
            }
        }
    }

    if (!czyIstniejeAdresat)
    {
        cout << "brak adresata o takim id";
        Sleep(600);
    }

    return najwyzszyNrId;
}

void edytujAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    char wybor = {0};
    int nrId;
    int numerEdytowanegoAdresata = -1;

    system("cls");
    cout << "Podaj Id adresata, ktorego chcesz edytowac: ";
    cin >> nrId;

    for (int i = 0; i < (int) adresaci.size(); i++)
    {
        if (adresaci[i].id == nrId)
        {
            numerEdytowanegoAdresata = i;
        }
    }

    if (numerEdytowanegoAdresata == -1)
    {
        cout << "Brak adresata o takim id.";
        Sleep(600);
    }

    else
    {
        while (wybor != '9')
        {
            system("cls");
            cout << "Dane adresata, ktorego chcesz edytowac: " << endl;
            wyswietlDane(adresaci, numerEdytowanegoAdresata);

            cout << "Ktore dane chcesz edytowac?" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Adres zamieszkania" << endl;
            cout << "5. Adres email" << endl;
            cout << "9. Koniec edycji" << endl << endl;

            wybor = wczytajZnak();

            switch (wybor)
            {
            case '1':
                cout << "Podaj nowe imie: ";
                adresaci[numerEdytowanegoAdresata].imie = wczytajLinie();
                break;

            case '2':
                cout << "Podaj nowe nazwisko: ";
                adresaci[numerEdytowanegoAdresata].nazwisko = wczytajLinie();
                break;

            case '3':
                cout << "Podaj nowy numer telefonu: ";
                adresaci[numerEdytowanegoAdresata].nrTel = wczytajLinie();
                break;

            case '4':
                cout << "Podaj nowy adres zamieszkania: ";
                adresaci[numerEdytowanegoAdresata].adres = wczytajLinie();
                break;

            case '5':
                cout << "Podaj nowy adres email: ";
                adresaci[numerEdytowanegoAdresata].email = wczytajLinie();
                break;

            case '9':
                zapiszWszystkieDanePoEdycji(adresaci, idZalogowanegoUzytkownika, numerEdytowanegoAdresata);
                break;

            default:
                cout << "Nie ma takiej opcji w MENU. Wybierz ponownie";
                Sleep(600);
                break;
            }
        }
    }
}

int main()
{
    vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;

    char wybor;
    int idZalogowanegoUzytkownika = 0;
    int najwyzszyNrId;

    pobierzDaneUzytkownikow(uzytkownicy);

    while (true)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            wyswietlMenuLogowaniaIRejestracji();
            wybor = wczytajZnak();

            switch (wybor)
            {
            case '1':
                rejestracjaUzytkownika(uzytkownicy);
                break;

            case '2':
                idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy);
                najwyzszyNrId = pobierzDane(adresaci, idZalogowanegoUzytkownika);
                break;

            case '9':
                exit(0);
                break;

            default:
                cout << "Nie ma takiej opcji w MENU. Wybierz ponownie";
                Sleep(600);
                break;
            }
        }

        else
        {
            wyswietlMenuGlowne();
            wybor = wczytajZnak();

            switch (wybor)
            {
            case '1':
                najwyzszyNrId = dodajAdresata(adresaci, najwyzszyNrId, idZalogowanegoUzytkownika);
                break;

            case '2':
                wyszukajAdresataPoImieniu(adresaci);
                break;

            case '3':
                wyszukajAdresataPoNazwisku(adresaci);
                break;

            case '4':
                wyswietlWszystkichAdresatow(adresaci);
                break;

            case '5':
                najwyzszyNrId = usunAdresata(adresaci, najwyzszyNrId);
                break;

            case '6':
                edytujAdresata(adresaci, idZalogowanegoUzytkownika);
                break;

            case '7':
                zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
                break;

            case '9':
                idZalogowanegoUzytkownika = wyloguj(idZalogowanegoUzytkownika, adresaci);
                break;

            default:
                cout << "Nie ma takiej opcji w MENU. Wybierz ponownie";
                Sleep(600);
                break;
            }
        }
    }
    return 0;
}
