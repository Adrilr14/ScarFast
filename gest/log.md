# Log del trabajo realizado por dia

## 20220305 ElenaAlcaraz @(1h 15min)
Creación de clases para las armas y sus herencias. Cambio de sprite.

## 20220306 ElenaAlcaraz @(1h 20min)
Cuando se selecciona el arma espada se cambia el sprite.

## 20220306 AlejandroGomariz @(1h 10 min)
Crear la fachada entre el entorno gráfico SFML y el entorno del juego.

## 20220306 AdrianLarrosa @(2h)
Crear la clase colision para comprobar si colisiona el jugador con algún sprite cuando está en movimiento, si colisiona no puede avanzar hacia esa dirección.

## 20220307 ElenaAlcaraz @(2h 40min)
Cuando el personaje tiene el arma de disparar, aparece la bola (el disparo) en su posición.

## 20220307 AlejandroGomariz @(3h 10 min)
Se han implementado un cargador de mapas, de momento hemos creado un mapa por defecto pero se iran ampliando en siguientes hitos.

## 20220307 ElenaAlcaraz @(15min)
Disparo en movimiento.

## 20220308 DanielSantoyo @(1h 30 min)
Recopilación de información sobre el movimiento fluido de dos jugadores a la vez.

## 20220310 DanielSantoyo @(2h 30 min)
Creación del movimiento fluido en ámbos jugadores con las teclas correspondientes.

## 20220312 AlejandroGomariz @(8h 10 min)
Se han creado las colisones con el mapa, la forma en la que hemos implementado estas colisiones ha sido calculando el cuadrante en el que se encuentra en jugador x. Mirar lo que tiene alrededor para saber si colisiona con algo. Así evitamos ver si colisiona con algo que no esta cerca del jugador.

## 20220312 ElenaAlcaraz @(1h 30min)
Asignar las direcciones al jugador para poder dirsparar en esas direcciones

## 20220313 AdrianLarrosa @(3h 20 min)
Se ha creado la clase powerup, y se han usado las clases arma, magia, disparo, espada y player previamente creadas. Se le ha añadido una variable kit a player para saber si tiene el kit cogido. En la ventana encontramos un sprite arriba a la izquierda que es un arma de tipo magia que si el jugador colisiona con ella la coge y cambia de arma. También encontramos un sprite abajo a la izquierda que es el kit, si el jugador se acerca y colisiona lo coge y eso imposibilita que pueda usar el arma, simpulsa enter soltará el kit y aparecerá en el mismo lugar. Por último encontamos un sprite abajo a la derecha que es un powerup, si el jugador se acerca y colisiona lo cogerá.

## 20220313 AlejandroGomariz @(1h 40 min)
Se han implementado las 8 direcciones para que tanto el jugador 1 como el jugador 2 puedan moverse con total libertal por el mapa.

## 20220313 ElenaAlcaraz @(2h 30min)
El jugador puede disparar en 4 direcciones. Si tiene en arma de espada cambia de sprite y si tiene el de disparar dispara en la dirección que este mirando.

## 202203014 DanielSantoyo @(1h 45 min)
Recopilación de información sobre cómo mostrar texto con sfl y ejecución del temporizador de manera correcta con algún pequeño detalle y efecto que otorga dinamismo al trancurso del tiempo.

## 202203015 AdrianLarrosa @(1h 10 min)
Se ha implmentado que cuando el jugador coja el powerup y pulse shift derecho lo usa y le triplica la velocidad.

## 20220319 AlejandroGomariz @(2h)
Recopilar información de como crear un sistema centralizado para el hito 2.

## 20220320 AdrianLarrosa @(3h 10 min)
Se ha implementado que cuando el jugador use el arma si es una espada y está colisionando con el jugador de abajo a la derecha le quita 10 HP, y como el jugador se ha creado con 10 HP lo elimina. También se ha implementado que cuando el jugador use el arma y sea magia (tendrá que coger la magia previamente, que está arriba a la izquierda), saldrá el disparo (siempre hacia abajo), si colisiona con el otro jugador le quitará 10 de HP y lo eliminará.

## 20220320 ElenaAlcaraz @(2h)
Menu básico, selección de 3 opciones y guardar seleccionado. Cerrar ventana, cargar juego y opciones, a falta de que cambie a esas ventanas.

## 20220320 AlejandroGomariz @(2h 10 min)
Se ha creado el respawn para el jugador si gana la ronda, y cuando se acerca al respawn del otro jugador con el kit de supervivencia se gana la ronda automáticamente. Al ganar la ronda el jugador aparece otra vez en su spawn.

## 20220325 AdrianLarrosa @(2h)
Se ha juntado el código de eliminar jugador/enemigo con el disparo en todas las direcciones, para así poder disparar a la dirección hacia la que vaya el jugador y poder eliminar a un jugador/enemigo pudiendo apuntar. Se han creado las clases ia y enemy para poder desarrollar en ellas los diferentes tipos de IA.

## 20220325 AlejandroGomariz @(3h)
Se han arreglado algunos fallos con las colisiones con el mapa que no se detectaban de forma correcta y provocaba huecos entre el mapa y el jugador.

## 202203026 AdrianLarrosa @(2h 20 min)
Se ha creado el script setup.sh y modificado el gitignore para no subir los recursos a git y una vez descargado el repositorio ujecutar el fichero para descargar los recursos.

## 20220401 AlejandroGomariz DanielSantoyo @(1h 30 min)
Se han juntado la rama developer con el prototipo de temporizador.

## 20220404 AdrianLarrosa @(2h 50 min)
Se ha implementado la IA tipo patrol para que un enemigo se mueva continuamente, en base a un patrón que se le asigne al crear el objeto de tipo IA.

## 20220401 AlejandroGomariz AdrianLarrosa @(2h 30 min)
Se han juntado la rama developer con el prototipo del disparo.

## 20220402 AlejandroGomariz @()
Bucle interpolado

## 20220403 AlejandroGomariz @()
Movimiento mapa más dos jugadores

## 20220404 ElenaAlcaraz @(4h 30 min)
Se ha implementado la IA tipo pursuit para que un enemigo tendrá un rango del que cuando el jugado lo toque el enemigo irá a por él y cuando el jugador salga del rango, el enemigo volverá a su posición inicial.

## 20220406 AlejandroGomariz @()
Mapa más disparos

## 20220409 AlejandroGomariz @()
Disparo

## 20221304 AlejandroGomariz @()
Estados del mapa y menu estados

## 20221504 AlejandroGomariz @()
Respawns y cambios en el mapa

## 20221804 Daniel Santoyo @(2h)
Búsqueda, selección y recorte de los sonidos del juego

## 20222504 Daniel Santoyo @(4h)
Creación de todas las clases relacionadas con el sonido (audios cortos y música).

## 20220320 PaulaAlonsoMorales @(3h)
Se han creado los dos menus el principal y el de pausa y se han unido con el proyecto.

## 20221104 Pablo García @(3h 30 min)
Implementación del HUD, tanto de la vida como del objeto. Cada corazón representa 20 de vida, y cada vez que se coge un objeto aparece en pequeño en la parte de arriba de la pantalla.

## 20222204 AlejandroGomariz @()
Ganar partida

## 20222504 AlejandroGomariz @()
PowerUps

## 20222504 Pablo García @(2h 30 min)
Cambio de toda la parte del Hud a develop.

## 20230504 AlejandroGomariz @()
Falta arreglar un powerUp spikes

## 20223004 Elena Alcaraz @(10h 45 min)
Edición de sprites en GIMP. Editar cada sprite y escalar cada uno. Generar las imágenes de cada animación junto con su JSON.

## 20230105 AlejandroGomariz @()
Anmaciones

## 20220205 Elena Alcaraz @(8h)
Animaciones del primer jugador, pero solo la de andar sin cambios de estado.

## 20220305 Daniel Santoyo @(2h 30 min)
Implementación de algunos de los sonidos en develop.

## 20220305 Alejandro Gomariz @()
Vida personajes y animaciones v2

## 20220405 Adrián Larrosa @()
Implementación de la IA shooter

## 20220505 Adrián Larrosa @()
Implementación de la IA patrol y pursuit

## 20220605 Elena Alcaraz @(4h)
Animaciones del primer jugador terminadas, con cambios de estado, andar izquierda y derecha, morir, atacar e idle.

## 20220705 Alejando Gomariz @(4h)
Arreglo disparo y arreglo fallo animaciones

## 20220605 Daniel Santoyo @(3h)
Respawn del jugador cuando muere, regenrando tanto su posición como su vida iniciales.

## 20220805 Pablo García @(3h)
Unión de toda la vida del jugador con el hud, cuadrando que baje todo a la vez de manera correcta.

## 20220805 Elena Alcaraz @(6h)
Animaciones para el segundo jugador, funcionamiento de las animaciones para ambos jugadores con sus estados.

## 20220905 Alejando Gomariz @(4h)
Guarda

## 20221005 Alejando Gomariz @(4h)
Cambios animaciones

## 20221105 Adrián Larrosa @(4h 20 min)
Enemigos en el mapa, IA patrol, y tiempo arreglado

## 202201205 Daniel Santoyo @(3h)
Realización de la cámara del juego.

## 20221205 Alejando Gomariz @(4h)
HUD con powerUps random

## 20221205 Adrián Larrosa @(3h 30 min)
IA pursuit funcional en el mapa

## 20221305 Elena Alcaraz @(5h 30 min)
Edición de la escala de todos los sprites para arreglar el setOrigin.

## 20221305 Adrián Larrosa @(2h 50 min)
IA shooter dispara hacia el jugador con una cadencia

## 20221405 Daniel Santoyo @(6h)
Creación de mapas según la dificultad.
 
## 20221405 Elena Alcaraz @(8h 30 min)
Animaciones enemigos con sus 4 estados, andar, parado, morir y atacar.

## 20221405 Pablo García @(5h)
Creación del menú y preselección.

## 20221505 Elena Alcaraz @(6h)
Edición de escala de los sprites. Cada uno tiene una escala distinta. Arreglo de error que se hacían pequeños al atacar y morir.

## 20221505 Alejando Gomariz @(4h)
Arreglo colisiones y mejora de rendimiento

## 20221505 Adrián Larrosa @(8h 30 min)
Enemigos atacan a los jugadores, clase armas actualizada, recursos eliminados, disparo enemigo cambiado, control frames animaciones, jugador inmune cuando ataca y countdown disparo de jugadores

## 20221605 Elena Alcaraz @(3h 30 min)
Movimiento de atacar los enemigos de tipo ia pursuit, que cuando mueran los enemigos no quiten vida, añadir la animación, y respawn de los enemigos. 

## 20221605 Daniel Santoyo @(1h)
He realizado la portada y el background de controles.

## 20221605 Adrián Larrosa @(3h)
Los enemigos se ponen en rojo cuando reciben daño, jugador no pierde vida cuando esta muerto, disparo arreglado y jugador con estado atacar quita vida durante la animación 

## 20221605 Adrián Larrosa @(5h)
Respawn de los enemigos por tiempo, también se reinician cuando acaba la ronda. Jugador no se mueve muerto
