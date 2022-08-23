#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/StateInit.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StateGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StateMenuPlay.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/StateControles.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

