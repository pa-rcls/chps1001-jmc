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
            newMolecule.feuillet =0; // Vous pouvez le changer si nécessaire
            newMolecule.moleculeId = std::stoi(atom.name.substr(0, atom.name.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
            newMolecule.atoms = { atom };

            molecules.push_back(newMolecule);
        }
    }

    // Calculer le centre de masse pour chaque molécule, l'atom de reference et l'orientation
    for (auto& molecule : molecules) {       
        molecule.centerOfMass =  calculateCenterOfMass(molecule.atoms);
        molecule.atomRef = determinateReferenceAtom(molecule);
        molecule.orientation = calculateOrientation(molecule);
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

int calculateOrientation(const Molecule& molecule) {
    // Obtenez la position du centre de masse
    float comz = molecule.centerOfMass.z;

    // Obtenez la position de l'atome de référence
    float refz = molecule.atomRef.pos.z;

    // Comparaison pour déterminer l'orientation
    if (fabs(refz - comz) > 0.0001) {
        // Si l'atome de référence est plus haut que le centre de masse
        // alors l'orientation est 1 (vers le haut), sinon c'est 0 (vers le bas)
        return (refz > comz) ? 1 : 0;
    } else {
        // Si les positions sont presque égales, on peut considérer les orientations comme égales
        return 0;
    }
}
 
//DPPC ,DUPC et POPC = N , CHOL = ROH
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
        if(molecule.name.find("DUPC") != std::string::npos){
            for (const auto& atom: molecule.atoms){
                if(atom.atomType.find("N") != std::string::npos){
                    molecule.atomRef.name = atom.atomType;
                    molecule.atomRef.pos.x = atom.x;
                    molecule.atomRef.pos.y = atom.y;
                    molecule.atomRef.pos.z = atom.z;
                }
            }
        }
        if(molecule.name.find("POPC") != std::string::npos){
            for (const auto& atom: molecule.atoms){
                if(atom.atomType.find("N") != std::string::npos){
                    molecule.atomRef.name = atom.atomType;
                    molecule.atomRef.pos.x = atom.x;
                    molecule.atomRef.pos.y = atom.y;
                    molecule.atomRef.pos.z = atom.z;
                }
            }
        }
        if(molecule.name.find("CHOL") != std::string::npos){
            for (const auto& atom: molecule.atoms){
                if(atom.atomType.find("ROH") != std::string::npos){
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
    std::ofstream fichier(filename);

    if (fichier.is_open()) {
        for (const Molecule& mol : molecules) {
            fichier << mol.name << " " << mol.centerOfMass.x << " " << mol.centerOfMass.y << " " << mol.centerOfMass.z << " " << mol.feuillet << "\n";
        }

        fichier.close();
        std::cout << "Les données ont été sauvegardées dans le fichier " << filename << ".\n";
    } else {
        std::cerr << "Impossible d'ouvrir le fichier " << filename << " pour l'écriture.\n";
    }
}


Vector3D calculateMedianPosition(const std::vector<Molecule>& molecules) {
    // Tri des molécules en fonction de leur position en y
    std::vector<Molecule> sortedMolecules = molecules;
    std::sort(sortedMolecules.begin(), sortedMolecules.end(), [](const Molecule& a, const Molecule& b) {
        return a.centerOfMass.y < b.centerOfMass.y;
    });

    // Calcul de la médiane
    size_t size = sortedMolecules.size();
    Vector3D medianPosition = {0.0f, 0.0f, 0.0f};
    if (size % 2 == 0) {
        // Si le nombre de molécules est pair, prendre la moyenne des deux molécules du milieu
        size_t mid = size / 2;
        medianPosition.x = (sortedMolecules[mid - 1].centerOfMass.x + sortedMolecules[mid].centerOfMass.x) / 2.0f;
        medianPosition.y = (sortedMolecules[mid - 1].centerOfMass.y + sortedMolecules[mid].centerOfMass.y) / 2.0f;
        medianPosition.z = (sortedMolecules[mid - 1].centerOfMass.z + sortedMolecules[mid].centerOfMass.z) / 2.0f;
    } else {
        // Si le nombre de molécules est impair, prendre simplement la position de la molécule du milieu
        size_t mid = size / 2;
        medianPosition = sortedMolecules[mid].centerOfMass;
    }

    return medianPosition;
}

Vector3D calculateAveragePosition(const std::vector<Molecule>& molecules) {
    // Calcul de la moyenne
    Vector3D averagePosition = {0.0f, 0.0f, 0.0f};
    size_t size = molecules.size();
    
    for (const auto& molecule : molecules) {
        averagePosition.x += molecule.centerOfMass.x;
        averagePosition.y += molecule.centerOfMass.y;
        averagePosition.z += molecule.centerOfMass.z;
    }

    averagePosition.x /= static_cast<float>(size);
    averagePosition.y /= static_cast<float>(size);
    averagePosition.z /= static_cast<float>(size);

    return averagePosition;
}
void assignFeuilletValues(std::vector<Molecule>& molecules) {
    // Calcul de la moyenne des positions des centres de masse
    Vector3D averagepos = calculateAveragePosition(molecules);
    
    // Plage de variation autour de la moyenne
    double variationThreshold = 0.3;

    // Attribution des valeurs de feuillet en fonction de la position relative à la moyenne
    for (Molecule& molecule : molecules) {
        double zDifference = std::abs(molecule.centerOfMass.z - averagepos.z);

        if (zDifference > variationThreshold) {
            // Si la position z diffère de plus de 0.3 de la moyenne
            if (molecule.centerOfMass.z > averagepos.z) {
                molecule.feuillet = 1;  // Si au-dessus de la moyenne avec une différence significative
            } else {
                molecule.feuillet = 0;  // Si en dessous de la moyenne avec une différence significative
            }
        } else {
            // Si la position z est dans la plage de variation autour de la moyenne
            // Ajoutez ici la logique pour influencer l'orientation en fonction de la direction
            // Actuelle : Utilisez simplement la valeur de feuillet existante (1 ou 0) comme exemple
            molecule.feuillet = molecule.feuillet;  
        }
    }
}