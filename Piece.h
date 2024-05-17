#ifndef PIECE_H
#define PIECE_H

class Radiateur;  // Déclaration avant la définition

class Piece {
private:
    float surface;
    float hauteur;
    float temperature;
    Radiateur& radiateur;
    float volume;
    const float capaciteThermiqueVolumique = 0.33; // Wh/m³°C

public:
    Piece(float s, float h, float t, Radiateur& r);

    float recuperer_temperature() const;
    void mettre_a_jour_temperature(float puissance, float deltaTime);
};

#endif // PIECE_H
