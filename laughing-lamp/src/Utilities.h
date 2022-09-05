#include <string>
#include <vector>

namespace Utilities
{
    std::vector<std::string> split(const std::string splitter, std::string line)
    {
        std::vector<std::string> arr;
        int spacePos;
        int currPos = 0;
        int k = 0;
        int prevPos = 0;

        do
        {
            spacePos = line.find(splitter, currPos);

            if(spacePos >= 0)
            {
            
                currPos = spacePos;
                arr.push_back(line.substr(prevPos, currPos - prevPos));
                currPos++;
                prevPos = currPos;
                k++;
            }
        }while( spacePos >= 0);

        arr.push_back(line.substr(prevPos,line.length()));
        return arr;
    }
}