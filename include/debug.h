#ifndef __DEBUG_H
#define __DEBUG_H
#include "ds_comm.h"
#include <stdarg.h>


// 开启的信息输出配置，值越大，输出的调试信息越多
#define DBG_LEVEL_NONE           0         // 不开启任何输出
#define DBG_LEVEL_ERROR          1         // 只开启错误信息输出
#define DBG_LEVEL_WARNING        2         // 开启错误和警告信息输出
#define DBG_LEVEL_INFO           3         // 开启错误、警告、一般信息输出

/**设置信息输出等级，登记越高，输出的信息越多 */
#define DBG_LEVEL_CTL_SET     3  

/**
 * @brief 格式化日志并打印到串口
 */
void dbg_print(int level,const char* file, const char* func, int line, const char* fmt, ...);

#define dbg_info(fmt, ...)  dbg_print( DBG_LEVEL_INFO,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define dbg_error(fmt, ...)  dbg_print( DBG_LEVEL_ERROR,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define dbg_warning(fmt, ...) dbg_print( DBG_LEVEL_WARNING,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#endif