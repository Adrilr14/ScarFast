#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ControllerMan.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SfmlGraphics.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Menu.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MenuP.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MenuJugar.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/MenuControles.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ShortSound.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/LongSound.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Buffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../game/factory/MainSound.cpp"

)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}"
)

