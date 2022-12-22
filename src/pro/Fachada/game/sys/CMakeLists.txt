#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/collision.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/input.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/physics.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

