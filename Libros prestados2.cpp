#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> 

using namespace std;

string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}


class Publicacion {
protected:
    string codigo;
    string titulo;
    int anio;
    bool prestado;

public:
    Publicacion(string c, string t, int a) : codigo(c), titulo(t), anio(a), prestado(false) {}

    virtual ~Publicacion() {}

    void prestar() {
        if (!prestado) {
            prestado = true;
        } else {
            cout << "La publicaci�n ya est� prestada." << endl;
        }
    }

    void devolver() {
        if (prestado) {
            prestado = false;
        } else {
            cout << "La publicaci�n no est� prestada." << endl;
        }
    }

    virtual string obtenerInformacion() const {
        string estado = prestado ? "Prestado" : "No Prestado";
        return "C�digo: " + codigo + "\nT�tulo: " + titulo + "\nA�o: " + intToString(anio) + "\nEstado: " + estado + "\n";
    }

    bool estaPrestado() const {
        return prestado;
    }
};

class Libro : public Publicacion {
public:
    Libro(string c, string t, int a) : Publicacion(c, t, a) {}

    string obtenerInformacion() const {
        return "Libro\n" + Publicacion::obtenerInformacion();
    }
};

class Revista : public Publicacion {
public:
    Revista(string c, string t, int a) : Publicacion(c, t, a) {}

    string obtenerInformacion() const {
        return "Revista\n" + Publicacion::obtenerInformacion();
    }
};

void guardarInformacion(const vector<Publicacion*>& publicaciones) {
    ofstream librosPrestados("LibrosPrestados.txt");
    ofstream librosEnStock("LibrosEnStock.txt");

    for (size_t i = 0; i < publicaciones.size(); ++i) {
        if (publicaciones[i]->estaPrestado()) {
            librosPrestados << publicaciones[i]->obtenerInformacion() << endl;
        } else {
            librosEnStock << publicaciones[i]->obtenerInformacion() << endl;
        }
    }

    librosPrestados.close();
    librosEnStock.close();
}

int main() {
    vector<Publicacion*> publicaciones;


    publicaciones.push_back(new Libro("001", "Cien A�os de Soledad", 1967));
    publicaciones.push_back(new Revista("002", "Revista de Historia", 2022));
    publicaciones.push_back(new Libro("003", "Matar a un ruise�or", 1960));
    publicaciones.push_back(new Revista("004", "Revista de Biologia", 2021));


    publicaciones[0]->prestar();
    publicaciones[2]->prestar(); 

    guardarInformacion(publicaciones);

	cout<<"Archivo generado con exito"<<endl;

    return 0;
}

