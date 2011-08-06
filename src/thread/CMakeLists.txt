set(HDRS 
      message.h
      queue.h
      pool.h
   )
 
set(SRCS
      queue.cpp
      pool.cpp
)
 
add_library(threadUtil ${HDRS} ${SRCS})
target_link_libraries(threadUtil pthread)

install(TARGETS threadUtil ARCHIVE DESTINATION lib/GLUtil)
install(FILES ${HDRS} DESTINATION include/GLUtil)
