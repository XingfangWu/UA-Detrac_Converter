# UA-Detrac_Converter
Convert original UA-Detrac format annotation to frame-based(sequence-based)/ object-based(PETS) XML format

* use ConvertXML.py to convert frame-based XML to Oject-based(PETS) XML

Build:
```
cd /path/to/this/repo
mkdir build
cd build
cmake ..
make install
```

Usage:

```
./UADetracConvertor arg1 arg2
arg1: input filename
arg2: output filename
```

```
python ConvertXML.py arg
arg: path/to/folders/to/be/converted
```
Example input directory structure

```
./dataset
└── predictions
    ├── 0.0
    │   ├── MVI_39031_H.txt
    │   ├── MVI_39031_LX.txt
    │   ├── MVI_39031_LY.txt
    │   ├── MVI_39031_W.txt
    │   ├── MVI_39031_speed.txt
    │   └── .....
    ├── 0.1
    │   └── .....
    ├── 0.2
    ├── .
    ├── .
    ├── .
    ├── .
    ├── .
    └── 1.0
```