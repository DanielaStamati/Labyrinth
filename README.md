Labyrinth
=========

A character walking though a labyrinth in search for a portal to get him out.

Cuprins 
1. Descriere generala 
2. Utilizare 
3. Implementare 
4. Testare 
5. Probleme Aparute 
6. Continutul Arhivei 
7. Functionalitati 

 
1. Descriere generala
Construirea unui labirint si miscarea unui personaj in acesta pana la atingerea unui portal. Aplicatia 
comuta camera First Person, Third Person si Map View.
 
2. Utilizare 

Input Tastatura 

	- UP_KEY miscarea jucatorului in directia orientarii acestruia 
	- DOWN_KEY  miscare spate o LEFT_KEY miscare stanga 
	- RIGHT_KEY miscare dreapta 
	- ‘y’   rotire pe axa OY counterclockwise 
	- ‘u’   rotire pe axa OY clockwise 
	- ‘x’,’X’  rotire pe axa OX 
	- ‘z’,’Z’  rotire pe axa OZ 
	- ‘c’      comutare camera 
 
3. Implementare 
Platforma: Windows 7, Visual Studio Express. 

- Camera TPS am implementat-o pe baza camerei FPS, folosind o rotire de tip FPS si o translatie in spate. 
La fiecare mutare, misc camera FPS, urmand ca pozitia jucatorului sa o egalez cu vectorul position a camerei FPS. 

- Coliziunile le testez cu bounding spheres. 
Mai mult informatii se gasesc in comentariile din cod.

 
4. Continutul Arhivei 
Folderul levels contine codificarea hartilor folosite in joc.  
  - camera.cpp, camera.h - obiecte de tip camera si operatii aplicate asupra ei (translatie,  rotire)   
  - maze.cpp, Maze.h - obiect care codifica labirintul, contine coordonatele si caracteristicile obiectelor din labirint. 
  - Vector3D.h – vector de coordonate, contine operatii aplicate asupra acestuia. 
  - main.cpp 
  - README.pdf (acest fisier)  


5. Functionalitati 
  - Miscare prin labirint 
  - Comutare camera 
  - Rotirea personajului pe toate axele o Coliziune cu obstacolele o Functionalitati Bonus  
  - Puteri speciale (la coliziunea cu ceainic-ul jucatorul se face mai mic si poate trece prin pasaje mai inguste). 
  - Posibilitatea de a trece de la un nivel la altul prin portale. (portalul rosu te duce intr-un nivel superior, iar 
    cel albastru in unul inferior).   
