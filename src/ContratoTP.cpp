#include "ContratoTP.h"

int ContratoTP::minutosTP=300;
float ContratoTP::precioTP=10;
const float ContratoTP::precioExcesoMinutos=0.15;


//static se pone en el .h (no se pone en el .cpp)
void ContratoTP::setTarifaPlana(int m, float p) {
  ContratoTP::minutosTP=m; //puedo poner minutosTP=m ...pongo ContratoTP::minutosTP para recordar que es estatico
  ContratoTP::precioTP=p;  //puedo poner precioTP=p  ...pongo ContratoTP::precioTP para recordar que es estatico
}

float ContratoTP::factura() const {
  //implementarlo...
  if(minutosHablados>minutosTP)
    return precioTP+((minutosHablados-minutosTP)*precioExcesoMinutos);
  else
    return precioTP;
}
//RESTO DE METODOS Y FUNCIONES A RELLENAR POR EL ALUMNO...
ContratoTP::ContratoTP(long int dni, Fecha f, int m):Contrato(dni,f){
    ContratoTP::minutosHablados=m;
}

void ContratoTP::ver() const{
    Contrato::ver();
    cout<<" "<<minutosHablados<<"m, "<<minutosTP<<"("<<precioTP<<")"<<" - "<<factura()<<"€";
}

ostream& operator<<(ostream &s, const ContratoTP &c){
    s<<(Contrato &)c;
    s<<" "<<c.getMinutosHablados()<<"m, "<<c.getLimiteMinutos()<<"("<<c.getPrecio()<<") - ";
    s<<c.factura()<<"€";
    return s;
}
