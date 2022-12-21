#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libSrc PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/arma.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/magia.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/espada.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/disparo.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libSrc PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

