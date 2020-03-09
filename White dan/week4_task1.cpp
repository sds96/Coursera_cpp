// Example program
#include <iostream>
#include <string>

using namespace std;

struct Specialization {
    string name;
    explicit Specialization (string new_name){
        name = new_name;
        }
    };
    
struct Course{
    string name;
    explicit Course (string new_name){
        name = new_name;
        }
    };
    
struct Week{
    string name;
    explicit Week (string new_name){
        name = new_name;
        }
    };

struct LectureTitle {
  string specialization;
  string course;
  string week;
  
  LectureTitle (Specialization spec_, Course course_, Week week_){
      specialization = spec_.name;
      course = course_.name;
      week = week_.name;
      }
};