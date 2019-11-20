<h1 align="center">ColorMap Plugin</h1>

The Color Map plugin allows a user to overlay an intensity map over a whole slide image (WSI). 
The intensity map is displayed with a violet (low intensity) to red (high intensity) rainbow colour scale. 
The user can set a percent transparency value that determines how the overlay is displayed.
The intensity map file must be a greyscale image in .jpg format.

## User Manual
##### 1.	Open a whole-slide image (WSI) in Sedeen Viewer.
##### 2.    Open the Analysis Manager, and load the "ColorMap" plugin from the pulldown list of Algorithms.

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_1.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 1.</strong> The Analysis Manager, after loading a whole-slide image (WSI) and choosing the ColorMap plugin from the pulldown list of algorithms.</h6>
</div>

##### 3.	Adjust the Transparency slider or enter a number between 0 and 100 in the spinbox to choose how the intensity map will be displayed over the whole slide image.
##### 4.	Click the folder icon to choose an intensity map file. The file must be in .jpg format.

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_2.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 2.</strong> The Transparency slider allows the user to adjust the display of the intensity map. The second parameter allows the user to open an intensity file in .jpg format.</h6>
</div>

##### 4.	Click the Run button to overlay the intensity map on the image.

<div align="center">
  <img src="https://github.com/sedeen-piip-plugins/ColorMap/blob/master/Images/ColorMap_3.png"/>
</div>
<div align="center">
  <h6> <strong>Fig 3.</strong> An intensity map displayed at 60% intensity over a whole-slide image.</h6>
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





