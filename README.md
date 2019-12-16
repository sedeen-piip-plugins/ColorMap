<h1 align="center">ColorMap Plugin</h1>

The Color Map plugin allows a user to overlay an intensity map over a whole slide image (WSI). 
In particular, this is useful for the visual representation of cellularity or 2D probability distributions.
The intensity map is displayed with a violet (low) to red (high) color scale (the "jet" scale in OpenCV). 
The color scale is normalized between the lowest and highest pixel values in the intensity map. 
The user can set a percent transparency value that determines how the color map is displayed, 
and can choose whether to display the color map with or without the underlying slide image.

The intensity map file must be a greyscale image in .jpg format. Before running, the view must be zoomed
out so that the entire low-resolution slide image is contained within the view area. When the 
intensity map is loaded, the horizontal and vertical dimensions of the slide image are used 
to scale the horizontal and vertical dimensions of the intensity map's JPEG image. If the dimensions 
of the imported file are not in the same ratio as the dimensions of the whole slide image, unexpected
stretching or shrinking of the intensity map may result.

## User Manual
##### 1.	Open a whole-slide image (WSI) in Sedeen Viewer. Zoom out so that the whole image is displayed within the view area.
##### 2.    Open the Analysis Manager, and load the "ColorMap" plugin from the pulldown list of Algorithms.

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_1.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 1.</strong> The Analysis Manager, after loading a whole-slide image (WSI) and choosing the ColorMap plugin from the pulldown list of algorithms.</h6>
</div>

##### 3.	Adjust the Transparency slider or enter a number between 0 and 100 in the spinbox to choose how the intensity map will be displayed.
##### 4.	To display only the color map and hide the slide image, check the box labeled, "Display color map only". Leave this unchecked to overlay the color map over the slide image.
##### 5.	Click the folder icon to choose an intensity map file. The file must be in .jpg format.

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_2.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 2.</strong> The "Transparency" slider allows the user to adjust the display of the intensity map. The "Display color map only" checkbox determines whether the color map will be overlaid on the slide image (unchecked), or if only the color map will be displayed (checked).</h6>
</div>

##### 6.	Click the Run button to display the intensity map. Two examples of the output are shown below. Fig. 3 shows the result of setting transparency to 40% and choosing to display the whole slide image (unchecking the Display color map only box). Fig. 4 shows the result of setting the transparency to 0%.

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_3.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 3.</strong> A color map displayed at 40% transparency over a whole-slide image.</h6>
</div>

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_4.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 3.</strong> A color map displayed at 0% transparency with the "Display color map only" box checked.</h6>
</div>

## Authors
Color Map Plugin was developed by **Azadeh Yazanpanah** with contributions by **Michael Schumaker**, Martel lab at Sunnybrook Research Institute (SRI), University of Toronto and was partially funded by [NIH grant](https://itcr.cancer.gov/funding-opportunities/pathology-image-informatics-platform-visualization-analysis-and-management).

## Copyright & License

Copyright (c) 2019 Sunnybrook Research Institute

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.





