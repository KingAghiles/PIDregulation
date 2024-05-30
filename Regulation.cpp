#include "Regulation.h"
#include <algorithm>
#include <cmath>

Regulation::Regulation(float p, float i, float d, float consigne_val)
    : P(p), I(i), D(d), consigne(consigne_val), previous_error(0), error_integral(0), last_pid_output(0.0), last_raw_pid_output(0.0), regulation_active(false) {}

void Regulation::calculatePID(float temperature_actuelle, int currentTemp) {
    float error = consigne - temperature_actuelle;
    last_raw_pid_output = pid_controller(error, 1.0);  // Calcul du PID et stockage de la sortie brute
    last_pid_output = roundToNearestFivePercent(std::max(0.0f, std::min(last_raw_pid_output, 100.0f)));  // entre 0 et 100%, arrondi à 5%
      // Mettre à jour le plan ON/OFF
    updateOnOffSchedule(last_pid_output);

    // Forcer toutes les périodes à OFF si la température actuelle est égale ou supérieure à la consigne
    if (temperature_actuelle >= consigne) {
        std::fill(onOffSchedule.begin(), onOffSchedule.end(), false);
    }
     
}



void Regulation::updateOnOffSchedule(float pid_output_rounded) {
    onOffSchedule.clear();
    int onPeriods = static_cast<int>(20 * (pid_output_rounded / 100.0));
    for (int i = 0; i < 20; ++i) {
        onOffSchedule.push_back(i < onPeriods);
    }
}


// Méthode pour obtenir une représentation textuelle de l'horaire ON/OFF
std::string Regulation::getOnOffSchedule() const {
    std::string schedule;
    for (bool status : onOffSchedule) {
        schedule += status ? "ON, " : "OFF, ";
    }
    if (!schedule.empty()) {
        schedule.pop_back();  // Enlever la dernière virgule et espace
        schedule.pop_back();
    }
    return schedule;
}

void Regulation::updateRegulation(int current_time, float currentTemp) {
    int current_period = (current_time % 200) / 10;  // Calcul du période actuelle dans le cycle de 200 secondes

    // Vérifie si le cycle actuel est dans la phase ON selon le PID
    if (currentTemp >= consigne) {
        regulation_active = false;  // Désactive la régulation si la température est égale ou supérieure à la consigne
    } else if (current_period < onOffSchedule.size() && onOffSchedule[current_period]) {
        regulation_active = true;  // Active la régulation si on est dans une période ON
    } else {
        regulation_active = false;  // Désactive la régulation sinon
    }
}





bool Regulation::isRegulationActive() const {
    return regulation_active;
}

float Regulation::getLastPIDOutput() const {
    return last_pid_output;
}

float Regulation::getLastRawPIDOutput() const {
    return last_raw_pid_output;
}

float Regulation::pid_controller(float error, float dt) {
    float proportional = P * error;
    error_integral += error * dt;
    float integral = I * error_integral;
    float derivative = D * ((error - previous_error) / dt);
    previous_error = error;
    return proportional + integral + derivative;
}

float Regulation::recuperer_consigne() const {
    return consigne;
}

void Regulation::definir_consigne(float nouvelleConsigne) {
    consigne = nouvelleConsigne;
}

// Nouvelle méthode pour arrondir à 5%
float Regulation::roundToNearestFivePercent(float value) {
    return std::round(value / 5.0f) * 5.0f;
}                                  