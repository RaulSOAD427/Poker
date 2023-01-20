//
//  AboutMe.hpp
//  Assignment0
//
//  Created by rick gessner on 09/15/20.
//

#ifndef AboutMe_hpp
#define AboutMe_hpp

#include <stdio.h>
#include <string>

namespace ECE17 {

  const std::string kDfltPID{"00000000"};

  class AboutMe {
  public:
    AboutMe();
    AboutMe(const AboutMe &aStudent);
    AboutMe& operator=(const AboutMe &aStudent);
    ~AboutMe()=default;
    
    bool operator==(const AboutMe &aStudent) const;
    
    const std::string& getPID() const;
    const std::string& getName() const;

  protected:
    std::string name;
    std::string pid;
    size_t      years_at_ucsd;
  };
}

#endif /* AboutMe_hpp */
