# content/pNN-xxx/NN-xxx/CMakeLists.txt を持つ章を自動で取り込む
# 
# 章を追加しても、このファイルを編集する必要はない。

file(GLOB chapter_lists CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/p[0-9][0-9]-*/[0-9][0-9]-*/CMakeLists.txt"
)

foreach(list_file IN LISTS chapter_lists)
    cmake_path(GET list_file PARENT_PATH chapter_dir)
    add_subdirectory("${chapter_dir}")
endforeach()