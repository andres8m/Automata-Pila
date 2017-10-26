#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
//#include <alloc.h>
#include <ctype.h>
#include <conio.h>
#include <vector>
#include <sstream>

using namespace std;

struct definicion{
    vector <string> estados;
    string estadoInicial;
    vector<string> alfabeto;
    string alfabetoCinta;
    string estadoAceptacion;
    string Z0;
};

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
vector <string> info;
string activeState;
bool encontrado = false;



definicion automataDef;

void defineABCD()
{
    abcd.push_back("a");
    abcd.push_back("b");
    abcd.push_back("c");
}


//void defineVars()
//{
//    pila.push_back("Z0");
//    string iState = "q0";
//
//
//    transicion t1;
//    t1.estado = "q0";
//    t1.simbolo = "a";
//    t1.tope_pila = "Z0";
//
//    movimiento m1;
//    m1.estado = "q0";
//    m1.simbolo1 = "a";
//    m1.simbolo2 = "Z0";
//    t1.move = m1;
//
//
//    transicion t2;
//    t2.estado = "q0";
//    t2.simbolo = "a";
//    t2.tope_pila = "a";
//    movimiento m2;
//    m2.estado = "q0";
//    m2.simbolo1 = "a";
//    m2.simbolo2 = "a";
//    t2.move = m2;
//
//
//
//    transicion t3;
//    t3.estado = "q0";
//    t3.simbolo = "a";
//    t3.tope_pila = "b";
//
//    movimiento m3;
//    m3.estado = "q0";
//    m3.simbolo1 = "$";
//    m3.simbolo2 = "$";
//    t3.move = m3;
//
//
//
//    transicion t4;
//    t4.estado = "q0";
//    t4.simbolo = "b";
//    t4.tope_pila = "Z0";
//
//    movimiento m4;
//    m4.estado = "q0";
//    m4.simbolo1 = "b";
//    m4.simbolo2 = "Z0";
//    t4.move = m4;
//
//
//
//    transicion t5;
//    t5.estado = "q0";
//    t5.simbolo = "b";
//    t5.tope_pila = "b";
//
//    movimiento m5;
//    m5.estado = "q0";
//    m5.simbolo1 = "b";
//    m5.simbolo2 = "b";
//    t5.move = m5;
//
//
//
//
//    transicion t6;
//    t6.estado = "q0";
//    t6.simbolo = "b";
//    t6.tope_pila = "a";
//
//    movimiento m6;
//    m6.estado = "q0";
//    m6.simbolo1 = "$";
//    m6.simbolo2 = "$";
//    t6.move = m6;
//
//
//
//    transicion t7;
//    t7.estado = "q0";
//    t7.simbolo = "$";
//    t7.tope_pila = "Z0";
//
//    movimiento m7;
//    m7.estado = "q1";
//    m7.simbolo1 = "Z0";
//    m7.simbolo2 = "$";
//    t7.move = m7;
//
//
//    trsns.push_back(t1);
//    trsns.push_back(t2);
//    trsns.push_back(t3);
//    trsns.push_back(t4);
//    trsns.push_back(t5);
//    trsns.push_back(t6);
//    trsns.push_back(t7);
//}


movimiento buscarTransicion(string simbolo, string tope, string estado)
{
    int index = 0;
    encontrado = false;
    for(unsigned i=0; i<trsns.size(); ++i)
    {
        if( trsns.at(i).simbolo==simbolo && trsns.at(i).tope_pila==tope && trsns.at(i).estado==estado)
        {
            index=i;
            activeState = trsns.at(i).move.estado;
            encontrado = true;
        }
    }
    return trsns[index].move;
}

void insertarEnPila(movimiento mov1)
{
    if(mov1.simbolo2 != "$")
    {pila.push_back(mov1.simbolo2);}
    if(mov1.simbolo1 != "$")
    {pila.push_back(mov1.simbolo1);}

}

string quitarTope()
{
    string response = pila[pila.size()-1];
    pila.pop_back();
    return response;
}


vector<string> castStringsBySpace(string cadena)
{
    int index;
    string stt;
    for(int i=0; i<cadena.size();i++)
    {
        if(cadena[i] == '(')
        {
            index = i;

        }
    }

    stt.append(cadena.begin(), cadena.begin()+index);

    istringstream iss(stt);
    string ss;



    vector<string> tokens;
    while (getline(iss, ss, ' '))
    {
        tokens.push_back(ss);
    }

    return tokens;
}


vector<string> castStringsByComma(string cadena)
{

    istringstream iss(cadena);
    string ss;

    vector<string> tokens;
    while (getline(iss, ss, ','))
    {
        tokens.push_back(ss);
    }

//    for(int i=0; i<tokens.size();i++)
//    {
//        cout << tokens[i]<<"\n";
//    }
    return tokens;
}


string cleanStringParentesis(string cadena)
{
    int index;
    int lastIndex;
    string response;
    bool f1 =false;
    bool f2 = false;

    for(int i=0; i<cadena.size();i++)
    {
        if(cadena[i] == '(')
        {
            index = i;f1 = true;

        } else if(cadena[i] == ')')
        {lastIndex=i;f2=true;}
    }

    if(index<=0)
    {
        index = 0;
    }
    else
    {
        index=index+1;

    }

    if(!f1 || !f2)
    {
        response = "ERROR";
    }

    response.append(cadena.begin()+index, cadena.begin()+lastIndex);
    return response;
}



string cleanString(string cadena)
{
    int index;
    int lastIndex;
    string response;
    bool f1 =false;
    bool f2 = false;

    for(int i=0; i<cadena.size();i++)
    {
        if(cadena[i] == '{')
        {
            index = i;f1 = true;

        } else if(cadena[i] == '}')
        {lastIndex=i;f2=true;}
    }

    if(index<=0)
    {
        index = 0;
    }
    else
    {
        index=index+1;

    }

    if(!f1 || !f2)
    {
        response = "ERROR";
    }

    response.append(cadena.begin()+index, cadena.begin()+lastIndex);
    return response;
}

bool checkS(string cadena)
{
    bool response = false;
    if(cadena[0]=='S' || cadena[0]=='s')
    {
        return true;
    }
    return response;
}

bool checkS0(string cadena)
{
    bool response = false;
    if((cadena[0]=='S' || cadena[0]=='s') && cadena[1]=='0')
    {
        return true;
    }
    return response;
}

bool checkA(string cadena)
{
    bool response = false;
    if(cadena[0]=='A' || cadena[0]=='a')
    {
        return true;
    }
    return response;
}

bool checkAC(string cadena)
{
    bool response = false;
    if((cadena[0]=='A' || cadena[0]=='a') && (cadena[1]=='C' || cadena[1]=='c'))
    {
        return true;
    }
    return response;
}

bool checkT(string cadena)
{
    bool response = false;
    if(cadena[0]=='T' || cadena[0]=='t')
    {
        return true;
    }
    return response;
}

bool checkZ0(string cadena)
{
    bool response = false;
    if((cadena[0]=='Z' || cadena[0]=='z') && cadena[1]=='0')
    {
        return true;
    }
    return response;
}

bool readFile()
{
    bool response;
    string x;
    ifstream file("automata.txt");


    while(getline(file,x))
    {
        if( x[0]!='/' && x[1] != '+' )
        {
            info.push_back(x);
//            cout<<x<<"\n";
        }
    }

    if( checkS(info[0]) && checkS0(info[1]) && checkA(info[2]) && checkAC(info[3]) && checkT(info[4]) && checkZ0(info[5]))
    {
        response = true;

    }
    else
    {
        response = false;
    }

    string val = info[0];
    string clnStr = cleanString(val);
    vector <string> myStrs = castStringsByComma(clnStr);
    automataDef.estados = myStrs;

    string val2 = info[1];
    string clnStr2 = cleanString(val2);
    automataDef.estadoInicial = clnStr2;

    string val3 = info[2];
    string clnStr3 = cleanString(val3);
    vector <string> myStrs3 = castStringsByComma(clnStr3);
    automataDef.alfabeto = myStrs3;

    string val4 = info[3];
    string clnStr4 = cleanString(val4);
    automataDef.alfabetoCinta = clnStr4;

    string val5 = info[4];
    string clnStr5 = cleanString(val5);
    automataDef.estadoAceptacion = clnStr5;

    string val6 = info[5];
    string clnStr6 = cleanString(val6);
    automataDef.Z0 = clnStr6;

    return response;

//    for(int i=0; i<info.size();i++)
//    {
//        cout<< info[i] << "\n";
//    }
}

void readTransitions()
{
//    cout<<info.size();
    for(int i = 6; i<info.size();i++)
    {
//        cout<<info[i]<<"\n";
        string val = info[i];
        string clnStr = cleanStringParentesis(val);

        vector <string> myStrs = castStringsByComma(clnStr);

        vector <string> myStrs2 = castStringsBySpace(val);


        transicion ts;
        ts.estado = myStrs2[0];
        ts.simbolo = myStrs2[1];
        ts.tope_pila = myStrs2[2];


        movimiento mv;
        mv.simbolo1= myStrs[0];
        mv.simbolo2 = myStrs[1];
        mv.estado = myStrs[2];
        ts.move = mv;

        trsns.push_back(ts);

    }



//    cout<<"Movimientos"<<"\n";
//        for(int i=0; i<myStrs.size();i++)
//    {
//        cout<< myStrs[i] << "\n";
//    }
//
//    cout<<"Transiciones"<<"\n";
//    for(int i=0; i<myStrs2.size();i++)
//    {
//        cout<< myStrs2[i] << "\n";
//    }




}


int main()
{

    if(!readFile())
    {
        cout<<"Error en el archivo.";
        return 0;
    }
//    readFile();
    readTransitions();
    pila.push_back(automataDef.Z0);


    string cadena;
    cout << "Bienvenido, ingrese cadena a validar: " <<endl;



    getline (cin,cadena);
    cout << "Estado inicial de pila: " << pila.at(0)<<"\n"<<"\n"<<"\n";

    activeState = automataDef.estadoInicial;
    for(int i=0; i<cadena.length(); ++i)
    {

        string str;
        string tope = quitarTope();
        str.append(cadena,i,1);
        movimiento move = buscarTransicion(str, tope,activeState);
        if(!encontrado)
        {
            cout<<"No se puede realizar este movimiento: "<<str<<", "<<tope;
            i = cadena.length();
        } else{
            insertarEnPila(move);

            cout << "Iteracion #" <<i+1<< " |Ingresandor: " <<str<<", "<<tope <<"\n";
            for(int j=0; j<pila.size();j++)
            {
                cout << pila[j]<<"\n";
            }
            cout << "\n";
        }


    }
    if(encontrado)
    {
        cout<<"Se alcanzo el estado de aceptacion: "<<activeState;
    }
    getch();
    return 0;
}

//Hasta aqui

