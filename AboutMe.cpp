//
//  AboutMe.cpp
//  Assignment0
//
//  Created by rick gessner on 10/1/20.
//

#include "AboutMe.hpp"

namespace ECE17 {

//update the following class to reflect your information...
  AboutMe::AboutMe() :
    name{"Raul Valadez"}, pid{"A16167148"}, years_at_ucsd{3} {
    //other initializers would go here...
  }
  
  AboutMe::AboutMe(const AboutMe &aStudent) {
    *this=aStudent;
  }
  
  AboutMe& AboutMe::operator=(const AboutMe &aStudent) {
    name=aStudent.name;
    pid=aStudent.pid;
    years_at_ucsd=aStudent.years_at_ucsd;
    return *this;
  }
          
  bool AboutMe::operator==(const AboutMe &aStudent) const {
    return false;
  }

  const std::string& AboutMe::getPID() const {return pid;}
  const std::string& AboutMe::getName() const {return name;}

}

