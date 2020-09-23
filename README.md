# Capstone Project (Udacity C++ Nanodegree)

This is the description of and the instruction for running the Berlin Realtime Public Transport Monitor designed by Sergei Kononov as a Capstone Project in the [Udacity C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) program in September 2020. The project is built out of curiosity to visualize realtime public transportation system in a densely-populated urban area. With the ever-increasing pace of urbanization globally, extended versions of similar applications can contribute to improving urban transportation systems, especially taking into account problems of energy supply, logistics and environmental concerns.

Possible application extensions can include:

* Mapping the most dense and public transport routes – can be beneficial for GPS systems to re-route passenger vehicle / local logistics traffic to increase speed of commuting
* Mapping traffic to track the most delay-prone time of the day for the local public transport, as well as mappring jammed urban areas
* Etc.

![Screenshot of the project in action](misc/demo.gif "Title")

## Project Description – Berlin Realtime Public Transport Monitor

The goal of the project is to track, map and display all public transport units operating at the current time in Berlin, Germany. The project uses data from the API [provided](https://github.com/public-transport/hafas-client/blob/5/docs/radar.md) by the Transportation Union of Berlin and Brandedburg (Verkehrsverbund Berlin-Brandenburg, VBB) and HAFAS ([company website](https://www.hacon.de/en/solutions/trip-planner-and-travel-companion/), [about HAFAS in Wikipedia](https://de.wikipedia.org/wiki/HAFAS)) to track realtime geographic locations of all types of public transport vehicles at a given part of the map. The documentation to the API used in this project is written by [Jannis Redmann (aka derhuerst)](https://github.com/derhuerst).

The transport units include:

* Buses           (orange)
* Trams           (red)
* Subway trains   (light blue)
* Suburban trains (green)
* Express trains  (dark blue)
* Regional trains (purple)
* Ferries         (brown, larger blob)

According to the [documentation](https://github.com/public-transport/hafas-client/blob/5/docs/radar.md) written by [Jannis Redmann](https://github.com/derhuerst), the API allows a user to send up to 100 requests per minute. This works nominally, but in practice the VBB's server sends real updates approximately every 8-12 seconds, therefore vehicle positions will update every 8-12 seconds.

## Project Structure and Logic

`Controller.cpp` is the main file controlling the application. The application's logic is described below:

1. Set up graphics via creating an instance of `Graphics` class on the heap (required by OpenCV) based on pre-set map coordinates corresponding to map images from Google Maps. 4 maps and coordinate sets are available in the folder `Data` and in the map `geo` in `ApiData.h::23` (instructions below)
    * Create a map background using a map image. Map images are stored in the folder "Data"
    * Set the respective image resolution to allow presisely normalizing vehicle positions later on (convert from latitude and longitude into X and Y coordinates on the map image)
    * To choose a different map set, please comment out / uncomment respective map coordinate sets in `std::map<...> geo` in the file `ApiData.h` and choose an appropriate map image name and image resolution in `Controller.cpp` The map images are stored in the folder "Data". For instance, the image for experimental set 2 is "berlin-md-2.jpg"
1. Create a PublicTransport object. The object will contain:
    * Data object (owned) – created with the separate class `Data`
    * Vector of all vehicles on the map – created with the separate class `Vehicle`
    * Method `PublicTransport::Run()` responsible for:
        * Fetching, processing and storing public transport data at a given location in Berlin via the HTTP request through the class `Data`
        * Managing the vehicle fleet once the `Data` class updated its `_data`. This includes:
            * Creating, deleting and updating vehicles
1. Allow the instance of `Graphics` accessing array of `Vehicle`s stored in the `PublicTransport` object
1. Run simulation which includes `PublicTransport::Run()` and `Graphics::DrawVehicles()` running in an infinite loop

### Expected Behavior

After the application is launched, a window with map should be displayed, where vehicles are displayed. The vehicles' positions should update approx. every 8-12 seconds, whereas HTTP requests should be send every 3-5 seconds. The VBB server allows sending up to 100 HTTP requests per minute, but the real data on the server renews every 8-12 seconds only, hence the long update time.

## Dependencies for Running Locally

* cmake >= 3.9
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Linux: make is installed by default on most Linux distros
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
    * An alternative to conventional gcc/g++ on Mac: use llvm-gcc (`export CC=/usr/bin/llvm-gcc`) and llvm-g++ (`export CXX=/usr/bin/llvm-g++`)
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* OpenCV >= 4.1.0 ([general installation instructions](https://docs.opencv.org/4.2.0/df/d65/tutorial_table_of_content_introduction.html))
  * [Mac](https://docs.opencv.org/4.2.0/d0/db2/tutorial_macos_install.html)
  * [Linux](https://docs.opencv.org/4.2.0/d7/d9f/tutorial_linux_install.html)
  * [Windows](https://docs.opencv.org/4.2.0/d3/d52/tutorial_windows_install.html)
* C++ REST SDK, formerly known as Casablanca ([GitHub page](https://github.com/Microsoft/cpprestsdk)). The library requires installation of development files for Boost and OpenSSL. Depending on your machine, please read detailed installation instructions for:
  * [Mac](https://github.com/Microsoft/cpprestsdk/wiki/How-to-build-for-Mac-OS-X)
  * [Linux](https://github.com/Microsoft/cpprestsdk/wiki/How-to-build-for-Linux)
  * [Windows](https://github.com/Microsoft/cpprestsdk/wiki/How-to-build-for-Windows)

## Build Instructions

After installing project dependencies, please proceed to build:

1. Clone this repository into your project folder
1. Make a build directory in the top level directory: `mkdir build && cd build`
1. Compile -> Step 1: `cmake ..` (should you have hard times linking the OpenSSL library, please tell cmake where OpenSSL files are located on your machine. Make sure to do it prior to calling `cmake ..`. Example for Mac: `export OPENSSL_ROOT_DIR=/usr/local/Cellar/openssl@1.1/1.1.1g/` and `export OPENSSL_INCLUDE_DIR=/usr/local/Cellar/openssl@1.1/1.1.1g/include/`)
1. Compile -> Step 2: `make`
1. Run the application: `./BerlinTransport`

## Udacity Capstone Project Requirements – Rubric Points Addressed

Below is the description of how Udacity project requirements are fulfilled.

### 1. README (All Rubric Points REQUIRED)

* A README with instructions is included with the project
  * Yes: `README.md` file included into the project root folder.
* The README indicates which project is chosen
  * Yes: see section "Project Description" in the `README.md` file.
* The README includes information about each rubric point addressed
  * Yes.

### 2. Compiling and Testing (All Rubric Points REQUIRED)

* The submission must compile and run
  * Yes.

### 3. Loops, Functions, I/O

* The project demonstrates an understanding of C++ functions and control structures
  * Yes.
* The project reads data from a file and process the data, or the program writes data to a file
  * Yes & No: the project is designed to read and process data from a JSON stream received via the HTTP request (see `ApiData.h::52` and `ApiData.cpp::22`).
* The project accepts user input and processes the input
  * No.

### 4. Object Oriented Programming

* The project uses Object Oriented Programming techniques
  * Yes: see `ApiData.h`, `Vehicle.h`, `PublicTransport.h`, and `Graphics.h`, as well as all respective `.cpp` files.
* Classes use appropriate access specifiers for class members
  * Yes.
* Class constructors utilize member initialization lists
  * Yes: please see e.g. constructor `Data::Data()` in `ApiData.cpp::5`, constructor `Vehicle::Vehicle()` in `Vehicle.cpp::71` and constructor `PublicTransport::PublicTransport()` in `PublicTransport.cpp::4`.
* Classes abstract implementation details from their interfaces
  * Yes.
* Classes encapsulate behavior
  * Yes: e.g. `Graphics::Simulate()` in `Graphics.h::23`, `PublicTransport::Run()` in `PublicTransport.h::18`, etc.
* Classes follow an appropriate inheritance hierarchy
  * No: no parent classes are implemented in this project.
* Overloaded functions allow the same function to operate on different parameters
  * Yes: overloading a template though "Template specializations"; please see `Vehicle.h::31` and `Vehicle.cpp::8`.
* Derived class functions override virtual base class functions
  * No: no virtual base classes implemented in the project.
* Templates generalize functions in the project
  * Yes: see `Vehicle.h::28` and `Vehicle.cpp::4`.

### 5. Memory Management

* The project makes use of references in function declarations
  * Yes: see e.g. `void NormalizeLatitude(double &latitude)` and `void NormalizeLongitude(double &longitude)` in `Graphics.h::19` and `Graphics.h::20`.
* The project uses destructors appropriately
  * Yes: see e.g. `Vehicle::~Vehicle()` in `Vehicle.cpp::87`; no `free` or `delete` used, as the project uses smart pointers.
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate
  * Yes: see `std::shared_ptr<Data> _data` in `PublicTransport.h::20` and `std::vector<std::unique_ptr<Vehicle>> _vehicles` in `PublicTransport.h::23`.
* The project follows the Rule of 5
  * No: smart pointers are used instead.
* The project uses move semantics to move data, instead of copying it, where possible
  * Yes: see `void Update(const web::json::value &&data)` in `ApiData.h::53`, `ApiData.cpp::47` and `ApiData.cpp::64`.
* The project uses smart pointers instead of raw pointers
  * Yes & No: smart pointers are used in `PublicTransport.h::20`, `PublicTransport.h::23`, but simple raw pointers (neither `malloc` nor `new`) are used for learning purposes in `Graphics.h::31`, `PublicTransport.h::21` and `PublicTransport.h::22`.

### 6. Concurrency

* The project uses multithreading
  * No: a multithreading setup added to `Graphics::DrawVehicles()` in `Graphics.cpp::70`, but "linear" execution is chosen (`std::launch::deferred`). The dataset of 500+ vehicles is too small to run async.
* A promise and future is used in the project
  * Yes: see `Graphics::DrawVehicles()` in `Graphics.cpp::70`.
* A mutex or lock is used in the project
  * No.
* A condition variable is used in the project
  * No.
