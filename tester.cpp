#include <iostream>
#include "wl/Subject.hpp"
using namespace wl;
using namespace std;

struct FireEvent {
    string location;
    int level;
};

class FireDepartment {
public:
    void response(FireEvent fire_event) {
        cout << "A level " << fire_event.level 
            << " fire at " << fire_event.location << endl; 
        cout << "On my way" << endl;
    }
};

class SecuritySystem {
public:
    Subject<FireEvent> fire_alarm;
};

int main(int argc, const char *argv[])
{
    SecuritySystem sys;
    FireDepartment dep;

    sys.fire_alarm += wl::bind(&dep, &FireDepartment::response);
    sys.fire_alarm(FireEvent{"NYC", 100000});

    sys.fire_alarm -= &dep;
    sys.fire_alarm(FireEvent{"LAS", 100000});
    return 0;
}
