import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Fonction pour lire les données du fichier
def lire_fichier_molecules(nom_fichier):
    molecules = []
    with open(nom_fichier, 'r') as fichier:
        for ligne in fichier:
            elements = ligne.split()
            nom_molecule = elements[0]
            position = [float(x) for x in elements[1:4]]  # Utilisez les trois valeurs x, y, et z
            feuillet = int(elements[4])
            molecules.append((nom_molecule, position, feuillet))
    return molecules

# Fonction pour afficher les molécules dans un plot 3D avec des couleurs différentes pour chaque feuillet
def afficher_molecules_3d_xyz(molecules):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    for molécule, position, feuillet in molecules:
        if feuillet == 1:
            ax.scatter(position[0], position[1], position[2], c='blue')
        elif feuillet == 0:
            ax.scatter(position[0], position[1], position[2], c='red')

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()

# Lecture des molécules depuis le fichier
molecules = lire_fichier_molecules('molecule.txt')

# Affichage des molécules dans un plot 3D avec les valeurs x, y, et z
afficher_molecules_3d_xyz(molecules)