set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(Test ${HDRS} ${SRCS})
target_link_libraries(Test imageUtil textUtil glUtil renderUtil ${SFML_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

include_directories(util)
include_directories(image)
include_directories(render)
include_directories(text)

add_subdirectory(util)
add_subdirectory(text)
add_subdirectory(image)
add_subdirectory(render)

