# ResourceWatcher

一个加强版的top，运行在linux平台

编码格式严格按照 谷歌代码规范[https://zh-google-styleguide.readthedocs.io/en/latest/]

系统模式 
    监控内容：
    系统的 cpu 使用情况，内存使用情况, 进程数，磁盘使用情况 
    cpu ：
        1. 实时cpu使用率 
        2. cpu使用时间，
    内存 ：(free -h)
        1. 物理内存使用情况：总共的物理内存total，被使用的内存used，完全不被使用的内存free，缓存数据buff，内存使用率 used/total*100%，共享内存 
        2. 交换内存使用情况
            total，used，free
    磁盘：(df -h)
        1. 文件系统 total used Avail Use% Mounted 
    进程：
        1. 总进程数，运行进程数，僵尸进程
        2. 进程列表

数据格式:
    protobuf
    



录制模式：
    把数据写入到本地文件
