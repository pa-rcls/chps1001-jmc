import sys

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Chemin vers le fichier
file_path = sys.argv[1]

# Lire le fichier et extraire les coordonnées
with open(file_path, 'r') as file:
    lines = file.readlines()

# Initialiser les listes pour les coordonnées X, Y, Z
x_coords = []
y_coords = []
z_coords = []
color_values = []

# Parcourir les lignes et extraire les coordonnées
for line in lines:
    # Séparer les éléments de la ligne par un espace
    elements = line.split()
    # Récupérer les coordonnées X, Y, Z (colonne 4, 5, 6)
    x_coords.append(float(elements[3]))
    y_coords.append(float(elements[4]))
    z_coords.append(float(elements[5]))
    if int(elements[6]) == 0:
        color_values.append("red")
    else :
        color_values.append("blue")


# Créer le graphique 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Tracer les points
ax.scatter(x_coords, y_coords, z_coords,c=color_values)

# Étiqueter les axes
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.savefig('result.png')  # Save the figure to an image file
