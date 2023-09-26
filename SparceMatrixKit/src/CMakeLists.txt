project(SparceMatrixKit)

file(GLOB header_SRC
        "*.h"
        )

file(GLOB source_SRC
        "*.cpp"
        )

set(HEADER_FILES
        ${header_SRC}
        )

set(SOURCE_FILES
        ${source_SRC}
        )

add_library(SparceMatrixKit_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})