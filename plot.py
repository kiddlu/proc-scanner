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
