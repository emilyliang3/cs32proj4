//
//  MemberDatabase.cpp
//  Unhinged
//
//  Created by Emily Liang on 3/13/22.
//

#include "MemberDatabase.h"
#include "utility.h"
#include <fstream>
using namespace std;

bool MemberDatabase::LoadDatabase(std::string filename)
{
    ifstream data(filename);
    if (!data)
        return false;
    //the following variables are to loop thru each member's data
    string str, curName, curEmail;
    int remainingPairs = 0;
    bool readingPairs = false;
    bool readingName = true;
    bool readingEmail = false;
    bool readingNum = false;
    int count = 0;
    //PersonProfile curMember("", "");
    PersonProfile* p;
    
    while (getline(data, str)) {
        cout << count << "-";
        if (readingName) {
            curName = str;
            readingEmail = true;
            readingName = false;
        }
        else if(readingEmail) {
            curEmail = str;
            p = new PersonProfile(curName, curEmail);
            m_profileptrs.push_back(p);
            //m_emailList.insert(m_emailList.begin(), curEmail);
            readingNum = true;
            readingEmail = false;
        }
        else if(readingNum) {
            remainingPairs = stoi(str);
            readingPairs = true;
            readingNum = false;
        }
        else if(readingPairs) {
            //*p = PersonProfile(curName, curEmail);
            int comma = (int) str.find(',');
            string attribute = str.substr(0, comma);
            string value = str.substr(comma+1);
            AttValPair avp(attribute, value);
            p->AddAttValPair(avp);
            //adding avp and set of emails to database
            set<string> s;
            set<string>* sptr = m_emails.search(str);
            if (sptr != nullptr)
                s = *sptr;
            s.insert(curEmail);
            m_emails.insert(str, s);
            remainingPairs--;
            if (remainingPairs == 0) { //done reading input of current member
                readingPairs = false;
                m_members.insert(curEmail, p); //add member's profile to database DELETE
            }
        }
        else if(str.empty()) //in btwn members, starting the loop over for next member
            readingName = true;
        count++;
    }
    if (data.is_open())
        data.close();
    return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string avp = input.attribute + "," + input.value;
    set<string> s = *m_emails.search(avp);
    vector<string> v;
    set<string>::iterator it;
    it = s.begin();
    while (it != s.end()) {
        v.insert(v.begin(), *it);
    }
    return v;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const
{
    PersonProfile** p = m_members.search(email);
    return *p;
}

MemberDatabase::~MemberDatabase()
{
    vector<PersonProfile*>::iterator it;
    it = m_profileptrs.begin();
    while (it != m_profileptrs.end()) {
        delete *it;
        m_profileptrs.erase(it);
        it = m_profileptrs.begin();
    }
}
