#ifndef REGULATION_H
#define REGULATION_H

#include <vector>
#include <string>

class Regulation {
public:
    Regulation(float p, float i, float d, float consigne_val);

    void calculatePID(float temperature_actuelle, int currentTemp);
    void updateOnOffSchedule(float pid_output_rounded);
    void updateRegulation(int current_time, float currentTemp);

    bool isRegulationActive() const;
    float getLastPIDOutput() const;
    float getLastRawPIDOutput() const;  // Nouvelle méthode pour obtenir la sortie PID non arrondie

    std::string getOnOffSchedule() const;

    float recuperer_consigne() const;
    void definir_consigne(float nouvelleConsigne);

private:
    float pid_controller(float error, float dt);
    float roundToNearestFivePercent(float value);

    float P;
    float I;
    float D;
    float consigne;
    float previous_error;
    float error_integral;
    float last_pid_output;
    float last_raw_pid_output;  // Nouveau membre pour stocker la sortie PID non arrondie
    bool regulation_active;
    
    std::vector<bool> onOffSchedule;
};

#endif // REGULATION_H       