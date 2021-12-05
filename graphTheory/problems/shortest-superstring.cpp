#include <vector>
#include <string>
#include <tuple>
#include <bitset>
#include <optional>
#include <map>
using namespace std;

string append(string current, string word)
{
    int startIndex = current.size() - word.size();
    if (startIndex < 0)
        startIndex = 0;
    
    bool appended = false;
    for (startIndex; startIndex < current.size(); startIndex++)
    {
        appended = true;
        for (int wordIndex = 0; wordIndex < word.size(); wordIndex++)
        {
            int index = startIndex + wordIndex;
            if (index >= current.size())
            {
                current.push_back(word[wordIndex]);
            }
            else if (current[index] != word[wordIndex])
            {
                appended = false;
                break;
            }
        }

        if (appended)
            break;
    }

    if (!appended)
        current.append(word);

    return current;
}


string findShortestSuperString(string currentWord, const vector<string>& words, bitset<32> state, map<pair<unsigned long, string>, string>& memoization)
{
    if (state.count() == words.size())
        return currentWord;

    if (auto it = memoization.find({state.to_ulong(), currentWord}); it != end(memoization))
        return it->second;

    optional<string> solution;
    for (int i = 0; i < words.size(); i++)
    {
        if (state[i])
            continue;
        
        auto superString = findShortestSuperString(words[i], words, state.set(i), memoization);
        auto appendedSuperString = append(currentWord, superString);

        if (!solution || solution->size() > appendedSuperString.size())
            solution = appendedSuperString;

        state.reset(i);
    }

    memoization[{state.to_ulong(), currentWord}] = *solution;

    return *solution;
}


string shortestSuperstring(vector<string> words)
{
    map<pair<unsigned long, string>, string> memoization;

    return findShortestSuperString("", words, bitset<32>(), memoization);
}

int main()
{
    string res1 = shortestSuperstring({"catg","ctaagt","gcta","ttca","atgcatc"});
    //  gctaagttcatgcatc
    // "gctaagttcatgcatc"

    string res2 = shortestSuperstring({"abcdef","efde","defab"});
    // "efdefabcdef"
    // "abcdefdefab"
    // "efdeabcdefab"

    string res3 = shortestSuperstring({"phuutlgczfspygaljkv","fspygaljkvahvuii","csywjodtnkynkjckq","poyykqyrhbvcwvjl","xijupvzzwphuutlg","aljkvahvuiivqbqrw","vahvuiivqbqrwryd","wjodtnkynkjckqurgu","ecdmbshotqbxjqgbou","hvuiivqbqrwrydgnr","ivqbqrwrydgnrubcsywj","wphuutlgczfspyga"});
    // 
}