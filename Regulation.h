#ifndef REGULATION_H
#define REGULATION_H

#include &lt;vector&gt;
#include &lt;string&gt;

class Regulation {
private:
    float consigne;
    float P, I, D;  
    float previous_error;
    float error_integral;
    float last_pid_output;  
    bool regulation_active;
    std::vector&lt;bool&gt; onOffSchedule; 

public:
    Regulation(float p, float i, float d, float consigne_val);
    void calculatePID(float temperature_actuelle, int current_time);
    float getLastPIDOutput() const;
    float pid_controller(float error, float dt);
    void updateOnOffSchedule(float pid_output_rounded);
    std::string getOnOffSchedule() const;
    void updateRegulation(int current_time,float currentTemp );
    bool isRegulationActive() const;  
    float recuperer_consigne() const;
    void definir_consigne(float nouvelleConsigne);
};

#endif // REGULATION_H