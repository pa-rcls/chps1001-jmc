#include "calcul.h"

Vector3D calculateCenterOfMass(const std::vector<Atom>& atoms) {
    Vector3D centerOfMass = {0.0f, 0.0f, 0.0f};
    float totalMass = 0.0f;

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