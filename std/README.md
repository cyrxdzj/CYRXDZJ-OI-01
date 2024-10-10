# CYRXDZJ-OI-01 std 文件

这里介绍了比赛筹办过程中需要的，std 目录下的文件。

**请务必注意，所有 Python 脚本均需在源代码所在目录下运行。**

| 文件名                                 | 介绍                                                         |
| -------------------------------------- | ------------------------------------------------------------ |
| `introduction.md`                      | 比赛首页介绍内容。                                           |
| `summary.md`                           | 赛后总结帖模板内容。                                         |
| `README.md`                            | 本文件。                                                     |
| `auto_compile.cpp`                     | 自动编译题解、validator、checker 脚本。                      |
| `all_batch_checker.py`                 | 自动化测试脚本。<br>本质是批量运行 `task/task_batch_checker.py`。 |
| `pdf_merger.py`                        | PDF 合并脚本。                                               |
| `down_copy.py`                         | `down.zip` 打包脚本。                                        |
| `task/data/*`                          | 评测数据文件，内含样例文件。                                 |
| `task/task.md`                         | 题面文件。                                                   |
| `task/task_generator.py`               | 数据生成程序。                                               |
| `task/task_batch_checker.py`           | 自动化测试脚本，用于测试标程。                               |
| `task/task_config_generator.py`        | `config.yml` 文件生成程序。                                  |
| `task/config.yml`                      | HydroOJ 题目配置文件。                                       |
| `task/task_sol.md`                     | 题解文件。                                                   |
| `task/task_sol[1-9].cpp`               | 标程。需要注意部分标程只能获得部分分。                       |
| `task/task_testlib_validator[1-9].cpp` | validator 程序，负责判断输入正确性。                         |
| `task/task_testlib_checker.cpp`        | checker 程序，负责判断输出正确性。                           |
| `task/testlib.h`                       | testlib 库。                                                 |