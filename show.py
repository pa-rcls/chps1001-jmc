import matplotlib
matplotlib.use('TkAgg')  # Utilisez un backend adapté à votre environnement
import matplotlib.pyplot as plt


def read_atom_positions(file_path):
    positions = []
    with open(file_path, 'r') as file:
        for line in file:
            data = line.strip().split()
            if len(data) == 6:
                x, y, z = map(float, data[3:6])
                positions.append((x, y, z))
    return positions

def plot_atoms_3d(atom_positions):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    x, y, z = zip(*atom_positions)
    ax.scatter(x, y, z, c='r', marker='o')

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()

if __name__ == "__main__":
    file_path = "positionatoms.txt"
    atom_positions = read_atom_positions(file_path)
    plot_atoms_3d(atom_positions)