#ifndef UNTITLED6_NO_H
#define UNTITLED6_NO_H

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Punkt
{
    int x,y;
public:
    Punkt(int x,int y) : x(x), y(y) {}
    bool operator==(const Punkt& p) const
    {
        if(x==p.x && y==p.y) return true;
        return false;
    }
    int getx() const
    {
        return x;
    }
    int gety() const
    {
        return y;
    }
};

class Zbior
{
    vector<Punkt*> zbior;
public:
    Zbior()=default;
    void dodajPunkt(Punkt* p)
    {
        zbior.push_back(p);
    }

    Punkt* getPunkt(int index) const
    {
        if(index>=0 && index<zbior.size())
        {
            return zbior[index];
        }
        return nullptr;
    }

    int rozmiar() const
    {
        return zbior.size();
    }

    int get_maxx() const
    {
        int mx=0;
        for(const auto& p:zbior)
        {
            if(p->getx()>mx) mx=p->getx();
        }
        return mx;
    }
    int get_maxy() const
    {
        int my=0;
        for(const auto& p:zbior)
        {
            if(p->gety()>my) my=p->gety();
        }
        return my;
    }

    bool jest_punkt(const Punkt* p) const
    {
        for(const auto& q : zbior)
        {
            if(*q==*p) return true;
        }
        return false;
    }

    void drukuj() const
    {
        for(const auto& p : zbior)
        {
            cout<<"Punkt: ["<<p->getx()<<","<<p->gety()<<"]"<<endl;
        }
    }

    friend ostream& operator<<(ostream& os, const Zbior& z)
    {
        for(int i=0;i<z.get_maxy()+1;i++)
        {
            for(int j=0;j<z.get_maxx()+1;j++)
            {
                Punkt q(j,i);
                if(z.jest_punkt(&q))
                {
                    os<<"X";
                }
                else os<<".";
            }
            os<<endl;
        }
        return os;
    }

    friend istream& operator>>(istream& is, Zbior& z)
    {
        int x,y;
        cout<<"podaj x:";
        is>>x;
        cout<<"podaj y:";
        is>>y;
        z.dodajPunkt(new Punkt(x,y));
        return is;
    }

    void usun(int index)
    {
        if(index>=0 && index<zbior.size())
        {
            delete zbior[index]; //usun punkt
            zbior.erase(zbior.begin()+index); //usun wskaznik
        }
    }

    void usunwszystko()
    {
        for(auto& p : zbior)
        {
            delete p; //usun punkty
        }
        zbior.clear(); //usun wskazniki

    }

    //konstrukor kopiujacy
    Zbior(const Zbior& inny)
    {
        for(auto& p : inny.zbior)
        {
            zbior.push_back(new Punkt(p->getx(),p->gety()));
        }
    }
    //operator przypisania
    Zbior& operator=(const Zbior& inny)
    {
        //sprawdzanie czy to nie jest przypisanie do samego siebie

        if(this!=&inny)
        {
            usunwszystko();
            //skopiuj punkty z innego zbioru
            for(auto& p : inny.zbior)
            {
                zbior.push_back(new Punkt(p->getx(),p->gety()));
            }
        }
        return *this;
    }
    Zbior wiekszeNiz(int liczba) const
    {
        Zbior nowyZbior;
        for(auto& p: zbior)
        {
            if(p->getx()>liczba && p->gety()>liczba)
            {
                nowyZbior.dodajPunkt(new Punkt(p->getx(),p->gety()));
            }
        }
        return nowyZbior;
    }

    Zbior operator+(const Zbior& inny)
    {
        Zbior suma=*this; //skopiowanie biezacego zbioru

        for(auto& p : inny.zbior)
        {
            suma.dodajPunkt(new Punkt(p->getx(),p->gety()));
        }
        return suma;
    }

    virtual ~Zbior()
    {
        usunwszystko();
    }

};

class KolorowyZbior : public Zbior
{
    string kolor;
public:
    KolorowyZbior(const string& kolor) : kolor(kolor) {}

    void ustawkolor(const string& nowykolor)
    {
        kolor=nowykolor;
    }

    string pobierzkolor() const
    {
        return kolor;
    }

    void drukuj() const
    {
        cout<<"Kolor: "<<kolor<<endl;
        Zbior::drukuj();
    }
};







#endif //UNTITLED6_NO_H
