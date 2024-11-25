#子目录所有文件赋值给 _SUB_SOURCES变量
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} src_sources)
# message(STATUS src_sources=${src_sources})
#设置_SUB_SOURCES变量，让它能被根目录访问
set(src_sources ${src_sources} PARENT_SCOPE)
