#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/enemigo.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/enemigo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fantasma.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/minotauro.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/golem.cpp"
    
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

