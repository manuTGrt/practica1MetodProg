#include "Empresa.h"

Empresa::Empresa():nmaxcli(100)
{
    //ctor
    this->ncli=0;
    this->ncon=0;
    this->nmaxcon=10;
    this->contratos=new Contrato *[10];
}

void Empresa::crearContrato()
{
    long int dni;
    int cli,creado,dia,mes,anio;
    char *nombre_cli=new char[20];
    cout<<"Introduzca dni: ";
    cin>>dni;
    cli=buscarCliente(dni);
    if(cli>-1)
    {
        creaCon(dni);
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
        Cliente *c=new Cliente(dni,nombre_cli,f);
        creado=altaCliente(c);
        if(creado>-1)
            creaCon(dni);
    }
}

void Empresa::comprueba_ncon(int ncon)
{
    if(ncon>nmaxcon)
    {
        Contrato **aux;
        nmaxcon=nmaxcon*2;
        aux=contratos;
        contratos=new Contrato*[nmaxcon];
        for(int i=0; i<nmaxcon/2; i++)
        {
            contratos[i]=aux[i];
        }
        delete [] aux;
    }
}

void Empresa::creaCon(long int dni)
{
    int tipo_con,dia,mes,anio,min_hablados;
    float pre_min;
    char *nac = new char[20];
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
        contratos[ncon]=new ContratoTP(dni,f,min_hablados);
    }
    else if(tipo_con==2)
    {
        cout<<"Precio minuto: ";
        cin>>pre_min;
        cout<<"Nacionalidad: ";
        cin>>nac;
        ncon++;
        comprueba_ncon(ncon);
        contratos[ncon]=new ContratoMovil(dni,f,pre_min,min_hablados,nac);
    }
    else
    {
        cout<<"Tipo de contrato incorrecto."<<endl;
    }
}

int Empresa::buscarCliente(long int dni) const
{
    bool encontrado=false;
    int i=0;
    while(!encontrado && i<ncli)
    {
        if(dni==this->clientes[i]->getDni())
            encontrado=true;
        else
            i++;
    }
    if(!encontrado)
        i=-1;
    return i;
}

int Empresa::altaCliente(Cliente *c)
{
    int pos=-1; //devuelve -1 si no cabe y la posici�n donde
    if (this->ncli<nmaxcli)   //donde lo he metido si cabe
    {
        this->clientes[this->ncli]=c;
        pos=this->ncli;
        this->ncli++;
    }
    else
    {
        cout << "Lo siento, el cupo de clientes esta lleno";
        pos=-1;
    }
    return pos;
}

bool Empresa::cancelarContrato(int idContrato)
{
    int i=0;
    bool encontrado=false;
    while(!encontrado && i<ncon)
    {
        if(idContrato==this->contratos[i]->getIdContrato())
        {
            encontrado=true;
            for(int j=i+1; j<ncon; j++)
            {
                contratos[j-1]=contratos[j];
            }
            delete this->contratos[ncon];
            ncon--;
        }
        else
            i++;
    }
    return encontrado;
}

bool Empresa::bajaCliente(long int dni)
{
    int i=0;
    bool encontrado=false;
    while(!encontrado && i<ncli)
    {
        if(dni==this->clientes[i]->getDni())
        {
            encontrado=true;
            for(int j=i+1; j<ncon; j++)
            {
                clientes[j-1]=clientes[j];
            }
            delete this->clientes[ncli];
            ncli--;
        }
        else
            i++;
    }
    return encontrado;
}

void Empresa::cargarDatos()
{
    Fecha f1(29,2,2001), f2(31,1,2002), f3(1,2,2002);
    this->clientes[0] = new Cliente(75547001, "Peter Lee", f1);
    this->clientes[1] = new Cliente(45999000, "Juan Perez", Fecha(29,2,2000));
    this->clientes[2] = new Cliente(37000017, "Luis Bono", f2);
    this->ncli=3;
    this->contratos[0] = new ContratoMovil(75547001, f1, 0.12, 110, "DANES"); //habla 110m a 0.12�/m
    this->contratos[1] = new ContratoMovil(75547001, f2, 0.09, 170, "DANES"); //habla 170m a 0.09�/m
    this->contratos[2] = new ContratoTP(37000017, f3, 250); //habla 250m (300m a 10�, exceso 0.15�/m)
    this->contratos[3] = new ContratoTP(75547001, f1, 312); //habla 312m (300m a 10�, exceso 0.15�/m)
    this->contratos[4] = new ContratoMovil(45999000, f2, 0.10, 202, "ESPA�OL"); //habla 202m a 0.10/m
    this->contratos[5] = new ContratoMovil(75547001, f2, 0.15, 80, "DANES"); //habla 80m a 0.15�/m
    this->contratos[6] = new ContratoTP(45999000, f3, 400); //habla 400m (300m a 10�, exceso 0.15�/m)
    this->ncon=7;
}

void Empresa::ver() const
{
    cout<<"Clientes:"<<endl;
    for(int i=0; i<ncli; i++)
    {
        cout<<this->clientes[i]->getNombre()<<" ("<<this->clientes[i]->getDni()<<" - "<<this->clientes[i]->getFecha()<<")"<<endl;
    }
    cout<<endl<<"Contratos:"<<endl;
    for(int i=0; i<ncon; i++)
    {
        contratos[i]->ver();
        cout<<endl;
    }
}

Empresa::~Empresa()
{
    //dtor
    for(int i=0; i<this->ncon; i++)   //primero elimino los objetos contratos
    {
        delete this->contratos[i];
    }
    delete [] this->contratos; //luego elimino el array de punteros
    for(int i=0; i<this->ncli; i++)   //primero elimino los objetos contratos
    {
        delete this->clientes[i];
    }
}
