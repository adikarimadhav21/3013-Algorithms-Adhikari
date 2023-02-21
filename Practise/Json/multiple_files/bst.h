
#include <vector>
using namespace std;

/**
 * define the GPS struct with the operator== and operator< functions
 * operator function can used later in insert and search function to compare GPS  types data
 */
struct GPS
{
public:
    double lat;
    double lon;

    bool operator==(const GPS &other) const
    {
        return lat == other.lat && lon == other.lon;
    }

    bool operator<(const GPS &other) const
    {
        if (lat == other.lat)
        {
            return lon < other.lon;
        }
        return lat < other.lat;
    }
};

//  BinarySearchTree class is defined using a template parameter typename T,
// which allows it to work with any data type
template <typename T>
class BinarySearchTree
{
private:
    struct Node
    {
        T value; // this variable will be used to make binary search tree for different types like int,string ,GPS
        int id;
        string first_name;
        string last_name;
        string email;
        string address;
        string city;
        string state;
        double latitude;
        double longitude;
        string car;
        string car_model;
        string car_color;
        string favorite_movie;
        string pet;
        string job_title;
        string phone_number;
        vector<string> stocks;

        Node *left;
        Node *right;

        Node(const T &value, int id, string first_name, string last_name, string email, string address, string city, string state, string car,
             string car_model, string car_color, string favorite_movie, string pet, string job_title, string phone_number, double latitude, double longitude, vector<string> stocks)
            : value(value),
              id(id),
              first_name(first_name),
              last_name(last_name),
              email(email),
              address(address),
              city(city),
              state(state),
              car(car),
              car_model(car_model),
              car_color(car_color),
              favorite_movie(favorite_movie),
              pet(pet),
              job_title(job_title),
              phone_number(phone_number),
              latitude(latitude),
              longitude(longitude),
              stocks(stocks),
              left(nullptr),
              right(nullptr)

        {
        }
    };
    Node *root;

    void insert(Node *&, const T &, int, string, string, string, string, string, string, string,
                string, string, string, string, string, string, double, double, vector<string>);

    Node *search(Node *, const T &) const;

    void print(Node *);

public:
    BinarySearchTree();

    void insert(const T &, int, string, string, string, string, string, string, string,
                string, string, string, string, string, string, double, double lngitude, vector<string>);

    Node *search(const T &) const;

    void print();

    // print the found json  if search values is found
    void printSearch(Node *);
};
