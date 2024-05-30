#include "Piece.h"
#include "Radiateur.h"

Piece::Piece(float surface_piece, float hauteur_sous_plafond, float temperature_initiale, Radiateur& radiateur)
    : surface(surface_piece), hauteur(hauteur_sous_plafond), temperature(temperature_initiale), radiateur(radiateur) {
    volume = surface * hauteur;
}

float Piece::recuperer_temperature() const {
    return temperature;
}

void Piece::mettre_a_jour_temperature(float puissance, float deltaTime, bool chauffage_actif) {
    // Calculer l'énergie apportée (en Wh)
    float energie = puissance * (deltaTime / 3600.0);  // Puissance en W, deltaTime en secondes
    // Calculer le changement de température dû à la puissance du radiateur
    float deltaT_apportee = energie / (volume * capaciteThermiqueVolumique);
    // Calculer la perte de chaleur seulement si le chauffage est éteint
    float deltaT_perdue = chauffage_actif ? 0 : coefficient_perte_chaleur * deltaTime;

    // Mettre à jour la température
    temperature += deltaT_apportee - deltaT_perdue;
}
