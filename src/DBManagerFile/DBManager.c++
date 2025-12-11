#include "DBManager.hpp"
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Helper functions to convert between JSON and structs

static User userFromJson(const json& j) {
    User user;
    user.ID = j.at("ID").get<int>();
    user.username = j.at("username").get<std::string>();
    user.password = j.at("password").get<std::string>();
    user.permissions = j.at("permissions").get<int>();
    user.isActive = j.at("isActive").get<bool>();
    user.voteToOwnership.clear();
    for (const auto& pair : j.at("voteToOwnership")) {
        user.voteToOwnership.emplace_back(
            pair.at("first").get<int>(), pair.at("second").get<bool>());
    }
    return user;
}

static json userToJson(const User& user) {
    json j;
    j["ID"] = user.ID;
    j["username"] = user.username;
    j["password"] = user.password;
    j["permissions"] = user.permissions;
    j["isActive"] = user.isActive;
    j["voteToOwnership"] = json::array();
    for (const auto& p : user.voteToOwnership) {
        j["voteToOwnership"].push_back({{"first", p.first}, {"second", p.second}});
    }
    return j;
}

static Vote voteFromJson(const json& j) {
    Vote vote;
    vote.voteID = j.at("voteID").get<int>();
    vote.creatorID = j.at("creatorID").get<int>();
    vote.title = j.at("title").get<std::string>();
    vote.options = j.at("options").get<std::vector<std::string>>();
    vote.endTime = j.at("endTime").get<std::string>();
    vote.votes.clear();
    for (auto it = j.at("votes").begin(); it != j.at("votes").end(); ++it) {
        int userID = std::stoi(it.key());
        int optionIndex = it.value().get<int>();
        vote.votes[userID] = optionIndex;
    }
    return vote;
}

static json voteToJson(const Vote& vote) {
    json j;
    j["voteID"] = vote.voteID;
    j["creatorID"] = vote.creatorID;
    j["title"] = vote.title;
    j["options"] = vote.options;
    j["endTime"] = vote.endTime;
    j["votes"] = json::object();
    for (const auto& [userID, optionIdx] : vote.votes) {
        j["votes"][std::to_string(userID)] = optionIdx;
    }
    return j;
}

static PermissionReason prFromJson(const json& j) {
    PermissionReason pr;
    pr.userID = j.at("userID").get<int>();
    pr.username = j.at("username").get<std::string>();
    pr.reason = j.at("reason").get<std::string>();
    return pr;
}

static json prToJson(const PermissionReason& pr) {
    json j;
    j["userID"] = pr.userID;
    j["username"] = pr.username;
    j["reason"] = pr.reason;
    return j;
}

// DBManager implementation

DBManager::DBManager(const std::string& dbFilePath)
    : filePath(dbFilePath) {}

bool DBManager::load() {
    std::ifstream in(filePath);
    if (!in.is_open()) return false;
    try {
        json jdoc;
        in >> jdoc;
        in.close();
        // store document in an internal variable if needed, but functionally this does nothing in this stub
    }
    catch (...) {
        return false;
    }
    return true;
}

bool DBManager::save() {
    // Only stub, real implementation would freeze the internal DB state to file
    // Just try to open file for writing
    std::ofstream out(filePath);
    if (!out.is_open())
        return false;
    out.close();
    return true;
}

std::optional<User> DBManager::getUserByUsername(const std::string& username) const {
    std::ifstream in(filePath);
    if (!in.is_open()) return std::nullopt;
    json jdoc;
    in >> jdoc;
    in.close();

    for (const auto& juser : jdoc.at("users")) {
        if (juser.at("username") == username) {
            return userFromJson(juser);
        }
    }
    return std::nullopt;
}

std::optional<User> DBManager::getUserByID(int id) const {
    std::ifstream in(filePath);
    if (!in.is_open()) return std::nullopt;
    json jdoc;
    in >> jdoc;
    in.close();
    for (const auto& juser : jdoc.at("users")) {
        if (juser.at("ID") == id) {
            return userFromJson(juser);
        }
    }
    return std::nullopt;
}

void DBManager::addUser(const User& user) {
    std::ifstream in(filePath);
    json jdoc;
    if (in.is_open()) {
        in >> jdoc;
        in.close();
    }
    else {
        jdoc = json::object();
    }
    if (!jdoc.contains("users"))
        jdoc["users"] = json::array();
    jdoc["users"].push_back(userToJson(user));
    std::ofstream out(filePath);
    out << jdoc.dump(4);
    out.close();
}

bool DBManager::updateUser(const User& updatedUser) {
    std::ifstream in(filePath);
    if (!in.is_open()) return false;
    json jdoc;
    in >> jdoc;
    in.close();

    bool found = false;
    for (auto& juser : jdoc["users"]) {
        if (juser.at("ID") == updatedUser.ID) {
            juser = userToJson(updatedUser);
            found = true;
            break;
        }
    }
    if (!found) return false;
    std::ofstream out(filePath);
    out << jdoc.dump(4);
    out.close();
    return true;
}

std::vector<Vote> DBManager::getVotes() const {
    std::vector<Vote> res;
    std::ifstream in(filePath);
    if (!in.is_open()) return res;
    json jdoc;
    in >> jdoc;
    in.close();
    if (!jdoc.contains("votes")) return res;
    for (const auto& jvote : jdoc.at("votes")) {
        res.push_back(voteFromJson(jvote));
    }
    return res;
}

std::optional<Vote> DBManager::getVoteByID(int voteID) const {
    std::ifstream in(filePath);
    if (!in.is_open()) return std::nullopt;
    json jdoc;
    in >> jdoc;
    in.close();
    if (!jdoc.contains("votes")) return std::nullopt;
    for (const auto& jvote : jdoc.at("votes")) {
        if (jvote.at("voteID") == voteID) {
            return voteFromJson(jvote);
        }
    }
    return std::nullopt;
}

void DBManager::addVote(const Vote& vote) {
    std::ifstream in(filePath);
    json jdoc;
    if (in.is_open()) {
        in >> jdoc;
        in.close();
    }
    else {
        jdoc = json::object();
    }
    if (!jdoc.contains("votes"))
        jdoc["votes"] = json::array();
    jdoc["votes"].push_back(voteToJson(vote));
    std::ofstream out(filePath);
    out << jdoc.dump(4);
    out.close();
}

bool DBManager::updateVote(const Vote& updatedVote) {
    std::ifstream in(filePath);
    if (!in.is_open()) return false;
    json jdoc;
    in >> jdoc;
    in.close();

    bool found = false;
    for (auto& jvote : jdoc["votes"]) {
        if (jvote.at("voteID") == updatedVote.voteID) {
            jvote = voteToJson(updatedVote);
            found = true;
            break;
        }
    }
    if (!found) return false;
    std::ofstream out(filePath);
    out << jdoc.dump(4);
    out.close();
    return true;
}

std::vector<PermissionReason> DBManager::getPermissionReasons() const {
    std::vector<PermissionReason> res;
    std::ifstream in(filePath);
    if (!in.is_open()) return res;
    json jdoc;
    in >> jdoc;
    in.close();
    if (!jdoc.contains("permission_reasons")) return res;
    for (const auto& jpr : jdoc.at("permission_reasons")) {
        res.push_back(prFromJson(jpr));
    }
    return res;
}

void DBManager::addPermissionReason(const PermissionReason& pr) {
    std::ifstream in(filePath);
    json jdoc;
    if (in.is_open()) {
        in >> jdoc;
        in.close();
    }
    else {
        jdoc = json::object();
    }
    if (!jdoc.contains("permission_reasons"))
        jdoc["permission_reasons"] = json::array();
    jdoc["permission_reasons"].push_back(prToJson(pr));
    std::ofstream out(filePath);
    out << jdoc.dump(4);
    out.close();
}

bool DBManager::removePermissionReason(int userID) {
    std::ifstream in(filePath);
    if (!in.is_open()) return false;
    json jdoc;
    in >> jdoc;
    in.close();

    if (!jdoc.contains("permission_reasons")) return false;
    auto& arr = jdoc["permission_reasons"];
    size_t oldsize = arr.size();
    arr.erase(
        std::remove_if(arr.begin(), arr.end(), [&](const json& pr) {
            return pr.at("userID").get<int>() == userID;
        }),
        arr.end()
    );
    if (arr.size() == oldsize) return false;
    std::ofstream out(filePath);
    out << jdoc.dump(4);
    out.close();
    return true;
}

int DBManager::getNextUserID() const {
    std::ifstream in(filePath);
    if (!in.is_open()) return 1;
    json jdoc;
    in >> jdoc;
    in.close();
    int maxID = 0;
    if (!jdoc.contains("users")) return 1;
    for (const auto& juser : jdoc.at("users")) {
        maxID = std::max(maxID, juser.at("ID").get<int>());
    }
    return maxID + 1;
}

int DBManager::getNextVoteID() const {
    std::ifstream in(filePath);
    if (!in.is_open()) return 0;
    json jdoc;
    in >> jdoc;
    in.close();
    int maxID = -1;
    if (!jdoc.contains("votes")) return 0;
    for (const auto& jvote : jdoc.at("votes")) {
        maxID = std::max(maxID, jvote.at("voteID").get<int>());
    }
    return maxID + 1;
}
