import sys
import matplotlib.pyplot as plt
from joblib import Parallel, delayed

def read_gro_file(file_path):
    atoms = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines[2:-1]:
            atom_info = {
                'atom_number': line[:9].strip(),  # Garder la partie non numérique
                'atom_name': line[10:15].strip(),
                'x': float(line[20:28]),
                'y': float(line[28:36]),
                'z': float(line[36:44])
            }
            #print(atom_info)
            atoms.append(atom_info)
    return atoms

def process_atom(atom):
    if 'DPPC' in atom['atom_number'] or 'CHOL' in atom['atom_number'] or 'POPC' in atom['atom_number']:
        color = hash(atom['atom_number']) % 255.
        color = color / 255
        #print(color)
        return (atom['x'], atom['y'], color, atom['atom_name'])

def plot_filtered_atoms(atoms, name, num_cores):
    plt.figure(figsize=(8, 6))

    # Define the number of parallel jobs
    #num_cores = 2  # Adjust this according to your system

    # Parallelize the loop to collect data for plotting
    plot_data = Parallel(n_jobs=num_cores)(delayed(process_atom)(atom) for atom in atoms)

    # Unpack the plot data
    x_values, y_values, colors, atom_names = zip(*[data for data in plot_data if data is not None])

    # Plot the collected data
    plt.scatter(x_values, y_values, s=1, c=colors)

    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title(name + ' Atoms Representation (Filtered)')
    plt.grid()
    plt.savefig(name + '.png')  # Save the figure to an image file

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python script_name.py input_file.gro output_image_namenum_cores")
    else:
        file_path = sys.argv[1]
        atoms_data = read_gro_file(file_path)
        plot_filtered_atoms(atoms_data,sys.argv[2],int(sys.argv[3]))
