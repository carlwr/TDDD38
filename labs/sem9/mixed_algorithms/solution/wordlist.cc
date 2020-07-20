#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main()
{
    vector<string> text { istream_iterator<string>{cin},
                          istream_iterator<string>{} };
    vector<string> words {text};
    
    sort(begin(words), end(words));
    words.erase(unique(begin(words), end(words)), end(words));
 
    transform(begin(words), end(words), ostream_iterator<string>{cout, "\n"},
              [&text](string const& word)
              {
                  int n{count(begin(text), end(text), word)};
                  return word + ": " + to_string(n);
              });
              
}
