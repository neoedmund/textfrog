# textfrog stdlib 内置函数文档

> 本文档 generate assistant-by-AI: `Grok Build` ver `grok-0.2.11` 
> textfrog 是一门结合 Java/C 运行时的简洁脚本语言，stdlib 提供了“电池包含”的丰富能力，尤其擅长 FFI（Java/C 互操作）、系统脚本、文本处理和个人工具开发。

**调用示例**（类似 C/Java 语法，无需分号和逗号）：
```tfg
s = file("a.txt")
save("hello" "/tmp/x.txt")
loop 10 i { log(i) }
```

---

## 1. 文件与 I/O 操作

| 函数 | 签名 | 说明 |
|------|------|------|
| file | `file(fn [, enc])` | 读取文件内容为 String。可指定编码，失败抛异常 |
| save | `save(val, fn)` | 将 val.toString() 以 UTF-8 保存到文件（自动建父目录，带日志） |
| appendFile | `appendFile(fn, data)` | 追加字符串或 byte[] 到文件，返回写入字节数 |
| copyFile | `copyFile(src, dest)` | 复制文件（自动创建目标父目录） |
| readFileLines | `readFileLines(fn)` | 读取文件全部内容（内部使用 readStringBig） |
| readFileToBs | `readFileToBs(fn, byteArr)` | 读取文件内容填充到预分配 byte[]，返回实际读取字节数 |
| gzfile | `gzfile(fn)` | 读取 gzip 压缩文件内容为字符串 |
| writeGzFile | `writeGzFile(txt, fn)` | 将文本 gzip 压缩保存（要求 .gz 后缀），返回字节长度 |
| saveBin | `saveBin(nativeAddr, size, fn)` | 将 native 内存区域保存为二进制文件 |
| FileObj | `FileObj(fn)` | 创建 File 对象包装 |
| MapFile | `MapFile(fn)` | 内存映射文件（mmap）支持 |
| openFileWrite | `openFileWrite(fn)` | 打开文件用于写入，返回包装对象 |
| openFileChannel | `openFileChannel(...)` | 获取 NIO FileChannel 包装 |
| symLink | `symLink(target, linkName)` | 创建符号链接相关操作 |

---

## 2. 字符串与文本处理

| 函数 | 签名 | 说明 |
|------|------|------|
| format | `format(fmt, args...)` | Java String.format，支持列表展开参数 |
| removeSpace | `removeSpace(s)` | 移除所有空格、\n、\r |
| removeTag | `removeTag(s)` | 简单移除 HTML/XML 标签 `<...>` |
| warpLine | `warpLine(s, width)` | 按显示宽度自动换行（ASCII=1，CJK=2） |
| noControlString | `noControlString(s)` | 过滤控制字符 |
| bb2string | `bb2string(bb [, enc])` | ByteBuffer/byte[] 转字符串 |
| bs2string | `bs2string(bs [, enc])` | byte[] 转字符串 |
| getBytes | `getBytes(s [, enc])` | 字符串转 byte[] |
| long2str | `long2str(v, radix)` | 长整型按进制转字符串 |
| ascii2int | `ascii2int(s [, len])` | 字符串前最多8字节转 int（大端？） |
| charDispLen | `charDispLen(s)` | 计算字符串显示宽度（CJK 占 2） |
| indexOfBs | `indexOfBs(b1, b2)` | byte[] / ByteBuffer 搜索 |
| indexOfBs2 | `indexOfBs2(...)` | 带偏移长度的高级 byte 搜索 |
| split2 | `split2(src, sep)` | 字符串分割（保留空串，split(..., -1)） |
| spacedTokens | `spacedTokens(txt)` | 按空白分割 token |
| CTokens | `CTokens(txt)` | C 语言风格 token 解析 |
| guessEncoding | `guessEncoding(fn_or_bs)` | 猜测文件/字节流编码 |
| base64dec | `base64dec(s)` | Base64 解码 |
| urlEncode | `urlEncode(s)` | URL 编码 |
| urlDecode | `urlDecode(s)` | URL 解码 |
| allocString | `allocString(s)` | 分配 native 字符串（FFI 用） |
| constString | `constString(s)` | 创建常量字符串 |

---

## 3. 类型转换与检查

| 函数 | 签名 | 说明 |
|------|------|------|
| toInt | `toInt(v [, radix])` | 转 int，支持字符串 radix、Number、char |
| toLong | `toLong(v [, radix])` | 转 long，支持 Date→时间戳 |
| toFloat | `toFloat(v)` | 转 float |
| toDouble | `toDouble(v)` | 转 double |
| toBool | `toBool(v)` | 转 boolean（null→false） |
| toChar | `toChar(v)` | 转 char（Number/String[0]） |
| toList | `toList(arr)` | 数组转 List |
| toJavaIntArr | `toJavaIntArr(list)` | List 转 Java int[] |
| toJson | `toJson(obj)` | 对象转 JSON 字符串（JSONObject） |
| tryNumber | `tryNumber(s)` | 尝试转 Number，失败返回 null |
| nv | `nv(a, b)` | **重要**：a 非 null 则返回 a，否则返回 b（null coalescing）, 新语法: `a or b` |
| isStr / isNumber / isList / isMap / isStruct / isEmpty | `isXxx(o)` | 类型判断，返回 boolean |

---

## 4. 日期时间处理

| 函数 | 签名 | 说明 |
|------|------|------|
| now / currentMs | `now()` / `currentMs()` | 当前毫秒时间戳（System.currentTimeMillis） |
| date | `date(ms_or_Date)` | 毫秒或 Date 转 Date 对象 |
| formatDate | `formatDate(fmt, ts_ms)` | 简单日期格式化 |
| formatDateNeoe | `formatDateNeoe(ts)` | neoe 风格日期格式 |
| SDF | `SDF(fmt)` | 创建 java.text.SimpleDateFormat |
| SDFParse | `SDFParse(sdf, str)` | 使用 SDF 解析日期字符串 |
| addDay / addMonth | `addDay(date, n)` | 日期加减天/月 |
| getWeekday | `getWeekday(date)` | 获取星期几（Calendar） |
| iso8601date | `iso8601date(...)` | ISO8601 日期处理 |

---

## 5. 集合与数据结构

| 函数 | 签名 | 说明 |
|------|------|------|
| array | `array(v1, v2, list...)` | 扁平化创建 ArrayList |
| array2 | `array2(v1, v2, ...)` | 非扁平创建 ArrayList |
| newMap | `newMap([fromMap])` | 创建 ConcurrentHashMap |
| treeMap | `treeMap([from])` | 创建 TreeMap |
| linkedList | `linkedList()` | 创建 LinkedList |
| syncList / syncMap | `syncList([list])` / `syncMap([map])` | 线程安全包装 |
| set | `set([v...])` | 创建 HashSet |
| setSub | `setSub(...)` | 子集操作？ |
| objList | `objList(...)` | 对象列表 |
| newLoopList / newLoopList2 | `newLoopList(size)` | 循环/环形缓冲列表 |
| newSB | `newSB()` | StringBuilder 包装 |
| newBaos | `newBaos()` | ByteArrayOutputStream 包装（初始 4K） |
| newByteArray | `newByteArray(len)` | 创建 byte[len] |
| intArray / floatArray | `intArray(...)` / `floatArray(...)` | 基本类型数组创建 |
| zigmap / zigmap2 | `zigmap(...)` | 特殊 zig-zag / 压缩 map 结构 |
| struct | `struct(name [, shareMem])` | **FFI**：根据 G.struct 定义创建 C Struct，支持内存共享 |
| struct2 | `struct2(name, nameId)` | 重用命名内存的 struct |

---

## 6. 进程执行与 Shell

| 函数 | 签名 | 说明 |
|------|------|------|
| exec | `exec(cmd...)` 或 `exec(list)` | 执行命令，返回 `[stdout, stderr, exitCode]`，带日志 |
| execp | `execp(wd, cmd...)` | 在指定工作目录执行，返回同上 |
| execp_blind | `execp_blind(wd, cmd...)` | 无 stdout/stderr 捕获版（长驻 daemon 省内存） |
| execp_passout | `execp_passout(wd, cmd...)` | 实时把输出传递到当前 stdout/stderr |
| checkExec | `checkExec(execResult)` | 检查 exec 返回的 exitCode，非 0 则 panic |
| realtimeLineBash | `realtimeLineBash(wd, cmd, lambda, ...)` | 实时逐行 bash 执行 + lambda 回调处理 |
| ping | `ping(host, timeoutMs)` | ICMP 探测，返回纳秒延迟或 -1 |
| robotKey | `robotKey(keyStr)` | 使用 java.awt.Robot 发送键盘事件（自动化） |

---

## 7. 并发与同步

| 函数 | 签名 | 说明 |
|------|------|------|
| sleep | `sleep(ms)` | 线程睡眠毫秒 |
| asleep | `asleep(ms)` | 异步/另一种 sleep？ |
| thread | `thread(lambda)` | 启动新线程执行 lambda |
| threadPool | `threadPool()` | 创建线程池 |
| threadlocal | `threadlocal()` | ThreadLocal 变量支持 |
| sync | `sync(lambda)` | 同步执行 lambda（内置锁） |
| timeit | `timeit(lambda, label?)` | 计时执行并记录 |
| addExitHook | `addExitHook(hook)` | 注册 JVM 退出钩子 |

---

## 8. 日志调试与错误处理

| 函数 | 签名 | 说明 |
|------|------|------|
| log | `log(fmt, args...)` | 格式化日志（tfg logger，带时间/文件） |
| nolog | `nolog(fmt, args...)` | 仅 stdout 格式化打印（不写日志文件） |
| logError | `logError(fmt...)` | 错误级别日志 |
| logname | `logname(dir, basename)` | 设置日志目录和文件名 |
| getlog | `getlog([dir], name)` | 获取/创建指定日志 |
| stackTrace | `stackTrace(e?)` | 获取/格式化堆栈 |
| pos | `pos()` | 返回当前源码位置（调试用） |
| error | `error(fmt, args...)` | 抛出带格式化消息的 RuntimeException（含位置） |
| confirm | `confirm(bool, msg)` | 断言失败立即抛异常（类似 assert） |
| throwException | `throwException(v)` | 直接抛出异常 |
| hashCode | `hashCode(o)` | 返回对象的 hashCode |
| tryGC | `tryGC()` | 尝试触发 GC |

---

## 9. 网络与消息

| 函数 | 签名 | 说明 |
|------|------|------|
| urlPage | `urlPage(url)` | 下载网页，返回 `[content, httpCode]` |
| urlDownload | `urlDownload(url)` | 下载，返回 UrlUtil 对象（支持后续 savePage 等） |
| urlEncode / urlDecode | 标准 URL 编解码 | |
| tgMsg | `tgMsg(msg)` | 发送 Telegram 消息（需预配置 token/chat_id，支持长消息分片） |

---

## 10. 随机、数学与系统信息

| 函数 | 签名 | 说明 |
|------|------|------|
| rand | `rand()` | 返回共享 Random 实例 |
| nextRand | `nextRand(n)` | 返回 0 ~ n-1 的随机 int |
| randStr | `randStr(len)` | 生成随机字母数字字符串 |
| sin | `sin(x)` | Math.sin |
| cpuCount | `cpuCount()` | 可用 CPU 核数 |
| hostname | `hostname()` | 获取主机名（Windows/Unix 兼容） |
| homeDir | `homeDir()` | 用户主目录 |
| env | `env()` | 返回当前 Env 运行时对象（高级用法） |
| scriptPath | `scriptPath(fn?)` | 当前脚本路径相关 |
| searchPath / addSearchPath / findFileInSearchPath | 模块搜索路径管理 | |
| pathJoin | `pathJoin(dir, fn)` | 路径拼接 |
| errno | `errno()` | 获取最近 native errno |
| unpackDeb | `unpackDeb(...)` | 解包 .deb 包 |
| conffile / getConf / getConfInFile | 配置加载 | `getConf(obj, key)` / 从文件加载 conf |

---

## 11. 模块与代码组织

| 函数 | 签名 | 说明 |
|------|------|------|
| include | `include(fn1, fn2...)` | 包含其他 .tfg 脚本的**公共**函数（隔离私有），执行其 init |
| inline | `inline(fn...)` | 内联包含（共享作用域，合并 init 和函数） |
| hasFunc | `hasFunc(name)` | 检查当前作用域是否存在该函数 |
| parseTfg | `parseTfg(fn)` | 解析 .tfg 脚本文件为 EUnit AST |
| parseData | `parseData(txt)` | 使用 PyData 解析文本数据（类 Python 数据结构） |
| template | `template(tplStr, map)` | 使用 Template2 渲染字符串模板（带缓存） |
| templateFile | `templateFile(fn, map)` | 渲染模板文件 |
| finder | `finder(txt)` | 文本查找器（Finder 类） |
| loadJars | `loadJars(jarPaths...)` | 动态加载 jar（自定义 ClassLoader） |
| loadLib | `loadLib(name)` | 加载 native lib |
| loadImageMem | `loadImageMem(bb, ...)` | 从内存 ByteBuffer 加载图片 |

---

## 12. 原生 FFI / C & Java 互操作（最强特色）

textfrog 对 FFI 支持极强，可直接操作 native 内存、C struct、调用 libc/Java 方法。

### Java 互操作
- `Java(nameOrClass)` — 用无参构造实例化 Java 对象
- `JavaClass(name [, classLoader])` — 获取 Class 对象用于反射
- `loadJars(...)` — 动态 classpath

### Native 内存与数组
- `nativeByteArray(size [, addr])`、`nativeIntArray`、`nativeShortArray`、`nativeFloatArray`、`nativeDoubleArray`、`nativePointerArray`、`nativeStringArray`
- `nativeStructArray(name, size, addr?)`
- `nativeInt(addr)`、`nativeString(addr [, enc])`、`nativeStringExact`
- `initNativeIntArray(list)`、`initNativeFloatArray(list)`
- `allocString(s)`、`constString(s)`

### C Struct & 内存搜索
- `struct(name)` / `struct2(name, id)` — 定义在 G.struct 中的 C 结构体
- `findInNativeArray(...)` / `findInNativeArrayTyped(...)` — 内存中搜索（memdig 类工具）
- `nativeCallAddr(...)` — 获取 native 函数地址

### 其他底层
- `libC()` — 加载 libc
- `forLineBB(bb, ...)` — 在 ByteBuffer 上按行迭代 + lambda
- `createImage(w, h)`、`saveImage(img, fn)`、`loadImageMem`
- `bbcopy`、`getBytes` 等 bytebuffer 操作
- `toJavaIntArr` 等桥接

**典型用法**：用 struct 定义 C 头，nativeXXX 分配内存，libC 调用函数，实现零拷贝高性能脚本。

---

## 13. 其他杂项

- `print(...)` — 旧版？向集合追加格式化字符串（已标记 deprecated）
- `stackTrace`、`tryGC`、`throwException`
- `newLoopList*`、`zigmap*` 等专用结构
- 各种内部测试/辅助函数（ascii2int、long2str 等）

---

## 附录：全部内置命令列表（共 ~130 个，按字母排序）

（完整共约 129 个命令，覆盖文件/执行/FFI/字符串/并发/网络等全部领域）

---

## 总结与建议

- **最常用**：`file/save/exec/format/array/newMap/log/confirm/nv/thread/url*`
- **脚本利器**：`execp* + checkExec` 实现健壮的 shell 脚本替代品
- **个人工具神器**：强大的 FFI + struct + nativeArray，可写内存分析、逆向、系统工具
- **模块化**：优先使用 `include`（隔离）或 `inline`（共享）
- **调试**：`confirm` + `error` + `pos` + `log` + `stackTrace`

**文档来源**：纯源码静态分析 + 少量运行时行为推断。实际使用建议结合 samples/ 目录中的真实 .tfg 脚本学习。


---
*Generated for textfrog stdlib documentation — by AI analysis of source*
