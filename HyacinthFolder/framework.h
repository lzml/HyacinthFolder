// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "../miniblink/wke.h"

#include <base/bind_internal.h>
#include <base/bind.h>

#include <base/message_loop/message_loop.h>
#include <base/win/wrapped_window_proc.h>

#include <base/memory/singleton.h>

#include <base/files/file_path.h>

#include <base/base_paths.h>
#include <base/base_paths_win.h>
#include <base/path_service.h>

#include <base/strings/string16.h>
#include <base/strings/string_util.h>
#include <base/strings/utf_string_conversions.h>

#define CLASSNAME   L"HyacinthFolderClass"

