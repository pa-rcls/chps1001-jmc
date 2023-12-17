import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_molecule_file(file_path):
    molecules = []
    with open(file_path, 'r') as file:
        molecule = {}
        for line in file:
            if line.startswith('Molecule Name:'):
                molecule['name'] = line.split(': ')[1].strip()
            elif line.startswith('Molecule ID:'):
                molecule['id'] = int(line.split(': ')[1].strip())
            elif line.startswith('Center of Mass:'):
                coordinates = line.split(': ')[1].strip().split()
                molecule['x'] = float(coordinates[1])
                molecule['y'] = float(coordinates[3])
                molecule['z'] = float(coordinates[5])
            elif line.startswith('------------------------'):
                molecules.append(molecule)
                molecule = {}
    return molecules

def plot_molecules(molecules):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    for molecule in molecules:
        ax.scatter(molecule['x'], molecule['y'], molecule['z'], label=f"{molecule['name']} (ID: {molecule['id']})")

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()

if __name__ == "__main__":
    file_path = "output.txt"  # Remplacez par le chemin de votre fichier
    molecules = read_molecule_file(file_path)
    plot_molecules(molecules)