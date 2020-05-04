# Digital Earth based on WMS Service developed on OpenGL
This is a Project to demostrate a Visualization of Digital Earth, with Request on Earth Visualization Image from Internet Server via WMS Service.

The Code is heavily based on my Bachelor Thesis at CUMT.

The Earth grid net is basically developed based on [Icosahedron](https://en.wikipedia.org/wiki/Icosahedron)

data source:
[DEM dataset](https://asterweb.jpl.nasa.gov/gdem.asp)<- not in use, 
[DEM dataset](https://www.eea.europa.eu/data-and-maps/data/world-digital-elevation-model-etopo5)
[Texture Dataset](https://visibleearth.nasa.gov/)
## TODO: 

1. Apply google test. 
2. refine structure.
3. Doxygen Document.
4. WMS broadcasted images.
5. Extend some type specific function to be template function, to handle various depth images
6. extract a parent calss for both DEMModel and TextureModel.
7. automatic load of different GeoTiFF images (Generallization)
## Future Work
* reduce CPU Usage.
* pyrimid model()