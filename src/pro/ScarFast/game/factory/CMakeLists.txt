#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/map.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/arma.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/disparo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ronda.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/powerup.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/animation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hud.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemy.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MainSound.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

