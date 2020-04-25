#ifndef TP1_PARTIDO_H
#define TP1_PARTIDO_H

#include <string>
#include <tuple>

using namespace std;

class partido {

private:
    string fecha;
    string equipo1, equipo2;
    int puntaje1, puntaje2;

public:
    partido(const string &fecha, const string &equipo1, int puntaje1, const string &equipo2, int puntaje2);

    const string &getEquipo1() const;

    void setEquipo1(const string &equipo1);

    const string &getEquipo2() const;

    void setEquipo2(const string &equipo2);

    int getPuntaje1() const;

    void setPuntaje1(int puntaje1);

    int getPuntaje2() const;

    void setPuntaje2(int puntaje2);

    string getGanador();

    const string &getFecha() const;

    void setFecha(const string &fecha);

};


#endif //TP1_PARTIDO_H
