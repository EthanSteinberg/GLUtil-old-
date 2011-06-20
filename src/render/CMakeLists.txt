set(HDRS 
   render.h
   renderList.h
   )
 
set(SRCS
   render.cpp
   renderList.cpp
)
 
add_library(renderUtil ${HDRS} ${SRCS})
target_link_libraries(renderUtil glUtil pngUtil ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

install(TARGETS renderUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
