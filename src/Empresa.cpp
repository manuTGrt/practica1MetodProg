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
    int tContrato,dia,mes,anio,minhablados,bcliente;
    bool existe=false;
    char nombre[50],tmp[10],nac[50];
    char *nombrecli;
    float pmin;
    cout<<"\nIntroduzca dni: ";
    cin>>dni;
    cin.getline(tmp,10);
    bcliente=buscarCliente(dni);
    if (bcliente==-1)
    {
        cout<<"Nombre del cliente: ";
        cin.getline(nombre, 50);
        cout<<"dia: ";
        cin>>dia;
        cout<<"mes: ";
        cin>>mes;
        cout<<"anio: ";
        cin>>anio;
        Fecha f(dia,mes,anio);
        Cliente *c;
        c=new Cliente(dni,nombre,f);
        int pos;
        pos=altaCliente(c);
    }
    comprueba_ncon(ncon); //para incrementar el tama�o del array contratos si �ste est� lleno, porque es din�mico sin l�mites
    do
    {
        cout<<"Tipo de Contrato a abrir (1-Tarifa Plana, 2-Movil): ";
        cin>>tContrato;
        cin.getline(tmp,10);
        switch(tContrato)
        {
        case 1:
        {
            cout<<"Fecha del contrato:"<<endl;
            cout<<"dia: ";
            cin>>dia;
            cout<<"mes: ";
            cin>>mes;
            cout<<"anio: ";
            cin>>anio;
            Fecha f(dia,mes,anio);
            cout<<"minutos hablados: ";
            cin>>minhablados;
            cin.getline(tmp,10);
            contratos[ncon]=new ContratoTP(dni,f,minhablados);
            ncon++;
            break;
        }
        case 2:
        {
            cout<<"Fecha del contrato:"<<endl;
            cout<<"dia: ";
            cin>>dia;
            cout<<"mes: ";
            cin>>mes;
            cout<<"anio: ";
            cin>>anio;
            Fecha f(dia,mes,anio);
            cout<<"minutos hablados: ";
            cin>>minhablados;
            cout<<"Precio minuto: ";
            cin>>pmin;
            cout<<"Nacionalidad: ";
            cin>>nac;
            cin.getline(tmp,10);
            contratos[ncon]=new ContratoMovil(dni,f,pmin,minhablados,nac);
            ncon++;
            break;
        }
        default:
            cout<<"Opcion incorrecta."<<endl;
        }
    }
    while(tContrato!=1 && tContrato!=2);
}

void Empresa::comprueba_ncon(int ncon)
{
    if(ncon+1>=nmaxcon)
    {
        Contrato **aux;
        aux=contratos;
        contratos=new Contrato*[nmaxcon*2];
        for(int i=0; i<ncon; i++)
            contratos[i]=aux[i];
        delete [] aux;
        nmaxcon=nmaxcon*2;
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
    bool existe=false;
    int i=0;
    while (!existe && i<ncon)
    {
        if(contratos[i]->getIdContrato()==idContrato) existe=true;
        else
            i++;
    }
    if (existe)
    {
        delete contratos[i];
        for(int a=i; a<ncon; a++)
        {
            contratos[a]=contratos[a+1];
        }
        ncon--;
    }
    return existe;
}

bool Empresa::bajaCliente(long int dni)
{
    int i=0;
    bool encontrado=false;
    while(!encontrado && i<ncli)
    {
        if(dni==this->clientes[i]->getDni())
            encontrado=true;
        else
            i++;
    }
    if(encontrado)
    {
        for(int x=0; x<ncon; x++)
        {
            if (contratos[x]->getDniContrato()==dni)
            {
                delete contratos[x];
                for(int a=x; a<ncon; a++)
                {
                    contratos[a]=contratos[a+1];
                }
                x--;
                ncon--;
            }
        }
        delete this->clientes[i];
        for(int j=i; j<ncon; j++)
        {
            clientes[j]=clientes[j+1];
        }
        ncli--;
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
    cout<<endl<<"La empresa tiene "<<ncli<<" clientes y "<<ncon<<" contratos"<<endl;
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

int Empresa::descuento (float porcentaje) const{
    int x=0;
    for(int i=0;i<ncon;i++){
        if(typeid(*contratos[i])==typeid(ContratoMovil)){
            ContratoMovil *cm=dynamic_cast<ContratoMovil*>(contratos[i]);
            cm->setPrecioMinuto(cm->getPrecioMinuto()*(1-(porcentaje/100)));
            x++;
        }
    }
    return x;
}

int Empresa::nContratosTP() const{
    int x=0;
    for(int i=0;i<ncon;i++){
        if(typeid(*contratos[i])==typeid(ContratoTP))
            x++;
    }
    return x;
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
