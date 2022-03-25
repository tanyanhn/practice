add_custom_target(doc
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
COMMAND xelatex doc.tex
COMMAND xelatex doc.tex
)

add_custom_target(cleanDoc
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
COMMAND rm -rf *.pdf *.aux *.log
)
