 rosbag record -O subset /command/twist /ground_truth_to_tf/pose

rosbag record -O subset  /ground_truth_to_tf/pose

rostopic echo   /ground_truth_to_tf/pose -b subset.bag -p >file.csv
