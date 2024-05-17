#include "Piece.h"
#include "Radiateur.h"

Piece::Piece(float surface_piece, float hauteur_sous_plafond, float temperature_initiale, Radiateur& radiateur)
    : surface(surface_piece), hauteur(hauteur_sous_plafond), temperature(temperature_initiale), radiateur(radiateur) {
    volume = surface * hauteur;
}

float Piece::recuperer_temperature() const {
    return temperature;
}

void Piece::mettre_a_jour_temperature(float puissance, float deltaTime) {
    // Calculer l'énergie apportée (en Wh)
    float energie = puissance * (deltaTime / 3600.0);  // Puissance en W, deltaTime en secondes
    // Calculer le changement de température
    float deltaT = energie / (volume * capaciteThermiqueVolumique);
    temperature += deltaT;
}
