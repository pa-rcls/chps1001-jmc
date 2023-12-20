import matplotlib.pyplot as plt

# Fonction pour lire les données du fichier
def lire_fichier_molecules(nom_fichier):
    molecules = []
    with open(nom_fichier, 'r') as fichier:
        for ligne in fichier:
            elements = ligne.split()
            nom_molecule = elements[0]
            position = [float(x) for x in elements[1:4:2]]  # Utilisez les valeurs x et z
            feuillet = int(elements[4])
            molecules.append((nom_molecule, position, feuillet))
    return molecules

# Fonction pour afficher les molécules dans un plot 2D avec des couleurs différentes pour chaque feuillet
def afficher_molecules_2d_xz(molecules):
    plt.figure()

    for molécule, position, feuillet in molecules:
        if feuillet == 1:
            plt.scatter(position[0], position[1], c='red', label='Feuillet 1')
        elif feuillet == 0:
            plt.scatter(position[0], position[1], c='blue', label='Feuillet 0')

    plt.xlabel('X')
    plt.ylabel('Z')
    plt.show()

# Lecture des molécules depuis le fichier
molecules = lire_fichier_molecules('molecule.txt')

# Affichage des molécules dans un plot 2D avec les valeurs x et z
afficher_molecules_2d_xz(molecules)