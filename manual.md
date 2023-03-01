eelua 文档
--------------------------------

## 安装后目录结构说明

```
EverEdit/
  lua51.dll
  plugin/
    eelua.dll
  eelua/
    eelua_init.lua  # 启动初始化脚本
    eeluarc.lua     # 用户自定义配置脚本
    plugins/        # 自定义插件脚本
    scripts/        # 显示在 “扩展” -> “插件” -> “lua scripts” 下的脚本文件
```

## 命令窗口 lua 命令

打开命令窗口 C+K, C，输入 `lua print("hello world")` 即可。

你可以在这里执行一小段代码，除了内置的 lua 命令，还支持用户自定义命令处理逻辑（比如示例插件就注册了 CtrlP 和 CtrlPRg 命令）。

## 快捷键命令

默认提供了 `pl_eelua_execute_current_file` 命令，执行当前打开的 lua 脚本文件。

自带的插件示例 `plugins\ctrlp.lua` 提供了 `pl_ctrlp` 命令，用于列出当前工程下的文件列表、在工程下搜索文件内容（需要 ripgrep 支持，有需要请自行下载并将其加到环境变量 PATH 下）

通过菜单『工具』→『设置』→『快捷键』打开「快捷键」窗口，在最下方将上面命令绑定到自己熟悉的快捷键上。

比如将 `pl_eelua_execute_current_file` 绑定到 `C+F5` 或者 `F5` 上，将 `pl_ctrlp` 绑定到 `C+P` 上。

## 一个脚本示例

`pl_eelua_execute_current_file` 命令绑定好后，新建一个 `demo.lua` 文件，输入如下内容：

```
local tpl = [[
        if (sRawParam@1@ != NULL && sRawParam@1@[0] != '\0') {
            lua_pushstring(L, sRawParam@1@);
            lua_setfield(L, -2, "raw_s@1@");
            lua_pushstring(L, sParam@1@);
            lua_setfield(L, -2, "s@1@");
            ++argc;
        } else {
            break;
        }
]]

for i = 1, 10 do
  App:output_line(tpl:gsub("@1@", tostring(i)))
end
```

按对应快捷键 F5 就会执行脚本，可以在输出窗口看到反馈结果。

## 插件菜单下的自定义脚本

可以将一些可复用的脚本放到 `eelua\scripts` 目录下，会显示在菜单『扩展』→『插件』→『lua scripts』下，点击相应菜单项执行对应脚本。

## 模式文件中调用插件提供的 dofile 接口

这里以插件自带的 `mode\ctrlp.esm` 为例：

```ini
[Menu]
Title=CtrlP
[Menu0]
Key=F5
Command0=1,refresh,${AppPath}\plugin\eelua.dll,dofile,eelua\autoload\ctrlp\init.lua^^refresh
[Menu1]
Key=A+Enter
Command0=1,accept,${AppPath}\plugin\eelua.dll,dofile,eelua\autoload\ctrlp\init.lua^^accept
[Menu2]
Key=C+o
Command0=1,multi_accept,${AppPath}\plugin\eelua.dll,dofile,eelua\autoload\ctrlp\init.lua^^accept
[Menu3]
Key=C+f
Command0=1,toggle_type(1),${AppPath}\plugin\eelua.dll,dofile,eelua\autoload\ctrlp\init.lua^^toggle_type^^1
[Menu4]
Key=C+b
Command0=1,toggle_type(-1),${AppPath}\plugin\eelua.dll,dofile,eelua\autoload\ctrlp\init.lua^^toggle_type^^-1
```

在激活上面模式下按 `C+b` 键会执行脚本 `eelua\autoload\ctrlp\init.lua` 中的 `toggle_type("-1")` 函数，上述配置中函数以及函数参数都是可选的，并且以 ^^ 分隔开。

## 自带的一些 lua 库

除了 luajit 本身的功能，插件还通过 ffi 封装了一些 windows api，简要说明如下：

```
eelua\
  lfs.lua         # 文件目录操作
  minipath.lua    # 文件路径处理辅助库
  unicode.lua     # 字符编码转换
  print_r.lua     # 打印表结构
  sqlite3_ffi.lua # 封装 EverEdit 自带的 sqlite3 库（接口封装还不完善）
  wininet.lua     # 封装 wininet 网络库（未完成）
```

你也可以自己通过 ffi 封装其他库来调用，甚至可以自行编译第三方扩展库加进来（需要的头文件和库安装包里已经带了）。

## 总结
命令行、脚本文件、快捷键、模式以及lua扩展库这几个相互结合可以实现复杂的功能，比如自带的 ctrlp 插件。