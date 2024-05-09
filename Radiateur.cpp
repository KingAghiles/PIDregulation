#include "Radiateur.h"

Radiateur::Radiateur(int puissance_watt, Regulation& regulation)
    : puissance_watt(puissance_watt), regulation(regulation) {}

int Radiateur::get_max_watt() {
    return puissance_watt;
}

int Radiateur::get_sortie_actuelle() {
    // Appeler getLastPIDOutput au lieu de calculer_sortie, qui n'existe pas
    int sortie_actuelle = static_cast<int>(regulation.getLastPIDOutput());
    return sortie_actuelle > 0 ? puissance_watt : 0;
}

float Radiateur::recuperer_temperature_consigne() {
    // Utiliser recuperer_consigne directement si elle est définie dans Regulation
    return regulation.recuperer_consigne();  // Assurez-vous que cette méthode existe
}

void Radiateur::definir_temperature_consigne(float temperature) {
    regulation.definir_consigne(temperature);
}

void Radiateur::mettre_a_jour_regulation(float temperature_consigne, float temperature_actuelle, int current_time) {
    // Utiliser la méthode updateRegulation au lieu de mettre_a_jour
    regulation.updateRegulation(current_time,temperature_actuelle);
}
double Radiateur::calculer_joules(double deltaT) const {
    return puissance_watt * deltaT;
}




