# - Try to find GLUtil
# Once done this will define
#  GLUtil_FOUND - System has GLUtil
#  GLUtil_INCLUDE_DIRS - The GLUtil include directories
#  GLUtil_LIBRARIES - The libraries needed to use GLUtil

include(LibFindMacros)

libfind_package(GLUtil Freetype)
libfind_package(GLUtil GLEW)
libfind_package(GLUtil OpenGL)
libfind_package(GLUtil GTK3 3.0 COMPONENTS gtkmm gtk)
libfind_package(GLUtil PNG)

find_path(GLUtil_INCLUDE_DIR
   NAMES text.h pngUtil.h renderList.h
   PATHS /usr/include/GLUtil /usr/local/include/GLUtil
)

set (
   GLUtil_COMPONENTS
  textUtil
  renderUtil
   imageUtil
   threadUtil
   gtkUtil
  glUtil
  json_linux-gcc-4.5.3_libmt
   )

foreach(COMPONENT ${GLUtil_COMPONENTS})
   find_library(GLUtil_${COMPONENT}
      ${COMPONENT}
   PATHS /usr/lib/GLUtil /usr/local/lib/GLUtil)
list(APPEND GLUtil_LIBRARY ${GLUtil_${COMPONENT}})

endforeach()
list(APPEND GLUtil_LIBRARY ${FREETYPE_LIBRARIES} rt ${PNG_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GTK3_LIBRARIES})

set(GLUtil_PROCESS_INCLUDES GLUtil_INCLUDE_DIR FREETYPE_INCLUDE_DIRS)
set(GLUtil_PROCESS_LIBS GLUtil_LIBRARY FREETYPE_LIBRARIES )
libfind_process(GLUtil)


