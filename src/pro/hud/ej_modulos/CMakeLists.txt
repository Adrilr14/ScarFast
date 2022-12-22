#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/hud.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/arma.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/magia.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/espada.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/disparo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/game/powerup.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sys/collision.cpp"


    
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

