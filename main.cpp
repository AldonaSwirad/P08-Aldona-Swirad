#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <iterator>
#include <string>
#include <time.h>
#include <algorithm>
#include <functional>

using namespace std;
void dostuffA();
void dostuffB();
void dostuffC();

class Triplet                          //klasa, aby moc stworzyc ciag trojelemenowy jako objekt
{
public:
    int f, s, t;
};
int find_numbersA(int tab[], int n, int m)
{
    cout <<"Algorytm 1"<<endl;
    clock_t start, stop;
    double czas;

    fstream file_out;
    file_out.open("triplets_exit.txt", ios::out);

    vector<Triplet> triplets;            //w tym wektorze beda magazynowane ciagi trojelementowe(z niego bede potem wypisywane)
    set<string> saveTriplets;         //zbior, gdzie beda przechowywane wartości ciagow, by uniknac ich powtorzenia
    string tas  ;                          //tas=triplet as a string, zmienna string sluzaca przekonwertowaniu ciagu liczb na tekst
    Triplet outputTriplet;                 //objekt, gdzie zapisany bedzie ciag trojelemenowy z wektora, jesli dany ciag sie nie powtarza

    start = clock();
    //pętla szukająca elementow ciagu
    for (int i=0; i<n-2; i++)                  //wez pierwszy element
    {
        for (int j=i+1; j<n-1; j++)               //wez drugi element
        {
            for(int k=j+1; k<n; k++)               //wez trzeci element
            {
                if(tab[i]+tab[j]+tab[k]==m)     //zobacz czy dany ciąg jest równy sumie
                {
                    tas=to_string(tab[i])+" : "+to_string(tab[j])+" : "+to_string(tab[k]);   //konwertowanie ciągu trojelementowego z typu int na string
                    if(saveTriplets.find(tas)==saveTriplets.end())                          //sprawdzanie czy dany ciąg znajduje się w zbiorze saveTriplets
                    {
                        saveTriplets.insert(tas);                                           //dodanie elementow z wektora tas do zbioru saveTriplets
                        outputTriplet.f = tab[i];                                           //przypisanie strukturze outputTriplet wartości
                        outputTriplet.s = tab[j];
                        outputTriplet.t = tab[k];
                        triplets.push_back(outputTriplet);                                    //dodanie elemwntow z outputTriplet do wektora triplets
                    }

                }
            }
        }
    }
    if (triplets.size() == 0)                   //liczba elementów w wektorze triplets jest równa liczbie kombinacji,
        //jeżeli elementów w wektorze jest 0 to nie wypisujemy kombinacji
    {
        cout<<"Liczba kombinacji: 0"<<endl;
        return 0;
    }
    cout <<"Mozliwe kombinacje: "<< endl;
    for(int i = 0; i< triplets.size(); i++)          //petla wypisujaca poszczgolne ciagi i liczbe kombinacji
    {
        cout <<" [ " << triplets[i].f <<" "<< triplets[i].s <<" "<< triplets[i].t<<" ] ";
    }
    cout<<endl<<"Liczba kombinacji: "<<triplets.size();    //liczba elementów w wektorze triplets jest równa liczbie kombinacji
    for(int i = 0; i< triplets.size(); i++)          //petla wypisujaca poszczgolne ciagi i liczbe kombinacji do pliku
    {
        file_out << triplets[i].f;
        file_out << triplets[i].s;
        file_out << triplets[i].t<<endl;
    }

    file_out.close();

    stop = clock();
    czas = (double)(stop - start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas: "<<czas<<" s"<<endl;
    ;
}

int find_numbersB(int tab[], int n, int m)
{
    cout <<"Algorytm 2"<<endl;
    clock_t start, stop;
    double czas;
    sort (tab, tab+n);                           // KONIECZNIE posortuj tablice, inaczej zacznie gubic niektore skrajne kombinacje
    fstream file_out;
    file_out.open("triplets_exit.txt", ios::out);

    vector<Triplet> triplets;            //w tym wektorze beda magazynowane ciagi trojelementowe(z niego bede potem wypisywane)
    set<string> saveTriplets;         //zbior, gdzie beda przechowywane wartości ciagow, by uniknac ich powtorzenia
    string tas  ;                          //tas=triplet as a string, zmienna string sluzaca przekonwertowaniu ciagu liczb na tekst
    Triplet outputTriplet;                 //objekt, gdzie zapisany bedzie ciag trojelemenowy z wektora, jesli dany ciag sie nie powtarza

    start = clock();
    //pętla szukająca elementow ciagu
    for (int i=0; i<n-2; i++)                 //wez pierwszy element
    {
        int j=i+1;                             // wez drugi element
        int k=n-1;                             // weź ostatni element
        while (j<k)                            // jeśli j<k(tablica posortowana, więc jest to prawda):
        {
            if(tab[i]+tab[j]+tab[k]==m)    //jak i+j+k=m to zapisz ciąg
            {

                tas=to_string(tab[i])+" : "+to_string(tab[j])+" : "+to_string(tab[k]);   //konwertowanie ciągu trojelementowego z int na string
                if(saveTriplets.find(tas)==saveTriplets.end())                          //sprawdzanie czy dany ciąg znajduje się w zbiorze saveTriplets
                {
                    saveTriplets.insert(tas);                                           //dodanie elemwntow z wektora tas do zbioru saveTriplets
                    outputTriplet.f = tab[i];                                           //przypisanie strukturze outputTriplet wartości
                    outputTriplet.s = tab[j];
                    outputTriplet.t = tab[k];
                    triplets.push_back(outputTriplet);                                    //dodanie elemwntow z outputTriplet do wektora triplets
                }
                j++;
                k--;

            }
            else if(tab[i]+tab[j]+tab[k]<m)     // jeśli i+j+k<m powiększ j, bo j mniejsze
            {
                j++;
            }
            else if(tab[i]+tab[j]+tab[k]>m)     // jeśli i+j+k<m pomniejsz k, bo k wieksze
            {
                k--;
            }
        }

    }

    if (triplets.size() == 0)                   //liczba elementów w wektorze triplets jest równa liczbie kombinacji, jeżeli elementów w wektorze jest 0 to nie wypisujemy kombinacji
    {
        cout<<"Liczba kombinacji: 0"<<endl;
        return 0;
    }
    cout <<"Mozliwe kombinacje: "<< endl;
    for(int i = 0; i< triplets.size(); i++)          //petla wypisujaca poszczgolne ciagi i liczbe kombinacji
    {
        cout <<" [ " << triplets[i].f <<" "<< triplets[i].s <<" "<< triplets[i].t<<" ] ";
    }
    cout<<endl<<"Liczba kombinacji: "<<triplets.size() ;    //liczba elementów w wektorze triplets jest równa liczbie kombinacji
    for(int i = 0; i< triplets.size(); i++)          //petla wypisujaca poszczgolne ciagi i liczbe kombinacji
    {
        file_out << triplets[i].f;
        file_out << triplets[i].s;
        file_out << triplets[i].t<<endl;
    }

    file_out.close();

    stop = clock();
    czas = (double)(stop - start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas: "<<czas<<" s"<<endl;

}

int main()
{
    char choice;
    cout<<"1.Sam/a chce wpisac tablice"<<endl;
    cout<<"2.Pobierz dane z gotowego pliku"<<endl;
    cout<<"3.Pobierz dane z pliku, gdzie dane zostaly wygenerowane losowo"<<endl;
    cout<<"Wpisz 1 lub 2 lub 3: "<<endl;
    cin >> choice;
    switch(choice)
    {
    case '1':
        dostuffA();
        break;
    case '2':
        dostuffB();
        break;
    case '3':
        dostuffC();
        break;
    default:
        cout<<"Nie ma takiej opcji w menu!";
    }

    return 0;
}

void dostuffA()
{
    int n, M;
    cout << "Ile elementow w tablicy:"<< endl;
    cin >> n;
    int arr[n];
    cout << "Wpisz liczby do tablicy: "<<endl;
    for (int i=0; i<n; i++)
    {
        cin>> arr[i];
    }
    cout << "Ciag 3-ch znakow ma byc rowny liczbie M = "<<endl;
    cin >> M;
    find_numbersA(arr, n, M);
    find_numbersB(arr, n, M);
}

void dostuffB()
{
    fstream file;
    int n=0, M, nr_lines=0 ;
    int i=0;
    int *arr;
    arr=new int [nr_lines];

    string line;
    file.open("random_from_0_to_9.txt", ios::in);
    if(file.good()==false)
    {
        cout<<"Nie mozna otworzyc pliku!";
    }
    else
    {
        while( !file.eof() )
        {
            getline(file, line);
            arr[nr_lines]=atof(line.c_str());
            nr_lines++;
        }

        cout << "Ciag 3-ch znakow ma byc rowny liczbie M = "<<endl;
        cin >> M;
        for (int i=0; i<nr_lines; i++)
        {
            file>>arr[i];
        }
        cout <<"Tablica z ktorej pobrano dane: "<< endl;
        for (int i=0; i<nr_lines; i++)
        {
            cout << arr[i];
        }
        cout << endl;
        find_numbersA(arr, nr_lines, M);
        find_numbersB(arr, nr_lines, M);
    }
    file.close();
}

void dostuffC()
{
    srand ( ( unsigned )time ( NULL ) );
    fstream file_random;
    int n, M;
    cout << "Ile elementow w tablicy:"<< endl;
    cin >> n;
    cout << "Ciag 3-ch znakow ma byc rowny liczbie M = "<<endl;
    cin >> M;
    file_random.open("new_random.txt", ios::out);
    file_random.open("new_random.txt", ios::in);
    int *arr = new int[n];
    for(int i=0; i<n; i++)  //zapis liczb losowych do tablicy
    {
        arr[i] = rand() % 10;
    }
    for(int i=0; i<n; i++) // zapis tablicy do pliku
    {
        file_random << arr[i];
    }

    file_random.open("new_random.txt", ios::in);

    for(int i=0; i<n; i++)
    {
        file_random >> arr[i];
    }
    cout <<"Tablica z ktorej pobrano dane: "<< endl;
    for(int i=0; i<n; i++)
    {
        cout << arr[i];
    }
    cout << endl;

    find_numbersA(arr, n, M);
    find_numbersB(arr, n, M);
    file_random.close();
}

