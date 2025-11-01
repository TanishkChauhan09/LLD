class Profile;
class Message;
class ChatRoom;
class NotificationObserver;
class LocationService;

// -------------------- Observer Pattern -------------------- //

// Observer Pattern: Interface for notification observers
class NotificationObserver {
public:
    virtual ~NotificationObserver() {}
    virtual void update(const std::string& message) = 0;
};

// Concrete observer
class UserNotificationObserver : public NotificationObserver {
private:
    std::string userId;
public:
    UserNotificationObserver(const string& id) {
        userId = id;
    }
    void update(const string& message) override {
        cout << "Notification for user " << userId << ": " << message << endl;
    }
};

// Observable for Observer Pattern
class NotificationService {
private:
    std::map<std::string, NotificationObserver*> observers;
    
    // Singleton Pattern
    static NotificationService* instance;
    NotificationService() {}
    
public:
    static NotificationService* getInstance() {
        if (instance == nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }
    
    void registerObserver(const string& userId, NotificationObserver* observer) {
        observers[userId] = observer;
    }
    
    void removeObserver(const string& userId) {
        observers.erase(userId);
    }
    
    void notifyUser(const string& userId, const string& message) {
        if (observers.find(userId) != observers.end()) {
            observers[userId]->update(message);
        }
    }
    
    void notifyAll(const string& message) {
        for (auto& pair : observers) {
            pair.second->update(message);
        }
    }
};

// Initialize static member
NotificationService* NotificationService::instance = nullptr;

// -------------------- Basic Models -------------------- //

// Gender enum
enum class Gender {
    MALE,
    FEMALE,
    NON_BINARY,
    OTHER
};


class Location {
private:
    double latitude;
    double longitude;
    
public:
    Location() {
        latitude = 0.0;
        longitude = 0.0;
    }
    
    Location(double lat, double lon) {
        latitude = lat;
        longitude = lon;
    }
    
    double getLatitude() const {
        return latitude;
    }
    
    double getLongitude() const {
        return longitude;
    }
    
    void setLatitude(double lat) {
        latitude = lat;
    }
    
    void setLongitude(double lon) {
        longitude = lon;
    }

        double distanceInKm(const Location& other) const {
        const double earthRadiusKm = 6371.0;
        double dLat = (other.latitude - latitude) * M_PI / 180.0;
        double dLon = (other.longitude - longitude) * M_PI / 180.0;
        
        double a = sin(dLat/2) * sin(dLat/2) +
                   cos(latitude * M_PI / 180.0) * cos(other.latitude * M_PI / 180.0) *
                   sin(dLon/2) * sin(dLon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        return earthRadiusKm * c;
    }
};


class Interest {
private:
    std::string name;
    std::string category;
    
public:
    Interest() {
        name = "";
        category = "";
    }
    
    Interest(const string& n, const string& c) {
        name = n;
        category = c;
    }
    
    std::string getName() const {
        return name;
    }
    
    std::string getCategory() const {
        return category;
    }
};
