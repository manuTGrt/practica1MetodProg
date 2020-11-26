#ifndef EMPRESA_H
#define EMPRESA_H


class Empresa
{
    Contrato* con[];
    Cliente* cli[];
    int ncon=0;
    int ncli=0;
    public:
        Empresa();
        virtual ~Empresa();
        void crearContrato();
        void cancelarContrato();
        void bajaCliente();
        bool altaCliente(long int dni);
        bool compruebaDni(long int dni);
        void comprueba_ncon(int ncon);
        void creaCon(long int dni);
};

#endif // EMPRESA_H
