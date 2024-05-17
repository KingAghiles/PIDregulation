#include <iostream>
#include <fstream>
#include <cmath>
#include "Piece.h"
#include "Radiateur.h"
#include "Regulation.h"

int main() {
    // Initialisation des objets
    Regulation regulation(5, 0.1, 0.1, 23.0); // Coefficients PID et température de consigne de 23°C
    Radiateur radiateur(5000, regulation); // 5000 Watts pour l'exemple
    Piece piece(50, 2.5, 10, radiateur); // Supposons une surface de 50 m² et une hauteur de 2.5 m, température initiale de 10°C

    // Ouvrir un fichier CSV pour l'enregistrement
    std::ofstream dataFile("simulation_results.csv");
    dataFile << "Time,Sortie PID,Sortie PID Arrondie,Regulation,Température Pièce,Température Consigne, Joules\n";

    // Simulation pour 3600 secondes (1 heure), en supposant que chaque boucle représente une seconde
    for (int time = 0; time <= 3600; ++time) {
        if (time % 200 == 0) {  // Calcul du PID et mise à jour de l'horaire ON/OFF chaque début de cycle de 200 secondes
            float currentTemp = piece.recuperer_temperature();
            regulation.calculatePID(currentTemp, time);  // Mise à jour du PID chaque début de cycle
            dataFile << regulation.getOnOffSchedule() << "\n";  // Afficher le planning ON/OFF à chaque début de cycle
        }

        if (time % 10 == 0) {  // Mise à jour de la régulation et écriture des données toutes les 10 secondes
            regulation.updateRegulation(time, piece.recuperer_temperature());
            float sortiePID = regulation.getLastRawPIDOutput();
            float sortiePIDArrondie = regulation.getLastPIDOutput();  // Utilisation de la sortie PID arrondie
            int regulationActive = regulation.isRegulationActive() ? 1 : 0;
            float temperatureConsigne = regulation.recuperer_consigne(); // Récupère la température de consigne

            float currentTemp = piece.recuperer_temperature();
            double deltaT = currentTemp - 10.0; // Écart de température initiale
            double joules = radiateur.get_max_watt() * deltaT; // Calcul des joules

            // Écrire les données dans le fichier CSV toutes les 10 secondes
            dataFile << time << "," << sortiePID << "," << sortiePIDArrondie << "," << regulationActive << ",";
            dataFile << piece.recuperer_temperature() << "," << temperatureConsigne << "," << joules << "\n";
        }

        // Simuler un changement de température chaque seconde
        float puissance = regulation.isRegulationActive() ? radiateur.get_max_watt() : 0.0;
        piece.mettre_a_jour_temperature(puissance, 1.0);  // Mise à jour de la température avec une puissance et deltaTime de 1 seconde
    }

    // Fermer le fichier
    dataFile.close();
    std::cout << "Simulation terminée\n";
    return 0;
}
