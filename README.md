# Open Procedural City Generation



This project aims to create a basic open-source implementation of the method for the procedural generation of a 3D city environment described in this study: [Procedural Modeling of Cities](https://dl.acm.org/doi/epdf/10.1145/383259.383292). The authors went on to create [CityEngine](https://en.wikipedia.org/wiki/CityEngine), a proprietary 3D modeling software implementing the method described in the study.



My first objective is to be able to generate a road network map based on multiple input maps: population Density, land-water-park boundaries, elevation, and street patterns.



Next objectives:

* adding a GUI to facilitate the selection of input maps, as well as other parameters such as the size of the output map, the scale, colors…
* implementing the rest of the pipeline with lot subdivision and building generation with new possible input maps: building style/zoning and building height.
* being able to export a 3D scene



### Libraries



#### Turtle Graphics:



[YATG](https://github.com/blackbat13/yatg) (Yet Another Turtle Graphics)

