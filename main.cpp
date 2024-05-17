#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;cmath&gt;
#include "Piece.h"
#include "Radiateur.h"
#include "Regulation.h"

int main() {
    // Initialisation des objets
    Regulation regulation(5, 0.1, 0.1, 22.0); // Coefficients PID et température de consigne
    Radiateur radiateur(1000, regulation); // 1000 Watts pour l'exemple
    Piece piece(50, 2.5, 0, radiateur); // Supposons une surface de 50 m² et une hauteur de 2.5 m
    float previousTemp = piece.recuperer_temperature();
    // Ouvrir un fichier CSV pour l'enregistrement
    std::ofstream dataFile("simulation_results.csv");
    dataFile &lt;&lt; "Time,Sortie PID,Sortie PID Arrondie,Regulation,Température Pièce,Température Consigne, Joules\n";

    // Simulation pour 200 secondes, en supposant que chaque boucle représente une seconde
    for (int time = 0; time &lt;= 200; ++time) {
        float currentTemp = piece.recuperer_temperature();
        regulation.calculatePID(currentTemp, time);  // Mise à jour du PID chaque seconde
        regulation.updateRegulation(time, currentTemp); 
        float sortiePID = regulation.getLastPIDOutput();
        int sortiePIDArrondie = static_cast&lt;int&gt;(std::round(sortiePID));
        int regulationActive = regulation.isRegulationActive() ? 1 : 0;
        float temperatureConsigne = regulation.recuperer_consigne(); // Récupère la température de consigne

        float deltaT = currentTemp - previousTemp; // Calcul de deltaT
        float joules = radiateur.get_max_watt() * deltaT; // Calcul des joules

        // Écrire les données dans le fichier CSV
        dataFile &lt;&lt; time &lt;&lt; "," &lt;&lt; sortiePID &lt;&lt; "," &lt;&lt; sortiePIDArrondie &lt;&lt; "," &lt;&lt; regulationActive &lt;&lt; ",";
        dataFile &lt;&lt; currentTemp &lt;&lt; "," &lt;&lt; temperatureConsigne &lt;&lt; "," &lt;&lt; joules &lt;&lt;"\n";

        if (time % 10 == 0) {  // Optionnellement, afficher le planning ON/OFF à chaque début de cycle
            dataFile &lt;&lt; regulation.getOnOffSchedule();
        }
        dataFile &lt;&lt; "\n";

        // Simuler un changement de température
        piece.definir_temperature(currentTemp + (sortiePID / 100.0f) - 0.05); // Changement hypothétique basé sur PID
    }

    // Fermer le fichier
    dataFile.close();
    std::cout &lt;&lt; "Simulation \n";
    return 0;
}