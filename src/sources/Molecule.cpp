// Molecule.cpp

#include "Molecule.h"
void createMoleculesFromAtoms(const std::vector<Atom>& atoms, std::vector<Molecule>& molecules) {
    for (const auto& atom : atoms) {
        bool moleculeExists = false;

        // Vérifie si la molécule existe déjà dans le vecteur de molécules 
        for (auto& molecule : molecules) {
            // Si la molécule existe avec le même nom que le nom de l'atome, alors ajoutez l'atome au vecteur d'atomes de la molécule
            if (molecule.name == atom.name) {
                molecule.atoms.push_back(atom);
                moleculeExists = true; // La molécule existe déjà
                break;
            }
        }

        // Si la molécule n'existe pas encore, la crée
        if (!moleculeExists) {
            Molecule newMolecule;
            newMolecule.name = atom.name; // Utilisez l'opérateur '=' pour définir le nom
            newMolecule.moleculeFeuillet = "default"; // Vous pouvez le changer si nécessaire
            newMolecule.moleculeId = std::stoi(atom.name.substr(0, atom.name.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
            newMolecule.atoms = { atom };

            molecules.push_back(newMolecule);
        }
    }

    // Calculer le centre de masse pour chaque molécule
    for (auto& molecule : molecules) {       
        molecule.centerOfMass =  calculateCenterOfMass(molecule.atoms);
    }

     // Calculer l'atom de reference de la molecule pour chaque molécule
    for (auto& molecule : molecules) {       
        molecule.atomRef = determinateReferenceAtom(molecule);
    }
}

Vector3D calculateCenterOfMass(const std::vector<Atom>& atoms) {
    float totalMass = 0.0f;
    Vector3D centerOfMass;
    centerOfMass.x =0.0f;
    centerOfMass.y=0.0f;
    centerOfMass.z=0.0f;
    for (const auto& atom : atoms) {
        // Vous pouvez utiliser la masse atomique ou simplement considérer chaque atome comme ayant une masse unitaire
        float atomMass = 1.0f;

        centerOfMass.x += atom.x * atomMass;
        centerOfMass.y += atom.y * atomMass;
        centerOfMass.z += atom.z * atomMass;

        totalMass += atomMass;
    }

    centerOfMass.x /= totalMass;
    centerOfMass.y /= totalMass;
    centerOfMass.z /= totalMass;

    return centerOfMass;
}

// Les fonctions calculateOrientation() et determinateReferenceAtom() semblent non implémentées.
// Vous devez ajouter leur implémentation selon vos besoins.
int calculateOrientation() {
    // Ajoutez votre implémentation ici
    return 0; // Remplacez 0 par la valeur réelle ou le résultat de votre fonction
}

//DPPC = N , 
AtomReference determinateReferenceAtom(Molecule molecule) {
        if(molecule.name.find("DPPC") != std::string::npos){
            for (const auto& atom: molecule.atoms){
                if(atom.atomType.find("N") != std::string::npos){
                    molecule.atomRef.name = atom.atomType;
                    molecule.atomRef.pos.x = atom.x;
                    molecule.atomRef.pos.y = atom.y;
                    molecule.atomRef.pos.z = atom.z;
                }
            }
        }
    return molecule.atomRef; // Remplacez 0 par la valeur réelle ou le résultat de votre foncn
}

// Fonction pour sauvegarder les molécules dans un fichier
void saveMoleculesToFile(const std::vector<Molecule>& molecules, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier : " << filename << std::endl;
        return;
    }

    for (const auto& molecule : molecules) {
        outputFile << "Molecule Name: " << molecule.name << std::endl;
        outputFile << "Molecule ID: " << molecule.moleculeId << std::endl;
        outputFile << "Center of Mass: x " << molecule.centerOfMass.x << " y " << molecule.centerOfMass.y << " z " << molecule.centerOfMass.z << std::endl;
        outputFile << "------------------------" << std::endl;
    }

    outputFile.close();
}