set(HDRS 
      glUtil.h
      util.h
      matrix.h
   )
 
set(SRCS
      glUtil.cpp
      util.cpp
      matrix.cpp
)
 
add_library(glUtil ${HDRS} ${SRCS})
target_link_libraries(glUtil ${GLEW_LIBRARY} ${OPENGL_LIBRARY} rt)

install(TARGETS glUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
