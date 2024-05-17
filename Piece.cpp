#include "Piece.h"

Piece::Piece(float surface_piece, float hauteur_sous_plafond, float temperature_initiale, Radiateur& radiateur)
    : volume(surface_piece * hauteur_sous_plafond), temperature(temperature_initiale), radiateur(radiateur) {}

float Piece::recuperer_volume() {
    return volume;
}

float Piece::recuperer_temperature() {
    return temperature;
}

void Piece::definir_temperature(float temperature) {
    this->temperature = temperature;
}

void Piece::mettre_a_jour_regulation(float temperature_consigne, int current_time) {
    const double capacite_thermique_piece = 1000 * volume;
    const double coefficient_perte = 0.01;

    double perte_thermique = temperature * coefficient_perte;
    double joules_apportes = radiateur.get_sortie_actuelle() * 1.0;
    double dT = (joules_apportes / capacite_thermique_piece) - perte_thermique;

    temperature += dT;
    radiateur.mettre_a_jour_regulation(temperature_consigne, temperature, current_time);
}