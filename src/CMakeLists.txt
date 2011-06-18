set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(Test ${HDRS} ${SRCS})
target_link_libraries(Test text util matrix ${SFML_LIBRARY} ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} ${OPENGL_LIBRARY})

add_subdirectory(util)
add_subdirectory(text)
