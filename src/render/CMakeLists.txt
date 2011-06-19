set(HDRS 
      
   renderList.h
   )
 
set(SRCS
   render.cpp
   renderList.cpp
)
 
add_library(render ${HDRS} ${SRCS})
target_link_libraries(render glUtil pngUtil matrix ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

