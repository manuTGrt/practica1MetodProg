#include "Empresa.h"

int max_con=10;

Empresa::Empresa()
{
    //ctor
    con=new Contrato[max_con];
    cli=new Cliente[100];
}

void Empresa::crearContrato()
{
    long int dni;
    bool existecli,creado;
    cout<<"Introduzca dni: ";
    cin>>dni;
    existecli=compruebaDni(dni);
    if(existecli)
    {
        creaCon(dni);
    }
    else
    {
        creado=altaCliente(dni);
        if(creado)
            creaCon(dni);
    }
}

void Empresa::comprueba_ncon(int ncon)
{
    if(ncon>max_con)
    {
        Contrato *aux;
        max_con=max_con*2;
        aux=con;
        con=new Contrato[max_con];
        for(int i=1;i<=max_con/2;i++;){
            con[i]=aux[i];
        }
        delete [] aux;
    }
}

void Empresa::creaCon(long int dni)
{
    int tipo_con,dia,mes,anio,min_hablados,pre_min;
    char nac;
    cout<<"Tipo de Contrato a abrir (1-Tarifa Plana, 2-Movil): ";
    cin>>tipo_con;
    cout<<"Fecha del contrato"<<endl<<"dia: ";
    cin>>dia;
    cout<<"mes: ";
    cin>>mes;
    cout<<"anio: ";
    cin>>anio;
    Fecha f(dia,mes,anio);
    cout<<"minutos hablados: ";
    cin>>min_hablados;
    if(tipo_con==1)
    {
        ncon++;
        comprueba_ncon(ncon);
        con[ncon]=new ContratoTP(dni,f,min_hablados);
    }
    else if(tipo_con==2)
    {
        cout<<"Precio minuto: ";
        cin>>pre_min;
        cout<<"Nacionalidad: ";
        cin>>nac;
        ncon++;
        comprueba_ncon(ncon);
        con[ncon]=new ContratoMovil(dni,f,pre_min,min_hablados,nac);
    }
    else
    {
        cout<<"Tipo de contrato incorrecto."<<endl;
    }
}

bool Empresa::compruebaDni(long int dni)
{
    bool encontrado=false;
    int i=1;
    while(!encontrado && i<=ncli)
    {
        if(dni==cli[i].getDni())
            encontrado=true;
    }
    return encontrado;
}

bool Empresa::altaCliente(long int dni)
{
    bool creado=false;
    char nombre_cli;
    int dia,mes,anio;
    if(ncli>100)
    {
        cout<<"No es posible crear mas clientes."<<endl;
    }
    else
    {
        cout<<"Nombre del cliente: ";
        cin>>nombre_cli;
        cout<<"dia: ";
        cin>>dia;
        cout<<"mes: ";
        cin>>mes;
        cout<<"anio: ";
        cin>>anio;
        Fecha f(dia,mes,anio);
        ncli++;
        cli[ncli]=new Cliente(dni,nombre_cli,f);
        creado=true;
    }
    return creado;
}

Empresa::~Empresa()
{
    //dtor
}
