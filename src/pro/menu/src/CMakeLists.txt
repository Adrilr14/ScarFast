#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libSrc PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menuP.cpp"
)


#Y donde se encuentran los .h
target_include_directories(libSrc PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)