#ifndef RADIATEUR_H
#define RADIATEUR_H

#include "Regulation.h"

class Radiateur {
private:
    int puissance_watt;
    Regulation& regulation;
    

public:
    Radiateur(int puissance_watt, Regulation& regulation);
    int get_max_watt();
    int get_sortie_actuelle();
    float recuperer_temperature_consigne();
    void definir_temperature_consigne(float temperature);
    void mettre_a_jour_regulation(float temperature_consigne, float temperature_actuelle, int current_time);
    // Calculer l'énergie consommée en joules
    double calculer_joules(double deltaT) const;


};

#endif // RADIATEUR_H


