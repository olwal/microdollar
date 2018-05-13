MicroDollar: $1 Gesture Recognizer C++ port with optimizations for embedded hardware
======================
MicroDollar makes it possible to use the template-based $1 gesture recognizer on
resource-constrained microcontrollers, such as the ESP8266, Arduino Uno, and others.

This library was initially developed for the [SpeckleSense/SpeckleEye](http://olwal.com/#high-speed_embedded_motion_sensing) research projects at MIT. 

SpeckleSense exploits laser speckle sensing for precise, high-speed, low-latency motion tracking, which can be applied to a wide range of interaction scenarios and devices.

[![SpeckleEye - Gestural Remote Interaction with Cabinet](https://i.vimeocdn.com/video/434556108_260x146.jpg)](https://vimeo.com/63967600)
[![SpeckleEye - Gestural Remote Interaction with Camera](https://i.vimeocdn.com/video/434555965_260x146.jpg)](https://vimeo.com/64055145)

The work is based on the [$1 Unistroke Recognizer project](http://depts.washington.edu/madlab/proj/dollar/) at University of Washington/Microsoft Research.

Repository Contents
-------------------
* **/examples**: Example Arduino sketches for the library (.ino). Run these from the Arduino IDE.
* **/src**:  Source files for the library (.cpp, .h). Not dependent on Arduino
* **library.properties**: General library properties for the Arduino package manager.

Research Papers
-------------------
* [SpeckleEye: Gestural Interaction for Embedded Electronics in Ubiquitous Computing](http://olwal.com/projects/research/specklesense/olwal_speckleeye_chi_2012.pdf). Olwal, A., Bardagjy, A., Zizka, J., and Raskar, R. CHI 2012 Extended Abstracts. [ACM Digital Library](https://doi.org/10.1145/2212776.2223782) 
* [SpeckleSense: Fast, Precise, Low-cost and Compact Motion Sensing using Laser Speckle](http://olwal.com/projects/research/specklesense/zizka_specklesense_uist_2011.pdf). Zizka, J., Olwal, A., and Raskar, R. Proceedings of UIST 2011. [ACM Digital Library](https://doi.org/10.1145/2047196.2047261)
        
Original paper:
* [Gestures without libraries, toolkits or training: a $1 recognizer for user interface prototypes](http://faculty.washington.edu/wobbrock/pubs/uist-07.01.pdf). Wobbrock, J., Wilson, A. and Li, Y. Proceedings of UIST 2007. [ACM Digital Library](https://doi.org/10.1145/1294211.1294238)


Version History
---------------
0.1: 2018 05 12.

License Information
-------------------
This library is **open source**.

Distributed as-is; no warranty is given.

Alex Olwal (olwal.com)
