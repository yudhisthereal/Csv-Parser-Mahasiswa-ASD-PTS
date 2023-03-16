# Csv-Parser-Mahasiswa-ASD-PTS
Mid-Semester Project for Algorithm and Data Structure subject.

<h2><b>WHAT'S GOING ON HERE???</b></h2>
> "Why are the files and folders structured in such a weird manner? the CSV files exist in both the `main folder` and `csv` folder??"
is probably what you're thinking.
This section was made in order to eliminate possible confusions.

<h3>The CSV Files</h3>

![csv files in the main folder](https://user-images.githubusercontent.com/63510362/225620267-561bce41-a061-4ef8-8187-48dbfe7a46d2.png "csv files in main folder")

![csv files in csv folder](https://user-images.githubusercontent.com/63510362/225625434-31c242f7-94eb-4dbf-ad67-e115739c3329.png "csv files in csv folder")

`MK-A.csv`,`MK-B.csv`,`MK-C.csv`, and `MK-D.csv` were put in both the `main folder` and `csv` folder for testing purposes.

The test is as follows:

![imgae of promt folder for csv files](https://user-images.githubusercontent.com/63510362/225622897-5bf36e05-7bd0-45ba-a48f-c744df5862cb.png "image of initial prompt")

The image being shown above is the first thing the program asks the user: "where does the CSV files exist?" So for testing purposes, I put the CSV files in two different directories: in the `main folder` (acting as the current folder) and `csv` folder. If the input is either `csv` or `.` it should work without issue. Other inputs should make the program ask the user for the valid path again.

<h3>A Folder With Only 1 Text File?</h3>

![content of test folder](https://user-images.githubusercontent.com/63510362/225626176-d97f5e8b-aa6c-442a-9c2f-240982057c1e.png "content of test folder")

`test` folder only has one file: purpose.txt which states the purpose of the existence of `test` folder. (Spoiler: it's for testing purposes, see `The CSV Files` section above).

<h3>main.exe</h3>
The executable file that you can run if you're on <b>Windows</b>.

<h3>main.cpp</h3>
It's the source code, as you'd expect. 

### <b>Prerequisites :</b>
1. A working CLI based tool (i.e. CMD, powershell, terminal, etc.)

2. G++ v8 (or any other C++ compiler that fully supports `<filesystem>` library)


### Author
By Yudhistira (225150301111029)
