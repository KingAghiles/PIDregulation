import pandas as pd
import matplotlib.pyplot as plt

# Lire le fichier CSV ligne par ligne, en filtrant les lignes contenant 'ON' et 'OFF'
rows = []
with open('simulation_results.csv', 'r') as file:
    for line in file:
        if 'ON' not in line and 'OFF' not in line:
            rows.append(line)

# Joindre les lignes filtrées en une seule chaîne de caractères
filtered_data = ''.join(rows)

# Lire les données filtrées dans un DataFrame
from io import StringIO
data = pd.read_csv(StringIO(filtered_data))

# Afficher les noms des colonnes pour vérifier s'il y a des caractères spéciaux
print("Colonnes originales : ", data.columns)

# Renommer les colonnes pour enlever les caractères spéciaux si nécessaire
data.columns = ['Time', 'Sortie PID', 'Sortie PID Arrondie', 'Regulation', 'Temperature Piece', 'Temperature Consigne', 'Wh']

# Afficher les nouveaux noms des colonnes pour vérifier les changements
print("Colonnes renommées : ", data.columns)

# Convertir les colonnes en types de données appropriés
data['Time'] = pd.to_numeric(data['Time'], errors='coerce')
data['Sortie PID'] = pd.to_numeric(data['Sortie PID'], errors='coerce')
data['Sortie PID Arrondie'] = pd.to_numeric(data['Sortie PID Arrondie'], errors='coerce')
data['Regulation'] = pd.to_numeric(data['Regulation'], errors='coerce')
data['Temperature Piece'] = pd.to_numeric(data['Temperature Piece'], errors='coerce')
data['Temperature Consigne'] = pd.to_numeric(data['Temperature Consigne'], errors='coerce')
data['Wh'] = pd.to_numeric(data['Wh'], errors='coerce')

# Supprimer les lignes avec des valeurs manquantes ou invalides
data.dropna(inplace=True)

# Vérifier les types de données
print("Types de données après conversion :")
print(data.dtypes)

# Créer une figure avec trois sous-graphiques
fig, axs = plt.subplots(3, 1, figsize=(10, 18))

# Graphique 1: Evolution de la température de la pièce en fonction du temps
axs[0].plot(data['Time'], data['Temperature Piece'], label='Température Pièce')
axs[0].axhline(y=data['Temperature Consigne'].iloc[0], color='r', linestyle='--', label='Température Consigne')
axs[0].set_xlabel('Temps (secondes)')
axs[0].set_ylabel('Température (°C)')

axs[0].legend()
axs[0].grid(True)

# Graphique 2: Régulation (0 et 1) en fonction du temps
axs[1].plot(data['Time'], data['Regulation'], label='Régulation (0=Off, 1=On)', drawstyle='steps-post')
axs[1].set_xlabel('Temps (secondes)')
axs[1].set_ylabel('Régulation')

axs[1].legend()
axs[1].grid(True)

# Graphique 3: Consommation Wh en fonction du temps
axs[2].plot(data['Time'], data['Wh'], label='Consommation (Wh)')
axs[2].set_xlabel('Temps (secondes)')
axs[2].set_ylabel('Consommation (Wh)')

axs[2].legend()
axs[2].grid(True)

# Ajuster l'espacement entre les sous-graphiques
plt.tight_layout()

# Sauvegarder le graphique dans un fichier
plt.savefig('simulation_results.png')

# Afficher les graphiques
plt.show()
