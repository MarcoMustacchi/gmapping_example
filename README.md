# gmapping example

Documentation:

> http://wiki.ros.org/gmapping

Note also at the end of the documentation the **Required tf Transforms** and the **Provided tf Transforms**


## Result
![enter image description here](https://github.com/MarcoMustacchi/gmapping_example/blob/master/images/gmapping_example.png)


## RVIZ

### "For frame `laser_frame`: Frame `laser_frame` does not exist"

**Global Fixed Frame**: The "Fixed Frame" in RViz represents the reference frame to which all data should be transformed for visualization.

**Global Frame (`map`)**: In RViz, the "Fixed Frame" is set to `map`, meaning all data needs to be transformed into this frame for visualization.

![enter image description here](https://i.sstatic.net/PlIDu.png)

### Explanation of the Error

When RViz gives the error "For frame [laser_frame]: Frame [laser_frame] does not exist," it means RViz cannot find a transformation in the TF tree connecting the `laser_frame` to the `map` frame.

#### Solution 1

To fix the error, you need to ensure that the necessary transformations are being published in ROS (e.g., `map` to `base_link` and `base_link` to `laser_frame`). The TF broadcaster must provide these transformations for RViz to visualize the sensor data correctly.

#### Solution 2

To fix the error, you can also change the Fixed frame of RVIZ from `map` to another option, as seen in the top image.


## Topic Remapping

### What is Topic Remapping?

Topic remapping in a ROS launch file allows you to change the name of a topic that a node is subscribing to or publishing to at runtime.

### Why is Topic Remapping Useful?

1. **Consistency Across Different Packages**:
   - Different packages may use different topic names for similar data types. For example, one package might publish LaserScan data on the topic `/scan`, while another expects it on `/laser_scan`.
   - By remapping, you can adapt your node to work with different naming conventions without changing the source code.
2. **Avoiding Conflicts**:
   - If multiple nodes are publishing to the same topic, you can remap the topics to prevent conflicts or data overwriting.

### Example Use Case

Suppose you have a node that publishes laser scan data on `/laser_scan`, but the `gmapping` package expects the scan data on a topic called `/scan`. You can remap the topic like this:

```xml
<node pkg="gmapping" type="slam_gmapping" name="gmapping" output="screen">
    <remap from="/scan" to="/laser_scan"/>
</node>
```

This remapping tells the `slam_gmapping` node that whenever it looks for data on `/scan`, it should actually subscribe <br> to `/laser_scan` instead.
