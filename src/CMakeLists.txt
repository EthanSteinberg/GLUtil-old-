set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(Test ${HDRS} ${SRCS})
target_link_libraries(Test ${SFML_LIBRARY} ${GLEW_LIBRARY} ${FREETYPE_LIBRARIES} ${OPENGL_LIBRARY})

