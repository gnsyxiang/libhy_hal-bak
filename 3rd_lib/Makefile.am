# ===============================================================
# 
# Release under GPLv-3.0.
# 
# @file    Makefile.am
# @brief   
# @author  gnsyxiang <gnsyxiang@163.com>
# @date    08/05 2021 13:45
# @version v0.0.1
# 
# @since    note
# @note     note
# 
#     change log:
#     NO.     Author              Date            Modified
#     00      zhenquan.qiu        08/05 2021      create the file
# 
#     last modified: 08/05 2021 13:45
# ===============================================================

libs_3rd_dst_path 	= $(prefix)
libs_3rd_src_path 	= $(top_srcdir)/3rd_lib/install

install-exec-hook:
	${MKDIR_P} ${libs_3rd_dst_path};
	cp -ar ${libs_3rd_src_path}/* ${libs_3rd_dst_path};

uninstall-hook:
	rm -rf ${libs_3rd_dst_path}/*
