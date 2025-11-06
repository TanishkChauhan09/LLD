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

class Preference {
private:
    std::vector<Gender> interestedIn;
    int minAge;
    int maxAge;
    double maxDistance; // in kilometers
    std::vector<std::string> interests;
    
public:
    Preference() {
        minAge = 18;
        maxAge = 100;
        maxDistance = 100.0;
    }
    
    void addGenderPreference(Gender gender) {
        interestedIn.push_back(gender);
    }
    
    void removeGenderPreference(Gender gender) {
        interestedIn.erase(std::remove(interestedIn.begin(), interestedIn.end(), gender), interestedIn.end());
    }
    
    void setAgeRange(int min, int max) {
        minAge = min;
        maxAge = max;
    }
    
    void setMaxDistance(double distance) {
        maxDistance = distance;
    }
    
    void addInterest(const std::string& interest) {
        interests.push_back(interest);
    }
    
    void removeInterest(const std::string& interest) {
        interests.erase(std::remove(interests.begin(), interests.end(), interest), interests.end());
    }
    
    bool isInterestedInGender(Gender gender) const {
        return std::find(interestedIn.begin(), interestedIn.end(), gender) != interestedIn.end();
    }
    
    bool isAgeInRange(int age) const {
        return age >= minAge && age <= maxAge;
    }
    
    bool isDistanceAcceptable(double distance) const {
        return distance <= maxDistance;
    }
    
    const std::vector<std::string>& getInterests() const {
        return interests;
    }
    
    const std::vector<Gender>& getInterestedGenders() const {
        return interestedIn;
    }
    
    int getMinAge() const {
        return minAge;
    }
    
    int getMaxAge() const {
        return maxAge;
    }
    
    double getMaxDistance() const {
        return maxDistance;
    }
};

class Message {
private:
    string senderId;
    string content;
    time_t timestamp;
    
public:
    Message(const string& sender, const string& msg) {
        senderId = sender;
        content = msg;
        timestamp = time(nullptr);
    }
    
    string getSenderId() const {
        return senderId;
    }
    
    string getContent() const {
        return content;
    }
    
    time_t getTimestamp() const {
        return timestamp;
    }
    
    string getFormattedTime() const {
        struct tm* timeinfo;
        char buffer[80];
        
        timeinfo = localtime(&timestamp);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        return string(buffer);
    }
};

// Chat room class
class ChatRoom {
private:
    string id;
    vector<string> participantIds;
    vector<Message*> messages;
    
public:
    ChatRoom(const string& roomId, const string& user1Id, const string& user2Id) {
        id = roomId;
        participantIds.push_back(user1Id);
        participantIds.push_back(user2Id);
    }
    
    ~ChatRoom() {
        for (auto msg : messages) {
            delete msg;
        }
    }
    
    string getId() const {
        return id;
    }
    
    void addMessage(const string& senderId, const string& content) {
        Message* msg = new Message(senderId, content);
        messages.push_back(msg);
    }
    
    bool hasParticipant(const string& userId) const {
        return find(participantIds.begin(), participantIds.end(), userId) != participantIds.end();
    }
    
    const vector<Message*>& getMessages() const {
        return messages;
    }
    
    const vector<string>& getParticipants() const {
        return participantIds;
    }
    
    void displayChat() const {
        cout << "===== Chat Room: " << id << " =====" << endl;
        for (const auto& msg : messages) {
            cout << "[" << msg->getFormattedTime() << "] " 
                 << msg->getSenderId() << ": " << msg->getContent() << endl;
        }
        cout << "=========================" << endl;
    }
};


class UserProfile {
private:
    string name;
    int age;
    Gender gender;
    string bio;
    vector<string> photos;
    vector<Interest*> interests;
    Location location;
    
public:
    UserProfile() {
        name = "";
        age = 0;
        gender = Gender::OTHER;
    }
    
    ~UserProfile() {
        for (auto interest : interests) {
            delete interest;
        }
    }
    
    void setName(const string& n) {
        name = n;
    }
    
    void setAge(int a) {
        age = a;
    }
    
    void setGender(Gender g) {
        gender = g;
    }
    
    void setBio(const string& b) {
        bio = b;
    }
    
    void addPhoto(const string& photoUrl) {
        photos.push_back(photoUrl);
    }
    
    void removePhoto(const string& photoUrl) {
        photos.erase(remove(photos.begin(), photos.end(), photoUrl), photos.end());
    }
    
    void addInterest(const string& name, const string& category) {
        Interest* interest = new Interest(name, category);
        interests.push_back(interest);
    }
    
    void removeInterest(const string& name) {
        auto it = find_if(interests.begin(), interests.end(), 
            [&name](const Interest* interest) {
                return interest->getName() == name;
            });
        
        if (it != interests.end()) {
            delete *it;
            interests.erase(it);
        }
    }
    
    void setLocation(const Location& loc) {
        location = loc;
    }
    
    string getName() const {
        return name;
    }
    
    int getAge() const {
        return age;
    }
    
    Gender getGender() const {
        return gender;
    }
    
    string getBio() const {
        return bio;
    }
    
    const vector<string>& getPhotos() const {
        return photos;
    }
    
    const vector<Interest*>& getInterests() const {
        return interests;
    }
    
    const Location& getLocation() const {
        return location;
    }
    
    void display() const {
        cout << "===== Profile =====" << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: ";
        switch (gender) {
            case Gender::MALE: cout << "Male"; break;
            case Gender::FEMALE: cout << "Female"; break;
            case Gender::NON_BINARY: cout << "Non-binary"; break;
            case Gender::OTHER: cout << "Other"; break;
        }
        cout << endl;
        
        cout << "Bio: " << bio << endl;
        
        cout << "Photos: ";
        for (const auto& photo : photos) {
            cout << photo << ", ";
        }
        cout << endl;
        
        cout << "Interests: ";
        for (const auto& interest : interests) {
            cout << interest->getName() << " (" << interest->getCategory() << "), ";
        }
        cout << endl;
        
        cout << "Location: " << location.getLatitude() << ", " << location.getLongitude() << endl;
        cout << "===================" << endl;
    }
};

enum class SwipeAction {
    LEFT,  
    RIGHT  
};


class User {
private:
    string id;
    UserProfile* profile;
    Preference* preference;
    map<string, SwipeAction> swipeHistory; // userId -> action
    NotificationObserver* notificationObserver;
    
public:
    User(const string& userId) {
        id = userId;
        profile = new UserProfile();
        preference = new Preference();
        notificationObserver = new UserNotificationObserver(userId);
        NotificationService::getInstance()->registerObserver(userId, notificationObserver);
    }
    
    ~User() {
        delete profile;
        delete preference;
        NotificationService::getInstance()->removeObserver(id);
        delete notificationObserver;
    }
    
    string getId() const {
        return id;
    }
    
    UserProfile* getProfile() {
        return profile;
    }
    
    Preference* getPreference() {
        return preference;
    }
    
    void swipe(const string& otherUserId, SwipeAction action) {
        swipeHistory[otherUserId] = action;
    }
    
    bool hasLiked(const string& otherUserId) const {
        auto it = swipeHistory.find(otherUserId);
        if (it != swipeHistory.end()) {
            return it->second == SwipeAction::RIGHT;
        }
        return false;
    }
    
    bool hasDisliked(const string& otherUserId) const {
        auto it = swipeHistory.find(otherUserId);
        if (it != swipeHistory.end()) {
            return it->second == SwipeAction::LEFT;
        }
        return false;
    }
    
    bool hasInteractedWith(const string& otherUserId) const {
        return swipeHistory.find(otherUserId) != swipeHistory.end();
    }
    
    void displayProfile() const {  // Principle of least knowledge
        profile->display();
    }
};

class LocationStrategy {
public:
    virtual ~LocationStrategy() {}
    virtual std::vector<User*> findNearbyUsers(const Location& location, double maxDistance, const std::vector<User*>& allUsers) = 0;
};


class BasicLocationStrategy : public LocationStrategy {
public:
    vector<User*> findNearbyUsers(const Location& location, double maxDistance, const vector<User*>& allUsers) override {
        vector<User*> nearbyUsers;
        for (User* user : allUsers) {
            double distance = location.distanceInKm(user->getProfile()->getLocation());
            if (distance <= maxDistance) {
                nearbyUsers.push_back(user);
            }
        }
        return nearbyUsers;
    }
};


class LocationService {
private:
    LocationStrategy* strategy;
    
    // Singleton Pattern
    static LocationService* instance;
    
    LocationService() {
        strategy = new BasicLocationStrategy();
    }
    
public:
    static LocationService* getInstance() {
        if (instance == nullptr) {
            instance = new LocationService();
        }
        return instance;
    }
    
    ~LocationService() {
        delete strategy;
    }
    
    void setStrategy(LocationStrategy* newStrategy) {
        delete strategy;
        strategy = newStrategy;
    }
    
    vector<User*> findNearbyUsers(const Location& location, double maxDistance, const vector<User*>& allUsers) {
        return strategy->findNearbyUsers(location, maxDistance, allUsers);
    }
};
