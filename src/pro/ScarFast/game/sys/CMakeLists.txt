#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/input.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/physics.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ia.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hp.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

