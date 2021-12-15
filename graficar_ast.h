#ifndef GRAFICAR_AST_H
#define GRAFICAR_AST_H

#include <QObject>
#include "nodo_arbol.h"
class graficar_ast
{
public:
    //graficar_ast();
    //Constructor
    graficar_ast(Nodo_arbol *root);
    //Atributos
    Nodo_arbol *raiz;
    QString dot;
    int cont;
    //Metodos, funciones
    QString generarCodigoGraphviz();
    QString limpiarString(QString str);
    void recorrerAST(QString padre, Nodo_arbol *hijo);
    void generarImagen();
};

#endif // GRAFICAR_AST_H
