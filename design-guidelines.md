## Design Guidelines

1. 区别方法常规IO，同步IO，直接IO的方法:

```c++
unsinged long flags =  get_flags(/proc/<pid>/fdinfo/<fd>) ;
if(flags & O_DIRECT)
  direct++;
else if (flags & O_SYNC)
  sync++;
else
  normal++;
```

2. 每次进程扫描/proc，统计下面的信息，使用结构体：
```c++
typedef strcut
{
  unsigned int normal;
  unsigned int sync;
  unsigned int direct;
} stat_t
```

3. 使用queue作为数据存储结构，FIFO统计所有扫描得到的数据
```c++
struct node{
  stat_t item;
  struct node *next;
}
typedef struct{
  struct node *fonrt;
  struct node *rear;
} queue
```

4. 命令行接受扫描次数和扫描间隔时间，没有参数则使用默认参数
```c++
#define DEFAULT_LOOP 5
#define DEFAULT_INTERVAL 10
```
5. 统计结束后，将queue数据pop输出成csv格式，
```csv
scan,normal,sync,direct
1,X,Y,Z
2,X,Y,Z
3,X,Y,Z
4,X,Y,Z
5,X,Y,Z
...
```
6. 使用可视化工具plotly将csv数据做乘pie chat

```python
# -*- coding:utf-8 -*-
import plotly.offline as po
import plotly.graph_objs as go
import pandas as pd

def avg(seq):
    return sum(seq) / len(seq)

if __name__ == "__main__":

    df = pd.read_csv("data.csv")
    normal = df["normal"]
    sync = df["sync"]
    direct = df["direct"]

    labels = ["normal", "sync", "direct"]
    values = [avg(normal), avg(sync), avg(direct)]
    trace = go.Pie(labels=labels, values=values)
    po.plot([trace], filename='./pie_chart.html')
```