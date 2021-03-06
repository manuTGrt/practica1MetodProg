#include "Fecha.h"

Fecha::Fecha(const int &dia, const int &m, const int &anio) {
    this->setFecha(dia, m, anio); //el cogido es el mismo que el del metodo setFecha
}

void Fecha::setFecha(const int &dia, const int &mes, const int &a) {
/*
  if ((mes == 1) || (mes == 3) || (mes == 5) ....
      dmax=31;
  else if ((mes == 4) || (mes == 6) || (mes == 9) ....
      dmax=30;
  else if (mes == 2)
      dmax=28;

  switch (mes) {
    case 1:
    case 3:
    case 5:
       ...
            dmax=31;
            break;
    case 4:
    case 6:
    case 9:
       ...
            dmax=30;
            break;
    default:
            dmax=28;
            break;
  }
*/
//ES MAS RAPIDO Y COMODO USAR UN ARRAY QUE GUARDE LOS DIAS DE CADA MES...
    /*int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int auxd,auxm;
    this->anio=a; //VIP debo asignar a�o para que al llamar a bisiesto() tenga el a�o bien
    if (this->bisiesto())
        diaMes[2]=29;

    if (mes<1)  //si el mes es incorrecto
        auxm=1;//mes=1;
    else if (mes>12) //si el mes es incorrecto
        auxm=12;//mes=12;
    else
        auxm=mes;
    this->mes=auxm;

    dmax=diaMes[mes]; //una vez fijado el mes veo cuantos dias tiene ese mes como maximo
    if (dia>dmax) //si dia es superior al numero de dias de dicho mes
        auxd=dmax;//dia=dmax;
    else if (dia<1) //si dia es inferior a 1
        auxd=1;//dia=1;
    else
        auxd=dia;

    //this->dia=dia;
    this->dia=auxd;*/
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    this->anio=a; //VIP debo asignar a�o para que al llamar a bisiesto() tenga el a�o bien
    if (this->bisiesto())
        diaMes[2]=29;

    if (mes<1)  //si el mes es incorrecto
      this->mes=1;
    else if (mes>12) //si el mes es incorrecto
      this->mes=12;
    else
      this->mes=mes;
    dmax=diaMes[this->mes]; //una vez fijado el mes veo cuantos dias tiene ese mes como maximo

    if (dia>dmax) //si dia es superior al numero de dias de dicho mes
      this->dia=dmax;
    else if (dia<1) //si dia es inferior a 1
      this->dia=1;
    else
      this->dia=dia;
}

bool Fecha::bisiesto() const {
    if (this->anio%4==0 && this->anio%100!=0 || this->anio%400==0) //esto no es exacto... corregidlo ustedes
        return true;
    else
        return false;
}

void Fecha::ver() const {
  if (this->dia < 10)
    cout << "0";
  cout << this->dia << "/";
  if (this->mes < 10)
    cout << "0";
  cout << this->mes << "/" << this->anio;
}

Fecha Fecha::operator++() {   //++f
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (this->bisiesto()) //si el a�o es bisiesto febrero tiene 29 dias
      diaMes[2]=29;
    dmax=diaMes[this->mes];
    this->dia++;
    if (this->dia>dmax) { //si al incrementar dia superamos el numero de dias de dicho mes
        this->dia=1;      //pasamos a 1
        this->mes++;      //del mes siguiente
        if (this->mes>12) { //si al incrementar mes pasamos de 12 meses
            this->mes=1;    //pasamos al mes 1
            this->anio++;   //del a�o siguiente
        }
    }
    return *this; //devolvemos el objeto fecha ya incrementado
}

//RESTO DE METODOS Y FUNCIONES A RELLENAR POR EL ALUMNO...

Fecha Fecha::operator++(int i){
    Fecha f(this->dia,this->mes,this->anio);
    int dmax, diaMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (this->bisiesto()) //si el a�o es bisiesto febrero tiene 29 dias
      diaMes[2]=29;
    dmax=diaMes[this->mes];
    this->dia++;
    if (this->dia>dmax) { //si al incrementar dia superamos el numero de dias de dicho mes
        this->dia=1;      //pasamos a 1
        this->mes++;      //del mes siguiente
        if (this->mes>12) { //si al incrementar mes pasamos de 12 meses
            this->mes=1;    //pasamos al mes 1
            this->anio++;   //del a�o siguiente
        }
    }
    return f; //devolvemos el objeto fecha sin incrementar
}
Fecha Fecha::operator+(const int &i) const{
    Fecha fech(dia,mes,anio);
    for(int x=1;x<=i;x++){
        ++fech;
    }
    return fech;
}

Fecha operator+(const int &i, const Fecha &f){
    Fecha fech(f.getDia(),f.getMes(),f.getAnio());
    for(int x=0;x<i;x++){
        fech++;
    }
    return fech;
}

ostream& operator<<(ostream &s, const Fecha &f){
    string mes;
    switch (f.getMes()){
        case 1:
            mes="ene";
            break;
        case 2:
            mes="feb";
            break;
        case 3:
            mes="mar";
            break;
        case 4:
            mes="abr";
            break;
        case 5:
            mes="may";
            break;
        case 6:
            mes="jun";
            break;
        case 7:
            mes="jul";
            break;
        case 8:
            mes="ago";
            break;
        case 9:
            mes="sep";
            break;
        case 10:
            mes="oct";
            break;
        case 11:
            mes="nov";
            break;
        case 12:
            mes="dic";
            break;
}
    s<<f.getDia()<<" "<<mes<<" "<<f.getAnio();
    return s;
}
