#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Estudiante {
    string cedula;
    string apellidos;
    string nombres;
    float notaFinal;
    string carrera;
    int nivel;

    Estudiante* izq;
    Estudiante* der;

    Estudiante(string c, string a, string n, float nota, string car, int niv) {
        cedula = c;
        apellidos = a;
        nombres = n;
        notaFinal = nota;
        carrera = car;
        nivel = niv;
        izq = NULL;
        der = NULL;
    }
};

class ArbolBST {
private:
    Estudiante* raiz;

    void mostrarDatos(Estudiante* nodo) {
        if (nodo != NULL) {
            cout << "\nCedula: " << nodo->cedula;
            cout << "\nApellidos: " << nodo->apellidos;
            cout << "\nNombres: " << nodo->nombres;
            cout << "\nNota: " << nodo->notaFinal;
            cout << "\nCarrera: " << nodo->carrera;
            cout << "\nNivel: " << nodo->nivel << endl;
            cout << "-----------------------\n";
        }
    }

    Estudiante* insertar(Estudiante* nodo, Estudiante* nuevo) {
        if (nodo == NULL)
            return nuevo;

        if (nuevo->cedula < nodo->cedula)
            nodo->izq = insertar(nodo->izq, nuevo);
        else if (nuevo->cedula > nodo->cedula)
            nodo->der = insertar(nodo->der, nuevo);

        return nodo;
    }

    Estudiante* buscar(Estudiante* nodo, string cedula) {
        if (nodo == NULL || nodo->cedula == cedula)
            return nodo;

        if (cedula < nodo->cedula)
            return buscar(nodo->izq, cedula);

        return buscar(nodo->der, cedula);
    }

    Estudiante* obtenerMinimo(Estudiante* nodo) {
        while (nodo->izq != NULL)
            nodo = nodo->izq;

        return nodo;
    }

    Estudiante* eliminar(Estudiante* nodo, string cedula) {
        if (nodo == NULL)
            return NULL;

        if (cedula < nodo->cedula) {
            nodo->izq = eliminar(nodo->izq, cedula);
        }
        else if (cedula > nodo->cedula) {
            nodo->der = eliminar(nodo->der, cedula);
        }
        else {
            if (nodo->izq == NULL) {
                Estudiante* temp = nodo->der;
                delete nodo;
                return temp;
            }

            if (nodo->der == NULL) {
                Estudiante* temp = nodo->izq;
                delete nodo;
                return temp;
            }

            Estudiante* temp = obtenerMinimo(nodo->der);

            nodo->cedula = temp->cedula;
            nodo->apellidos = temp->apellidos;
            nodo->nombres = temp->nombres;
            nodo->notaFinal = temp->notaFinal;
            nodo->carrera = temp->carrera;
            nodo->nivel = temp->nivel;

            nodo->der = eliminar(nodo->der, temp->cedula);
        }

        return nodo;
    }

    void inorden(Estudiante* nodo) {
        if (nodo != NULL) {
            inorden(nodo->izq);
            mostrarDatos(nodo);
            inorden(nodo->der);
        }
    }

    void preorden(Estudiante* nodo) {
        if (nodo != NULL) {
            mostrarDatos(nodo);
            preorden(nodo->izq);
            preorden(nodo->der);
        }
    }

    void postorden(Estudiante* nodo) {
        if (nodo != NULL) {
            postorden(nodo->izq);
            postorden(nodo->der);
            mostrarDatos(nodo);
        }
    }

    int contar(Estudiante* nodo) {
        if (nodo == NULL)
            return 0;

        return 1 + contar(nodo->izq) + contar(nodo->der);
    }

    int altura(Estudiante* nodo) {
        if (nodo == NULL)
            return 0;

        int izq = altura(nodo->izq);
        int der = altura(nodo->der);

        return 1 + max(izq, der);
    }

    void buscarMayorNota(Estudiante* nodo, Estudiante*& mayor) {
        if (nodo == NULL) return;

        if (mayor == NULL || nodo->notaFinal > mayor->notaFinal)
            mayor = nodo;

        buscarMayorNota(nodo->izq, mayor);
        buscarMayorNota(nodo->der, mayor);
    }

    void buscarMenorNota(Estudiante* nodo, Estudiante*& menor) {
        if (nodo == NULL) return;

        if (menor == NULL || nodo->notaFinal < menor->notaFinal)
            menor = nodo;

        buscarMenorNota(nodo->izq, menor);
        buscarMenorNota(nodo->der, menor);
    }

    void aprobados(Estudiante* nodo) {
        if (nodo != NULL) {
            aprobados(nodo->izq);

            if (nodo->notaFinal >= 7)
                mostrarDatos(nodo);

            aprobados(nodo->der);
        }
    }

    void reprobados(Estudiante* nodo) {
        if (nodo != NULL) {
            reprobados(nodo->izq);

            if (nodo->notaFinal < 7)
                mostrarDatos(nodo);

            reprobados(nodo->der);
        }
    }

public:
    ArbolBST() {
        raiz = NULL;
    }

    void insertarEstudiante() {
        string cedula, apellidos, nombres, carrera;
        float nota;
        int nivel;

        cout << "Cedula: ";
        cin >> cedula;

        cout << "Apellidos: ";
        cin >> apellidos;

        cout << "Nombres: ";
        cin >> nombres;

        cout << "Nota: ";
        cin >> nota;

        cout << "Carrera: ";
        cin >> carrera;

        cout << "Nivel: ";
        cin >> nivel;

        Estudiante* nuevo = new Estudiante(
            cedula, apellidos, nombres,
            nota, carrera, nivel
        );

        raiz = insertar(raiz, nuevo);
    }

    void buscarEstudiante() {
        string cedula;

        cout << "Cedula a buscar: ";
        cin >> cedula;

        Estudiante* encontrado = buscar(raiz, cedula);

        if (encontrado)
            mostrarDatos(encontrado);
        else
            cout << "No encontrado.\n";
    }

    void eliminarEstudiante() {
        string cedula;

        cout << "Cedula a eliminar: ";
        cin >> cedula;

        raiz = eliminar(raiz, cedula);
    }

    void recorridoInorden() {
        inorden(raiz);
    }

    void recorridoPreorden() {
        preorden(raiz);
    }

    void recorridoPostorden() {
        postorden(raiz);
    }

    void recorridoPorNiveles() {
        if (raiz == NULL)
            return;

        queue<Estudiante*> cola;
        cola.push(raiz);

        while (!cola.empty()) {
            Estudiante* actual = cola.front();
            cola.pop();

            mostrarDatos(actual);

            if (actual->izq)
                cola.push(actual->izq);

            if (actual->der)
                cola.push(actual->der);
        }
    }

    void contarNodos() {
        cout << "Total: " << contar(raiz) << endl;
    }

    void calcularAltura() {
        cout << "Altura: " << altura(raiz) << endl;
    }

    void buscarNotaMayor() {
        Estudiante* mayor = NULL;

        buscarMayorNota(raiz, mayor);

        mostrarDatos(mayor);
    }

    void buscarNotaMenor() {
        Estudiante* menor = NULL;

        buscarMenorNota(raiz, menor);

        mostrarDatos(menor);
    }

    void mostrarAprobados() {
        aprobados(raiz);
    }

    void mostrarReprobados() {
        reprobados(raiz);
    }
};

int main() {
    ArbolBST arbol;

    int op;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Insertar\n";
        cout << "2. Buscar\n";
        cout << "3. Eliminar\n";
        cout << "4. Inorden\n";
        cout << "5. Preorden\n";
        cout << "6. Postorden\n";
        cout << "7. BFS\n";
        cout << "8. Contar\n";
        cout << "9. Altura\n";
        cout << "10. Mayor nota\n";
        cout << "11. Menor nota\n";
        cout << "12. Aprobados\n";
        cout << "13. Reprobados\n";
        cout << "14. Salir\n";
        cin >> op;

        switch(op) {
            case 1: arbol.insertarEstudiante(); break;
            case 2: arbol.buscarEstudiante(); break;
            case 3: arbol.eliminarEstudiante(); break;
            case 4: arbol.recorridoInorden(); break;
            case 5: arbol.recorridoPreorden(); break;
            case 6: arbol.recorridoPostorden(); break;
            case 7: arbol.recorridoPorNiveles(); break;
            case 8: arbol.contarNodos(); break;
            case 9: arbol.calcularAltura(); break;
            case 10: arbol.buscarNotaMayor(); break;
            case 11: arbol.buscarNotaMenor(); break;
            case 12: arbol.mostrarAprobados(); break;
            case 13: arbol.mostrarReprobados(); break;
        }

    } while(op != 14);

    return 0;
}