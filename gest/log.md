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

## 20220305 AdrianLarrosa @(2h)
Se ha juntado el código de eliminar jugador/enemigo con el disparo en todas las direcciones, para así poder disparar a la dirección hacia la que vaya el jugador y poder eliminar a un jugador/enemigo pudiendo apuntar. Se han creado las clases ia y enemy para poder desarrollar en ellas los diferentes tipos de IA.

## 20220309 AdrianLarrosa @(2h 20 min)
Se ha creado el script setup.sh y modificado el gitignore para no subir los recursos a git y una vez descargado el repositorio ujecutar el fichero para descargar los recursos.

## 20220310 AdrianLarrosa @(2h 50 min)
Se ha implementado la IA tipo patrol para que un enemigo se mueva continuamente, en base a un patrón que se le asigne al crear el objeto de tipo IA.
