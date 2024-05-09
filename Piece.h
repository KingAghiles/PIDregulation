#ifndef PIECE_H
#define PIECE_H

#include "Radiateur.h"

class Radiateur;

class Piece {
private:
    float volume;
    float temperature;
    Radiateur& radiateur;

public:
    Piece(float surface_piece, float hauteur_sous_plafond, float temperature_initiale, Radiateur& radiateur);
    float recuperer_volume();
    float recuperer_temperature();
    void definir_temperature(float temperature);
    void mettre_a_jour_regulation(float temperature_consigne, int current_time);
};

#endif // PIECE_H



