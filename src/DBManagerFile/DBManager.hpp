#pragma once
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <optional>

struct User {
    int ID;
    std::string username;
    std::string password;
    int permissions;
    bool isActive;
    std::vector<std::pair<int, bool>> voteToOwnership;
};

struct Vote {
    int voteID;
    int creatorID;
    std::string title;
    std::vector<std::string> options;
    std::string endTime;
    std::map<int, int> votes;
};

struct PermissionReason {
    int userID;
    std::string username;
    std::string reason;
};

class DBManager {
public:
    DBManager(const std::string& dbFilePath = "src/DBManagerFile/DB.json");

    bool load();
    bool save();

    std::optional<User> getUserByUsername(const std::string& username) const;
    std::optional<User> getUserByID(int id) const;
    void addUser(const User& user);
    bool updateUser(const User& updatedUser);

    std::vector<Vote> getVotes() const;
    std::optional<Vote> getVoteByID(int voteID) const;
    void addVote(const Vote& vote);
    bool updateVote(const Vote& updatedVote);

    std::vector<PermissionReason> getPermissionReasons() const;
    void addPermissionReason(const PermissionReason& pr);
    bool removePermissionReason(int userID);

    int getNextUserID() const;
    int getNextVoteID() const;

private:
    std::string filePath;
    // JSON document, e.g. nlohmann::json, would be here in implementation file
};

