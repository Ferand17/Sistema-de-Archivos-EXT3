#ifndef NODO_ARBOL_H
#define NODO_ARBOL_H

#include <QObject>
#include <QString>
#include <QList>

using namespace std;
class Nodo_arbol
{
public:
    //constructor
    Nodo_arbol(QString ptipo, QString pvalor);
    //VARIABLES
    //el tipo que va ser el nodo, por ejemplo saber si es un nodo
    QString tipo;
    //el valor o lexema que se obtiene por ejemplo -path="dads" el valor seria dads
    QString valor;
    //indicadores de linea
    int linea;
    //indicadores de columna
    int columna;
    //para saber el tipo, en numero
    int tipo_;
    //este va ser la variable global que concatena el AST para saber como manejar nuestro arboo
    QString cadenaDot;
    //son los hijos de cada nodo
    QList<Nodo_arbol> hijos;


    //METODOS


    void add(Nodo_arbol n);//agrega los nuevos hijos a la lista de hijos
     int getTipo();//devuelve el tipo en int
};

#endif // NODO_ARBOL_H
