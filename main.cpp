#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
//#include <alloc.h>
#include <ctype.h>
#include <conio.h>
#include <vector>

using namespace std;


struct movimiento {
    string simbolo1;
    string simbolo2;
    string estado;
};

struct transicion {
    string simbolo;
    string tope_pila;
    string estado;
    movimiento move;
};

vector <string> pila;
vector <transicion> trsns;
vector <string> abcd;

void defineABCD()
{
    abcd.push_back("a");
    abcd.push_back("b");
    abcd.push_back("c");
}

void defineVars()
{
    pila.push_back("Z0");
    string iState = "q0";


    transicion t1;
    t1.estado = "q0";
    t1.simbolo = "a";
    t1.tope_pila = "Z0";

    movimiento m1;
    m1.estado = "q0";
    m1.simbolo1 = "a";
    m1.simbolo2 = "Z0";
    t1.move = m1;


    transicion t2;
    t2.estado = "q0";
    t2.simbolo = "a";
    t2.tope_pila = "a";
    movimiento m2;
    m2.estado = "q0";
    m2.simbolo1 = "a";
    m2.simbolo2 = "a";
    t2.move = m2;



    transicion t3;
    t3.estado = "q0";
    t3.simbolo = "a";
    t3.tope_pila = "b";

    movimiento m3;
    m3.estado = "q0";
    m3.simbolo1 = "$";
    m3.simbolo2 = "$";
    t3.move = m3;



    transicion t4;
    t4.estado = "q0";
    t4.simbolo = "b";
    t4.tope_pila = "Z0";

    movimiento m4;
    m4.estado = "q0";
    m4.simbolo1 = "b";
    m4.simbolo2 = "Z0";
    t4.move = m4;



    transicion t5;
    t5.estado = "q0";
    t5.simbolo = "b";
    t5.tope_pila = "b";

    movimiento m5;
    m5.estado = "q0";
    m5.simbolo1 = "b";
    m5.simbolo2 = "b";
    t5.move = m5;




    transicion t6;
    t6.estado = "q0";
    t6.simbolo = "b";
    t6.tope_pila = "a";

    movimiento m6;
    m6.estado = "q0";
    m6.simbolo1 = "$";
    m6.simbolo2 = "$";
    t6.move = m6;



    transicion t7;
    t7.estado = "q0";
    t7.simbolo = "$";
    t7.tope_pila = "Z0";

    movimiento m7;
    m7.estado = "q1";
    m7.simbolo1 = "Z0";
    m7.simbolo2 = "$";
    t7.move = m7;


    trsns.push_back(t1);
    trsns.push_back(t2);
    trsns.push_back(t3);
    trsns.push_back(t4);
    trsns.push_back(t5);
    trsns.push_back(t6);
    trsns.push_back(t7);
}


movimiento buscarTransicion(string simbolo, string tope)
{
    int index = 0;
    for(unsigned i=0; i<trsns.size(); ++i)
    {
        if( trsns.at(i).simbolo==simbolo && trsns.at(i).tope_pila==tope)
        {
            index=i;
        }
    }
    return trsns[index].move;
}

void insertarEnPila(movimiento mov1)
{
    if(mov1.simbolo2!="$")
    {pila.push_back(mov1.simbolo2);}
    if(mov1.simbolo1!="$")
    {pila.push_back(mov1.simbolo1);}

}

string quitarTope()
{
    string response = pila[pila.size()-1];
    pila.pop_back();
    return response;
}






int main()
{
    defineVars();

    string cadena;
    cout << "Bienvenido, ingrese cadena a validar " <<endl;
    getline (cin,cadena);
    cout << "Estado inicial de pila: " << pila.at(0)<<"\n";


    for(int i=0; i<cadena.length(); ++i)
    {
        string str;
        string tope = quitarTope();
        str.append(cadena,i,1);
        movimiento move = buscarTransicion(str, tope);
        insertarEnPila(move);

        cout << "Iteracion #" <<i+1<<"\n";
        for(int j=0; j<pila.size();j++)
        {
            cout << pila[j]<<"\n";
        }
        cout << "\n";
    }

    return 0;
}

//Hasta aqui

