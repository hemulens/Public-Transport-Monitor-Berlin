#include <string>
#include <vector>

class Aeroplane {
  public:
    Aeroplane();
    Aeroplane(struct data); // change data type or change constructor
  private:
    std::string _icao24;
    std::string _callsign;
    std::string _origin_country;
    int _time_position;
    int _last_contact;
    double _longitude;
    double _latitude;
    double _baro_altitude;
    bool _on_ground;
    double _velocity;
    double _true_track;
    double _vertical_rate;
    std::vector<int> _sensors;  // check after registering in the OpenSky Network!
    double _geo_altitude;
    std::string _squawk;
    bool _spi;
    int _position_source;
};