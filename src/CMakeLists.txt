set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(Test ${HDRS} ${SRCS})
target_link_libraries(Test gtkUtil imageUtil textUtil glUtil renderUtil threadUtil ${SFML_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

include_directories(util)
include_directories(image)
include_directories(render)
include_directories(text)
include_directories(thread)
include_directories(gtk)

add_subdirectory(util)
add_subdirectory(image)
add_subdirectory(render)
add_subdirectory(text)
add_subdirectory(thread)
add_subdirectory(gtk)

