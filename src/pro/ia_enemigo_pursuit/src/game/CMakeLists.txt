#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libSrc PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/arma.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/disparo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/powerup.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemy.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libSrc PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

