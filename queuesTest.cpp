#include "queues.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include <string>

using std::cout;
using std::endl;
using std::out_of_range;
using std::strcmp;
using std::ostringstream;
using std::stoi;
using std::string;

//This helps with testing, do not modify.
bool checkTest(int testNum, int& correct, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}


//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(int testNum, int& correct, string whatItShouldBe, string whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    if (whatItShouldBe == "") {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
    }
    else {
      cout << "***Failed test " << testNum << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
    }
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}

//This helps with testing, do not modify.
bool checkTestMemory(int testNum, int& correct, int whatItShouldBe, int whatItIs) {

  if (whatItShouldBe == whatItIs) {
    correct++;
    cout << "Passed " << testNum << endl;
    return true;
  }
  else {
    cout << "***Failed test " << testNum << " *** " << endl << ".  ";
    cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
    cout << "The unit test checker is closing down the program now due to a failed test" << endl;
    exit(1);
    return false;
  }
}


//This helps with testing, do not modify.

//Copyright 2023, Bradley Peterson, Weber State University, All rights reserved. (May 2024)

bool testQueueForCS2420() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testQueueForCS2420 Tests--------" << endl;

  string result;
  string caughtError;
  {
    QueueForCS2420<string> pQueue(5);

    // Tests push_back
    string item = "penny";
    pQueue.push_back(item);
    item = "nickel";
    pQueue.push_back(item);
    item = "dime";
    pQueue.push_back(item);
    item = "quarter";
    pQueue.push_back(item);

    checkTest(testNum++, correct, 4, pQueue.size()); // 1

    checkTest(testNum++, correct, "penny", pQueue.front()); // 2
    checkTest(testNum++, correct, "quarter", pQueue.back()); // 3
    pQueue.pop_front();
    checkTest(testNum++, correct, 3, pQueue.size()); // 4

    checkTest(testNum++, correct, "nickel", pQueue.front()); // 5
    checkTest(testNum++, correct, "quarter", pQueue.back()); // 6

    pQueue.pop_front();
    checkTest(testNum++, correct, "dime", pQueue.front()); // 7 
    pQueue.pop_front();
    checkTest(testNum++, correct, "quarter", pQueue.front()); // 8
    pQueue.pop_front();
    checkTest(testNum++, correct, 0, pQueue.size()); // 9

    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (std::out_of_range&) {
      caughtError = "caught";
    }
    checkTest(testNum++, correct, "caught", caughtError); // 10

    caughtError = "not caught";
    try {
      result = pQueue.back();
    }
    catch (std::out_of_range&) {
      caughtError = "caught";
    }
    checkTest(testNum++, correct, "caught", caughtError); // 11

    checkTest(testNum++, correct, 0, pQueue.size()); // 12

    item = "penny";
    pQueue.push_back(item);
    checkTest(testNum++, correct, "penny", pQueue.front()); // 13
    pQueue.push_back("nickel");
    pQueue.push_back("dime");
    pQueue.push_back("quarter");

    checkTest(testNum++, correct, "penny", pQueue.front()); // 14
    pQueue.pop_front();
    pQueue.push_back("half dollar");
    pQueue.push_back("silver dollar");

    // It should be full, no more room to add more.
    pQueue.push_back("million dollar bill");

    // Take a look at what is coming next.
    checkTest(testNum++, correct, "nickel", pQueue.front()); // 15
    pQueue.pop_front();
    checkTest(testNum++, correct, "dime", pQueue.front()); // 16
    pQueue.pop_front();
    checkTest(testNum++, correct, "quarter", pQueue.front()); // 17
    pQueue.pop_front();
    checkTest(testNum++, correct, "half dollar", pQueue.front()); // 18
    pQueue.pop_front();
    checkTest(testNum++, correct, "silver dollar", pQueue.front()); // 19
    pQueue.pop_front();
    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (std::out_of_range&) {
      caughtError = "caught";
    }
    checkTest(testNum++, correct, "caught", caughtError); // 20

    // Test adding and removing back and forth
    pQueue.push_back("penny");
    checkTest(testNum++, correct, "penny", pQueue.front()); // 21
    pQueue.pop_front();
    pQueue.push_back("nickel");
    checkTest(testNum++, correct, "nickel", pQueue.front()); // 22
    pQueue.pop_front();
    pQueue.push_back("dime");
    checkTest(testNum++, correct, "dime", pQueue.front()); // 23
    pQueue.pop_front();
    pQueue.push_back("quarter");
    checkTest(testNum++, correct, "quarter", pQueue.front()); // 24
    pQueue.pop_front();
    pQueue.push_back("half dollar");
    checkTest(testNum++, correct, "half dollar", pQueue.front()); // 25
    pQueue.pop_front();
    pQueue.push_back("silver dollar");
    checkTest(testNum++, correct, 1, pQueue.size()); // 26

    checkTest(testNum++, correct, "silver dollar", pQueue.front()); // 27
    pQueue.pop_front();
    caughtError = "not caught";
    try {
      result = pQueue.front();
    }
    catch (std::out_of_range&) {
      caughtError = "caught";
    }
    checkTest(testNum++, correct, "caught", caughtError); // 28
  }
  {
    QueueForCS2420<int> iQueue(3); // A queue of 3 items

    iQueue.push_back(1);
    iQueue.push_back(2);
    iQueue.pop_front();
    iQueue.push_back(3);
    iQueue.pop_front();
    checkTest(testNum++, correct, 3, iQueue.front()); // 29
    checkTest(testNum++, correct, 3, iQueue.back()); // 30
    iQueue.push_back(4);
    iQueue.push_back(5);
    checkTest(testNum++, correct, 3, iQueue.front()); // 31
    iQueue.pop_front();
    checkTest(testNum++, correct, 4, iQueue.front()); // 32
    iQueue.pop_front();
    checkTest(testNum++, correct, 5, iQueue.front()); // 33
  }
  return testNum - 1 == correct;
}

bool testQueueClone() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testQueueClone Tests--------" << endl;

  string result;
  string caughtError;

  // Test copy constructor
  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);

    QueueForCS2420<int> iCopy(iQueue);
    checkTest(testNum++, correct, 5, iQueue.size()); // 1
    checkTest(testNum++, correct, 5, iCopy.size()); // 2
    checkTest(testNum++, correct, 10, iQueue.front()); // 3
    checkTest(testNum++, correct, 10, iCopy.front()); // 4

    iCopy.pop_front();
    checkTest(testNum++, correct, 4, iCopy.size()); // 5
    checkTest(testNum++, correct, 20, iCopy.front()); // 6
    checkTest(testNum++, correct, 10, iQueue.front()); // 7
  }

  // Test operator=
  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);

    QueueForCS2420<int> iCopy(5);
    iCopy.push_back(1111);
    iCopy = iQueue;
    checkTest(testNum++, correct, 5, iQueue.size()); // 8
    checkTest(testNum++, correct, 5, iCopy.size()); // 9
    checkTest(testNum++, correct, 10, iQueue.front()); // 10
    checkTest(testNum++, correct, 10, iCopy.front()); // 11

    iCopy.pop_front();
    checkTest(testNum++, correct, 4, iCopy.size()); // 12
    checkTest(testNum++, correct, 20, iCopy.front()); // 13
    checkTest(testNum++, correct, 10, iQueue.front()); // 14
  }

  // Test an attempted cloning an object onto itself (obviously it shouldn't attempt to clone it)
  {
    QueueForCS2420<int> iQueue(5);
    iQueue.push_back(10);
    iQueue.push_back(20);
    iQueue.push_back(30);
    iQueue.push_back(40);
    iQueue.push_back(50);

    iQueue = iQueue;
    checkTest(testNum++, correct, 5, iQueue.size()); // 15
    checkTest(testNum++, correct, 10, iQueue.front()); // 16
    iQueue.pop_front();
    checkTest(testNum++, correct, 20, iQueue.front()); // 17
  }
  return testNum - 1 == correct;
}


bool testQueueLarge() {

  int testNum = 1;
  int correct = 0;
  cout << "--------testQueueLarge Tests--------" << endl;

  string result;
  string caughtError;

  // Test copy constructor
  {
    QueueForCS2420<int> iQueue(10'000'000);
    for (int i = 10'000'000; i < 10'800'000; i++) {
      iQueue.push_back(i);
    }
    for (int i = 0; i < 400'000; i++) {
      iQueue.pop_front();
    }
    for (int i = 10'800'000; i < 11'200'000; i++) {
      iQueue.push_back(i);
    }

    QueueForCS2420<int> iCopy(iQueue);
    checkTest(testNum++, correct, 800000, iQueue.size()); // 1
    checkTest(testNum++, correct, 10400000, iQueue.front()); // 2
  }
  return testNum - 1 == correct;
}

int main(int argc, char** argv) {

  int test = 0;
  int count = 0;

  if (argc > 1) {
    test = stoi(argv[1]);
  }
  switch (test) {
  case 0:
    if (testQueueForCS2420()) count++;
    if (testQueueClone()) count++;
    if (testQueueLarge()) count++;
    cout << "Passed " << count << " out of 3 tests";
    return count != 3;
  case 1:
    return !testQueueForCS2420();
  case 2:
    return !testQueueClone();
  case 3:
    return !testQueueLarge();
  }
}