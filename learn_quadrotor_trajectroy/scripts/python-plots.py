#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Apr 12 17:16:15 2020

@author: arslanali
"""

import csv
import os
import sklearn
import graphviz
import sys

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt; plt.rcdefaults()
from mpl_toolkits.mplot3d import Axes3D

from mpl_toolkits import mplot3d
#%%  Constants

"""
Define constants and load csv file from the user define path and read as pandas dataframe
"""

file_path = "/home/arslanali/quadrotor-simulation/bagfiles/file.csv"

COL_NAMES = ["%time",	"field.header.seq",	"ield.header.stamp",	"field.header.frame_id",	"field.pose.position.x",	"field.pose.position.y",	"field.pose.position.z",	"field.pose.orientation.x",	"field.pose.orientation.y",	"field.pose.orientation.z",	"field.pose.orientation.w"]

csv_data = {}


if not os.path.isfile(file_path):
    print("File not found {}".format(file_path))
d = pd.read_csv(file_path, names=COL_NAMES, header=1)


csv_data = d

#%%
#%%

"""
Select three feature set to test with our classification and regression tree algorithm. 
"""

#  This contains list of desired features and should be subset of COL_NAMES
position = ["field.pose.position.x",	"field.pose.position.y",	"field.pose.position.z"]

position_data = pd.DataFrame([], columns=position)


#  print(row)
position_data = csv_data.filter(items=position)
#  print(features_d1)

#%%
fig = plt.figure()

ax = plt.axes(projection='3d')

# Data for a three-dimensional line
xline = position_data["field.pose.position.x"]
yline =position_data["field.pose.position.y"]
zline =position_data["field.pose.position.z"]
ax.plot(xline, yline, zline, 'gray')


