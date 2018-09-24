/* main and it's supporting extras
 */

#include "MyMap.h"
#include <cstdlib>

int main()
{
  //srand(time(NULL));
  MyMap<int, std::string> map1;

  cout << endl << "Inserting 300 items to map1:" << endl;
  for (int i = 0; i < 300; i++)
  {
    map1.insert(MyPair<int, std::string>(rand()%300,std::to_string(rand()%300)));
  }

  MyMap<int, std::string> map2(map1);

  cout << endl << "Printing Map 2:" << endl;
  cout << "************************************************" << endl;
  map2.print();
  cout << "************************************************" << endl;

  cout << endl << "map2.clear():" << endl;
  map2.clear();

  MyMap<int, std::string> map3 = map1;

  cout << endl << "Printing Map 3 (Should not be empty):" << endl;
  cout << "************************************************" << endl;
  map3.print();
  cout << "************************************************" << endl;

  cout << endl << "Erasing all elements of map3 one by one..." << endl;
  for (int i = 0; i < 300; i++)
    map3.erase(i);

  cout << endl << "Printing Map 3 (Should be emtpy):" << endl;
  cout << "************************************************" << endl;
  map3.print();
  cout << "************************************************" << endl;

  cout << endl << "Size of BST1: " << map1.size() << endl;
  cout << endl << "Size of BST2: " << map2.size() << endl;
  cout << endl << "Size of BST3: " << map3.size() << endl;

  cout << endl << "Map1.empty(): " << ((map1.empty())?("Yes"):("No")) << endl;
  cout << endl << "Map2.empty(): " << ((map2.empty())?("Yes"):("No")) << endl;
  cout << endl << "Map3.empty(): " << ((map3.empty())?("Yes"):("No")) << endl;

  MyMap<int, std::string> map4 = map2 = map3;

  MyMap<int, std::string> map5(map4);

  cout << endl << "Testing operator[] on all trees..." << endl;
  for (int i = 0; i < 300; i++)
  {
    map1[rand()%401] = std::to_string(i);
    map2[rand()%401] = std::to_string(i);
    map3[rand()%401] = std::to_string(i);
    map4[rand()%401] = std::to_string(i);
    map5[rand()%401] = std::to_string(i);
  }

  cout << endl << "Testing at() on all trees..." << endl;
  for (int i = 0; i < 400; i++)
  {
    try
    {
      map1.at(i) = std::to_string(i+rand()%400);
    }
    catch(std::out_of_range &e)
    {
      cout << "Index " << i << " not in map1" << endl;
    }
    try
    {
      map2.at(i) = std::to_string(i+rand()%400);
    }
    catch(std::out_of_range &e)
    {
      cout << "Index " << i << " not in map2" << endl;
    }
    try
    {
      map3.at(i) = std::to_string(i+rand()%400);
    }
    catch(std::out_of_range &e)
    {
      cout << "Index " << i << " not in map3" << endl;
    }
    try
    {
      map4.at(i) = std::to_string(i+rand()%400);
    }
    catch(std::out_of_range &e)
    {
      cout << "Index " << i << " not in map4" << endl;
    }
    try
    {
      map5.at(i) = std::to_string(i+rand()%400);
    }
    catch(std::out_of_range &e)
    {
      cout << "Index " << i << " not in map5" << endl;
    }
  }

  cout << endl << "Size of BST1: " << map1.size() << endl;
  cout << endl << "Size of BST2: " << map2.size() << endl;
  cout << endl << "Size of BST3: " << map3.size() << endl;
  cout << endl << "Size of BST4: " << map4.size() << endl;
  cout << endl << "Size of BST5: " << map5.size() << endl;

  cout << endl << "Testing map1.find()..." << endl;
  for (int i = 0; i < 400; i++)
  {
    int findval = rand()%400;
    MyPair<int, std::string>* kvfind = map1.find(findval);

    if (kvfind == nullptr)
      cout << "Key not found in tree" << endl;
    else
    {
      cout << endl << "Key: " << kvfind->first << endl;
      cout << endl << "Value: " << kvfind->second << endl;
    }
  }

  cout << endl << "Testing map2.find()..." << endl;
  for (int i = 0; i < 400; i++)
  {
    int findval = rand()%400;
    MyPair<int, std::string>* kvfind = map2.find(findval);

    if (kvfind == nullptr)
      cout << "Key not found in tree" << endl;
    else
    {
      cout << endl << "Key: " << kvfind->first << endl;
      cout << endl << "Value: " << kvfind->second << endl;
    }
  }

  cout << endl << "Testing map3.find()..." << endl;
  for (int i = 0; i < 400; i++)
  {
    int findval = rand()%400;
    MyPair<int, std::string>* kvfind = map3.find(findval);

    if (kvfind == nullptr)
      cout << "Key not found in tree" << endl;
    else
    {
      cout << endl << "Key: " << kvfind->first << endl;
      cout << endl << "Value: " << kvfind->second << endl;
    }
  }

  cout << endl << "Testing map4.find()..." << endl;
  for (int i = 0; i < 400; i++)
  {
    int findval = rand()%400;
    MyPair<int, std::string>* kvfind = map4.find(findval);

    if (kvfind == nullptr)
      cout << "Key not found in tree" << endl;
    else
    {
      cout << endl << "Key: " << kvfind->first << endl;
      cout << endl << "Value: " << kvfind->second << endl;
    }
  }

  cout << endl << "Testing map5.find()..." << endl;
  for (int i = 0; i < 400; i++)
  {
    int findval = rand()%400;
    MyPair<int, std::string>* kvfind = map5.find(findval);

    if (kvfind == nullptr)
      cout << "Key not found in tree" << endl;
    else
    {
      cout << endl << "Key: " << kvfind->first << endl;
      cout << endl << "Value: " << kvfind->second << endl;
    }
  }

  map1.clear();
  map2 = map3 = map4 = map5 = map1;

  cout << endl << "Size of BST1: " << map1.size() << endl;
  cout << endl << "Size of BST2: " << map2.size() << endl;
  cout << endl << "Size of BST3: " << map3.size() << endl;
  cout << endl << "Size of BST4: " << map4.size() << endl;
  cout << endl << "Size of BST5: " << map5.size() << endl;

  cout << endl << "Map1.empty(): " << ((map1.empty())?("Yes"):("No")) << endl;
  cout << endl << "Map2.empty(): " << ((map2.empty())?("Yes"):("No")) << endl;
  cout << endl << "Map3.empty(): " << ((map3.empty())?("Yes"):("No")) << endl;
  cout << endl << "Map4.empty(): " << ((map4.empty())?("Yes"):("No")) << endl;
  cout << endl << "Map5.empty(): " << ((map5.empty())?("Yes"):("No")) << endl;

  return 0;
}