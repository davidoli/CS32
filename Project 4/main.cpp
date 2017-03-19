/* #include <iostream>
 #include "MyMap.h"
 #include "provided.h"
 #include <string>
 
 using namespace std;





 int main()
 {
     
     
 MyMap<string, double> nameToGPA; // maps student name to GPA
 nameToGPA.associate("Carey", 3.5); // Carey has a 3.5 GPA
 nameToGPA.associate("David", 3.99); // David beat Carey
 nameToGPA.associate("Abe", 3.2); // Abe has a 3.2 GPA
 
 
 double* davidsGPA = nameToGPA.find("David");
 if (davidsGPA != nullptr)
     *davidsGPA = 1.5; // after a re-grade of David’s exam
 
 nameToGPA.associate("Carey", 4.0); // Carey deserves a 4.0
 // replaces old 3.5 GPA
 double* lindasGPA = nameToGPA.find("Linda");
 if (lindasGPA == nullptr)
     cout << "Linda is not in the roster!" << endl;
 else
     cout << "Linda’s GPA is: " << *lindasGPA << endl;
 
 MapLoader m;
 
 m.load("/Users/macbookpro/Documents/College Yr3/CS32/Project 4/Project 4/mapdata.txt");
 
 AttractionMapper am;
 am.init(m);
 
 SegmentMapper sm;
 cout << "hello" << endl;
 sm.init(m);
 
 GeoCoord g;
 am.getGeoCoord("us post office", g);
 
 vector<StreetSegment> lol = sm.getSegments(g);
 
 cout << g.latitudeText << endl;
 
 for(int i; i<lol.size();i++)
     std::cout << lol[i].streetName << endl;
 
 
 Navigator nav;
 nav.loadMapData("/Users/macbookpro/Documents/College Yr3/CS32/Project 4/Project 4/mapdata.txt");
 vector<NavSegment> hi;
     
 if(nav.navigate("ralph's", "Kaplan", hi) == NAV_SUCCESS)
     cout << "yay" << endl;
 else
     cout << "awh" << endl;
 }
*/

