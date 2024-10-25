#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;
void database_in (string basededatos);
void database_out (int letras ,string texto);
string noticiero(string texto);
int main(){
string ubicacion="database/";
cout<<"escriba el anno de la base de datos analizar desde el 2010-2023"<<endl;
int año=0;cin>>año;
if(año>2023 || año<2010){
    cout<<"ingreso una fecha incorrecta"<<endl;
}
else{
    cout<<"ESTAS SEGURO QUE QUIERES ANALIZAR LA BASE DE DATOS "<<año<<" ?"<<endl; 
    cout<<"escriba 1 para SI o 0 para NO"<<endl;
    bool pass=false;cin>>pass;
    if(pass==true){
    database_in(ubicacion+to_string(año)+".txt");
    }
}

    return 0;
}



void database_in (string basededatos){
    ifstream database;
    string texto,url;
    int pass=0;
    long long int letras=0;
    static bool linea_año=false;
    bool identificador=false;
    database.open(basededatos, ios::in); 
    if (database.fail()){ 
        cout<<"Error al abrir el archivo";
        cout<<endl;
        return ;
    }
    while (!database.eof()){ 
      getline(database,texto); 
        if(linea_año==false){
             database_out(0,texto);
             linea_año=true;
             continue;
        }
        if(identificador==false && texto!="####"){
            url=texto;
        }
        if(texto=="####"){
            if(identificador==true){
                identificador=false;
                pass++;
            }
            else{
            identificador=true;
            pass++;
            continue;
            }
        }
        if(identificador==true) {
            for (int i = 0; i < texto.size(); ++i){ 
                if(isalnum(texto[i])){
                      letras++; 
                }
             }
        }
        
        if(pass==2){
        database_out(letras,url);
        pass=0;
        letras=0;
        }
    }

}

void database_out (int letras,string texto){ //funcion para agregar datos al txt
    ofstream database; 
    static bool inicio=true;
    static string año;
   database.open("clean.txt", ios::app); 
    if (database.fail()){ 
        cout<<"no se pudo abrir el archivo se va crear uno nuevo";
         database.open("clean.txt",ios::app);
    }
    if(inicio==true){
            database<<"año,"<<"noticiero,"<<"URL,"<<"letras"<<endl;
            año=texto;
            inicio=false;
        }
    else if(inicio==false){
            database<<año<<","<<noticiero(texto)<<","<<texto<<","<<letras<<endl;
    }

        
}

string noticiero(string texto){
   string result;
    for (int i = 0; i < texto.size(); i++)
    {   if(texto[i]=='/' && texto[i+1]!='/'){
            if(texto[i+1]=='w'){
                i=i+5;
                while(texto[i]!='.'){
                    result=result+texto[i];
                    ++i;
                }
                break;
            }
            else{
                i++;
                while(texto[i]!='.'){
                    result=result+texto[i];
                    ++i;
                }
                break;
            }
        }
        
    }
    return result;
}