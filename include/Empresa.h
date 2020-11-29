#ifndef EMPRESA_H
#define EMPRESA_H

#include <typeinfo>
#include "Fecha.h" //definicion clase Fecha
#include "Cliente.h" // definicion clase Cliente
#include "Contrato.h" // definicion de la clase Contrato
#include "ContratoTP.h" // definicion de la clase ContratoTP
#include "ContratoMovil.h" // definicion de la clase ContratoMovil

class Empresa
{
    Contrato **contratos;
    Cliente *clientes[100];
    int ncon;
    int ncli;
    const int nmaxcli;
    int nmaxcon;

    protected:
        int buscarCliente(long int dni) const;
        int altaCliente(Cliente *c);

    public:
        Empresa();
        virtual ~Empresa();
        void crearContrato();
        bool cancelarContrato(int idContrato);
        bool bajaCliente(long int dni);
        int descuento (float porcentaje) const;
        int nContratosTP() const;
        void cargarDatos();

        void comprueba_ncon(int ncon);
        void ver() const;
};

#endif // EMPRESA_H
