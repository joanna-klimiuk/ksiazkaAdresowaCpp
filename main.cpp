#include <iostream>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

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
    cout << "9. Zakoncz program" << endl << endl;

    cout << "Wybierz opcje: ";
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

void przyporzadkujDaneDoAdresata (string tekstWejsciowy, vector <Adresat> &adresaci)
{
    int licznik = 0;
    Adresat nowyAdresat;

    nowyAdresat.id = atoi(rozbijDane(tekstWejsciowy, licznik).c_str());
    nowyAdresat.imie = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.nazwisko = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.nrTel = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.adres = rozbijDane(tekstWejsciowy, licznik);
    nowyAdresat.email = rozbijDane(tekstWejsciowy, licznik);

    adresaci.push_back(nowyAdresat);
}

void pobierzDane(vector <Adresat> &adresaci)
{
    string linia, tekstWejsciowy;
    ifstream daneZPliku("KsiazkaAdresowa.txt", ios::in | ios::app);

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

            przyporzadkujDaneDoAdresata(tekstWejsciowy, adresaci);
        }
    }
    daneZPliku.close();
}

void zapiszWszystkieDane(vector <Adresat> &adresaci)
{
    ofstream daneZPliku("KsiazkaAdresowa.txt", ios::out);

    for(auto adresat : adresaci)
    {
        daneZPliku << adresat.id << '|';
        daneZPliku << adresat.imie << '|';
        daneZPliku << adresat.nazwisko << '|';
        daneZPliku << adresat.nrTel << '|';
        daneZPliku << adresat.adres << '|';
        daneZPliku << adresat.email << '|' << endl;
    }

    daneZPliku.close();
}

void zapiszDaneJednegoAdresata(Adresat nowyAdresat)
{
    fstream daneZPliku;
    daneZPliku.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    daneZPliku << nowyAdresat.id << '|';
    daneZPliku << nowyAdresat.imie << '|';
    daneZPliku << nowyAdresat.nazwisko << '|';
    daneZPliku << nowyAdresat.nrTel << '|';
    daneZPliku << nowyAdresat.adres << '|';
    daneZPliku << nowyAdresat.email << '|' << endl;

    daneZPliku.close();
}

void dodajAdresata (vector <Adresat> &adresaci)
{
    string imie, nazwisko, nrTel, adres, email;
    int id = 1;
    Adresat nowyAdresat;

    id = !adresaci.size() ? 1 : adresaci.back().id + 1;

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

    zapiszDaneJednegoAdresata(nowyAdresat);

    cout << "Dodano adresata";
    Sleep(1000);
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

    for (int i = 0; i < (int) adresaci.size(); i++)
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

     for (int i = 0; i < (int) adresaci.size(); i++)
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
        for (int i = 0; i < (int) adresaci.size(); i++)
        {
            wyswietlDane(adresaci, i);
        }

        system("pause");
    }
}

void usunAdresata(vector <Adresat> &adresaci)
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
                adresaci.erase(itrUsuwanegoAdresata);
                zapiszWszystkieDane(adresaci);
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
}

void edytujAdresata (vector <Adresat> &adresaci)
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
                zapiszWszystkieDane(adresaci);
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
    char wybor;
    pobierzDane(adresaci);

    while (true)
    {
        wyswietlMenuGlowne();
        wybor = wczytajZnak();

        switch (wybor)
        {
        case '1':
            dodajAdresata(adresaci);
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
            usunAdresata(adresaci);
            break;

        case '6':
            edytujAdresata(adresaci);
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
    return 0;
}
