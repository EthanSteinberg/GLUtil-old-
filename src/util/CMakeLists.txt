set(HDRS 
      glUtil.h
   )
 
set(SRCS
      glUtil.cpp
)
 
add_library(glUtil ${HDRS} ${SRCS})
target_link_libraries(glUtil util ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

set(HDRS 
      util.h
   )
 
set(SRCS
      util.cpp
)

add_library(util ${HDRS} ${SRCS})
target_link_libraries(util rt)

set(HDRS 
      matrix.h
   )
 
set(SRCS
      matrix.cpp
)

add_library(matrix ${HDRS} ${SRCS})
target_link_libraries(matrix)
