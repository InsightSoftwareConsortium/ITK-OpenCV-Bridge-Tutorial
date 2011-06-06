find_package(LATEX)

if(NOT PDFLATEX_COMPILER)
  message("pdflatex compiler was not found. Please pass to advanced mode and provide its full path" FATAL_ERROR)
endif()

file(GLOB_RECURSE PNG_FILES "*.png")

add_subdirectory(Tutorial)

