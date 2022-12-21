#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libSys PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/collision.cpp"
)

#Y donde se encuentran los .h
target_include_directories(libSys PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

