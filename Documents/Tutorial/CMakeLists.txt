project(ITKOpenCVBridgeTutorialPresentation)

file(GLOB TEX_FILES *.tex)

file(
  COPY  ${TEX_FILES}
  DESTINATION ${ITKOpenCVBridgeTutorialPresentation_BINARY_DIR}
  )

#
# This adds a custom target that generates the output document
# This target depends on the list of copied files created
# with the custom command above and the Plots target.
#
add_custom_target(ShortTutorialPresentation ALL
   COMMAND ${PDFLATEX_COMPILER}
        ${ITKOpenCVBridgeTutorialPresentation_SOURCE_DIR}/ITKOpenCVBridgeTutorial.tex
        -output-directory ${ITKOpenCVBridgeTutorialPresentation_BINARY_DIR}
   COMMAND ${PDFLATEX_COMPILER}
        ${ITKOpenCVBridgeTutorialPresentation_SOURCE_DIR}/ITKOpenCVBridgeTutorial.tex
        -output-directory ${ITKOpenCVBridgeTutorialPresentation_BINARY_DIR}
   DEPENDS ${COPY_RESULTS} ${REPORT_ELEMENTS}
   WORKING_DIRECTORY ${ITKOpenCVBridgeTutorialPresentation_BINARY_DIR}
   )

