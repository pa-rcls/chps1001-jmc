
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def plot_atoms(file_name, color):
    with open(file_name, 'r') as f:
        lines = f.readlines()

    x = [float(line.split()[0]) for line in lines]
    y = [float(line.split()[1]) for line in lines]
    z = [float(line.split()[2]) for line in lines]

    ax.scatter(x, y, z, color=color, s=5)

# Créer une figure 3D
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Ajouter les molécules des deux feuilles
plot_atoms('feuillet1.txt', color='blue')
plot_atoms('feuillet2.txt', color='red')

# Mise en forme du graphique
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Molécules dans les Feuillets Lipidiques')

# Afficher le graphique
plt.show()