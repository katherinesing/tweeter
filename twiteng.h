#ifndef TWITENG_H
#define TWITENG_H
#include <map>
#include <string>
#include <set>
#include <vector>
#include "user.h"
#include "datetime.h"
#include "heap.h"
#include "tagdata.h"
#include "hash.h"

class TwitEng
{
 public:
  struct Node {
  User* user;
  int id = -1;
  int lowlink = -1;
  };

  TwitEng();
  ~TwitEng();
  /**
   * Parses the Twitter database and populates internal structures
   * @param filename of the database file
   * @return true if there is an error, false if successful
   */
  bool parse(char* filename);

  /**
   * Allocates a tweet from its parts and adds it to internal structures
   * @param username of the user who made the tweet
   * @param timestamp of the tweet
   * @param text is the actual text of the tweet as a single string
   */
  void addTweet(const std::string& username, const DateTime& time, const std::string& text);
  void addTweet(const std::string& text); //const std::string& username,

  /**
   * adds name_of_follower to name_to_follow's followers list.
   * adds name_to_follow to name_of_follower's following list.
   */
  void addFollower(std::string name_to_follow); //std::string name_of_follower,

  /**
   * Searches for tweets with the given words and strategy
   * @param words is the hashtag terms in any case without the '#'
   * @param strategy 0=AND, 1=OR
   * @return the tweets that match the search
   */
  std::vector<Tweet*> search(std::vector<std::string>& terms, int strategy);

  /**
   * Dump feeds of each user to their own file
   */
  void dumpFeeds();

  /**
   * creates a file and outputs the 
   * number of users,
   * who each user is following,
   * and all tweets
   */
  void save(std::string filename);

  

  void SCC(std::string filename);
  void SCChelper(Node*& node, int& index);
  void trending(int n);
  bool login(std::string username, std::string password);
  void logout();
  
 private:
  /* Add any other data members or helper functions here  */
  std::map <std::string,User*> allUsers; //used to initialize followers connection
  std::map <std::string, std::set<Tweet*> > allHashtags; 
  std::set <Tweet*> allTweets; //for destruct
  std::set< std::set<std::string> > components;
  Heap<TagData, TagStringEqual, TagIntGreater, TagStringHasher> trending_;
  std::string loggedInUsername;
  bool aUserIsLoggedIn = false;
};


#endif
