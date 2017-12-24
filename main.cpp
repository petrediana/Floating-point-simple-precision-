#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
int v[32],n, m, X[7], Y[7], X1[7];

void citire() ///Citirea efectiva a datelor
{
    cout<<"Introduceti partea intreaga a numarului: ";
    cin>>n;
    cout<<endl;
    cout<<"Introduceti partea fractionara a numarului: 0,";
    cin>>m;
    cout<<endl;
}

void Binar_PI(int k, int* x) /// Numarul intreg in binar
{
    if(k<0) k= -1 * k;
    int i, a=7;
    for(i=0; i<=7; i++)
    {
        x[a] = k & (1<<i); /// Shift
        if(x[a] != 0)
            x[a] = 1;
        a--;
    }
/// Vectorul dat prin parametrul x va contine numarul in codul binar de la stanga la dreapta
///x[0] fiind pozitia cea mai semnificativa, iar x[7] cea mai nesemnificativa
}
int Nr_Cif_m(int y) ///Numar cate cifre are nr m
{
    int nr = 0;
    while(y>0)
    {
        nr++;
        y=y/10;
    }
    return nr;
}

void Binar_PF() /// Partea fractionara in binar
{
    int Copie_m, nr = 0, nr_cif,i = 0;
    Copie_m = m;
    nr_cif = Nr_Cif_m(m);

    while( (Copie_m != pow(10,nr_cif)) && nr<8 ) ///Pun condiitle de oprire al calculelor
    {
        Copie_m *= 2; ///Inmultesc numarul cu baza
        if(Copie_m < pow(10,nr_cif)) /// Daca nu trec de numarul de cifre initial al lui m; in vector introduc astfel valoarea 0
        {
            Y[i] = 0;
            i++;
        }
        else /// In cazul in care numarul de cifre se mareste, in vector voi introduce valoarea 1 si aduc numarul la cate cifre are initial
        {
            Y[i] = 1;
            i++;
            if(Copie_m != pow(10,nr_cif))
                Copie_m -= pow(10,nr_cif);
        }
        nr++;
    }
    ///Verificarea de mai sus ma ajuta sa construiesc vectorul Y care contine numarul cu virgula in binar
    ///La fiecare verificare asigura corectitudinea algoritmului
}


int main()
{
    int i;
    citire();
    cout<<"Numarul: (" << n << "," << m <<")10 = (";
    if( n< 0) cout<<"-";
    Binar_PI(n,X);
    for(i=0; i<=7; i++)
        cout<<X[i];
    cout<<",";

    Binar_PF();
    for(i=0; i<=7; i++)
        cout<<Y[i];
    cout<<")2  //Reprezentat in baza 2";
    cout<<endl;
    cout<<endl; /// Afisez numarul initial in baza 2

    int Exp = 127, k = 1, E;

    i=0;
    while(X[i]==0) ///Caut unde este prima pozitie de 1 (caut de la stanga la dreapta)
    {
        k++;
        i++;
    }

    E = (8 - k) + Exp; ///Calculam exponentul
    //cout<<k;
    //cout<<endl;
    Binar_PI(n,X);
    cout<<"Numarul in virgula mobila: ";
    for(i=0; i<=k-1; i++)
    {
        if(X[i] != 0)
            cout<<X[i];
    }
    cout<<",";
    for(i=k; i<=7; i++)
        cout<<X[i];
    for(i=0; i<=7; i++)
        cout<<Y[i];
    cout<<" * 2^"<<8-k;
    cout<<endl;
    ///Afisez cum arata numarul in virgula mobila; respect formula (1,f)2 * 2^(8-k)
    if(n > 0) v[31] = 0; /// Semnul
    else
        v[31] = 1;

    int exponent = 30, mantisa = 22;
///Aranjez in vectorul v elementele pentru a respecta tabelul virgulei fixe
    Binar_PI(E,X1);
    for(i=0; i<=7; i++)
    {
        v[exponent] = X1[i];
        exponent--;

    } /// Calculez elementele v[30] ... v[23] adica exponentul deja calculat in baza 2

    Binar_PI(n,X);
    for(i=k; i<=7; i++)
    {
        v[mantisa] = X[i]; //cout<<v[mantisa];
        mantisa--;
    }
    for(i=0; i<=7; i++)
    {
        v[mantisa] = Y[i];
        mantisa--;
    } ///Aranjez mantisa in vectorul v; Mantisa este formata din elementele lui X impreuna cu elementele lui Y
/// ~Obs: pozitia k reprezinta prima pozitie in care se afla valoarea 1 in vectorul X
    cout<<endl;
    for(i=0; i<=33; i++)
        cout<<"-";
    cout<<endl;
    cout<<v[31]<<"|";
    for(i=30; i>=0; i--)
    {
        cout<<v[i];
        if(i==23)
            cout<<"|";
    } cout<<" //Reprezentarea sa";
    cout<<endl;
    for(i=0; i<=33; i++)
        cout<<"-";
        ///Afisez reprezentarea in virgula mobila pe 32 de biti a numarului respectiv
    getch();
    return 0;
}
