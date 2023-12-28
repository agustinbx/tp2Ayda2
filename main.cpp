#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
//#include <random>

using namespace std;
bool BackJornada(const vector<pair<int,int> >&TablaJornada,const vector<vector<int> >&TablaPuntajes,int n,int m,int&cotaG,int cotaA,vector<int>&Sol,vector<int>&SolA,int partido,int CantidadEstados);
bool ArbitroDisponible(const vector<int>&SolA,int arbitro, int partido);
int CalculaCotaInferior(const vector<pair<int,int> >&TablaJornada,const vector<vector<int> >&TablaPuntajes,vector<int>&SolA,int partido);
int main()
{
    vector<pair<int,int> > Fecha;
    Fecha.push_back(std::make_pair(1, 2));
    Fecha.push_back(std::make_pair(3, 4));

    vector<vector<int> > TablaPuntajes;

    std::vector<int> fila1;    //equipo 1
    fila1.push_back(0);
    fila1.push_back(7);
    fila1.push_back(8);

    TablaPuntajes.push_back(fila1);

    std::vector<int> fila2;    //equipo 2
    fila2.push_back(1);
    fila2.push_back(10);
    fila2.push_back(5);

    TablaPuntajes.push_back(fila2);

    std::vector<int> fila3;   //equipo 3
    fila3.push_back(4);
    fila3.push_back(6);
    fila3.push_back(9);

    TablaPuntajes.push_back(fila3);

    std::vector<int> fila4;    // equipo 4
    fila4.push_back(3);
    fila4.push_back(2);
    fila4.push_back(10);

    TablaPuntajes.push_back(fila4);

    vector<pair<int,int> > TablaJornada;// asigina la jornada actual previamente seleccionada.
/*
    int Cant_equipos;
    int Cant_arbitros;

    cout << "Ingrese la cantidad de equipos: ";
    cin >> Cant_equipos;

    cout << "Ingrese la cantidad de arbitros: ";
    cin >> Cant_arbitros;
*/
    int Cant_equipos = 4;
    int Cant_arbitros = 3;
    int MaximaPuntuacion=0;
    int MaximaActual = 0;
    int partido = 0;
    vector<int> Solucion;
    vector<int> SolucionActual;
    Solucion.resize(Cant_equipos/2);
    SolucionActual.resize(Cant_equipos/2);
    //vector<vector<int> > TablaPuntajes;
    //vector<pair<int,int> > TablaJornada;

    TablaJornada=Fecha;

    // Menu

/*
    int equipo1;
    int equipo2;
    cout << "Ingrese los partidos que se jugaran en una fecha determinada: "<<endl;
    cout <<endl;
    for (int i=1; i<= Cant_equipos/2; i++){
        cout << "Equipo: ";
        cin>> equipo1;
        cout<< "vs"<<endl;
        cout<<"Equipo: ";
        cin>> equipo2;
        cout<<endl;
        TablaJornada.push_back(make_pair(equipo1,equipo2));
    }


    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 10);

    for(int j=0; j < Cant_equipos; j++){
        vector<int> fila;
        for(int k=0; k < Cant_arbitros; k++){   // carga las puntuaciones de los equipos a los arbitros
            fila.push_back(dist(gen));
        }
        TablaPuntajes.push_back(fila);
    }

    for(int j=0; j < Cant_equipos; j++){
        for(int k=0; k < Cant_arbitros; k++){   // Muestra la matriz de las puntuaciones
            cout<<TablaPuntajes[j][k]<< " ";
        }
        cout<<endl;
    }


        cout<< "Partidos: "<<endl;
        for (int p=0; p<Cant_equipos/2; p++){
            cout<< TablaJornada[p].first<<" vs ";
            cout<< TablaJornada[p].second<<endl;
        }
*/

    cout<<endl;

    int CantidadEstados;
    BackJornada(TablaJornada,TablaPuntajes,Cant_equipos,Cant_arbitros,MaximaPuntuacion,MaximaActual,Solucion,SolucionActual,partido,CantidadEstados);
    cout<<"cantidad de estados: "<< CantidadEstados<<endl;
    cout<<"Mejor puntuacion: "<<MaximaPuntuacion<<endl;

    cout<<"Asignacion de arbitros: "<<endl;
    for (int j=0; j< Solucion.size(); j++){
        cout << "Partido "<< j+1 <<": Arbitro " << Solucion[j] <<" "<<endl;
    }
    cout << endl;
    return 0;
}

bool BackJornada(const vector<pair<int,int> >&TablaJornada,const vector<vector<int> >&TablaPuntajes,int n,int m,int&cotaG,int cotaA,vector<int>&Sol,vector<int>&SolA,int partido, int &CantidadEstados)
{
    CantidadEstados++;
    //el vector auxiliar SolA y Sol guardan un arreglo de enteros donde cada posicion representa un partido y el valor almacenado es el arbitro de ese mismo
    if(partido == (n/2))
    {
        for (int i=0; i<TablaJornada.size(); i++){  // Este for calcula la puntuacion actual
            int arbitro = SolA[i];
            cotaA += TablaPuntajes[TablaJornada[i].first - 1][arbitro-1] + TablaPuntajes[TablaJornada[i].second - 1][arbitro-1];
        }
        if(cotaA>cotaG)
        {
            cotaG=cotaA;
            Sol=SolA;
            return true;
        }

    }
    else
    {
        int arbitro=1;
        while(arbitro<=m)
        {
            if(ArbitroDisponible(SolA,arbitro, partido))
            {
                SolA[partido]=arbitro ;
                BackJornada(TablaJornada,TablaPuntajes,n,m,cotaG,cotaA,Sol,SolA,partido+1,CantidadEstados);    //Llamo a la función con partido+1
                SolA[partido]= 0;
            }
            arbitro++;
        }
    }
    return false;
}

bool ArbitroDisponible(const vector<int>& SolA, int arbitro, int partido) {
    for (unsigned int x=0; x < partido; x++) {
        if (SolA[x] == arbitro){
            return false;
        }
    }
     return true;
}
