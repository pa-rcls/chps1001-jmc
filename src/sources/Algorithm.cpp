#include "Algorithm.h"

float calculateMedian(const std::vector<Atom>& atoms, char dimension) {
    // Implémentation du calcul de la médiane (comme dans l'exemple précédent)
}

void processMolecules(Bilayer& bilayer, const std::vector<Molecule>& allMolecules,
                      const std::vector<Atom>& allAtoms) {
    // Calcul du plan médian
    float referencePointX = calculateMedian(allAtoms, 'x');
    float referencePointY = calculateMedian(allAtoms, 'y');
    float referencePointZ = calculateMedian(allAtoms, 'z');

    // Affectation des feuilles
    for (const auto& molecule : allMolecules) {
        // Calcul de la position du centre de masse de la molécule
        float moleculeCenterMassX = 0.0f;
        float moleculeCenterMassY = 0.0f;
        float moleculeCenterMassZ = 0.0f;

        for (const auto& atom : molecule.atoms) {
            moleculeCenterMassX += atom.x;
            moleculeCenterMassY += atom.y;
            moleculeCenterMassZ += atom.z;
        }

        moleculeCenterMassX /= static_cast<float>(molecule.atoms.size());
        moleculeCenterMassY /= static_cast<float>(molecule.atoms.size());
        moleculeCenterMassZ /= static_cast<float>(molecule.atoms.size());

        // Comparaison avec le point de référence
        if (moleculeCenterMassX > referencePointX) {
            bilayer.addMolecule(molecule, Bilayer::Part::Upper);
        } else {
            bilayer.addMolecule(molecule, Bilayer::Part::Lower);
        }
    }
}