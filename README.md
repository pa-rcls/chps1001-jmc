# chps1001-jmc
L’objectif de ce projet sera de développer un outil d’analyse de membrane lipidique qui sera capable d’attribuer les lipides à un feuillet spécifique.
## How to compile code :
```make -j```
## How to run code :
```./LipidX -source=chemin/vers/votre/fichier/gro```
- Optionnel :
- - ```-solver=[Graph][GS][AM]``` -> par defaut Graph
- - ```-n_slices=num_slices_in_GS``` -> pour le solver GS, par defaut 5