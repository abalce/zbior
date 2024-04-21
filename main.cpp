#include"no.h"

int main() {
    Punkt* p1 = new Punkt(2,3);
    Punkt* p2 = new Punkt(3,5);
    Punkt* p3 = new Punkt(1,2);

    Zbior z;

    z.dodajPunkt(p1);
    z.dodajPunkt(p2);
    z.dodajPunkt(p3);

    cout<<z;
    z.drukuj();
    z.usun(2);
    z.drukuj();

    cout<<"zbior p: "<<endl;

    Zbior o;
    o=z.wiekszeNiz(1);
    o.drukuj();

    KolorowyZbior kol("zielony");
    kol.dodajPunkt(new Punkt(4, 5));  // Dodaj nowy punkt, który nie jest przechowywany w innym zbiorze
    kol.drukuj();

    cout<<"///////lista"<<endl;

    vector<Zbior*> lista;
    lista.push_back(&z);
    lista.push_back(&o);
    lista.push_back(&kol);

    for(auto& zbior : lista)
    {
        KolorowyZbior* kolorowyZbior = dynamic_cast<KolorowyZbior*>(zbior);
        if(kolorowyZbior)  // Jeśli rzutowanie jest udane, wywołaj metodę drukuj() klasy KolorowyZbior
        {
            kolorowyZbior->drukuj();
        }
        else  // W przeciwnym razie wywołaj metodę drukuj() klasy Zbior
        {
            zbior->drukuj();
        }
    }

    z.usunwszystko();
    o.usunwszystko();
    kol.usunwszystko();  // Teraz możemy bezpiecznie usunąć wszystkie punkty z kol

    return 0;
}
